// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "uart.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_0, KC_1, MO(1),
        KC_2, KC_3, KC_4,
        KC_1
    ),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_1:
        if (record->event.pressed) {
            // uart_write(0x01);
            uint8_t data[6]={1,2,3,4,5,6};
            uart_transmit(data,6);
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case KC_3:
        if (record->event.pressed) {
            uart_write(0x02);
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};
