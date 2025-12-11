// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "analog.h"

extern MidiDevice midi_device;

#define ADC_DEADBAND 12

// static uint16_t last_val_con1;
// static uint16_t last_val_con2;
// static uint16_t last_val_con3;

static uint16_t last_val_conx;
static uint16_t last_val_cony;

static uint32_t fader_read_timer = 0;

void keyboard_post_init_kb(void) {}

void housekeeping_task_kb(void) {
    uint32_t timer_now = timer_read();
    if (TIMER_DIFF_32(timer_now, fader_read_timer) >= 100) {
        // uint16_t val_con1 = analogReadPin(A1);
        // if (abs(val_con1 - last_val_con1) > ADC_DEADBAND) {
        //     last_val_con1 = val_con1;
        //     val_con1 >>= 3;
        //     midi_send_cc(&midi_device, 0, 105, val_con1);
        // }

        // uint16_t val_con2 = analogReadPin(A2);
        // if (abs(val_con2 - last_val_con2) > ADC_DEADBAND) {
        //     last_val_con2 = val_con2;
        //     val_con2 >>= 3;
        //     midi_send_cc(&midi_device, 0, 106, val_con2);
        // }

        // uint16_t val_con3 = analogReadPin(A3);
        // if (abs(val_con3 - last_val_con3) > ADC_DEADBAND) {
        //     last_val_con3 = val_con3;
        //     val_con3 >>= 3;
        //     midi_send_cc(&midi_device, 0, 107, val_con3);
        // }

        uint16_t val_conx = analogReadPin(B1);
        if (abs(val_conx - last_val_conx) > ADC_DEADBAND) {
            last_val_conx = val_conx;
            val_conx >>= 3;
            midi_send_cc(&midi_device, 0, 110, val_conx);
        }

        uint16_t val_cony = analogReadPin(B0);
        if (abs(val_conx - last_val_cony) > ADC_DEADBAND) {
            last_val_cony = val_cony;
            val_cony >>= 3;
            midi_send_cc(&midi_device, 0, 111, val_cony);
        }
    }

    // uint16_t val = analogReadPin(A1);
    // val          = val >> 3;
    // if (val != last_val) {
    //     dprintf("A1: %d\n", val);
    //     last_val = val;
    //     midi_send_cc(&midi_device, 0, 1, val);
    // }
}
