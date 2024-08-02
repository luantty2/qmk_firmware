// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H

typedef struct {
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  min;
    uint8_t  sec;
} calendar_t;

void       calendar_init(void);
calendar_t calendar_get_current(void);
calendar_t calendar_update_current(void);
void       calendar_print_current(void);
uint16_t   calendar_dest_day_diff(calendar_t d);
