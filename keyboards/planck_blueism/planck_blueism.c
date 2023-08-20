// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "lpm_stm32l43x.h"

void keyboard_post_init_kb(void) {
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    setPinOutput(B3);
    writePinHigh(B3);
}
