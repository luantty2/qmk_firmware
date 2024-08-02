// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "vbus.h"
#include "lpm_stm32l43x.h"

void palCallback_vbus_sense(void *arg) {
    if (readPin(VBUS_DETECT_PIN)) {
        dprintf("vbus detected\n");
    } else {
        lpm_timer_reset();
        dprintf("vbus not detected\n");
    }
}

void vbus_init(void) {
    gpio_set_pin_input(VBUS_DETECT_PIN);
    palEnableLineEvent(VBUS_DETECT_PIN, PAL_EVENT_MODE_BOTH_EDGES);
    palSetLineCallback(VBUS_DETECT_PIN, palCallback_vbus_sense, NULL);
}
