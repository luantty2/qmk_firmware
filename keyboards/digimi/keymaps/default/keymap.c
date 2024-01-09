// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        MI_OCTD, MI_OCTU, MI_SUST,       MI_Cs, MI_Ds,   MI_Fs, MI_Gs, MI_As,     MI_Cs1, MI_Ds1,     MI_Fs1, MI_Gs1, MI_As1,
        MI_BNDD, MI_BNDU, MI_MOD,  MI_C, MI_D, MI_E, MI_F, MI_G, MI_A, MI_B,  MI_C1, MI_D1, MI_E1, MI_F1, MI_G1, MI_A1, MI_B1, MO(1)
    ),
    [1] = LAYOUT(
        RGB_HUI, RGB_SAI, RGB_VAI,       KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,
        RGB_HUD, RGB_SAD, RGB_VAD,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
