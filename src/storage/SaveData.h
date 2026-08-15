#include <cstdint>

struct SaveData {
    uint32_t magic; // "PICO"
    uint32_t dinoRunnerHighScore;
    char wifiSSID[32];
    char wifiPASS[64];
    char mistralApiKey[32];
};

void reset(SaveData data) {
    data.magic = 0x5049434F;
    data.dinoRunnerHighScore = 0;
    strcpy(data.wifiSSID, "ssid");
    strcpy(data.wifiPASS, "pass");
    strcpy(data.mistralApiKey, "apikey");
}