// Copyright 2026 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"

enum blueism_keycodes {
    BLUEISM_PING = QK_KB_0,
    BLUEISM_RESET,
    BLUEISM_GET_VERSION,
};

bool process_record_blueism(uint16_t keycode, keyrecord_t *record);
