/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "shuttle.h"
#include "print.h"
#include "action.h"

#define SHUTTLE_RESOLUTION 2

#define SHUTTLE_PAD_A A2
#define SHUTTLE_PAD_B A3

#define SHUTTLE_CLOCKWISE false
#define SHUTTLE_COUNTER_CLOCKWISE true

static int8_t shuttle_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

static uint8_t shuttle_state  = 0;
static int8_t  shuttle_pulses = 0;

static uint8_t shuttle_value = 0;

static uint8_t  shuttle_pos   = 1;
static uint16_t current_timer = TIMER_NO;

uint8_t shuttle_get_pos(void) {
    return shuttle_pos;
}

bool shuttle_in_deadzone(void) {
    if (shuttle_pos == 1 || shuttle_pos == 2 || shuttle_pos == 29 || shuttle_pos == 30) {
        return true;
    } else {
        return false;
    }
}

// bool shuttle_in_continouszone(void) {
//     if (shuttle_pos == 11 || shuttle_pos == 12 || shuttle_pos == 13 || shuttle_pos == 14 || shuttle_pos == 15 || shuttle_pos == 16 || shuttle_pos == 17 || shuttle_pos == 18 || shuttle_pos == 19 || shuttle_pos == 20) {
//         return true;
//     } else {
//         return false;
//     }
// }

void shuttle_set_timer(void) {
    switch (shuttle_get_pos()) {
        case 1:
        case 2:
        case 29:
        case 30:
            current_timer = TIMER_NO;
            break;
        case 3:
        case 4:
        case 27:
        case 28:
            current_timer = TIMER_1;
            break;
        case 5:
        case 6:
        case 25:
        case 26:
            current_timer = TIMER_2;
            break;
        case 7:
        case 8:
        case 23:
        case 24:
            current_timer = TIMER_3;
            break;
        case 9:
        case 10:
        case 21:
        case 22:
            break;
            current_timer = TIMER_4;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            current_timer = TIMER_5;
            break;
        default:
            current_timer = TIMER_NO;
            break;
    }
}

uint16_t shuttle_get_timer(void) {
    return current_timer;
}

void shuttle_behavior(void) {
    switch (shuttle_get_pos()) {
        case 1:
        case 2:
        case 29:
        case 30:
            break;
        case 3:
        case 4:
            // tap_code16(KC_RIGHT);
            // action_exec((keyevent_t){
            //     .key = (keypos_t){.row = 0, .col = 0}, .pressed = 1, .time = (timer_read() | 1) /* time should not be 0 */
            // });
            register_code(KC_RIGHT);
            wait_ms(2);
            unregister_code(KC_RIGHT);
            break;
        case 27:
        case 28:
            register_code(KC_LEFT);
            wait_ms(2);
            unregister_code(KC_LEFT);
            break;
        case 5:
        case 6:
            register_code(KC_RIGHT);
            wait_ms(2);
            unregister_code(KC_RIGHT);
            break;
        case 25:
        case 26:
            register_code(KC_LEFT);
            wait_ms(2);
            unregister_code(KC_LEFT);
            break;
        case 7:
        case 8:
            register_code(KC_RIGHT);
            wait_ms(2);
            unregister_code(KC_RIGHT);
            break;
        case 23:
        case 24:
            register_code(KC_LEFT);
            wait_ms(2);
            unregister_code(KC_LEFT);
            break;
        case 9:
        case 10:
            register_code(KC_RIGHT);
            wait_ms(2);
            unregister_code(KC_RIGHT);
            break;
        case 21:
        case 22:
            register_code(KC_LEFT);
            wait_ms(2);
            unregister_code(KC_LEFT);
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            // tap_code16(S(KC_RIGHT));
            register_code16(S(KC_RIGHT));
            wait_ms(5);
            unregister_code16(S(KC_RIGHT));
            break;
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            // tap_code16(S(KC_LEFT));
            register_code16(S(KC_LEFT));
            wait_ms(5);
            unregister_code16(S(KC_LEFT));
            break;
        default:
            break;
    }
}

void shuttle_pos_step(void) {
    if (shuttle_pos >= 30) {
        shuttle_pos = 1;
    } else {
        shuttle_pos += 1;
    }
}

void shuttle_pos_reverse(void) {
    if (shuttle_pos <= 1) {
        shuttle_pos = 30;
    } else {
        shuttle_pos -= 1;
    }
}

void shuttle_wait_pullup_charge(void) {
    wait_us(100);
}

void shuttle_init(void) {
    setPinInputHigh(SHUTTLE_PAD_A);
    setPinInputHigh(SHUTTLE_PAD_B);
    shuttle_wait_pullup_charge();
    shuttle_state = (readPin(SHUTTLE_PAD_A) << 0) | (readPin(SHUTTLE_PAD_B) << 1);
}

static bool shuttle_update(uint8_t index, uint8_t state) {
    bool changed = false;
    // uint8_t i       = index;

    const uint8_t resolution = SHUTTLE_RESOLUTION;

    shuttle_pulses += shuttle_LUT[state & 0xF];

    if (shuttle_pulses >= resolution) {
        shuttle_value++;
        changed = true;
        // encoder_update_kb(index, SHUTTLE_COUNTER_CLOCKWISE);
        // tap_code(KC_A);
        shuttle_pos_reverse();
        shuttle_set_timer();
        xprintf("pos: %d\n", shuttle_pos);
    }
    if (shuttle_pulses <= -resolution) { // direction is arbitrary here, but this clockwise
        shuttle_value--;

        // encoder_update_kb(index, SHUTTLE_CLOCKWISE);
        // tap_code(KC_B);
        shuttle_pos_step();
        shuttle_set_timer();
        xprintf("pos: %d\n", shuttle_pos);
    }
    shuttle_pulses %= resolution;
    return changed;
}

bool shuttle_read(void) {
    bool    changed    = false;
    uint8_t new_status = (readPin(SHUTTLE_PAD_A) << 0) | (readPin(SHUTTLE_PAD_B) << 1);
    if ((shuttle_state & 0x3) != new_status) {
        shuttle_state <<= 2;
        shuttle_state |= new_status;
        changed |= shuttle_update(0, shuttle_state);
    }
    return changed;
}