// Copyright 2023 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define LED_PIN GP25

void keyboard_post_init_kb(void) {
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    // setPinOutput(LED_PIN);
    // writePinHigh(LED_PIN);

    keyboard_post_init_user();
}

led_config_t g_led_config = {
    {
        {0, 1, 2, NO_LED, 3, 4, NO_LED, 5, 6, 7, NO_LED, 8, 9, NO_LED, 10, 11, 12, NO_LED, },
        {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}
    },
    {
        {13 ,0 }, {26 ,0 }, {39 ,0 },               {65 ,0 }, {78 ,0 },              {104 ,0 }, {117 ,0 }, {130 ,0 },                {156 ,0 }, {169 ,0 },               {195 ,0 }, {208 ,0 }, {221 ,0 },
        {13 ,64 }, {26 ,64 }, {39 ,64 }, {52 ,64 }, {65 ,64 }, {78 ,64 }, {91 ,64 }, {104 ,64 }, {117 ,64 }, {130 ,64 }, {143 ,64 }, {156 ,64 }, {169 ,64 }, {182 ,64 }, {195 ,64 }, {208 ,64 }, {221 ,64 }, {234 ,64 }
    },
    {
      4, 4, 4,    4, 4,    4, 4, 4,    4, 4,    4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};
