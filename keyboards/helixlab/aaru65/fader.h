// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include QMK_KEYBOARD_H
#ifdef VIA_ENABLE
#    include "via.h"
#endif

#define FADER_SAMPLE_RATE 10
#define CONTINUOUS_TRIGGER_TIMER 200
#define ADC_DEADBAND 255
#define ADC_ERROR 0xFF

#ifdef VIA_ENABLE
#    define EECONFIG_FADER ((uint32_t*)VIA_EEPROM_CUSTOM_CONFIG_ADDR)
#    define EECONFIG_FADER_EXTRA (EECONFIG_FADER + 256)
#else
#    define EECONFIG_FADER ((uint32_t*)EECONFIG_SIZE)
#    error
#endif

typedef union {
    uint32_t raw;
    struct {
        bool    enable : 1;
        bool    mode : 1;
        bool    reverse : 1;
        uint8_t channel : 8;
        uint8_t cc : 8;
        uint8_t trigger : 2;
        uint8_t layer_0 : 2;
        uint8_t layer_1 : 2;
    };
} fader_config_t;
fader_config_t fader_config;

typedef union {
    uint32_t raw;
    struct {
        uint16_t kc_0 : 16;
        uint16_t kc_1 : 16;
    };
} fader_extra_config_t;
fader_extra_config_t fader_extra_config;

void    fader_init(void);
void    eeconfig_init_fader(void);
void    eeconfig_update_fader(void);
void    eeconfig_update_fader_extra(void);
void    eeconfig_update_fader_default(void);
void    eeconfig_update_fader_extra_default(void);
void    eeconfig_debug_fader(void);
void    fader_enable(void);
void    fader_disable(void);
void    fader_enable_toggle(void);
void    fader_reverse(void);
void    fader_set_channel(uint8_t channel);
void    fader_increase_channel(void);
void    fader_decrease_channel(void);
void    fader_set_cc(uint8_t cc);
void    fader_increase_cc(void);
void    fader_decrease_cc(void);
uint8_t fader_get_val(void);
uint8_t fader_read(void);
void    fader_run(MidiDevice* device);
void    fader_custom_singleshot_handler(void);
void    fader_custom_continuous_handler(void);
void    fader_custom_layer_handler(void);
