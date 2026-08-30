#pragma once
// This file handles the connection to the Mistral API :3

#include <string>
#include <functional>
#include <cstdio>
#include <cstring>

#include "pico/cyw43_arch.h"

#include "lwip/dns.h"
#include "lwip/altcp.h"
#include "lwip/altcp_tls.h"
#include "lwip/pbuf.h"
#include "lwip/err.h"

#include "cJSON.h"

#define MISTRAL_API_KEY "u really thought i would leak my api key?"

#define API_HOST "api.mistral.ai"
#define API_PORT 443
#define API_PATH "/v1/chat/completions"

// ---------------------------------------------------------------------
// Result / error types
// ---------------------------------------------------------------------

enum class MistralError {
    NONE,

    INVALID_API_KEY,
    RATE_LIMITED,
    BAD_REQUEST,
    SERVER_ERROR,

    CONNECTION_ERROR,
    DNS_ERROR,
    TLS_ERROR,
    HTTP_ERROR,
    JSON_ERROR,

    UNKNOWN_ERROR
};

struct MistralResult {
    MistralError error = MistralError::UNKNOWN_ERROR;

    // Response text if the request was successful
    std::string content;

    // Error message returned by the API
    std::string detail;

    // HTTP status code (e.g. 200, 401, 429, 500)
    int http_status = 0;

    bool success() const {
        return error == MistralError::NONE;
    }
};

// ---------------------------------------------------------------------
// Internal state
// ---------------------------------------------------------------------

namespace mistral_internal {

struct RequestState {
    std::function<void(MistralResult)> callback;

    // Raw HTTP response
    std::string response_buf;

    struct altcp_pcb *pcb = nullptr;

    bool done = false;
};

static RequestState *g_state = nullptr;

// JSON body waiting for DNS/TLS connection
static std::string g_pending_body;

// ---------------------------------------------------------------------
// JSON helpers
// ---------------------------------------------------------------------

inline std::string create_request_body(const std::string &prompt) {
    cJSON *root = cJSON_CreateObject();

    if (!root)
        return {};

    cJSON_AddStringToObject(
        root,
        "model",
        "mistral-small-latest"
    );

    cJSON *messages = cJSON_CreateArray();

    if (!messages) {
        cJSON_Delete(root);
        return {};
    }

    cJSON *message = cJSON_CreateObject();

    if (!message) {
        cJSON_Delete(messages);
        cJSON_Delete(root);
        return {};
    }

    cJSON_AddStringToObject(
        message,
        "role",
        "user"
    );

    cJSON_AddStringToObject(
        message,
        "content",
        prompt.c_str()
    );

    cJSON_AddItemToArray(messages, message);
    cJSON_AddItemToObject(root, "messages", messages);

    char *json_string = cJSON_PrintUnformatted(root);

    if (!json_string) {
        cJSON_Delete(root);
        return {};
    }

    std::string result(json_string);

    // cJSON allocates this using its allocator
    cJSON_free(json_string);

    cJSON_Delete(root);

    return result;
}

// ---------------------------------------------------------------------
// HTTP status parser
// ---------------------------------------------------------------------

inline int parse_http_status(const std::string &raw) {
    size_t first_space = raw.find(' ');

    if (first_space == std::string::npos)
        return 0;

    size_t second_space = raw.find(' ', first_space + 1);

    if (second_space == std::string::npos)
        return 0;

    try {
        return std::stoi(
            raw.substr(
                first_space + 1,
                second_space - first_space - 1
            )
        );
    }
    catch (...) {
        return 0;
    }
}

// ---------------------------------------------------------------------
// HTTP body extraction
// ---------------------------------------------------------------------

inline std::string extract_http_body(const std::string &raw) {
    size_t body_start = raw.find("\r\n\r\n");

    if (body_start == std::string::npos)
        return {};

    return raw.substr(body_start + 4);
}

// ---------------------------------------------------------------------
// Parse Mistral response
// ---------------------------------------------------------------------

inline MistralResult parse_response(const std::string &raw) {
    MistralResult result;

    // -------------------------------------------------------------
    // HTTP status
    // -------------------------------------------------------------

    result.http_status = parse_http_status(raw);

    if (result.http_status == 0) {
        result.error = MistralError::HTTP_ERROR;
        result.detail = "Could not parse HTTP status";
        return result;
    }

    // -------------------------------------------------------------
    // HTTP body
    // -------------------------------------------------------------

    std::string body = extract_http_body(raw);

    if (body.empty()) {
        result.error = MistralError::HTTP_ERROR;
        result.detail = "HTTP response has no body";
        return result;
    }

    // -------------------------------------------------------------
    // Parse JSON
    // -------------------------------------------------------------

    cJSON *json = cJSON_Parse(body.c_str());

    if (!json) {
        result.error = MistralError::JSON_ERROR;
        result.detail = "Invalid JSON response";
        return result;
    }

    // -------------------------------------------------------------
    // HTTP errors
    // -------------------------------------------------------------

    if (result.http_status >= 400) {

        cJSON *detail =
            cJSON_GetObjectItemCaseSensitive(
                json,
                "detail"
            );

        if (detail && cJSON_IsString(detail)) {
            result.detail = detail->valuestring;
        }

        // ---------------------------------------------------------
        // Specific errors
        // ---------------------------------------------------------

        if (result.http_status == 401) {

            if (result.detail == "Invalid API key") {
                result.error =
                    MistralError::INVALID_API_KEY;
            }
            else {
                result.error =
                    MistralError::INVALID_API_KEY;
            }

        }
        else if (result.http_status == 429) {

            result.error =
                MistralError::RATE_LIMITED;

        }
        else if (result.http_status >= 400 &&
                 result.http_status < 500) {

            result.error =
                MistralError::BAD_REQUEST;

        }
        else if (result.http_status >= 500) {

            result.error =
                MistralError::SERVER_ERROR;

        }
        else {

            result.error =
                MistralError::UNKNOWN_ERROR;
        }

        cJSON_Delete(json);
        return result;
    }

    // -------------------------------------------------------------
    // Successful response
    //
    // Expected:
    //
    // {
    //   "choices": [
    //     {
    //       "message": {
    //         "content": "..."
    //       }
    //     }
    //   ]
    // }
    // -------------------------------------------------------------

    cJSON *choices =
        cJSON_GetObjectItemCaseSensitive(
            json,
            "choices"
        );

    if (!choices ||
        !cJSON_IsArray(choices) ||
        cJSON_GetArraySize(choices) == 0) {

        result.error = MistralError::JSON_ERROR;
        result.detail = "Missing choices";

        cJSON_Delete(json);
        return result;
    }

    cJSON *choice =
        cJSON_GetArrayItem(
            choices,
            0
        );

    if (!choice || !cJSON_IsObject(choice)) {

        result.error = MistralError::JSON_ERROR;
        result.detail = "Invalid choice";

        cJSON_Delete(json);
        return result;
    }

    cJSON *message =
        cJSON_GetObjectItemCaseSensitive(
            choice,
            "message"
        );

    if (!message || !cJSON_IsObject(message)) {

        result.error = MistralError::JSON_ERROR;
        result.detail = "Missing message";

        cJSON_Delete(json);
        return result;
    }

    cJSON *content =
        cJSON_GetObjectItemCaseSensitive(
            message,
            "content"
        );

    if (!content || !cJSON_IsString(content)) {

        result.error = MistralError::JSON_ERROR;
        result.detail = "Missing message content";

        cJSON_Delete(json);
        return result;
    }

    // -------------------------------------------------------------
    // Success
    // -------------------------------------------------------------

    result.error = MistralError::NONE;
    result.content = content->valuestring;

    cJSON_Delete(json);

    return result;
}

// ---------------------------------------------------------------------
// Finish request
// ---------------------------------------------------------------------

inline void finish(
    RequestState *st,
    const MistralResult &result
) {
    if (!st || st->done)
        return;

    st->done = true;

    auto callback = st->callback;

    if (st->pcb) {
        altcp_close(st->pcb);
        st->pcb = nullptr;
    }

    callback(result);

    if (g_state == st)
        g_state = nullptr;

    delete st;
}

// ---------------------------------------------------------------------
// Receive callback
// ---------------------------------------------------------------------

inline err_t on_recv(
    void *arg,
    struct altcp_pcb *pcb,
    struct pbuf *p,
    err_t err
) {
    auto *st =
        static_cast<RequestState *>(arg);

    if (err != ERR_OK) {
        MistralResult result;

        result.error =
            MistralError::CONNECTION_ERROR;

        char msg[64];

        snprintf(
            msg,
            sizeof(msg),
            "Receive error: %d",
            err
        );

        result.detail = msg;

        finish(st, result);

        return err;
    }

    // -------------------------------------------------------------
    // Connection closed = response complete
    // -------------------------------------------------------------

    if (p == nullptr) {
        MistralResult result =
            parse_response(
                st->response_buf
            );

        finish(st, result);

        return ERR_OK;
    }

    // -------------------------------------------------------------
    // Append received data
    // -------------------------------------------------------------

    for (
        struct pbuf *q = p;
        q != nullptr;
        q = q->next
    ) {
        st->response_buf.append(
            static_cast<char *>(q->payload),
            q->len
        );
    }

    altcp_recved(
        pcb,
        p->tot_len
    );

    pbuf_free(p);

    return ERR_OK;
}

// ---------------------------------------------------------------------
// Connection error callback
// ---------------------------------------------------------------------

inline void on_err(
    void *arg,
    err_t err
) {
    auto *st =
        static_cast<RequestState *>(arg);

    st->pcb = nullptr;

    MistralResult result;

    result.error =
        MistralError::CONNECTION_ERROR;

    char msg[64];

    snprintf(
        msg,
        sizeof(msg),
        "Connection error: %d",
        err
    );

    result.detail = msg;

    finish(st, result);
}

// ---------------------------------------------------------------------
// TLS connection established
// ---------------------------------------------------------------------

inline err_t on_connect(
    void *arg,
    struct altcp_pcb *pcb,
    err_t err
) {
    auto *st =
        static_cast<RequestState *>(arg);

    if (err != ERR_OK) {

        MistralResult result;

        result.error =
            MistralError::CONNECTION_ERROR;

        char msg[64];

        snprintf(
            msg,
            sizeof(msg),
            "Connect failed: %d",
            err
        );

        result.detail = msg;

        finish(st, result);

        return err;
    }

    // -------------------------------------------------------------
    // HTTP headers
    // -------------------------------------------------------------

    char header[512];

    int n = snprintf(
        header,
        sizeof(header),

        "POST %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Authorization: Bearer %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n",

        API_PATH,
        API_HOST,
        MISTRAL_API_KEY,
        static_cast<int>(
            g_pending_body.size()
        )
    );

    err_t write_err =
        altcp_write(
            pcb,
            header,
            n,
            TCP_WRITE_FLAG_COPY |
            TCP_WRITE_FLAG_MORE
        );

    if (write_err != ERR_OK) {

        MistralResult result;

        result.error =
            MistralError::CONNECTION_ERROR;

        result.detail =
            "Failed to write HTTP headers";

        finish(st, result);

        return write_err;
    }

    write_err =
        altcp_write(
            pcb,
            g_pending_body.data(),
            g_pending_body.size(),
            TCP_WRITE_FLAG_COPY
        );

    if (write_err != ERR_OK) {

        MistralResult result;

        result.error =
            MistralError::CONNECTION_ERROR;

        result.detail =
            "Failed to write HTTP body";

        finish(st, result);

        return write_err;
    }

    altcp_output(pcb);

    return ERR_OK;
}

// ---------------------------------------------------------------------
// DNS callback
// ---------------------------------------------------------------------

inline void on_dns_found(
    const char *name,
    const ip_addr_t *ipaddr,
    void *arg
) {
    auto *st =
        static_cast<RequestState *>(arg);

    if (!ipaddr) {

        MistralResult result;

        result.error =
            MistralError::DNS_ERROR;

        result.detail =
            "DNS lookup failed";

        finish(st, result);

        return;
    }

    // -------------------------------------------------------------
    // Create TLS configuration
    // -------------------------------------------------------------

    struct altcp_tls_config *tls_config =
        altcp_tls_create_config_client(
            nullptr,
            0
        );

    if (!tls_config) {

        MistralResult result;

        result.error =
            MistralError::TLS_ERROR;

        result.detail =
            "Failed to create TLS config";

        finish(st, result);

        return;
    }

    // -------------------------------------------------------------
    // Create TLS connection
    // -------------------------------------------------------------

    st->pcb =
        altcp_tls_new(
            tls_config,
            IPADDR_TYPE_V4
        );

    if (!st->pcb) {

        MistralResult result;

        result.error =
            MistralError::TLS_ERROR;

        result.detail =
            "Failed to create TLS connection";

        finish(st, result);

        return;
    }

    // -------------------------------------------------------------
    // TLS hostname
    // -------------------------------------------------------------

    mbedtls_ssl_set_hostname(
        static_cast<mbedtls_ssl_context *>(
            altcp_tls_context(st->pcb)
        ),
        API_HOST
    );

    // -------------------------------------------------------------
    // Callbacks
    // -------------------------------------------------------------

    altcp_arg(
        st->pcb,
        st
    );

    altcp_recv(
        st->pcb,
        on_recv
    );

    altcp_err(
        st->pcb,
        on_err
    );

    // -------------------------------------------------------------
    // Connect
    // -------------------------------------------------------------

    err_t err =
        altcp_connect(
            st->pcb,
            ipaddr,
            API_PORT,
            on_connect
        );

    if (err != ERR_OK &&
        err != ERR_INPROGRESS) {

        MistralResult result;

        result.error =
            MistralError::CONNECTION_ERROR;

        char msg[64];

        snprintf(
            msg,
            sizeof(msg),
            "TLS connect error: %d",
            err
        );

        result.detail = msg;

        finish(st, result);
    }
}

} // namespace mistral_internal

// ---------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------

static void send_promt(
    std::string prompt,
    std::function<void(MistralResult)> callback
) {
    using namespace mistral_internal;

    // -------------------------------------------------------------
    // Only one request at a time
    // -------------------------------------------------------------

    if (g_state != nullptr) {

        MistralResult result;

        result.error =
            MistralError::CONNECTION_ERROR;

        result.detail =
            "A request is already in flight";

        callback(result);

        return;
    }

    // -------------------------------------------------------------
    // Create request JSON
    // -------------------------------------------------------------

    g_pending_body =
        create_request_body(prompt);

    if (g_pending_body.empty()) {

        MistralResult result;

        result.error =
            MistralError::JSON_ERROR;

        result.detail =
            "Failed to create request JSON";

        callback(result);

        return;
    }

    // -------------------------------------------------------------
    // Create request state
    // -------------------------------------------------------------

    g_state =
        new RequestState();

    g_state->callback =
        callback;

    // -------------------------------------------------------------
    // DNS lookup
    // -------------------------------------------------------------

    cyw43_arch_lwip_begin();

    ip_addr_t dummy_ip;

    err_t derr =
        dns_gethostbyname(
            API_HOST,
            &dummy_ip,
            on_dns_found,
            g_state
        );

    cyw43_arch_lwip_end();

    // -------------------------------------------------------------
    // DNS already cached
    // -------------------------------------------------------------

    if (derr == ERR_OK) {

        on_dns_found(
            API_HOST,
            &dummy_ip,
            g_state
        );

    }
    // -------------------------------------------------------------
    // DNS lookup running asynchronously
    // -------------------------------------------------------------

    else if (derr == ERR_INPROGRESS) {

        // on_dns_found() will be called later

    }
    // -------------------------------------------------------------
    // DNS failed immediately
    // -------------------------------------------------------------

    else {

        MistralResult result;

        result.error =
            MistralError::DNS_ERROR;

        char msg[64];

        snprintf(
            msg,
            sizeof(msg),
            "DNS error: %d",
            derr
        );

        result.detail = msg;

        finish(
            g_state,
            result
        );
    }
}
