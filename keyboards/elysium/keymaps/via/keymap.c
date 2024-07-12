// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,   KC_GRV,   KC_1,   KC_2,     KC_3,    KC_4,    KC_5,   KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_NO,   KC_BSPC,  //16
        KC_PGUP,  KC_TAB,   KC_Q,   KC_W,     KC_E,    KC_R,    KC_T,   KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,   //15
        KC_PGDN,  KC_CAPS,  KC_A,   KC_S,     KC_D,    KC_F,    KC_G,   KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,  //14
        KC_END,   KC_LSFT,  KC_Z,   KC_X,     KC_C,    KC_V,    KC_B,   KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_UP,    KC_RSFT, //15
        KC_LCTL,  KC_LGUI,          KC_LALT,  KC_SPC,  KC_SPC,  MO(1),  KC_LEFT,  KC_DOWN,  KC_RIGHT  //9
    ),
    [1] = LAYOUT(
        QK_BOOT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,  _______,
        _______,  GU_TOGG,            AG_TOGG,  _______,  _______,  _______,  _______,  _______,  _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_BOOT:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    eeconfig_init();
                    reset_keyboard();
                }
            } else {
                // Do something else when release
            }
            return false;
        case GU_TOGG:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    keymap_config.no_gui = !keymap_config.no_gui;
                    eeconfig_update_keymap(keymap_config.raw);
                }
            } else {
            }
            return false;
        case AG_TOGG:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    keymap_config.swap_lalt_lgui = !keymap_config.swap_lalt_lgui;
                    keymap_config.swap_ralt_rgui = keymap_config.swap_lalt_lgui;
                    eeconfig_update_keymap(keymap_config.raw);
                }
            } else {
            }
            return false;
        default:
            return true; // Process all other keyzcodes normally
    }
}
