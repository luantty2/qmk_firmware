// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "gelix.h"
#include "eeprom.h"

static bool          gelix_active = false;
static gelix_modes_t current_gelix_mode;

void gelix_init(void) {
    gelix_config.raw = eeprom_read_dword(EECONFIG_GELIX);
}

void eeconfig_init_gelix(void) {
    eeconfig_update_gelix_default();
    current_gelix_mode = gelix_config.mode;
}

void eeconfig_update_gelix(void) {
    eeprom_update_dword(EECONFIG_GELIX, gelix_config.raw);
    current_gelix_mode = gelix_config.mode;
}

void eeconfig_update_gelix_default(void) {
    dprintf("gelix update default [EEPROM]\n");
    gelix_config.mode     = COUNTER_STRAFE;
    gelix_config.delay    = DELAY_0;
    gelix_config.duration = DURATION_100US;
    eeconfig_update_gelix();
}

void gelix_enable(void) {
    gelix_active = true;
}

void gelix_disable(void) {
    gelix_active = false;
}

void gelix_enable_toggle(void) {
    if (!gelix_active)
        gelix_enable();
    else
        gelix_disable();
}

bool get_gelix_enable_state(void) {
    return gelix_active;
}

gelix_modes_t get_gelix_mode(void) {
    current_gelix_mode = gelix_config.mode;
    return current_gelix_mode;
}

void tap_code16_gelix(uint16_t code) {
    switch (gelix_config.delay) {
        case DELAY_0:
            break;
        case DELAY_50US:
            wait_us(50);
            break;
        case DELAY_100US:
            wait_us(100);
            break;
        case DELAY_500US:
            wait_us(500);
            break;
        case DELAY_1000US:
            wait_us(1000);
        case DELAY_2000US:
            wait_us(2000);
            break;
        case DELAY_5000US:
            wait_us(5000);
            break;
        default:
            break;
    }
    register_code16(code);
    switch (gelix_config.duration) {
        case DURATION_100US:
            wait_us(100);
            break;
        case DURATION_500US:
            wait_us(500);
            break;
        case DURATION_1000US:
            wait_us(1000);
            break;
        case DURATION_2000US:
            wait_us(2000);
            break;
        case DURATION_5000US:
            wait_us(5000);
        case DURATION_10000US:
            wait_us(10000);
            break;
        default:
            break;
    }
    unregister_code16(code);
}
