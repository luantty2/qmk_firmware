// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "blueism.h"

enum keycodes{
    BLUETOOTH_UNPAIR = QK_KB_0,
};

#define BT_UNPR BLUETOOTH_UNPAIR

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_BSPC,  KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        KC_P4,    KC_P5,    KC_P6,
        KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        KC_P0,    LT(1, KC_PDOT)
    ),
    [1] = LAYOUT(
        KC_NUM,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,
        _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  _______,  BT_UNPR,
        _______,  _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BLUETOOTH_UNPAIR:
            if (record->event.pressed) {
                // Do something when pressed
                // if (get_mods() & MOD_MASK_SHIFT) {
                //     blueism_unpair();
                // }
                blueism_ble_button_unpair();
            } else {
                // Do something else when release
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                // Do something when pressed
                // gext_battery_lvl_str(bat_str, ARRAY_SIZE(bat_str));
                // send_string(bat_str);
                // send_byte(get_battery_lvl());
                rgb_matrix_toggle();
                if (rgb_matrix_is_enabled()) {
                    writePinHigh(RGB_SHUTDOWN_PIN);
                } else {
                    writePinLow(RGB_SHUTDOWN_PIN);
                }

            } else {
                // Do something else when release
            }
            return false;
        default:
            return true; // Process all other keyzcodes normally
    }
}
