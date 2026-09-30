// Copyright 2024 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "blueism_uart.h"
#include "blueism_keycodes.h"

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    blueism_init();

    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    housekeeping_task_blueism();

    housekeeping_task_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_blueism(keycode, record)) {
        return false;
    }

    return process_record_user(keycode, record);
}
