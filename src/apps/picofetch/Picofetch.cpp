#include "Picofetch.h"
#include "core/Display.h"
#include "fonts/fonts.h"
#include "gfx/Colors.h"
#include "gfx/Theme.h"
#include "core/Wifi.h"
 
#include "core/Input.h"
#include "core/Navigation.h"
 
#include "pico/stdlib.h"
#include "pico/unique_id.h"
#include "pico/version.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include <cstdio>
#include <malloc.h>
 
extern char __StackLimit, __bss_end__;
 
void Picofetch::init() {
    gatherInfo();
    setDirty();
}
 
void Picofetch::gatherInfo() {
    // Board / chip name
    boardName = PICO_BOARD;
#if PICO_RP2350
    chipName = "RP2350";
#elif PICO_RP2040
    chipName = "RP2040";
#else
    chipName = "unknown";
#endif
 
    // SDK version
    sdkVersion = PICO_SDK_VERSION_STRING;
 
    // Unique chip ID
    pico_unique_board_id_t id;
    pico_get_unique_board_id(&id);
    char idBuf[PICO_UNIQUE_BOARD_ID_SIZE_BYTES * 2 + 1];
    for (int i = 0; i < PICO_UNIQUE_BOARD_ID_SIZE_BYTES; i++) {
        sprintf(&idBuf[i * 2], "%02x", id.id[i]);
    }
    uniqueId = std::string(idBuf);
 
    // Clock speed
    clockMhz = clock_get_hz(clk_sys) / 1000000;
 
    // Temperature sensor
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
    uint16_t raw = adc_read();
    const float conversionFactor = 3.3f / (1 << 12);
    float voltage = raw * conversionFactor;
    tempC = 27.0f - (voltage - 0.706f) / 0.001721f;
 
    // Rough free heap
    struct mallinfo m = mallinfo();
    freeHeapBytes = (uint32_t)(&__StackLimit - &__bss_end__) - m.uordblks;
 
    // WiFi RSSI (only meaningful if connected — read fresh in render instead
    // if it changes often; cached here as a fallback/default)
    wifiRssi = 0;
}
 
void Picofetch::render() {
    Display::clear(Colors::black);
 
    // HEADING
    Display::drawCenteredString(11, "PICOFETCH", Colors::red, Display::alpha, &Font6x8, 4, -3);
    Display::drawCenteredString(8, "PICOFETCH",  Colors::white, Display::alpha, &Font6x8, 4, -6);
 
    int y = 55;
    const int rowHeight = 14;     
    const int labelX = 10;
    const int valueX = 110;
 
    char buf[32];
 
    auto row = [&](const char* label, const char* value, uint16_t valueColor) {
        Display::drawString(labelX, y, label, Colors::white, Display::alpha, false, &Font6x8, 1);
        Display::drawString(valueX, y, value, valueColor, Display::alpha, false, &Font6x8, 1);
        y += rowHeight;
    };
 
    row("Board:", boardName.c_str(), Colors::cyan);
    row("Chip:", chipName.c_str(), Colors::cyan);
 
    snprintf(buf, sizeof(buf), "%lu MHz", (unsigned long)clockMhz);
    row("Clock:", buf, Colors::cyan);
 
    snprintf(buf, sizeof(buf), "%.1f C", tempC);
    row("Temp:", buf, Colors::cyan);
 
    snprintf(buf, sizeof(buf), "%lu KB", (unsigned long)(freeHeapBytes / 1024));
    row("Free RAM:", buf, Colors::cyan);
 
    row("SDK:", sdkVersion.c_str(), Colors::cyan);
 
    // Unique ID (truncated — full ID is 16 bytes / 32 hex chars)
    std::string shortId = uniqueId.substr(0, 12) + "...";
    row("ID:", shortId.c_str(), Colors::cyan);
 
    y += 6; // small gap before WiFi block
 
    // WiFi status
    if (Wifi::wifiConnected) {
        row("WiFi:", "connected", Colors::green);
    } else {
        row("WiFi:", "disconnected", Colors::red);
    }
}
 
void Picofetch::update() {
    if (Input::justPressed(KEY_LEFT) || Input::justPressed(KEY_B)) {
        Navigation::pop();
    }
}
