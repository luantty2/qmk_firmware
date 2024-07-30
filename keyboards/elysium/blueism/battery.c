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
#define BAT_CHEAT

#ifdef BAT_CHEAT
static const uint8_t PROGMEM cheat_list[] = {1, 3, 4, 6, 7, 9, 12, 15, 17, 18, 20, 22, 25, 28, 29, 32, 35, 38, 41, 43, 46, 49, 50, 51, 53, 56, 59, 62, 63, 65, 68, 70, 71, 73, 75, 77, 77, 78, 78, 78, 78, 79, 79, 79, 79, 80, 80, 80, 80, 81, 81, 81, 81, 82, 82, 82, 82, 83, 83, 83, 84, 85, 85, 85, 86, 86, 87, 87, 88, 89, 89, 89, 90, 91, 91, 92, 92, 93, 93, 94, 94, 95, 95, 96, 96, 97, 97, 98, 98, 98, 98, 98, 98, 98, 99, 99, 100, 100, 100, 100};
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
