// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "usb_util.h"
#include "config_blueism.h"

void palCallback_caps_detected(void *arg) {
    if (!readPin(VBUS_DETECT_PIN)) {
        writePin(CAPS_LED_PIN, readPin(NRF_CAPS_DET) ? 1 : 0);
    }
}

void enable_leds_cb(void) {
    palEnableLineEvent(NRF_CAPS_DET, PAL_EVENT_MODE_BOTH_EDGES);
    palSetLineCallback(NRF_CAPS_DET, palCallback_caps_detected, NULL);
}

void disable_leds_cb(void) {
    palDisableLineEvent(NRF_CAPS_DET);
}

void hid_leds_init(void) {
    setPinOutput(CAPS_LED_PIN);
    setPinInput(NRF_CAPS_DET);

    enable_leds_cb();
}
