// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "outputselect.h"
#include "bluetooth.h"
#include "blueism.h"

void bluetooth_init(void) {}

void bluetooth_task(void) {}

void bluetooth_send_keyboard(report_keyboard_t *report) {
    blueism_send_keyboard(report);
}

void bluetooth_send_mouse(report_mouse_t *report) {}

void bluetooth_send_consumer(uint16_t usage) {}

void sys_switch_to_usb(void) {
    set_output(OUTPUT_USB);
}

void sys_switch_to_bt_1(void) {
    set_output(OUTPUT_BLUETOOTH);
}

void sys_switch_to_bt_2(void) {
    set_output(OUTPUT_BLUETOOTH);
}

void sys_switch_to_bt_3(void) {
    set_output(OUTPUT_BLUETOOTH);
}

void sys_switch_to_dongle(void) {
    set_output(OUTPUT_BLUETOOTH);
}
