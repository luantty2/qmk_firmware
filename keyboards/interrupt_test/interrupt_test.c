// Copyright 2023 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#define INT_GPIO B10

void gpio_interrupt_service(void) {
    dprintf("io level falling detected!\n");
}

void palCallback(void *arg) {
    gpio_interrupt_service();
}


void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    // GPIO_INT_INIT();
    // GPIO_INT_ON();
    
    palSetLineMode(INT_GPIO, PAL_MODE_INPUT);
    palEnableLineEvent(INT_GPIO, PAL_EVENT_MODE_FALLING_EDGE); \
    palSetLineCallback(INT_GPIO, palCallback, NULL); 
    palSetLineMode(A4, PAL_MODE_OUTPUT_PUSHPULL);

}

/*
Test polling rate
*/

void auto_clicking(void) {
    // register_code(KC_A);
    palSetLine(A4);
    wait_ms(1000);
    // unregister_code(KC_A);
    palClearLine(A4);
}

static uint32_t key_timer;

void polling_test(void) {
    uint32_t timer_now = timer_read();
    if (TIMER_DIFF_32(timer_now, key_timer) >= 1000) {
        auto_clicking();
        key_timer = timer_now;
    }
}

void housekeeping_task_kb(void) {
    polling_test();
}
