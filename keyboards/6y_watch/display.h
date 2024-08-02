// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H

#define NUM_MAX 9999
#define NUM_MAX_DIGITS 4

#define DIGIT_NULL 0b00000000
#define DIGIT_MINUS 0b01000000
#define DIGIT_0 0b00111111
#define DIGIT_1 0b00000110
#define DIGIT_2 0b01011011
#define DIGIT_3 0b01001111
#define DIGIT_4 0b01100110
#define DIGIT_5 0b01101101
#define DIGIT_6 0b01111101
#define DIGIT_7 0b00000111
#define DIGIT_8 0b01111111
#define DIGIT_9 0b01101111

#define DIGIT_C 0b01100001
#define DIGIT_O 0b01100011
#define DIGIT_N 0b00100011
#define DIGIT_G 0b11101111

static const uint8_t PROGMEM seg_digit_lookup[] = {DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7, DIGIT_8, DIGIT_9};
typedef struct {
    uint16_t val;
    uint8_t  digits[NUM_MAX_DIGITS];
    uint8_t  valid_digits;
    uint8_t  seg_digits[NUM_MAX_DIGITS];
} num_t;

num_t process_num(uint16_t val);
void  send_num(num_t num);
void  send_num_nozero(num_t num);
void  send_pattern_all(uint8_t *pat);
void  send_pattern_single(uint8_t dig, uint8_t *pat);
