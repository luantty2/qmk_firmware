// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "touch.h"
#include "lpm_stm32l43x.h"

void palCallback_touch_sense(void *arg) {
    if (readPin(TOUCH_INPUT_PIN)) {
        lpm_timer_reset();
        dprintf("touched\n");
    } else {
        dprintf("not touched\n");
    }
}

void touch_init(void) {
    gpio_set_pin_input(TOUCH_INPUT_PIN);
    palEnableLineEvent(TOUCH_INPUT_PIN, PAL_EVENT_MODE_RISING_EDGE);
    palSetLineCallback(TOUCH_INPUT_PIN, palCallback_touch_sense, NULL);
}
