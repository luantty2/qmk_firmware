// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "battery.h"
#include "max1704x.h"
#include <stdio.h>

#define MAX1704X_POLLING_MS 2000
#define MAX1704X_INIT_DELAY_MS 100
// #define MAX1704X_VRESET 0x6C //2700mV
#define MAX1704X_VRESET 0x60 // 2400mV
// #define MAX1704X_VRESET 0x78 //3000mV

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
        // dprintf("battery level init: %d\n", bat_lvl);
    }
}

uint8_t battery_fetch(void) {
    uint8_t soc_val[2];
    if (!max1704x_get_soc(soc_val)) {
        uint16_t soc_combined = soc_val[1] | (soc_val[0] << 8);
        bat_lvl               = soc_combined / 256;
        bat_lvl               = MAX(MIN(bat_lvl, 100U), 1U);
        // dprintf("battery level: %d\n", bat_lvl);
    }
    return bat_lvl;
}

uint8_t battery_get(void) {
    return bat_lvl;
}

void reset_battery(void) {
    max1704x_soft_reset();
}
