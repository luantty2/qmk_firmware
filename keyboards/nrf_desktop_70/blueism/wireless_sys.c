// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "bluetooth.h"
#include "blueism.h"
#include "usb_util.h"
#include "outputselect.h"
#include "config_blueism.h"
#include "quantum.h"

void output_manager_init(void);

void bluetooth_init() {
    blueism_init();
    output_manager_init();
}
void bluetooth_task() {
    blueism_task();
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
    blueism_send_keyboard(report);
}

void bluetooth_send_mouse(report_mouse_t *report) {
    blueism_send_mouse(report);
}

void bluetooth_send_consumer(uint16_t usage) {
    blueism_send_consumer(usage);
}

void palCallback_vbus_sense(void *arg) {
    if (usb_connected_state()) {
        set_output(OUTPUT_USB);
    } else {
        set_output(OUTPUT_BLUETOOTH);
    }
}

void output_manager_init(void) {
    palEnableLineEvent(VBUS_DETECT_PIN, PAL_EVENT_MODE_BOTH_EDGES);
    palSetLineCallback(VBUS_DETECT_PIN, palCallback_vbus_sense, NULL);
}
