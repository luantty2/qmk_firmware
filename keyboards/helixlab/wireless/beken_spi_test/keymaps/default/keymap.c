// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "bk3632_spi.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_1, QK_OUTPUT_BLUETOOTH,
        KC_2, KC_3, KC_4
    ),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_2:
        if (record->event.pressed) {
                // uint8_t payload[28] = {0x00, 0x16,0x07,0x09,0xa,0xb,0x10,0x55,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
                // bk3632_spi_send_cmd(0x02, payload, 28);
                // uint8_t payload[2] = {0x00, 0x00};
                // bk3632_spi_send_cmd(0x0a, payload, 2);
                bk3632_set_bt_name();
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};
