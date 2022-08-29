/* Copyright 2022 luantty2
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names { _BASE, _FN };

// Defines the keycodes used by our macros in process_record_user
// enum custom_keycodes { QMKBEST = SAFE_RANGE, QMKURL, RGB_INDICATOR_HUI, RGB_INDICATOR_SAI, RGB_INDICATOR_VAI, RGB_INDICATOR_MODE, RGB_INDICATOR_SELECT };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESC,   KC_1,     KC_2,     KC_3,    KC_4,     KC_5,   KC_6,     KC_7,     KC_8,   KC_9,     KC_0,     KC_MINUS,     KC_EQUAL,     KC_BSPACE, 
        KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,   KC_Y,     KC_U,     KC_I,   KC_O,     KC_P,     KC_LBRACKET,  KC_RBRACKET,  KC_BSLS, 
        KC_CAPS,  KC_A,     KC_S,     KC_D,    KC_F,     KC_G,   KC_H,     KC_J,     KC_K,   KC_L,     KC_SCLN,  KC_QUOT,      KC_ENT, 
        KC_LSFT,  KC_Z,     KC_X,     KC_C,    KC_V,     KC_B,   KC_N,     KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,      KC_UP,                                                                                   
        KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC,  KC_RALT,  MO(1),  KC_LEFT,  KC_DOWN,  KC_RGHT                                                                                                                          
        ),
    [_FN] = LAYOUT(
        QK_BOOT,   KC_F1,                KC_F2,          KC_F3,      KC_F4,      KC_F5,     KC_F6,    KC_F7,                      KC_F8,        KC_F9,    KC_F10,   _______,  _______,  EE_CLR, 
        DB_TOGG,   RGB_TOG,              RGB_MOD,        RGB_SPI,    RGB_HUI,    RGB_SAI,   RGB_VAI,  RGB_MATRIX_INDICATOR_ONLY,  DEVICE_INFO,  _______,  _______,  _______,  _______,  _______, 
        _______,   FADER_ENABLE_TOGGLE,  FADER_REVERSE,  FADER_CHI,  FADER_CCI,  _______,   _______,  _______,                    _______,      _______,  _______,  _______,  _______, 
        _______,   _______,              _______,        _______,    _______,    _______,   NK_TOGG,  _______,                    _______,      _______,  _______,  _______,  KC_PGUP, 
        CL_TOGG,   GUI_TOG,              AG_TOGG,        _______,    _______,    _______,   _______,  KC_PGDN,                    _______ 
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

// RGB_INDICATOR_HUI, RGB_INDICATOR_SAI, RGB_INDICATOR_VAI, RGB_INDICATOR_MODE, RGB_INDICATOR_SELECT, RGB_INDICATOR_SHUTDOWN,
// DEVICE_INFO, FADER_REVERSE, FADER_CHI, FADER_CCI, FADER_SHUTDOWN, 

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
