// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H

#define LED_STATE_ON 1
#define LED_STATE_OFF 0

#define LED_PIN_0 A6
#define LED_PIN_1 B13
#define LED_PIN_2 B14
#define LED_PIN_3 B15
#define LED_PIN_4 A13

void leds_init(void);
void leds_all_off(void);
void leds_set(pin_t pin, bool state);
void leds_toggle(pin_t pin);
