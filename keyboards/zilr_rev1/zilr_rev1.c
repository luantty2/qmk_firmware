// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "zilr_rev1.h"
#include "rgb_indicator.h"
#include "rgb_indicator_modes.h"
#include "timer.h"
#include "shuttle.h"

static uint32_t key_timer;

void keyboard_post_init_kb(void) {
    rgb_indicator_init();
    shuttle_init();
}

bool led_update_kb(led_t led_state) {
    // #ifdef RGB_INDICATOR_ENABLE
    bool res = led_update_user(led_state);
    if (res) {
        // rgb_indicator_toggle(led_state.caps_lock);
        if (led_state.caps_lock) {
            rgb_indicator_led0_fade_inout(true);
        } else {
            rgb_indicator_led0_fade_inout(false);
        }
        if (led_state.num_lock) {
            rgb_indicator_led1_fade_inout(true);
        } else {
            rgb_indicator_led1_fade_inout(false);
        }
        if (led_state.scroll_lock) {
            rgb_indicator_led2_fade_inout(true);
        } else {
            rgb_indicator_led2_fade_inout(false);
        }
    }
    return res;
    // #endif
}

void shuttle_run(void) {
    uint32_t timer_now = timer_read();
    if (!shuttle_in_deadzone()) {
        if (TIMER_DIFF_32(timer_now, key_timer) >= shuttle_get_timer()) {
            shuttle_behavior();
            key_timer = timer_now;
        }
    }
}


void housekeeping_task_kb(void) {
    // const bool = shuttle_changed = shuttle_read();
    shuttle_read();
    // if (shuttle_changed) {
    //     last_shuttle_activity_trigger();
    // }
    shuttle_run();
}