// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "blueism.h"

enum keycodes {
    BT_DONGLE_ID_0 = SAFE_RANGE,
    BT_ID_1,
    BT_ID_2,
    BT_ID_3,
    BT_ID_4,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(KC_S, BT_ID_1, BT_ID_2, BT_ID_3, BT_ID_4)};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BT_DONGLE_ID_0:
            if (record->event.pressed) {
                // Use hardware switch only
            } else {
                // Do something else when release
            }
            return false;
        case BT_ID_1:
            if (record->event.pressed) {
                // Use hardware switch, then send id
                blueism_id(0);
            } else {
                // Do something else when release
            }
            return false;
        case BT_ID_2:
            if (record->event.pressed) {
                // Use hardware switch, then send id
                blueism_id(1);
            } else {
                // Do something else when release
            }
            return false;
        case BT_ID_3:
            if (record->event.pressed) {
                // Use hardware switch, then send id
                blueism_id(2);
            } else {
                // Do something else when release
            }
            return false;
        case BT_ID_4:
            if (record->event.pressed) {
                // Use hardware switch, then send id
                blueism_id(3);
            } else {
                // Do something else when release
            }
            return false;
        default:
            return true; // Process all other keyzcodes normally
    }
}
