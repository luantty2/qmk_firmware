// Copyright 2024 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "6y_watch.h"
#include "battery.h"
#include "ch455x.h"
#include "rtc.h"
#include "display.h"
#include "calendar.h"
#include "leds.h"
#include "touch.h"
#include "vbus.h"
#include "lpm_stm32l43x.h"

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    vbus_init();
    touch_init();

    leds_init();
    leds_all_off();

    battery_init();
    ch455x_init();

    calendar_init();
    send_num(process_num(calendar_dest_day_diff(calendar_update_current())));

    lpm_init();

    keyboard_post_init_user();
}

static uint32_t        loop_timer;
static uint32_t        led_timer;
static display_modes_t display_mode = REMAINING_TIME_MODE;
static uint8_t         calli_pattern;
static uint8_t         eye_anim_timer;
#define EYE_OPENED 0b01011101
#define EYE_CLOSED 0b01001000

display_modes_t get_current_display_mode(void) {
    return display_mode;
}

uint8_t calli_pattern_anim(void) {
    if (calli_pattern == 255) {
        calli_pattern = 0;
    }
    return calli_pattern++;
}

void matrix_scan_kb(void) {
    uint32_t timer_now = timer_read32();
    if ((TIMER_DIFF_32(timer_now, loop_timer) > 1000)) {
        // battery_fetch();
        // if (is_batt_mode) {
        //     send_num(process_num(battery_fetch()));
        // } else {
        //     send_num(process_num(calendar_dest_day_diff(calendar_update_current())));
        // }
        battery_fetch();

        switch (display_mode) {
            case REMAINING_TIME_MODE:
                uint16_t diff = calendar_dest_day_diff(calendar_update_current());

                if (diff == 2085 || diff == 1720 || diff == 1355 || diff == 990 || diff == 624 || diff == 259) {
                    uint8_t data;
                    data = DIGIT_C;
                    send_pattern_single(CH455X_REG_DIG_1, &data);
                    data = DIGIT_O;
                    send_pattern_single(CH455X_REG_DIG_2, &data);
                    data = DIGIT_N;
                    send_pattern_single(CH455X_REG_DIG_3, &data);
                    data = DIGIT_G;
                    send_pattern_single(CH455X_REG_DIG_4, &data);
                } else if (diff > 0) {
                    send_num(process_num(diff));
                } else {
                    uint8_t pat = DIGIT_MINUS;
                    send_pattern_all(&pat);
                }
                // send_num(process_num(calendar_dest_day_diff(calendar_update_current())));
                break;
            case BATTERY_MODE:
                send_num_nozero(process_num(battery_get()));
                break;
            case FUTURE_CALLI_MODE_SYMBOL:
                // calli_pattern_anim();
                // send_pattern_all(&calli_pattern);
                if (eye_anim_timer % 10 == 0) {
                    eye_anim_timer   = 0;
                    uint8_t data     = EYE_CLOSED;
                    uint8_t data_dot = data | 0b10000000;
                    uint8_t null     = DIGIT_NULL;
                    send_pattern_single(CH455X_REG_DIG_1, &null);
                    send_pattern_single(CH455X_REG_DIG_2, &data);
                    send_pattern_single(CH455X_REG_DIG_3, &data_dot);
                    send_pattern_single(CH455X_REG_DIG_4, &null);
                } else {
                    uint8_t data = EYE_OPENED;
                    uint8_t null = DIGIT_NULL;
                    send_pattern_single(CH455X_REG_DIG_1, &null);
                    send_pattern_single(CH455X_REG_DIG_2, &data);
                    send_pattern_single(CH455X_REG_DIG_3, &data);
                    send_pattern_single(CH455X_REG_DIG_4, &null);
                }
                eye_anim_timer++;
                break;
            // case FUTURE_CALLI_MODE:
            default:
                break;
        }
        calendar_print_current();

        // if (display_sleeping) {
        //     ch455x_wakeup();
        //     send_num(process_num(num++));
        //     display_sleeping = false;
        // } else {
        //     ch455x_sleep();
        //     display_sleeping = true;
        // }

        loop_timer = timer_now;
    }
    if ((TIMER_DIFF_32(timer_now, led_timer) > 350)) {
        if (display_mode == REMAINING_TIME_MODE) {
            leds_toggle(LED_PIN_1);
        } else {
            leds_set(LED_PIN_1, LED_STATE_OFF);
        }
        if (battery_get() <= 20 && !readPin(VBUS_DETECT_PIN)) {
            leds_set(LED_PIN_3, LED_STATE_ON);
        } else {
            leds_set(LED_PIN_3, LED_STATE_OFF);
        }

        led_timer = timer_now;
    }
}

enum via_calendar {
    id_year   = 1,
    id_month  = 2,
    id_day    = 3,
    id_hour   = 4,
    id_minute = 5,
    id_sec    = 6,
};

void calendar_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    wait_ms(1);
    calendar_update_current();
    calendar_t curr = calendar_get_current();
    switch (*value_id) {
        case id_year:
            rtc_set_date(curr.month, curr.day, value_data[0] + 2024);
            break;
        case id_month:
            rtc_set_date(value_data[0], curr.day, curr.year);
            break;
        case id_day:
            rtc_set_date(curr.month, value_data[0], curr.year);
            break;
        case id_hour:
            rtc_set_time(value_data[0], curr.min, curr.sec);
            break;
        case id_minute:
            rtc_set_time(curr.hour, value_data[0], curr.sec);
            break;
        case id_sec:
            rtc_set_time(curr.hour, curr.min, value_data[0]);
            break;
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);
    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value:
                calendar_config_set_value(value_id_and_data);
                break;
            case id_custom_get_value:
                break;
            case id_custom_save:
                break;
            default:
                // Unhandled message.
                *command_id = id_unhandled;
                break;
        }
        return;
    }
    // Return the unhandled state
    *command_id = id_unhandled;
    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

// static uint16_t day_adjust_timer;

// void rtc_inc_day_count(uint16_t days) {
//     for (uint8_t i = 0; i < days; i++) {
//         rtc_increment_day();
//         wait_ms(10);
//         send_num(process_num(calendar_dest_day_diff(calendar_update_current())));
//     }
// }

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BAT_MOD:
            if (record->event.pressed) {
                lpm_timer_reset();
                if (display_mode == BATTERY_MODE) {
                    display_mode = REMAINING_TIME_MODE;
                } else {
                    display_mode = BATTERY_MODE;
                }
            } else {
            }
            return false;
        case FUT_MOD:
            if (record->event.pressed) {
                lpm_timer_reset();
                if (display_mode == FUTURE_CALLI_MODE_SYMBOL) {
                    display_mode = REMAINING_TIME_MODE;
                } else {
                    display_mode = FUTURE_CALLI_MODE_SYMBOL;
                }
            } else {
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}
