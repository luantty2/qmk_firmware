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

#include "aaru65_623.h"
#include "version.h"
#include "debug_custom.h"
#ifdef FADER_ENABLE
#    include "fader.h"
#endif
#ifdef RGB_INDICATOR_ENABLE
#    include "rgb_indicator.h"
#endif

#ifdef FADER_ENABLE
extern MidiDevice midi_device;
// static int16_t    midi_cc_value = 0;
#endif

void eeconfig_init_kb(void) {
#ifdef RGB_INDICATOR_ENABLE
    eeconfig_init_rgb_indicator();
#endif
#ifdef FADER_ENABLE
    eeconfig_init_fader();
#endif
    eeconfig_init_user();
}

/*
void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_scan_user();
}
*/

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;
#ifdef RGB_INDICATOR_ENABLE
    rgb_indicator_init();
#endif
#ifdef FADER_ENABLE
    fader_init();
#endif
    // matrix_init_user();
}

void matrix_scan_kb(void) {
#ifdef RGB_INDICATOR_ENABLE
    /*test each channels*/
    // rgb_indicator_factory_test();
    // if(rgb_indicator_factory_test_runner()) rgb_indicator_factory_test();
    rgb_indicator_factory_test_runner();
#endif
#ifdef FADER_ENABLE
    // midi_cc_value = fader_read();
    // if (midi_cc_value != ADC_ERROR) midi_send_cc(&midi_device, 0, 7, midi_cc_value);
    fader_run(&midi_device);
#endif
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DEVICE_INFO:
            if (record->event.pressed) {
                debug_custom();
            } else {
            }
            break;

#ifdef RGB_INDICATOR_ENABLE
        case RGB_INDICATOR_HUI:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    rgb_indicator_decrease_hue();
                } else {
                    rgb_indicator_increase_hue();
                }
            } else {
            }
            break;
        case RGB_INDICATOR_SAI:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    rgb_indicator_decrease_sat();
                } else {
                    rgb_indicator_increase_sat();
                }
            } else {
            }
            break;
        case RGB_INDICATOR_VAI:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    rgb_indicator_decrease_val();
                } else {
                    rgb_indicator_increase_val();
                }
            } else {
            }
            break;
        case RGB_INDICATOR_MODE:
            if (record->event.pressed) {
                rgb_indicator_step();
            } else {
            }
            break;
        case RGB_INDICATOR_SELECT:
            if (record->event.pressed) {
                rgb_indicator_select_toggle();
            } else {
            }
            break;
        case RGB_INDICATOR_ENABLE_TOGGLE:
            if (record->event.pressed) {
                rgb_indicator_enable_toggle();
            } else {
            }
            break;
#endif
#ifdef FADER_ENABLE
        case FADER_REVERSE:
            if (record->event.pressed) {
                fader_reverse();
            } else {
            }
            break;
        case FADER_CHI:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    fader_decrease_channel();
                } else {
                    fader_increase_channel();
                }
            } else {
            }
            break;
        case FADER_CCI:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    fader_decrease_cc();
                } else {
                    fader_increase_cc();
                }
            } else {
            }
            break;
        case FADER_ENABLE_TOGGLE:
            if (record->event.pressed) {
                fader_enable_toggle();
            } else {
            }
            break;
#endif
    }
    return true;
}

bool led_update_kb(led_t led_state) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

    // static uint8_t caps_state = 0;
    // if (caps_state != led_state.caps_lock) {
    //     // led_state.caps_lock ? AW2023_LED0_PWM(255) : AW2023_LED0_PWM(0);
    //     if (led_state.caps_lock) {
    //         AW2023_LED0_pwm(255);
    //         wait_ms(200);
    //         AW2023_LED0_pwm(180);
    //     } else {
    //         AW2023_LED0_pwm(255);
    //         wait_ms(100);
    //         AW2023_LED0_pwm(0);
    //     }
    //     caps_state = led_state.caps_lock;
    // }

    // static uint8_t caps_state = 0;
    // if (caps_state != led_state.caps_lock) {
    //     // led_state.caps_lock ? AW2023_LED0_PWM(255) : AW2023_LED0_PWM(0);
    //     if (led_state.caps_lock) {
    //         AW2023_enter_manual();
    //         AW2023_LED0_pwm(255);
    //         wait_ms(200);
    //         AW2023_LED0_pwm(180);
    //     } else {
    //         AW2023_LED0_pwm(255);
    //         wait_ms(100);
    //         AW2023_LED0_pwm(0);
    //         AW2023_LED0_RGBBreath();
    //     }
    //     caps_state = led_state.caps_lock;
    // }
    // static uint8_t caps_state = 0;
    // if (caps_state != led_state.caps_lock) {
    //     // led_state.caps_lock ? AW2023_LED0_PWM(255) : AW2023_LED0_PWM(0);
    //     if (led_state.caps_lock) {
    //         AW2023_process_indicator(INDICATOR_ON, 55, 100, 240, T1_2600MS, T3_770MS);
    //     } else {
    //         AW2023_process_indicator(INDICATOR_OFF, 0, 0, 0, T1_UNSET, T3_UNSET);
    //     }
    //     caps_state = led_state.caps_lock;
    // }
    // return led_update_user(led_state);

    // static uint8_t caps_state = 0;
    // if (caps_state != led_state.caps_lock) {
    //     // led_state.caps_lock ? AW2023_LED0_PWM(255) : AW2023_LED0_PWM(0);
    //     if (led_state.caps_lock) {
    //         rgb_indicator_process(INDICATOR_ON, indicator_led_data_color2_phase1, 380, indicator_led_data_color2_phase2);
    //     } else {
    //         rgb_indicator_process(INDICATOR_OFF, indicator_led_data_blank, 0, indicator_led_data_blank);
    //     }
    //     caps_state = led_state.caps_lock;
    // }
    // return led_update_user(led_state);
#ifdef RGB_INDICATOR_ENABLE
    bool res = led_update_user(led_state);
    if (res) {
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        // writePin(B0, !led_state.num_lock);
        // writePin(B1, !led_state.caps_lock);
        // writePin(B2, !led_state.scroll_lock);
        // writePin(B3, !led_state.compose);
        // writePin(B4, !led_state.kana);
        // if (led_state.caps_lock) {
        //     // rgb_indicator_process(INDICATOR_ON, indicator_led_data_color2_phase1, 380, indicator_led_data_color2_phase2);
        //     rgb_indicator_on();
        // } else {
        //     // rgb_indicator_process(INDICATOR_OFF, indicator_led_data_blank, 0, indicator_led_data_blank);
        //     rgb_indicator_off();
        // }
        rgb_indicator_toggle(led_state.caps_lock);
    }
    return res;
#endif
}

void suspend_power_down_kb(void) {
    // code will run multiple times while keyboard is suspended
    // rgb_indicator_off();
}