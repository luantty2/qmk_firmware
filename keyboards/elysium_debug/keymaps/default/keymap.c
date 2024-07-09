// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
// #include "blueism.h"
// #include "battery.h"

// enum keycodes{
//     UNPAIR = SAFE_RANGE,
//     // F_UNPAIR,
//     // BAT_LVL,
// };

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,   KC_GRV,   KC_1,   KC_2,     KC_3,    KC_4,    KC_5,   KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_DEL,   KC_TAB,   KC_Q,   KC_W,     KC_E,    KC_R,    KC_T,   KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_PGUP,  KC_CAPS,  KC_A,   KC_S,     KC_D,    KC_F,    KC_G,   KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_PGDN,  KC_LSFT,  KC_Z,   KC_X,     KC_C,    KC_V,    KC_B,   KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_UP,    KC_RSFT,
        KC_LCTL,  KC_LGUI,  KC_NO,  KC_LALT,  KC_SPC,  KC_SPC,  MO(1),  KC_LEFT,  KC_DOWN,  KC_RIGHT
    ),
    [1] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case UNPAIR:
//             if (record->event.pressed) {
//                 // Do something when pressed
//                 if (get_mods() & MOD_MASK_SHIFT) {
//                     blueism_unpair();
//                 }
//             } else {
//                 // Do something else when release
//             }
//             return false;
//         case F_UNPAIR:
//             if (record->event.pressed) {
//                 // Do something when pressed
//                 blueism_unpair();
//             } else {
//                 // Do something else when release
//             }
//             return false;
//         case BAT_LVL:
//             if (record->event.pressed) {
//                 // Do something when pressed
//                 // get_battery_lvl_str(bat_str, ARRAY_SIZE(bat_str));
//                 // send_string(bat_str);
//                 // send_byte(get_battery_lvl());
//             } else {
//                 // Do something else when release
//             }
//             return false;
//         case RGB_TOG:
//             if (record->event.pressed) {
//                 // Do something when pressed
//                 // gext_battery_lvl_str(bat_str, ARRAY_SIZE(bat_str));
//                 // send_string(bat_str);
//                 // send_byte(get_battery_lvl());
//                 rgb_matrix_toggle();
//                 if (rgb_matrix_is_enabled()) {
//                     writePinHigh(RGB_SHUTDOWN_PIN);
//                 } else {
//                     writePinLow(RGB_SHUTDOWN_PIN);
//                 }

//             } else {
//                 // Do something else when release
//             }
//             return false;
//         // case KEYLOCK:
//         //     static host_driver_t *host_driver = 0;

//         //     if (record->event.pressed) {
//         //         if (host_get_driver()) {
//         //             host_driver = host_get_driver();
//         //             clear_keyboard();
//         //             host_set_driver(0);
//         //             host_driver_disabled = true;
//         //         } else {
//         //             host_set_driver(host_driver);
//         //             host_driver_disabled = false;
//         //         }
//         //     }
//         //     return false;
//         default:
//             return true; // Process all other keyzcodes normally
//     }
// }
