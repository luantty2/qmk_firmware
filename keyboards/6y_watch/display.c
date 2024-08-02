// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "ch455x.h"
#include "display.h"

num_t process_num(uint16_t val) {
    if (val > NUM_MAX) {
        val = NUM_MAX;
    }
    num_t _num = {.val = val};
    // dprintf("num.val: %d\n", _num.val);
    for (uint8_t i = 0; i < NUM_MAX_DIGITS; i++) {
        _num.digits[i]     = val % 10;
        _num.seg_digits[i] = seg_digit_lookup[_num.digits[i]];
        if (val != 0) {
            _num.valid_digits++;
        }
        // dprintf("num.digit[%d]: %d, num.seg_digits[%d]: 0x%x\n", i, _num.digits[i], i, _num.seg_digits[i]);
        val /= 10;
    }
    // dprintf("num.valid_digits: %d.\n", _num.valid_digits);
    return _num;
}

void send_num(num_t num) {
    for (uint8_t i = 0; i < NUM_MAX_DIGITS; i++) {
        uint8_t seg_dig_no_pt = num.seg_digits[i];
        ch455x_write(CH455X_REG_INC(i), &seg_dig_no_pt);
    }
}

void send_num_nozero(num_t num) {
    for (uint8_t i = 0; i < num.valid_digits; i++) {
        uint8_t seg_dig_no_pt = num.seg_digits[i];
        ch455x_write(CH455X_REG_INC(i), &seg_dig_no_pt);
    }
    for (uint8_t i = num.valid_digits; i < NUM_MAX_DIGITS; i++) {
        uint8_t seg_dig_no_pt = DIGIT_NULL;
        ch455x_write(CH455X_REG_INC(i), &seg_dig_no_pt);
    }
}

void send_pattern_all(uint8_t *pat) {
    for (uint8_t i = 0; i < NUM_MAX_DIGITS; i++) {
        ch455x_write(CH455X_REG_INC(i), pat);
    }
}

void send_pattern_single(uint8_t dig, uint8_t *pat) {
    ch455x_write(dig, pat);
}
