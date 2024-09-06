// Copyright 2024 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "outputselect.h"
// #include "wireless_sys.h"

void keyboard_post_init_kb(void) {
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    // output_manager_init();
    set_output(OUTPUT_BLUETOOTH);

    keyboard_post_init_user();
}
