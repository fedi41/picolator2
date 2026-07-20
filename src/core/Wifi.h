#pragma once
#include <string>
#include "storage/Storage.h" 
#include "pico/cyw43_arch.h"
#include "core/Logger.h"

class Wifi {
public:
    static bool init() {
        if (cyw43_arch_init()) {
            Logger::d("WiFi init failed\n");
            return false;
        }
        cyw43_arch_enable_sta_mode();
        return true;
    }

    static bool connect() {
        Logger::d(Storage::data.wifiSSID);
        Logger::d(Storage::data.wifiPASS);

        int result = cyw43_arch_wifi_connect_timeout_ms(
            Storage::data.wifiSSID,
            Storage::data.wifiPASS,
            CYW43_AUTH_WPA2_AES_PSK,
            30000
        );

        Logger::d(("Connect result: " + std::to_string(result)).c_str());
        Logger::d(("Link status: " + std::to_string(cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA))).c_str());

        wifiConnected = (result == 0);
        return wifiConnected;
    }
    static inline bool wifiConnected = false;
};