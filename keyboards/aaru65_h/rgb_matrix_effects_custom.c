/* Copyright 2022 luantty2
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

#include "rgb_matrix_effects_custom.h"
#include "rgb_matrix.h"

uint8_t         target_v      = 0;
uint8_t         current_v     = 0;
static uint32_t fade_in_timer = 0;

#define FADE_IN_LENGTH 500

void rgb_matrix_set_target_v(void) {
    target_v = rgb_matrix_get_val();
}

bool rgb_matrix_fade_in(void) {
    uint32_t timer_now = timer_read();
    if (TIMER_DIFF_32(timer_now, fade_in_timer) <= FADE_IN_LENGTH) {
        rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), current_v);
        current_v += 1;
        if (current_v == target_v) return true;
        fade_in_timer = timer_now;
        return false;
    }
    return true;
    // target_v = rgb_matrix_get_val();

    // target_v=200;
    // for (uint8_t current_v = 0; current_v <= target_v; current_v+=5) {
    //     // float pwm_val = 255.0 * (1.0 - abs((2.0 * (ii / smoothness_pts)) - 1.0));
    //     // analogWrite(led_pins[jj], int(pwm_val));
    //     rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), current_v);
    //     wait_ms(5);
    //     // Serial.println(int(pwm_val));
    // }

    // target_v=200;
    // rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 0);
    // wait_ms(100);
    // rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 30);
    // wait_ms(100);
    // rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 100);
    // wait_ms(100);
    // rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 150);
    // wait_ms(100);
    // rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 220);
    // wait_ms(100);
}