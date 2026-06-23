#include "Storage.h"

#include "hardware/flash.h"
#include "hardware/sync.h"
#include <cstring>

#define FLASH_TARGET_OFFSET (PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)



SaveData Storage::load() {
    data = *(SaveData*)(XIP_BASE + FLASH_TARGET_OFFSET);
    return data;
}


void Storage::save() {
    uint8_t buffer[FLASH_PAGE_SIZE] = {0};
    memcpy(buffer, &data, sizeof(data));

    uint32_t interrupts = save_and_disable_interrupts();

    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_TARGET_OFFSET, buffer, FLASH_PAGE_SIZE);

    restore_interrupts(interrupts);
}