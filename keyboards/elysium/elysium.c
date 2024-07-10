// Copyright 2023 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_post_init_kb(void) {
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    // USB mux selection pin.
    // low = USB HS, high = USB FS.
    setPinOutput(USB_MUX_SEL_PIN);
    writePinLow(USB_MUX_SEL_PIN);

    keyboard_post_init_user();
}
