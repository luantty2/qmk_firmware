// Copyright 2024 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "outputselect.h"
#include "wireless_sys.h"
#include "hid_leds.h"

#ifdef RGB_MATRIX_ENABLE
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
    {0, SW7_CS11, SW8_CS11, SW9_CS11},
    {0, SW7_CS8, SW8_CS8, SW9_CS8},
    {0, SW7_CS3, SW8_CS3, SW9_CS3},
    {0, SW7_CS9, SW8_CS9, SW9_CS9},
    {0, SW7_CS10, SW8_CS10, SW9_CS10},

    {0, SW10_CS8, SW11_CS8, SW12_CS8},
    {0, SW10_CS3, SW11_CS3, SW12_CS3},
    {0, SW10_CS9, SW11_CS9, SW12_CS9},
    {0, SW10_CS10, SW11_CS10, SW12_CS10},

    {0, SW4_CS11, SW5_CS11, SW6_CS11},
    {0, SW4_CS8, SW5_CS8, SW6_CS8},
    {0, SW4_CS3, SW5_CS3, SW6_CS3},
    {0, SW4_CS9, SW5_CS9, SW6_CS9},
    {0, SW4_CS10, SW5_CS10, SW6_CS10},

    {0, SW1_CS8, SW2_CS8, SW3_CS8},
    {0, SW1_CS9, SW2_CS9, SW3_CS9},
    {0, SW1_CS10, SW2_CS10, SW3_CS10},

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
