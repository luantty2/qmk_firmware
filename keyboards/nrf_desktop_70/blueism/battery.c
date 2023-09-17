// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "battery.h"
#include "max1704x.h"
#include "blueism.h"
#include <stdio.h>

#define MAX1704X_POLLING_MS 1000
#define MAX1704X_INIT_DELAY_MS 1500
// #define MAX1704X_VRESET 0x6C //2700mV
#define MAX1704X_VRESET 0x60 // 2400mV
// #define MAX1704X_VRESET 0x78 //3000mV

static uint8_t bat_lvl;

void battery_init(void) {
    max1704x_init();
    max1704x_set_vreset(MAX1704X_VRESET);
    wait_ms(MAX1704X_INIT_DELAY_MS);

    uint8_t soc_val[2];
    if (!max1704x_get_soc(soc_val)) {
        uint16_t soc_combined = soc_val[1] | (soc_val[0] << 8);
        bat_lvl               = soc_combined / 256;
        bat_lvl               = MAX(MIN(bat_lvl, 100U), 1U);
        dprintf("battery level init: %d\n", bat_lvl);
        blueism_battery_update(bat_lvl);
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
            blueism_battery_update(bat_lvl);
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
    return bat_lvl >= 98 ? 100 : bat_lvl;
#else
    return bat_lvl;
#endif
}

void get_battery_lvl_str(char *bat_str, size_t size) {
    snprintf(bat_str, size, "%d", get_battery_lvl());
}
