#pragma once

#include "core/App.h"
#include "core/Display.h"

class Picofetch : public App {
    public:
        
        void render() override;
        void update() override;
        void init() override;

    private:

        void gatherInfo();  // reads hardware/SDK info once, called from init()
        
        std::string boardName;
        std::string chipName;
        std::string sdkVersion;
        std::string uniqueId;
        uint32_t clockMhz = 0;
        float tempC = 0.0f;
        uint32_t freeHeapBytes = 0;
        int wifiRssi = 0;

};