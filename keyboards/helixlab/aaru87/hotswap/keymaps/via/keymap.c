// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    RGB_MATRIX_TOG = USER00,
    RGB_MATRIX_STEP,
    RGB_MATRIX_HUE,
    RGB_MATRIX_SAT,
    RGB_MATRIX_VAL,
    RGBLIGHT_TOG,
    RGBLIGHT_STEP,
    RGBLIGHT_HUE,
    RGBLIGHT_SAT,
    RGBLIGHT_VAL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    KC_ESC,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_PSCR,KC_SCRL,KC_PAUS,  
    KC_GRAVE, KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,KC_EQUAL,KC_BSPC,KC_INS,KC_HOME,KC_PGUP, 
    KC_TAB, KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,KC_BSLS,KC_DEL,KC_END,KC_PGDN,  
    KC_CAPS, KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_ENT,                      
    KC_LSFT, KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,                           KC_UP, 
    KC_LCTL,KC_LGUI,KC_LALT,           KC_SPC,               KC_RALT,KC_RGUI,MO(1),KC_RCTL,     KC_LEFT,KC_DOWN,KC_RGHT
    ),
    [_FN] = LAYOUT(
    KC_TRNS,RGB_MATRIX_TOG,RGBLIGHT_TOG,KC_TRNS,KC_TRNS,RGB_MATRIX_STEP,RGB_MATRIX_HUE,RGB_MATRIX_SAT,RGB_MATRIX_VAL,RGBLIGHT_STEP,RGBLIGHT_HUE,RGBLIGHT_SAT,RGBLIGHT_VAL,KC_TRNS,KC_TRNS,KC_TRNS,  
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                      
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,NK_TOGG,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                           KC_TRNS, 
    KC_TRNS,KC_TRNS,KC_TRNS,           KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS
    ),
    [2] = LAYOUT(
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                      
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                           KC_TRNS, 
    KC_TRNS,KC_TRNS,KC_TRNS,           KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS
    ),
    [3] = LAYOUT(
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, 
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                      
    KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                           KC_TRNS, 
    KC_TRNS,KC_TRNS,KC_TRNS,           KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS
    )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_MATRIX_TOG:
            if (record->event.pressed) {
                rgb_matrix_toggle();
            } else {
            }
            break;
        case RGB_MATRIX_STEP:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
                    rgb_matrix_step();
                }
                else{
                    rgb_matrix_step_reverse();
                }
            } else {
            }
            break;
        case RGB_MATRIX_HUE:
            if (record->event.pressed) {
                rgb_matrix_increase_hue();
            } else {
            }
            break;
        case RGB_MATRIX_VAL:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
                    rgb_matrix_decrease_val();
                }else{
                rgb_matrix_increase_val();
                }   
            } else {
            }
            break;
        case RGB_MATRIX_SAT:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
                    rgb_matrix_decrease_sat();
                }else{
                rgb_matrix_increase_sat();
                }   
            } else {
            }
            break;
        case RGBLIGHT_TOG:
            if (record->event.pressed) {
                rgblight_toggle();
            } else {
            }
            break; 
        case RGBLIGHT_STEP:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
                    rgblight_step();
                }else{
                    rgblight_step_reverse();
                }
            } else {
            }
            break;
        case RGBLIGHT_VAL:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
                    rgblight_decrease_val();
                }else{
                rgblight_increase_val();
                }   
            } else {
            }
            break;
        case RGBLIGHT_HUE:
            if (record->event.pressed) {
                rgblight_increase_hue();
            } else {
            }
            break;
        case RGBLIGHT_SAT:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
                    rgblight_decrease_sat();
                }else{
                rgblight_increase_sat();
                }   
            } else {
            }
            break;
    }
    return true;
}