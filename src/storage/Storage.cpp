#include "Storage.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "hardware/xip_cache.h"  // für Cache-Invalidierung
#include <cstring>

#define FLASH_TARGET_OFFSET (PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)

SaveData Storage::load() {
    SaveData tmp;
    memcpy(&tmp, (void*)(XIP_BASE + FLASH_TARGET_OFFSET), sizeof(SaveData));

    if (tmp.magic != 0x5049434F) {
        tmp.magic = 0x5049434F;
        tmp.dinoRunnerHighScore = 0;
        strcpy(tmp.wifiSSID, "PicoLator");
        strcpy(tmp.wifiPASS, "picolator");
    }

    data = tmp;
    return tmp;
}

void Storage::save() {
    SaveData tmp = data;

    uint8_t buffer[FLASH_SECTOR_SIZE];
    memset(buffer, 0xFF, sizeof(buffer));
    memcpy(buffer, &tmp, sizeof(SaveData));

    uint32_t interrupts = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_TARGET_OFFSET, buffer, FLASH_SECTOR_SIZE);
    restore_interrupts(interrupts);

    xip_cache_invalidate_all();  // wichtig, falls du direkt danach im selben Boot wieder liest
}