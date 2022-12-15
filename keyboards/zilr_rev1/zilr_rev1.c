// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "zilr_rev1.h"
#include "rgb_indicator.h"
#include "rgb_indicator_modes.h"

void keyboard_post_init_kb(void) {
    rgb_indicator_init();
    // rgb_indicator_on();
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