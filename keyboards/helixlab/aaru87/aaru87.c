// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#    include "rgb_matrix_effects_custom.h"
#endif

#ifdef RGB_MATRIX_ENABLE
extern bool fade_completed;
#endif

void keyboard_post_init_kb(void) {
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_target_val();
#endif
    wait_ms(100);
    keyboard_post_init_user();
}

void matrix_scan_kb(void) {
#ifdef RGB_MATRIX_ENABLE
    if (!fade_completed) {
        if (rgb_matrix_fade_in()) {
            fade_completed = true;
        }
    }
#endif
    matrix_scan_user();
}

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
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

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        HSV hsv = rgb_matrix_get_hsv();
        RGB rgb;
        if(hsv.h % 191>0){
            hsv.h-=191;
        }
        hsv.h+=64;
        rgb   = hsv_to_rgb(hsv);
        for (uint8_t i = led_min; i < led_max; i++) {
            if ((g_led_config.flags[i] >> 3) & 1) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }
    return false;
}
#endif

void eeconfig_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable();
    rgblight_sethsv(45, 255, 255);
    rgblight_mode(RGBLIGHT_MODE_BREATHING + 1);
#endif
    eeconfig_init_user();
}
