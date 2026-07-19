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
        return true;
    }

    static bool connect() {

        Logger::d( Storage::data.wifiSSID );         
        Logger::d( Storage::data.wifiPASS );

        int result = cyw43_arch_wifi_connect_timeout_ms(
            Storage::data.wifiSSID,
            Storage::data.wifiPASS,
            CYW43_AUTH_WPA2_AES_PSK,
            30000
        );

        if (result) {
            Logger::d("Connection failed\n");
        }
        else {
            Logger::d("Connected!\n");
        }

        wifiConnected = !(bool) result;
        return result;
    }

    static inline bool wifiConnected = false;
};