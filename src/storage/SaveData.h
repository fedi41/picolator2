#include <cstdint>

struct SaveData {
    uint32_t magic; // "PICO"
    uint32_t dinoRunnerHighScore;
    char wifiSSID[32];
    char wifiPASS[64];
};