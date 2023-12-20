// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "battery.h"
#include "bluetooth.h"
#include "blueism.h"
#include "usb_util.h"
#include "usb_main.h"
#include "outputselect.h"
#include "config_blueism.h"
#include "wireless_sys.h"
#include "quantum.h"

void bluetooth_init() {
    blueism_init();
#ifdef MAX1704X_ENABLE
    battery_init();
#endif
}
void bluetooth_task() {
    blueism_task();
#ifdef MAX1704X_ENABLE
    battery_task();
#endif
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
    if (readPin(VBUS_DETECT_PIN)) {
        // if (usb_connected_state()) {
        // while(1){
        //     if(usb_connected_state()){
        //         break;
        //     }
        // }
        // clear_keyboard();
        // usb_start(&USBD1);
        // set_output(OUTPUT_USB);
    } else {
        clear_keyboard();
        set_output(OUTPUT_BLUETOOTH);
    }
}

void output_manager_init(void) {
    // if (readPin(VBUS_DETECT_PIN)) {
    if (usb_connected_state()) {
        set_output(OUTPUT_USB);
    } else {
        set_output(OUTPUT_BLUETOOTH);
    }
    palEnableLineEvent(VBUS_DETECT_PIN, PAL_EVENT_MODE_BOTH_EDGES);
    palSetLineCallback(VBUS_DETECT_PIN, palCallback_vbus_sense, NULL);
}

// void output_scan(void) {
//     // if (usb_connected_state()) {
//     if(readPin(VBUS_DETECT_PIN)){
//         set_output(OUTPUT_USB);
//     } else {
//         set_output(OUTPUT_BLUETOOTH);
//     }
// }
