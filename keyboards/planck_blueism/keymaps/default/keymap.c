// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "blueism.h"
#include "lpm_stm32l43x.h"

enum keycodes{
    UNPAIR = SAFE_RANGE,
    LPM,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_planck_mit(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP, KC_ENT,
        KC_LSFT,   KC_LCTL, KC_LOPT, KC_LCMD, UNPAIR,      KC_SPC,       LPM,   KC_RCTL, KC_LEFT, KC_DOWN,   KC_RGHT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case UNPAIR:
      if (record->event.pressed) {
        // Do something when pressed
        blueism_unpair();
      } else {
        // Do something else when release
      }
      return false;
    case LPM:
      if (record->event.pressed) {
        // Do something when pressed
      } else {
        // Do something else when release
        enter_power_mode_stop1();
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}

