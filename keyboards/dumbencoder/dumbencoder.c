// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

// #include "dumbencoder.h"
#include "shuttle.h"
#include "timer.h"

static uint32_t key_timer;
// static uint32_t last_shuttle_modification_time = 0;
// void            last_shuttle_activity_trigger(void) {
//     last_shuttle_modification_time = last_input_modification_time = timer_read32();
// }

void shuttle_run(void) {
    uint32_t timer_now = timer_read();
    if (!shuttle_in_deadzone()) {
        // if (!shuttle_in_continouszone()) {
        if (TIMER_DIFF_32(timer_now, key_timer) >= shuttle_get_timer()) {
            shuttle_behavior();
            key_timer = timer_now;
        }
        // } else {
        //     shuttle_behavior();
        // }
    }
}

void keyboard_post_init_kb(void) {
    shuttle_init();
}

void housekeeping_task_kb(void) {
    // const bool = shuttle_changed = shuttle_read();
    shuttle_read();
    // if (shuttle_changed) {
    //     last_shuttle_activity_trigger();
    // }
    shuttle_run();
}