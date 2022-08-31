/* Copyright 2022 HelixIndustryLimited
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

#include "aaru_hotswap.h"
#include "rgb_indicator.h"

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
    /*row0*/
    {0, K_1, L_1, J_1},
    {0, K_2, L_2, J_2},
    {0, K_3, L_3, J_3},
    {0, K_4, L_4, J_4},
    {0, K_5, L_5, J_5},
    {0, K_6, L_6, J_6},
    {0, K_7, L_7, J_7},
    {0, K_8, L_8, J_8},
    {0, K_9, L_9, J_9},
    {0, K_10, L_10, J_10},
    {0, K_11, L_11, J_11},
    {0, K_12, L_12, J_12},
    {0, K_13, L_13, J_13},
    {0, K_14, L_14, J_14},
    {0, K_15, L_15, J_15},
    {0, K_16, L_16, J_16},

    /*row1*/
    {0, H_1, I_1, G_1},
    {0, H_2, I_2, G_2},
    {0, H_3, I_3, G_3},
    {0, H_4, I_4, G_4},
    {0, H_5, I_5, G_5},
    {0, H_6, I_6, G_6},
    {0, H_7, I_7, G_7},
    {0, H_8, I_8, G_8},
    {0, H_9, I_9, G_9},
    {0, H_10, I_10, G_10},
    {0, H_11, I_11, G_11},
    {0, H_12, I_12, G_12},
    {0, H_13, I_13, G_13},
    {0, H_14, I_14, G_14},
    {0, H_15, I_15, G_15},
    {0, H_16, I_16, G_16},
    {1, B_13, C_13, A_13},

    /*row2*/
    {0, E_1, F_1, D_1},
    {0, E_2, F_2, D_2},
    {0, E_3, F_3, D_3},
    {0, E_4, F_4, D_4},
    {0, E_5, F_5, D_5},
    {0, E_6, F_6, D_6},
    {0, E_7, F_7, D_7},
    {0, E_8, F_8, D_8},
    {0, E_9, F_9, D_9},
    {0, E_10, F_10, D_10},
    {0, E_11, F_11, D_11},
    {0, E_12, F_12, D_12},
    {0, E_13, F_13, D_13},
    {0, E_14, F_14, D_14},
    {0, E_15, F_15, D_15},
    {0, E_16, F_16, D_16},
    {1, B_12, C_12, A_12},

    /*row3*/
    {0, B_1, C_1, A_1},
    {0, B_2, C_2, A_2},
    {0, B_3, C_3, A_3},
    {0, B_4, C_4, A_4},
    {0, B_5, C_5, A_5},
    {0, B_6, C_6, A_6},
    {0, B_7, C_7, A_7},
    {0, B_8, C_8, A_8},
    {0, B_9, C_9, A_9},
    {0, B_10, C_10, A_10},
    {0, B_11, C_11, A_11},
    {0, B_12, C_12, A_12},
    {0, B_13, C_13, A_13},

    /*row4*/
    {1, E_1, F_1, D_1},
    {1, E_2, F_2, D_2},
    {1, E_3, F_3, D_3},
    {1, E_4, F_4, D_4},
    {1, E_5, F_5, D_5},
    {1, E_6, F_6, D_6},
    {1, E_7, F_7, D_7},
    {1, E_8, F_8, D_8},
    {1, E_14, F_14, D_14},
    {1, E_15, F_15, D_15},
    {1, E_16, F_16, D_16},
    {1, E_12, F_12, D_12},
    {1, E_13, F_13, D_13},

    /*row5*/
    {1, B_1, C_1, A_1},
    {1, B_2, C_2, A_2},
    {1, B_3, C_3, A_3},
    {1, B_4, C_4, A_4},
    {1, B_5, C_5, A_5},
    {1, B_6, C_6, A_6},
    {1, B_7, C_7, A_7},
    {1, B_8, C_8, A_8},
    {1, B_14, C_14, A_14},
    {1, B_15, C_15, A_15},
    {1, B_16, C_16, A_16},
};

led_config_t g_led_config = {{
                                 /*C0      C1      C2          C3      C4      C5      C6      C7  C8      C9       C10      C11        C12    C13  */
                                 {0, NO_LED, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},                              /* R0_16 */
                                 {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32},                        /* R1_17 */
                                 {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49},                        /* R2_17 */
                                 {50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, NO_LED, NO_LED, NO_LED, NO_LED},        /* R3_13 */
                                 {63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, NO_LED, NO_LED, NO_LED, 75, NO_LED},        /* R4_13 */
                                 {76, 77, 78, NO_LED, NO_LED, 79, NO_LED, NO_LED, NO_LED, 80, 81, 82, 83, NO_LED, 84, 85, 86} /* R5_11 */
                             },
                             {
                                 {0, 0}, {28, 0}, {42, 0}, {56, 0}, {70, 0}, {84, 0}, {98, 0}, {112, 0}, {126, 0}, {140, 0}, {154, 0}, {168, 0}, {182, 0}, {196, 0}, {210, 0}, {224, 0}, {0, 13}, {13, 13}, {28, 13}, {42, 13}, {56, 13}, {70, 13}, {84, 13}, {98, 13}, {112, 13}, {126, 13}, {140, 13}, {154, 13}, {168, 13}, {182, 13}, {196, 13}, {210, 13}, {224, 13}, {0, 26}, {13, 26}, {28, 26}, {42, 26}, {56, 26}, {70, 26}, {84, 26}, {98, 26}, {112, 26}, {126, 26}, {140, 26}, {154, 26}, {168, 26}, {182, 26}, {196, 26}, {210, 26}, {224, 26}, {0, 39}, {13, 39}, {28, 39}, {42, 39}, {56, 39}, {70, 39}, {84, 39}, {98, 39}, {112, 39}, {126, 39}, {140, 39}, {154, 39}, {168, 39}, {0, 52}, {13, 52}, {28, 52}, {42, 52}, {56, 52}, {70, 52}, {84, 52}, {98, 52}, {112, 52}, {126, 52}, {140, 52}, {154, 52}, {210, 52}, {0, 64}, {13, 64}, {28, 64}, {70, 64}, {126, 64}, {140, 64}, {154, 64}, {168, 64}, {196, 64}, {210, 64}, {224, 64},

                             },
                             {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 1, 1, 1, 4, 1, 1, 1, 1, 4, 4, 4}};

void rgb_matrix_indicators_kb(void) {
    // rgb_matrix_set_color(50, 0xff, 0xff, 0x00);
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(50, rgb_indicator_config.r, rgb_indicator_config.g, rgb_indicator_config.b);
    }
}

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}

void eeconfig_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable();  // Enable RGB underglow by default
    rgblight_sethsv(125, 220, 255);
#    ifdef RGBLIGHT_ANIMATIONS
    // rgblight_mode(RGBLIGHT_MODE_TWINKLE + 5); // Set to RGB_TWINKLE animation by default
    rgblight_mode(RGBLIGHT_MODE_BREATHING + 1);  // Set to RGB_RAINBOW_SWIRL animation by default
#    endif
#endif
#ifdef RGB_MATRIX_ENABLE
#endif
    eeconfig_init_user();
}

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

/*
void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware

    return process_record_user(keycode, record);
}

bool led_update_kb(led_t led_state) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    return led_update_user(led_state);
}
*/
