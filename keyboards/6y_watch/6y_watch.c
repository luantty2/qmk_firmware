// Copyright 2024 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "ch455x.h"

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    keyboard_post_init_user();
}

static uint32_t loop_timer;

void housekeeping_task_kb(void){
    uint32_t timer_now = timer_read();
    if ((TIMER_DIFF_32(timer_now, loop_timer) >= 1000)) {
        uint8_t data = 0b01111001;
        ch455x_write(CH455X_REG_DIG_3, &data);
        loop_timer = timer_now;
    }
}
