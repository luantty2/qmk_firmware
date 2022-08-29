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
// #include "is31fl3199.h"
// #include "color.h"

/**************** rgb_indicator mode *****************
|-----------------|-----------------------------------|
|   mode number   |   mode name                       |
|-----------------|-----------------------------------|
|        1        | RGB_INDICATOR_MODE_PLAIN          |
|        2        | RGB_INDICATOR_MODE_FADE_IN        |
|        3        | RGB_INDICATOR_MODE_FADE_OUT       |
|        4        | RGB_INDICATOR_MODE_FADE_INOUT     |
|        5        | RGB_INDICATOR_MODE_GRADIENT       |
|        6        | RGB_INDICATOR_MODE_RANDOM_HUE     |
|-----------------|-----------------------------------|
*/

// #ifndef RGB_INDICATOR_SELECT_PIN
// #    define RGB_INDICATOR_SELECT_PIN GP27
// #endif
// #ifndef RGB_INDICATOR_TEST_PIN
// #    define RGB_INDICATOR_TEST_PIN GP23
// #endif
// #define RGB_INDICATOR_EFFECT_MAX 6
// #ifndef RGB_INDICATOR_GLOBAL_CURRENT
// #    define RGB_INDICATOR_GLOBAL_CURRENT LED_CURRENT_MAX
// #endif

// typedef union {
//     uint32_t raw;
//     struct PACKED {
//         bool    enable : 1;
//         bool    select : 1;
//         uint8_t mode : 6;
//         HSV     hsv;
//     };
// } rgb_indicator_config_t;
// rgb_indicator_config_t rgb_indicator_config;

void rgb_indicator_init(void);
void rgb_indicator_on(void);
// void eeconfig_init_rgb_indicator(void);
// void eeconfig_update_rgb_indicator_default(void);
// void eeconfig_update_rgb_indicator(void);
// void eeconfig_debug_rgb_indicator(void);
// void rgb_indicator_enable(void);
// void rgb_indicator_disable(void);
// void rgb_indicator_enable_toggle(void);
// void rgb_indicator_factory_test_runner(void);
// void rgb_indicator_factory_test(void);
// void rgb_indicator_process(bool hehaviour, indicator_led_data phase1_data, uint16_t wait, indicator_led_data phase2_data);
// void rgb_indicator_toggle(bool your_led_state);
// void rgb_indicator_select(void);
// void rgb_indicator_select_toggle(void);
// void rgb_indicator_sethsv(uint16_t hue, uint8_t sat, uint8_t val);
// void rgb_indicator_mode(uint8_t mode);
// void rgb_indicator_step(void);
// void rgb_indicator_increase_hue(void);
// void rgb_indicator_decrease_hue(void);
// void rgb_indicator_increase_sat(void);
// void rgb_indicator_decrease_sat(void);
// void rgb_indicator_increase_val(void);
// void rgb_indicator_decrease_val(void);