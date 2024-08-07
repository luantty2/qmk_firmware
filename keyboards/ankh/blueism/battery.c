// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "battery.h"
#include "max1704x.h"
#include "blueism.h"
#include <stdio.h>

#define MAX1704X_POLLING_MS 2000
#define MAX1704X_INIT_DELAY_MS 100
// #define MAX1704X_VRESET 0x6C //2700mV
#define MAX1704X_VRESET 0x60 // 2400mV
// #define MAX1704X_VRESET 0x78 //3000mV
// #define BAT_CHEAT

#ifdef BAT_CHEAT
static const uint8_t PROGMEM cheat_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 87, 88, 89, 91, 92, 93, 94, 96, 97, 98, 99, 100, 100, 100, 100};
#endif
static uint8_t bat_lvl;

void battery_init(void) {
    max1704x_init();
    // max1704x_set_vreset(MAX1704X_VRESET);
    wait_ms(MAX1704X_INIT_DELAY_MS);

    uint8_t soc_val[2];
    if (!max1704x_get_soc(soc_val)) {
        uint16_t soc_combined = soc_val[1] | (soc_val[0] << 8);
        bat_lvl               = soc_combined / 256;
        bat_lvl               = MAX(MIN(bat_lvl, 100U), 1U);
        dprintf("battery level init: %d\n", bat_lvl);
        blueism_battery_update(get_battery_lvl());
    }
}

void battery_task(void) {
    static uint32_t bat_poll_timer;

    if (timer_elapsed32(bat_poll_timer) >= MAX1704X_POLLING_MS) {
        bat_poll_timer = timer_read32();
        uint8_t soc_val[2];
        if (!max1704x_get_soc(soc_val)) {
            uint16_t soc_combined = soc_val[1] | (soc_val[0] << 8);
            bat_lvl               = soc_combined / 256;
            bat_lvl               = MAX(MIN(bat_lvl, 100U), 1U);
            dprintf("battery level: %d\n", bat_lvl);
            blueism_battery_update(get_battery_lvl());
        }

#if 0
        uint8_t vres[2];
        if (!max1704x_read_vreset(vres)) {
            dprintf("vres: %2x\n", vres[0]);
        }
#endif
    }
}

uint8_t get_battery_lvl(void) {
#ifdef BAT_CHEAT
    // return bat_lvl >= 97 ? 100 : bat_lvl;
    return cheat_list[bat_lvl - 1];
#else
    return bat_lvl;
#endif
}

uint8_t get_battery_lvl_blurry(void) {
#ifdef BAT_CHEAT
    // return bat_lvl >= 97 ? 100 : bat_lvl;
    return MAX(MIN(cheat_list[bat_lvl - 1] / 10, 9), 0);
#else
    return MAX(MIN(bat_lvl / 10, 9), 0);
#endif
}

void get_battery_lvl_str(char *bat_str, size_t size, bool blurry) {
    if (!blurry) {
        snprintf(bat_str, size, "%d", get_battery_lvl());
    } else {
        snprintf(bat_str, size, "%d", get_battery_lvl_blurry());
    }
}

void reset_battery(void) {
    max1704x_soft_reset();
}
