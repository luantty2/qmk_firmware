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

#include "aaru_solderable.h"

extern backlight_config_t backlight_config;

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.


// void matrix_init_kb(void) {
//     // put your keyboard start-up code here
//     // runs once when the firmware starts up
//     eeconfig_init();

//     matrix_init_user();
// }

// void matrix_scan_kb(void) {
//     // put your looping keyboard code here
//     // runs every cycle (a lot)

//     matrix_scan_user();
// }

// bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
//     // put your per-action keyboard code here
//     // runs for every action, just before processing by the firmware

//     return process_record_user(keycode, record);
// }

// bool led_update_kb(led_t led_state) {
//     // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

//     return led_update_user(led_state);
// }

void keyboard_pre_init_kb(void){
    setPinOutput(F1);
    setPinOutput(C5);
    keyboard_pre_init_user();
}
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    // uint8_t led_usb_state = host_keyboard_leds();
    if(res) {
        writePin(F1, !led_state.caps_lock);
        writePin(C5, !led_state.scroll_lock);
    }
    return res;
}

void eeconfig_init_kb(void) {
#ifdef BACKLIGHT_ENABLE
    backlight_enable();
#endif
#ifdef RGBLIGHT_ENABLE
    rgblight_enable(); // Enable RGB underglow by default
    rgblight_sethsv(105, 200, 255);
#ifdef RGBLIGHT_ANIMATIONS
    rgblight_mode(RGBLIGHT_MODE_BREATHING +1); // Set to RGB_RAINBOW_SWIRL animation by default
#endif
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
