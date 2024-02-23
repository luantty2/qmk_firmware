// Copyright 2024 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "outputselect.h"
#include "wireless_sys.h"
#include "hid_leds.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[IS31FL3733_LED_COUNT] = {
    {0, C_7, B_7, A_7},
    {0, C_1, B_1, A_1},
    {0, C_2, B_2, A_2},
    {0, C_3, B_3, A_3},
    {0, C_4, B_4, A_4},
    {0, C_5, B_5, A_5},
    {0, C_6, B_6, A_6},

    {0, C_8, B_8, A_8},
    {0, C_9, B_9, A_9},
    {0, C_10, B_10, A_10},
    {0, C_11, B_11, A_11},
    {0, C_13, B_13, A_13},
    {0, C_14, B_14, A_14},
    {0, C_16, B_16, A_16},


    {0, F_7, D_7, E_7},
    {0, F_1, D_1, E_1},
    {0, F_2, D_2, E_2},
    {0, F_3, D_3, E_3},
    {0, F_4, D_4, E_4},
    {0, F_5, D_5, E_5},
    {0, F_6, D_6, E_6},

    {0, F_8, D_8, E_8},
    {0, F_9, D_9, E_9},
    {0, F_10, D_10, E_10},
    {0, F_11, D_11, E_11},
    {0, F_13, D_13, E_13},
    {0, F_14, D_14, E_14},
    {0, F_15, D_15, E_15},
    {0, F_16, D_16, E_16},


    {0, I_7, H_7, G_7},
    {0, I_1, H_1, G_1},
    {0, I_2, H_2, G_2},
    {0, I_3, H_3, G_3},
    {0, I_4, H_4, G_4},
    {0, I_5, H_5, G_5},
    {0, I_6, H_6, G_6},

    {0, I_8, H_8, G_8},
    {0, I_9, H_9, G_9},
    {0, I_10, H_10, G_10},
    {0, I_11, H_11, G_11},
    {0, I_13, H_13, G_13},
    {0, I_14, H_14, G_14},
    {0, I_16, H_16, G_16},


    {0, L_7, J_7, K_7},
    {0, L_1, J_1, K_1},
    {0, L_2, J_2, K_2},
    {0, L_3, J_3, K_3},
    {0, L_4, J_4, K_4},
    {0, L_5, J_5, K_5},
    {0, L_6, J_6, K_6},

    {0, L_8, J_8, K_8},
    {0, L_9, J_9, K_9},
    {0, L_10, J_10, K_10},
    {0, L_11, J_11, K_11},
    {0, L_13, J_13, K_13},
    {0, L_14, J_14, K_14},
    {0, L_15, J_15, K_15},
    {0, L_16, J_16, K_16},


    {1, L_10, J_10, K_10},
    {1, L_9, J_9, K_9},
    {1, L_7, J_7, K_7},
    {1, L_6, J_6, K_6},
    {1, L_8, J_8, K_8},

    {1, L_1, J_1, K_1},
    {1, L_2, J_2, K_2},
    {1, L_3, J_3, K_3},
    {1, L_4, J_4, K_4},
    {1, L_5, J_5, K_5}

};
#endif

void keyboard_post_init_kb(void) {
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    // set_output(OUTPUT_BLUETOOTH);
    //this must be called here, not in "bluetooth_init()"
    output_manager_init();

    keyboard_post_init_user();
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock || get_hid_leds_state()) {
        HSV hsv = rgb_matrix_get_hsv();
        RGB rgb;
        if (hsv.h % 191 > 0) {
            hsv.h -= 191;
        }
        hsv.h += 64;
        rgb = hsv_to_rgb(hsv);
        for (uint8_t i = led_min; i < led_max; i++) {
            if ((g_led_config.flags[i] >> 3) & 1) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }
    return false;
}
#endif
