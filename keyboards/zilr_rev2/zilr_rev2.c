// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "zilr_rev2.h"
#include "rgb_indicator.h"
#include "rgb_indicator_modes.h"
#include "timer.h"
#include "shuttle_rev3.h"

#define INT_2HZ_PIN A7
#define INT_5HZ_PIN A6
#define INT_10HZ_PIN A5
#define INT_15HZ_PIN A4

#define SHUTTLE_READ_INTERVAL 100

static uint32_t shuttle_read_timer;

void palCallback_2HZ(void *arg) {
    // if (shuttle_get_zone() == SHUTTLE_ZONE_2X) {
    //     tap_code(KC_RIGHT);
    // } else if (shuttle_get_zone() == SHUTTLE_ZONE_N2X) {
    //     tap_code(KC_LEFT);
    // }
    // dprintf("2hz triggered\n");

    if (shuttle_get_zone() == SHUTTLE_ZONE_2X) {
        dprintf("2hz_2x triggered\n");
        // tap_code(KC_RIGHT);
        // register_code(KC_RIGHT);
        // wait_ms(10);
        // unregister_code(KC_RIGHT);
    } else if (shuttle_get_zone() == SHUTTLE_ZONE_N2X) {
        dprintf("2hz_n2x triggered\n");
        // tap_code(KC_LEFT);
    }
}

void palCallback_5HZ(void *arg) {
    // if (shuttle_get_zone() == SHUTTLE_ZONE_5X) {
    //     tap_code(KC_RIGHT);
    // } else if (shuttle_get_zone() == SHUTTLE_ZONE_N5X) {
    //     tap_code(KC_LEFT);
    // }
    // dprintf("5hz triggered\n");
    if (shuttle_get_zone() == SHUTTLE_ZONE_5X) {
        dprintf("5hz_5x triggered\n");
    } else if (shuttle_get_zone() == SHUTTLE_ZONE_N5X) {
        dprintf("5hz_n5x triggered\n");
    }
}

void palCallback_10HZ(void *arg) {
    // if (shuttle_get_zone() == SHUTTLE_ZONE_10X) {
    //     tap_code(KC_RIGHT);
    // } else if (shuttle_get_zone() == SHUTTLE_ZONE_N10X) {
    //     tap_code(KC_LEFT);
    // } else if (shuttle_get_zone() == SHUTTLE_ZONE_SX) {
    //     register_code16(S(KC_RIGHT));
    //     wait_ms(30);
    //     unregister_code16(S(KC_RIGHT));
    // } else if (shuttle_get_zone() == SHUTTLE_ZONE_NSX) {
    //     register_code16(S(KC_LEFT));
    //     wait_ms(30);
    //     unregister_code16(S(KC_LEFT));
    // }
    // dprintf("10hz triggered\n");

    if (shuttle_get_zone() == SHUTTLE_ZONE_10X) {
        dprintf("10hz_10x triggered\n");
    } else if (shuttle_get_zone() == SHUTTLE_ZONE_N10X) {
        dprintf("10hz_n10x triggered\n");
    }
}

void palCallback_15HZ(void *arg) {
    // if (shuttle_get_zone() == SHUTTLE_ZONE_15X) {
    //     tap_code(KC_RIGHT);
    // } else if (shuttle_get_zone() == SHUTTLE_ZONE_N15X) {
    //     tap_code(KC_LEFT);
    // }
    // dprintf("15hz triggered\n");
    if (shuttle_get_zone() == SHUTTLE_ZONE_15X) {
        dprintf("15hz_15x triggered\n");
    } else if (shuttle_get_zone() == SHUTTLE_ZONE_N15X) {
        dprintf("15hz_n15x triggered\n");
    }
}

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    rgb_indicator_init();
    shuttle_init();

    setPinInput(INT_2HZ_PIN);
    palEnableLineEvent(INT_2HZ_PIN, PAL_EVENT_MODE_FALLING_EDGE);
    palSetLineCallback(INT_2HZ_PIN, palCallback_2HZ, NULL);

    setPinInput(INT_5HZ_PIN);
    palEnableLineEvent(INT_5HZ_PIN, PAL_EVENT_MODE_FALLING_EDGE);
    palSetLineCallback(INT_5HZ_PIN, palCallback_5HZ, NULL);

    setPinInput(INT_10HZ_PIN);
    palEnableLineEvent(INT_10HZ_PIN, PAL_EVENT_MODE_FALLING_EDGE);
    palSetLineCallback(INT_10HZ_PIN, palCallback_10HZ, NULL);

    setPinInput(INT_15HZ_PIN);
    palEnableLineEvent(INT_15HZ_PIN, PAL_EVENT_MODE_FALLING_EDGE);
    palSetLineCallback(INT_15HZ_PIN, palCallback_15HZ, NULL);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
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
}

void shuttle_run(void) {
    uint32_t timer_now = timer_read();
    if (TIMER_DIFF_32(timer_now, shuttle_read_timer) >= SHUTTLE_READ_INTERVAL) {
        shuttle_read();
        shuttle_read_timer = timer_now;
    }
}

void housekeeping_task_kb(void) {
    shuttle_run();
}