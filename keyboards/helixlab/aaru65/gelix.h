// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include QMK_KEYBOARD_H
#include "via.h"

#define EECONFIG_GELIX ((uint32_t *)VIA_EEPROM_CUSTOM_CONFIG_ADDR + 324)

typedef enum {
    COUNTER_STRAFE = 0,
    MUTEX,
    HYBRID,
} gelix_modes_t;

enum delay {
    DELAY_0 = 0,
    DELAY_50US,
    DELAY_100US,
    DELAY_500US,
    DELAY_1000US,
    DELAY_2000US,
    DELAY_5000US,
};

enum duration {
    DURATION_100US = 0,
    DURATION_500US,
    DURATION_1000US,
    DURATION_2000US,
    DURATION_5000US,
    DURATION_10000US,
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t mode : 8;
        uint8_t delay : 8;
        uint8_t duration : 8;
    };
} gelix_config_t;
gelix_config_t gelix_config;

void          gelix_init(void);
void          eeconfig_init_gelix(void);
void          eeconfig_update_gelix(void);
void          eeconfig_update_gelix_default(void);
void          gelix_enable_toggle(void);
bool          get_gelix_enable_state(void);
gelix_modes_t get_gelix_mode(void);
void          tap_code16_gelix(uint16_t code);
