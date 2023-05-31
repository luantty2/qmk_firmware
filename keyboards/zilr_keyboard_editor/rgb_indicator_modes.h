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

void rgb_indicator_effect_plain(bool state);
void rgb_indicator_effect_fade_in(bool state);
void rgb_indicator_effect_fade_out(bool state);
void rgb_indicator_effect_fade_inout(bool state);
void rgb_indicator_effect_gradient(bool state);
// void rgb_indicator_effect_blink(bool state);
void rgb_indicator_effect_random_hue(bool state);

//for zilr
void rgb_indicator_led0_fade_inout(bool state);
void rgb_indicator_led1_fade_inout(bool state);
void rgb_indicator_led2_fade_inout(bool state);
void rgb_indicator_leds_blink(void);