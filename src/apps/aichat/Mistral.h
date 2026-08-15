#pragma once
// This file handles the connection to the mistral API :3

//  |
//  |
// \/
// THIS FILE WAS WRITTEN BY AI! sorry guys I am too dumb for this )

#include <string>
#include <functional>
#include <cstring>
#include <cstdio>

#include "pico/cyw43_arch.h"
#include "lwip/dns.h"
#include "lwip/altcp.h"
#include "lwip/altcp_tls.h"
#include "lwip/pbuf.h"
#include "lwip/err.h"

#define MISTRAL_API_KEY "u really thought i would leak my api key?"

#define API_HOST "api.mistral.ai"
#define API_PORT 443
#define API_PATH "/v1/chat/completions"

// ---------------------------------------------------------------------
// internal state — one request in flight at a time. good enough for a
// microcontroller, but don't call send_promt() again before the
// callback fires or you'll stomp the in-flight request.
// ---------------------------------------------------------------------
namespace mistral_internal {

struct RequestState {
    std::function<void(std::string)> callback;
    std::string response_buf;     // raw bytes as they arrive
    struct altcp_pcb *pcb = nullptr;
    bool done = false;
};

static RequestState *g_state = nullptr;

// crude JSON string escaper — enough for typical prompt text.
inline std::string json_escape(const std::string &in) {
    std::string out;
    out.reserve(in.size());
    for (char c : in) {
        switch (c) {
            case '"':  out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;
            default:   out += c;
        }
    }
    return out;
}

// pulls the model's reply text out of the raw HTTP response. does a
// simple string search rather than real JSON parsing — swap this for
// cJSON/ArduinoJson if you need something robust.
inline std::string extract_content(const std::string &raw) {
    size_t body_start = raw.find("\r\n\r\n");
    std::string body = (body_start != std::string::npos)
        ? raw.substr(body_start + 4)
        : raw;

    const std::string needle = "\"content\":\"";
    size_t key = body.find(needle);
    if (key == std::string::npos) return "[couldn't find content in response: " + body + "]";

    size_t start = key + needle.size();
    std::string result;
    for (size_t i = start; i < body.size(); i++) {
        char c = body[i];
        if (c == '"' && body[i - 1] != '\\') break;
        if (c == '\\' && i + 1 < body.size()) {
            char next = body[i + 1];
            if (next == 'n') { result += '\n'; i++; continue; }
            if (next == '"' || next == '\\') { result += next; i++; continue; }
        }
        result += c;
    }
    return result;
}

inline void finish(RequestState *st, const std::string &result) {
    if (st->done) return; // don't fire twice
    st->done = true;
    auto cb = st->callback;
    if (st->pcb) {
        altcp_close(st->pcb);
        st->pcb = nullptr;
    }
    cb(result);
    delete st;
    g_state = nullptr;
}

inline err_t on_recv(void *arg, struct altcp_pcb *pcb, struct pbuf *p, err_t err) {
    auto *st = static_cast<RequestState *>(arg);

    if (p == nullptr) {
        // server closed the connection -> response is complete
        finish(st, extract_content(st->response_buf));
        return ERR_OK;
    }

    for (struct pbuf *q = p; q != nullptr; q = q->next) {
        st->response_buf.append(static_cast<char *>(q->payload), q->len);
    }
    altcp_recved(pcb, p->tot_len);
    pbuf_free(p);
    return ERR_OK;
}

inline void on_err(void *arg, err_t err) {
    auto *st = static_cast<RequestState *>(arg);
    st->pcb = nullptr; // lwIP already freed it
    char msg[64];
    snprintf(msg, sizeof(msg), "[connection error: %d]", err);
    finish(st, msg);
}

inline err_t on_connect(void *arg, struct altcp_pcb *pcb, err_t err) {
    auto *st = static_cast<RequestState *>(arg);
    if (err != ERR_OK) {
        char msg[64];
        snprintf(msg, sizeof(msg), "[connect failed: %d]", err);
        finish(st, msg);
        return err;
    }

    // we stashed the prompt's JSON body on the state object before
    // connecting (see send_promt below)
    extern std::string g_pending_body;

    char header[512];
    int n = snprintf(header, sizeof(header),
        "POST %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Authorization: Bearer %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n",
        API_PATH, API_HOST, MISTRAL_API_KEY, (int) g_pending_body.size());

    altcp_write(pcb, header, n, TCP_WRITE_FLAG_COPY | TCP_WRITE_FLAG_MORE);
    altcp_write(pcb, g_pending_body.data(), g_pending_body.size(), TCP_WRITE_FLAG_COPY);
    altcp_output(pcb);
    return ERR_OK;
}

inline void on_dns_found(const char *name, const ip_addr_t *ipaddr, void *arg) {
    auto *st = static_cast<RequestState *>(arg);
    if (ipaddr == nullptr) {
        finish(st, "[dns lookup failed]");
        return;
    }

    struct altcp_tls_config *tls_config = altcp_tls_create_config_client(nullptr, 0);
    st->pcb = altcp_tls_new(tls_config, IPADDR_TYPE_V4);
    if (!st->pcb) {
        finish(st, "[failed to create tls connection]");
        return;
    }

mbedtls_ssl_set_hostname((mbedtls_ssl_context *) altcp_tls_context(st->pcb), API_HOST);
    altcp_arg(st->pcb, st);
    altcp_recv(st->pcb, on_recv);
    altcp_err(st->pcb, on_err);

    altcp_connect(st->pcb, ipaddr, API_PORT, on_connect);
}

// storage for the JSON body between building it in send_promt() and
// using it in on_connect() — lives as long as one request does.
inline std::string g_pending_body;

} // namespace mistral_internal

// ---------------------------------------------------------------------
// public API — this is your function, filled in for real
// ---------------------------------------------------------------------
static void send_promt(std::string prompt, std::function<void(std::string)> callback) {
    using namespace mistral_internal;

    if (g_state != nullptr) {
        callback("[a request is already in flight, try again shortly]");
        return;
    }

    g_state = new RequestState();
    g_state->callback = callback;

    g_pending_body =
        "{\"model\":\"mistral-small-latest\",\"messages\":[{\"role\":\"user\",\"content\":\"" +
        json_escape(prompt) + "\"}]}";

    cyw43_arch_lwip_begin();
    ip_addr_t dummy_ip;
    err_t derr = dns_gethostbyname(API_HOST, &dummy_ip, on_dns_found, g_state);
    cyw43_arch_lwip_end();

    if (derr == ERR_OK) {
        // hostname was already cached — dummy_ip is valid right now
        on_dns_found(API_HOST, &dummy_ip, g_state);
    } else if (derr != ERR_INPROGRESS) {
        char msg[64];
        snprintf(msg, sizeof(msg), "[dns_gethostbyname error: %d]", derr);
        finish(g_state, msg);
    }
    // else: on_dns_found will fire later from your existing poll loop
}