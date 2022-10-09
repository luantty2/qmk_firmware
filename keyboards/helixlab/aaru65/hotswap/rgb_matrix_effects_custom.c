// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "rgb_matrix_effects_custom.h"
#include "rgb_matrix.h"

uint8_t         target_v       = 0;
uint8_t         current_v      = 0;
static uint32_t fade_in_timer  = 0;
bool            fade_completed = false;

void rgb_matrix_set_target_v(void) {
    target_v = rgb_matrix_get_val();
}

bool rgb_matrix_fade_in(void) {
    uint32_t timer_now = timer_read();
    if (TIMER_DIFF_32(timer_now, fade_in_timer) <= FADE_IN_LENGTH) {
        rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), current_v);
        current_v += 1;
        if (current_v == target_v) {
            return true;
        }
        fade_in_timer = timer_now;
        return false;
    }
    return true;
}