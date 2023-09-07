// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "blueism.h"

enum keycodes{
    UNPAIR = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_1, KC_UP, MO(1),
        KC_LEFT, KC_DOWN, KC_RGHT,
        KC_LSFT
    ),
    [1] = LAYOUT(
        UNPAIR, KC_VOLU, KC_TRNS,
        KC_1, KC_VOLD, KC_2,
        KC_TRNS
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
    default:
      return true; // Process all other keycodes normally
  }
}

/*simulate battery power consumption*/
// static uint32_t bat_update_timer;
// static uint8_t  bat_level = 100U;

// void housekeeping_task_user(void) {
//     uint32_t timer_now = timer_read();
//     if ((TIMER_DIFF_32(timer_now, bat_update_timer) >= 1000)) {
//         bat_level--;
//         bat_level        = MAX(MIN(bat_level, 100U), 0U);
//         blueism_battery_update(bat_level);
//         bat_update_timer = timer_now;
//     }
// }
