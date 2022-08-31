/* Copyright 2022 HelixIndustryLimited
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
#include "rgb_indicator.h"
#include "hsv2rgb.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    RGB_MATRIX_TOG = SAFE_RANGE,
    RGB_MATRIX_MOD,
    RGB_MATRIX_HUE,
    RGB_MATRIX_VAL_INC,
    RGB_MATRIX_VAL_DEC,
    RGB_MATRIX_VAL_ADJUST,
    RGB_MATRIX_SAT_DEC,
    RGB_MATRIX_SAT_ADJUST,
    RGBLIGHT_TOG,
    RGBLIGHT_MOD,
    RGBLIGHT_MOD_REV,
    RGBLIGHT_VAL_INC,
    RGBLIGHT_VAL_DEC,
    RGBLIGHT_VAL_ADJUST,
    RGBLIGHT_HUE,
    RGBLIGHT_SAT_INC,
    RGBLIGHT_SAT_DEC,
    RGBLIGHT_SAT_ADJUST,
    INDICATOR_HUE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
    KC_ESC,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_PSCR,KC_SLCK,KC_PAUS,  
    KC_GRAVE, KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,KC_EQUAL,KC_BSPACE,KC_INS,KC_HOME,KC_PGUP, 
    KC_TAB, KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRACKET,KC_RBRACKET,KC_BSLS,KC_DEL,KC_END,KC_PGDN,  
    KC_CAPS, KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_ENT,                      
    KC_LSFT, KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,                           KC_UP, 
    KC_LCTL,KC_LGUI,KC_LALT,           KC_SPC,               KC_RALT,KC_RGUI,MO(1),KC_RCTL,     KC_LEFT,KC_DOWN,KC_RGHT
    ),
    [1] = LAYOUT(
    KC_TRNS,RGB_MATRIX_TOG,RGBLIGHT_TOG,INDICATOR_HUE,KC_TRNS,RGB_MATRIX_MOD,RGB_MATRIX_HUE,RGB_MATRIX_SAT_ADJUST,RGB_MATRIX_VAL_ADJUST,RGBLIGHT_MOD,RGBLIGHT_HUE,RGBLIGHT_SAT_ADJUST,RGBLIGHT_VAL_ADJUST,KC_TRNS,KC_TRNS,KC_TRNS,  
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
void keyboard_post_init_user(void) {
    hue_config.raw = eeconfig_read_user();
    rgb_indicator_config.raw = eeconfig_read_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case INDICATOR_HUE:
            if (record->event.pressed) {
                HSV hsv;
                hue_config.hue+=12;
                hue_config.hue%=360;
                hsv.h=hue_config.hue;
                hsv.s=220;
                hsv.v=180;
                RGB rgb=hsv_to_rgb(hsv);
                rgb_indicator_config.r=rgb.r;
                rgb_indicator_config.g=rgb.g;
                rgb_indicator_config.b=rgb.b;
                eeconfig_update_user(hue_config.raw);
                eeconfig_update_user(rgb_indicator_config.raw);
            } 
            return false;
            break;
        case RGB_MATRIX_TOG:
            if (record->event.pressed) {
                rgb_matrix_toggle();
            } else {
            }
            break;
        case RGB_MATRIX_MOD:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
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
        case RGB_MATRIX_VAL_INC:
            if (record->event.pressed) {
                rgb_matrix_increase_val();
            } else {
            }
            break;
        case RGB_MATRIX_VAL_DEC:
            if (record->event.pressed) {
                rgb_matrix_decrease_val();
            } else {
            }
            break;
        case RGB_MATRIX_VAL_ADJUST:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
                    rgb_matrix_decrease_val();
                }else{
                rgb_matrix_increase_val();
                }   
            } else {
            }
            break;
        case RGB_MATRIX_SAT_DEC:
            if (record->event.pressed) {
                rgb_matrix_decrease_sat();
            } else {
            }
            break;
        case RGB_MATRIX_SAT_ADJUST:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
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
        case RGBLIGHT_MOD:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
                    rgblight_step();
                }else{
                    rgblight_step_reverse();
                }
            } else {
            }
            break;
        case RGBLIGHT_MOD_REV:
            if (record->event.pressed) {
                rgblight_step_reverse();
            } else {
            }
            break;  
        case RGBLIGHT_VAL_INC:
            if (record->event.pressed) {
                rgblight_increase_val();
            } else {
            }
            break;  
        case RGBLIGHT_VAL_DEC:
            if (record->event.pressed) {
                rgblight_decrease_val();
            } else {
            }
            break;  
        case RGBLIGHT_VAL_ADJUST:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
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
        case RGBLIGHT_SAT_INC:
            if (record->event.pressed) {
                rgblight_increase_sat();
            } else {
            }
            break; 
        case RGBLIGHT_SAT_DEC:
            if (record->event.pressed) {
                rgblight_decrease_sat();
            } else {
            }
            break; 
        case RGBLIGHT_SAT_ADJUST:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
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


void eeconfig_init_user(void) {  // EEPROM is getting reset!
  hue_config.raw = 0;
  rgb_indicator_config.raw = 0;
  hue_config.hue = 0;
  rgb_indicator_config.r = 255;
  rgb_indicator_config.g = 0;
  rgb_indicator_config.b = 0;
  eeconfig_update_user(hue_config.raw); 
  eeconfig_update_user(rgb_indicator_config.raw); 
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
