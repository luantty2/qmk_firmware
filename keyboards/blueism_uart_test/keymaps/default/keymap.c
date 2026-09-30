// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "blueism_keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │ A │
     * └───┘
     */
    [0] = LAYOUT(
        QK_BLUETOOTH_PROFILE1, QK_BLUETOOTH_PROFILE2, QK_BLUETOOTH_PROFILE3, QK_OUTPUT_2P4GHZ, BLUEISM_PING, BLUEISM_RESET, BLUEISM_GET_VERSION, KC_8, KC_9, KC_0, QK_BLUETOOTH_UNPAIR, KC_ENT, KC_CAPS, NK_TOGG
    )
};
