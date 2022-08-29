// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "zilr.h"
#include "rgb_indicator.h"

void keyboard_post_init_kb(void) {
    rgb_indicator_init();
    rgb_indicator_on();
}

bool led_update_kb(led_t led_state) {
#ifdef RGB_INDICATOR_ENABLE
    bool res = led_update_user(led_state);
    if (res) {
        rgb_indicator_toggle(led_state.caps_lock);
    }
    return res;
#endif
}