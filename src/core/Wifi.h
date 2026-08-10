#pragma once
#include <string>
#include "storage/Storage.h" 
#include "pico/cyw43_arch.h"

class Wifi {
public:
    static bool init() {
        if (cyw43_arch_init()) {
            printf("WiFi init failed\n");
            return false;
        }
        cyw43_arch_enable_sta_mode();
        return true;
    }

    static bool connect() {
        printf(Storage::data.wifiSSID);
        printf(Storage::data.wifiPASS);

        int result = cyw43_arch_wifi_connect_timeout_ms(
            Storage::data.wifiSSID,
            Storage::data.wifiPASS,
            CYW43_AUTH_WPA2_AES_PSK,
            30000);

        printf(("Connect result: " + std::to_string(result)).c_str());
        printf("\n");
        printf(("Link status: " + std::to_string(cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA))).c_str());
        printf("\n");

        wifiConnected = (result == 0);
        return wifiConnected;
    }
    static inline bool wifiConnected = false;
};