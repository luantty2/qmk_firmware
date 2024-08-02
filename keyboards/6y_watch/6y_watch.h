// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H
#include "quantum.h"


typedef enum {
    REMAINING_TIME_MODE,
    BATTERY_MODE,
    FUTURE_CALLI_MODE_SYMBOL,
} display_modes_t;


enum { BAT_MOD = SAFE_RANGE, FUT_MOD, };

display_modes_t get_current_display_mode(void);
