// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "leds.h"

void leds_toggle(pin_t pin) {
    gpio_toggle_pin(pin);
}

void leds_set(pin_t pin, bool state) {
    gpio_write_pin(pin, !state);
}

void leds_all_off(void) {
    gpio_write_pin_high(LED_PIN_0);
    gpio_write_pin_high(LED_PIN_1);
    gpio_write_pin_high(LED_PIN_2);
    gpio_write_pin_high(LED_PIN_3);
}

void leds_init(void) {
    gpio_set_pin_output(LED_PIN_0);
    gpio_set_pin_output(LED_PIN_1);
    gpio_set_pin_output(LED_PIN_2);
    gpio_set_pin_output(LED_PIN_3);
}
