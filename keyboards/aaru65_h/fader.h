/* Copyright 2022 luantty2
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include QMK_KEYBOARD_H
#ifdef VIA_ENABLE
#    include "via.h"
#endif
// #include "eeconfig.h"
// #include "eeconfig.h" // put them in here or include them indirectly
// #undef EECONFIG_SIZE
// #define EECONFIG_SIZE 39
// #undef EECONFIG_SIZE
// #include "eeconfig.h" // restores

#define FADER_SAMPLE_RATE 100
#define ADC_DEADBAND 255
#define ADC_ERROR 0xFF

#ifdef VIA_ENABLE
#    define EECONFIG_FADER ((uint32_t*)VIA_EEPROM_CUSTOM_CONFIG_ADDR)
#else
#    define EECONFIG_FADER ((uint32_t*)EECONFIG_SIZE)
#endif
// #define EECONFIG_FADER (uint32_t *)35

// #undef EECONFIG_SIZE
// #define EECONFIG_SIZE 39  //now defined in eeconfig.h
// #ifdef EECONFIG_SIZE //if the macro MEDIAN_MAX_SIZE is defined
// // #pragma push_macro("EECONFIG_SIZE")
// #undef EECONFIG_SIZE
// // #undef EECONFIG_SIZE //un-define it
// #define EECONFIG_SIZE 39//redefine it with the new value
// // #pragma pop_macro("EECONFIG_SIZE")
// #endif

typedef union {
    uint32_t raw;
    struct {
        bool    enable : 1;
        bool    reverse : 1;
        uint8_t channel : 8;
        uint8_t cc : 8;
    };
} fader_config_t;
fader_config_t fader_config;

void    fader_init(void);
void    eeconfig_init_fader(void);
void    eeconfig_update_fader(void);
void    eeconfig_update_fader_default(void);
void    eeconfig_debug_fader(void);
void    fader_enable(void);
void    fader_disable(void);
void    fader_enable_toggle(void);
void    fader_reverse(void);
void    fader_setchannel(uint8_t channel);
void    fader_increase_channel(void);
void    fader_decrease_channel(void);
void    fader_setcc(uint8_t cc);
void    fader_increase_cc(void);
void    fader_decrease_cc(void);
uint8_t fader_get_val(void);
uint8_t fader_read(void);
void    fader_run(MidiDevice* device);