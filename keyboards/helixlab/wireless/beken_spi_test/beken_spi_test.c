// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;
    keyboard_post_init_user();
}
