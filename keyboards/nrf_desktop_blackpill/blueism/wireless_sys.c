// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "bluetooth.h"
#include "blueism.h"

void bluetooth_init() {
    blueism_init();
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
