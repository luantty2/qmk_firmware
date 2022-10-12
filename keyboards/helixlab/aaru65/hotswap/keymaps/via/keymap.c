// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#ifdef FADER_ENABLE
#    include "fader.h"
#endif
#include "debug_list.h"

enum keycodes { 
    DEVICE_INFO = USER00,
    RGB_MATRIX_INDICATOR_ONLY,
    FADER_REVERSE, 
    FADER_CHI, 
    FADER_CCI, 
    FADER_ENABLE_TOGGLE, 
};

// Defines names for use in layer keycodes and the keymap
enum layer_names { _BASE, _FN };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESC,   KC_1,     KC_2,     KC_3,    KC_4,     KC_5,   KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINUS,     KC_EQUAL,     KC_BSPACE, 
        KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,   KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRACKET,  KC_RBRACKET,  KC_BSLS, 
        KC_CAPS,  KC_A,     KC_S,     KC_D,    KC_F,     KC_G,   KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,      KC_ENT, 
        KC_LSFT,  KC_Z,     KC_X,     KC_C,    KC_V,     KC_B,   KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,      KC_UP,                                                                                   
        KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC,  KC_RALT,  MO(1),  KC_LEFT,  KC_DOWN,  KC_RGHT                                                                                                                          
        ),
    [_FN] = LAYOUT(
        _______,   KC_F1,                KC_F2,          KC_F3,      KC_F4,      KC_F5,     KC_F6,    KC_F7,                      KC_F8,        KC_F9,    KC_F10,   _______,  _______,  _______, 
        _______,   RGB_TOG,              RGB_MOD,        RGB_SPI,    RGB_HUI,    RGB_SAI,   RGB_VAI,  RGB_MATRIX_INDICATOR_ONLY,  DEVICE_INFO,  _______,  _______,  _______,  _______,  _______, 
        _______,   FADER_ENABLE_TOGGLE,  FADER_REVERSE,  _______,    _______,    _______,   _______,  _______,                    _______,      _______,  _______,  _______,  _______, 
        _______,   _______,              _______,        _______,    _______,    _______,   NK_TOGG,  _______,                    _______,      _______,  _______,  _______,  KC_PGUP, 
        _______,   GUI_TOG,              AG_TOGG,        _______,    _______,    _______,   _______,  KC_PGDN,                    _______ 
        ),
    [2] = LAYOUT(
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______, 
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______, 
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______ 
        ),
    [3] = LAYOUT(
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  _______, 
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______, 
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______ 
        )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DEVICE_INFO:
            if (record->event.pressed) {
                debug_custom();
            } else {
            }
            return false;
            case RGB_MATRIX_INDICATOR_ONLY:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_indicator_only);
            } else {
            }
            return false;
        case FADER_REVERSE:
            if (record->event.pressed) {
                fader_reverse();
            } else {
            }
            return false;
        case FADER_CHI:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    fader_decrease_channel();
                } else {
                    fader_increase_channel();
                }
            } else {
            }
            return false;
        case FADER_CCI:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    fader_decrease_cc();
                } else {
                    fader_increase_cc();
                }
            } else {
            }
            return false;
        case FADER_ENABLE_TOGGLE:
            if (record->event.pressed) {
                fader_enable_toggle();
            } else {
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}
