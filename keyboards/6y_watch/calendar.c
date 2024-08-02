// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "calendar.h"
#include "rtc.h"

static const calendar_t dest = {.year = 2030, .month = 8, .day = 19};
static calendar_t       curr;

void calendar_init(void) {
    rtc_refresh_time();
    if (rtc_get_year() == 1980) {
        rtc_set_time(21, 31, 00);
        rtc_set_date(8, 1, 2024);
    }
    // wait_ms(50);
    calendar_update_current();
}

calendar_t calendar_get_current(void) {
    return curr;
}

void calendar_print_current(void) {
    dprintf("year: %d, month: %d, day: %d, hour: %d, min: %d, sec: %d\n", curr.year, curr.month, curr.day, curr.hour, curr.min, curr.sec);
}

calendar_t calendar_update_current(void) {
    rtc_refresh_time();
    curr.year  = rtc_get_year();
    curr.month = rtc_get_month();
    curr.day   = rtc_get_day();
    curr.hour  = rtc_get_hour24();
    curr.min   = rtc_get_minute();
    curr.sec   = rtc_get_second();
    return curr;
}

uint16_t day_diff(calendar_t d1, calendar_t d2) {
    struct tm start = {0, 0, 0, d1.day, d1.month - 1, d1.year - 1900};
    struct tm end   = {0, 0, 0, d2.day, d2.month - 1, d2.year - 1900};
    time_t    s     = mktime(&start);
    time_t    e     = mktime(&end);
    return difftime(e, s) / (60 * 60 * 24);
}

uint16_t calendar_dest_day_diff(calendar_t d) {
    return day_diff(d, dest);
}
