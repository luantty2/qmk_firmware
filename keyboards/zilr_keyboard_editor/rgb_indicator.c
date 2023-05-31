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

#include "rgb_indicator.h"
#include "rgb_indicator_modes.h"
#include "aw2023.h"
#include <lib/lib8tion/lib8tion.h>

static uint32_t rgb_indicator_factory_test_timer = 0;
static bool     rgb_indicator_state              = false;

#if !defined(RGB_INDICATOR_HUE_STEP)
#    define RGB_INDICATOR_HUE_STEP 4
#endif

#if !defined(RGB_INDICATOR_SAT_STEP)
#    define RGB_INDICATOR_SAT_STEP 8
#endif

#if !defined(RGB_INDICATOR_VAL_STEP)
#    define RGB_INDICATOR_VAL_STEP 16
#endif

void rgb_indicator_init(void) {
    aw2023_init();
    // rgb_indicator_config.raw = eeconfig_read_kb();
    // rgb_indicator_select();
    // palSetLineMode(RGB_INDICATOR_TEST_PIN, PAL_MODE_INPUT);
}

// void eeconfig_init_kb(void) {
//     eeconfig_init_rgb_indicator();
// }

void eeconfig_init_rgb_indicator(void) {
    // rgb_indicator_mode(2);
    // rgb_indicator_sethsv(HSV_YELLOW);
    // rgb_indicator_config.enable = true;
    // rgb_indicator_config.select = false;
    // // rgb_indicator_select();
    // // eeconfig_update_kb(rgb_indicator_config.raw);

    // // rgb_indicator_config.mode   = 2;
    // rgb_indicator_mode(6);
    // rgb_indicator_sethsv(HSV_YELLOW);
    // // rgb_indicator_config.hsv.h  = 43;
    // // rgb_indicator_config.hsv.s  = 255;
    // // rgb_indicator_config.hsv.v  = 255;
    // // rgb_indicator_config.raw    = eeconfig_read_kb();
    // eeconfig_update_kb(rgb_indicator_config.raw); // Write default value to EEPROM now
    eeconfig_update_rgb_indicator_default();
}

void eeconfig_update_rgb_indicator(void) {
    eeconfig_update_kb(rgb_indicator_config.raw); // Write default value to EEPROM now
}

void eeconfig_update_rgb_indicator_default(void) {
    dprintf("rgb indicator update default [EEPROM]\n");
    // rgb_indicator_mode(2);
    // rgb_indicator_sethsv(HSV_YELLOW);
    rgb_indicator_config.enable = 1;
    rgb_indicator_config.select = 0;
    rgb_indicator_config.mode   = 6;
    rgb_indicator_config.hsv    = (HSV){HSV_GOLD};
    // rgb_indicator_select();
    // eeconfig_update_kb(rgb_indicator_config.raw);

    // rgb_indicator_config.mode   = 2;

    // rgb_indicator_mode(5);
    // rgb_indicator_sethsv(HSV_GOLD);
    // rgb_indicator_config.hsv.h  = 43;
    // rgb_indicator_config.hsv.s  = 255;
    // rgb_indicator_config.hsv.v  = 255;
    // rgb_indicator_config.raw    = eeconfig_read_kb();
    eeconfig_update_rgb_indicator(); // Write default value to EEPROM now
}

void eeconfig_debug_rgb_indicator(void) {
    dprintf("rgb_indicator_config.enable = %d\n", rgb_indicator_config.enable);
    dprintf("rgb_indicator_config.select = %d\n", rgb_indicator_config.select);
    dprintf("rgb_indicator_config.mode = %d\n", rgb_indicator_config.mode);
    dprintf("rgb_indicator_config.hsv.h = %d\n", rgb_indicator_config.hsv.h);
    dprintf("rgb_indicator_config.hsv.s = %d\n", rgb_indicator_config.hsv.s);
    dprintf("rgb_indicator_config.hsv.v = %d\n", rgb_indicator_config.hsv.v);
}

// void eeconfig_update_rgb_indicator_default(void) {
//     dprintf("eeconfig_update_rgb_matrix_default\n");
//     rgb_indicator_config.enable = 1;
//     rgb_indicator_config.mode   = 2;
//     rgb_indicator_config.hsv.
// }

void rgb_indicator_enable(void) {
    rgb_indicator_config.enable = 1;
    aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
    eeconfig_update_rgb_indicator();
    dprintf("rgb indicator enable [EEPROM]: %u\n", rgb_indicator_config.enable);
}

void rgb_indicator_disable(void) {
    rgb_indicator_config.enable = 0;
    aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
    eeconfig_update_rgb_indicator();
    dprintf("rgb indicator enable [EEPROM]: %u\n", rgb_indicator_config.enable);
}

void rgb_indicator_enable_toggle(void) {
    rgb_indicator_config.enable = !rgb_indicator_config.enable;
    if (rgb_indicator_config.enable)
        rgb_indicator_enable();
    else
        rgb_indicator_disable();
}

void rgb_indicator_factory_test_runner(void) {
    if (!palReadLine(RGB_INDICATOR_TEST_PIN)) {
        // rgb_indicator_factory_test();
        // rgb_indicator_is_testing = true;
        // return true;
        rgb_indicator_factory_test();
    }
    // return false;
}

void rgb_indicator_factory_test(void) {
    uint32_t timer_now = timer_read();
    if (TIMER_DIFF_32(timer_now, rgb_indicator_factory_test_timer) >= 1500) {
        aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
        /*set LED timing*/
        aw2023_LED_timing(LED0, T0_40MS, T1_130MS, T2_40MS, T3_130MS, T4_40MS, REPEAT_ONCE);
        /*enable fade in and out, mode set to manual, maximum current*/
        aw2023_LED_config(LED0, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_PATTERN, LED_CURRENT_MAX);
        /*this is needed*/
        aw2023_LED_pwm(LED0, 0xFF);
        /*set LED timing*/
        // aw2023_LED1_timing(T0_380MS, T1_130MS, T2_40MS, T3_130MS, T4_40MS, REPEAT_ONCE);
        aw2023_LED_timing(LED1, T0_380MS, T1_130MS, T2_40MS, T3_130MS, T4_40MS, REPEAT_ONCE);
        /*enable fade in and out, mode set to manual, maximum current*/
        aw2023_LED_config(LED1, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_PATTERN, LED_CURRENT_MAX);
        /*this is needed*/
        aw2023_LED_pwm(LED1, 0xFF);
        /*set LED timing*/
        aw2023_LED_timing(LED2, T0_770MS, T1_130MS, T2_40MS, T3_130MS, T4_40MS, REPEAT_ONCE);
        /*enable fade in and out, mode set to manual, maximum current*/
        aw2023_LED_config(LED2, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_PATTERN, LED_CURRENT_MAX);
        /*this is needed*/
        aw2023_LED_pwm(LED2, 0xFF);
        /*enable all LEDs*/
        aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
        togglePin(RGB_INDICATOR_SELECT_PIN);
        rgb_indicator_factory_test_timer = timer_now;
        rgb_indicator_state              = true;
    }
}

// // Manually turn indicator on or off
// void rgb_indicator_process(bool hehaviour, indicator_led_data phase1_data, uint16_t wait, indicator_led_data phase2_data) {
//     // Turn indicator on
//     if (hehaviour == INDICATOR_ON) {
//         /*Disable all LEDs*/
//         aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
//         aw2023_LED_pwm(LED0, 0x00);
//         aw2023_LED_pwm(LED1, 0x00);
//         aw2023_LED_pwm(LED2, 0x00);
//         /*Set LED0 timing*/
//         // aw2023_LED0_timing(T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
//         aw2023_LED_timing(LED0, T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         // aw2023_LED0_config(true, true, false, phase1_data.r_led_current);
//         aw2023_LED_config(LED0, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, phase1_data.r_led_current);
//         /*Set LED1 timing*/
//         // aw2023_LED1_timing(T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
//         aw2023_LED_timing(LED1, T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         // aw2023_LED1_config(true, true, false, phase1_data.g_led_current);
//         aw2023_LED_config(LED1, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, phase1_data.g_led_current);
//         /*Set LED2 timing*/
//         // aw2023_LED2_timing(T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
//         aw2023_LED_timing(LED2, T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         // aw2023_LED2_config(true, true, false, phase1_data.b_led_current);
//         aw2023_LED_config(LED2, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, phase1_data.g_led_current);
//         /*Enable all LEDs*/
//         aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
//         aw2023_LED_pwm(LED0, phase1_data.r);
//         aw2023_LED_pwm(LED1, phase1_data.g);
//         aw2023_LED_pwm(LED2, phase1_data.b);
//         // aw2023_LED0_pwm(phase1_data.r);
//         // aw2023_LED1_pwm(phase1_data.g);
//         // aw2023_LED2_pwm(phase1_data.b);
//         // wait_ms(wait);

//         // while (wait--) {
//         //     wait_ms(1);
//         // }
//         // // aw2023_LED0_timing(T0_UNSET, phase2_data.t1, T2_UNSET, phase2_data.t3, T4_UNSET, REPEAT_UNSET);
//         // aw2023_LED_timing(LED0, T0_UNSET, phase2_data.t1, T2_UNSET, phase2_data.t3, T4_UNSET, REPEAT_UNSET);
//         // /*Enable fade in and out, mode set to manual*/
//         // // aw2023_LED0_config(true, true, false, phase2_data.r_led_current);
//         // aw2023_LED_config(LED0, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, phase2_data.r_led_current);
//         // /*Set LED1 timing*/
//         // // aw2023_LED1_timing(T0_UNSET, phase2_data.t1, T2_UNSET, phase2_data.t3, T4_UNSET, REPEAT_UNSET);
//         // aw2023_LED_timing(LED1, T0_UNSET, phase2_data.t1, T2_UNSET, phase2_data.t3, T4_UNSET, REPEAT_UNSET);
//         // /*Enable fade in and out, mode set to manual*/
//         // // aw2023_LED1_config(true, true, false, phase2_data.g_led_current);
//         // aw2023_LED_config(LED1, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, phase2_data.g_led_current);
//         // /*Set LED2 timing*/
//         // // aw2023_LED2_timing(T0_UNSET, phase2_data.t1, T2_UNSET, phase2_data.t3, T4_UNSET, REPEAT_UNSET);
//         // aw2023_LED_timing(LED2, T0_UNSET, phase2_data.t1, T2_UNSET, phase2_data.t3, T4_UNSET, REPEAT_UNSET);
//         // /*Enable fade in and out, mode set to manual*/
//         // // aw2023_LED2_config(true, true, false, phase2_data.b_led_current);
//         // aw2023_LED_config(LED2, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, phase2_data.b_led_current);
//         // aw2023_LED_pwm(LED0, phase2_data.r);
//         // aw2023_LED_pwm(LED1, phase2_data.g);
//         // aw2023_LED_pwm(LED2, phase2_data.b);

//     } else {
//         aw2023_LED_pwm(LED0, 0x00);
//         aw2023_LED_pwm(LED1, 0x00);
//         aw2023_LED_pwm(LED2, 0x00);
//         // aw2023_LED0_pwm(0x00);
//         // aw2023_LED1_pwm(0x00);
//         // aw2023_LED2_pwm(0x00);
//         // aw2023_LED0_RGBBreath();
//     }
// }

void rgb_indicator_on(void) {
    // aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
    // aw2023_LED_pwm(LED0, 0x00);
    // aw2023_LED_pwm(LED1, 0x00);
    // aw2023_LED_pwm(LED2, 0x00);
    // /*Set LED0 timing*/
    // // aw2023_LED0_timing(T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
    // aw2023_LED_timing(LED0, T0_UNSET, T1_UNSET, T2_UNSET, T3_UNSET, T4_UNSET, REPEAT_UNSET);
    // /*Enable fade in and out, mode set to manual*/
    // // aw2023_LED0_config(true, true, false, phase1_data.r_led_current);
    // aw2023_LED_config(LED0, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, LED_CURRENT_MAX);
    // /*Set LED1 timing*/
    // // aw2023_LED1_timing(T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
    // aw2023_LED_timing(LED1, T0_UNSET, T1_UNSET, T2_UNSET, T3_UNSET, T4_UNSET, REPEAT_UNSET);
    // /*Enable fade in and out, mode set to manual*/
    // // aw2023_LED1_config(true, true, false, phase1_data.g_led_current);
    // aw2023_LED_config(LED1, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, LED_CURRENT_MAX);
    // /*Set LED2 timing*/
    // // aw2023_LED2_timing(T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
    // aw2023_LED_timing(LED2, T0_UNSET, T1_UNSET, T2_UNSET, T3_UNSET, T4_UNSET, REPEAT_UNSET);
    // /*Enable fade in and out, mode set to manual*/
    // // aw2023_LED2_config(true, true, false, phase1_data.b_led_current);
    // aw2023_LED_config(LED2, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, LED_CURRENT_MAX);
    // /*Enable all LEDs*/
    // aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
    // rgb_indicator_config.raw = eeconfig_read_kb();
    // RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
    // aw2023_LED_pwm(LED0, rgb.r);
    // aw2023_LED_pwm(LED1, rgb.g);
    // aw2023_LED_pwm(LED2, rgb.b);
    // rgb_indicator_state = true;
    if (rgb_indicator_config.enable) {
        switch (rgb_indicator_config.mode) {
            case 1:
                rgb_indicator_effect_plain(true);
                break;
            case 2:
                rgb_indicator_effect_fade_in(true);
                break;
            case 3:
                rgb_indicator_effect_fade_out(true);
                break;
            case 4:
                rgb_indicator_effect_fade_inout(true);
                break;
            case 5:
                rgb_indicator_effect_gradient(true);
                break;
            case 6:
                // rgb_indicator_effect_blink(true);
                rgb_indicator_effect_random_hue(true);
                break;
            default:
                break;
        }
    } else
        return;
}

void rgb_indicator_off(void) {
    // aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
    // aw2023_LED_pwm(LED0, 0x00);
    // aw2023_LED_pwm(LED1, 0x00);
    // aw2023_LED_pwm(LED2, 0x00);
    // rgb_indicator_state = false;
    if (rgb_indicator_config.enable) {
        switch (rgb_indicator_config.mode) {
            case 1:
                rgb_indicator_effect_plain(false);
                break;
            case 2:
                rgb_indicator_effect_fade_in(false);
                break;
            case 3:
                rgb_indicator_effect_fade_out(false);
                break;
            case 4:
                rgb_indicator_effect_fade_inout(false);
                break;
            case 5:
                rgb_indicator_effect_gradient(false);
                break;
            case 6:
                // rgb_indicator_effect_blink(false);
                rgb_indicator_effect_random_hue(false);
                break;
            default:
                break;
        }
    } else
        return;
}

void rgb_indicator_toggle(bool your_led_state) {
    if (rgb_indicator_config.enable) {
        if (your_led_state) {
            rgb_indicator_on();
        } else {
            rgb_indicator_off();
        }
    } else
        return;
}

void rgb_indicator_select(void) {
    // if (!rgb_indicator_config.enable) {
    //     return;
    // }
    palSetLineMode(RGB_INDICATOR_SELECT_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    if (rgb_indicator_config.select) {
        writePinHigh(RGB_INDICATOR_SELECT_PIN);
    } else {
        writePinLow(RGB_INDICATOR_SELECT_PIN);
    }
    // eeconfig_update_kb(rgb_indicator_config.raw);
    // dprintf("rgb indicator select [EEPROM]: %u\n", rgb_indicator_config.select);
}

void rgb_indicator_select_toggle(void) {
    // if (!rgb_indicator_config.enable) {
    //     return;
    // }
    if (rgb_indicator_config.select) {
        rgb_indicator_config.select = false;
        // writePinLow(RGB_INDICATOR_SELECT_PIN);
        rgb_indicator_select();
    } else {
        rgb_indicator_config.select = true;
        // writePinHigh(RGB_INDICATOR_SELECT_PIN);
        rgb_indicator_select();
    }
    eeconfig_update_rgb_indicator();
    dprintf("rgb indicator select [EEPROM]: %u\n", rgb_indicator_config.select);
}

void rgb_indicator_sethsv(uint16_t hue, uint8_t sat, uint8_t val) {
    // if (!rgb_indicator_config.enable) {
    //     return;
    // }
    if (rgb_indicator_config.enable) {
        rgb_indicator_config.hsv.h = hue;
        rgb_indicator_config.hsv.s = sat;
        rgb_indicator_config.hsv.v = val;
        eeconfig_update_rgb_indicator();
        dprintf("rgb indicator set hsv [EEPROM]: %u,%u,%u\n", rgb_indicator_config.hsv.h, rgb_indicator_config.hsv.s, rgb_indicator_config.hsv.v);
    } else
        return;
}

void rgb_indicator_mode(uint8_t mode) {
    // if (!rgb_indicator_config.enable) {
    //     return;
    // }
    if (rgb_indicator_config.enable) {
        rgb_indicator_config.mode = mode;
        eeconfig_update_rgb_indicator();
        dprintf("rgb indicator mode [EEPROM]: %u\n", rgb_indicator_config.mode);
    } else
        return;
}

void rgb_indicator_step(void) {
    // if (!rgb_indicator_config.enable) {
    //     return;
    // }
    if (rgb_indicator_config.enable) {
        uint8_t mode = rgb_indicator_config.mode + 1;
        if (mode < 1 || mode > RGB_INDICATOR_EFFECT_MAX) {
            rgb_indicator_config.mode = 1;
        } else {
            rgb_indicator_config.mode = mode;
        }
        rgb_indicator_mode(rgb_indicator_config.mode);
    } else
        return;
}

void rgb_indicator_increase_hue(void) {
    if (rgb_indicator_config.enable) {
        rgb_indicator_sethsv(rgb_indicator_config.hsv.h + RGB_INDICATOR_HUE_STEP, rgb_indicator_config.hsv.s, rgb_indicator_config.hsv.v);
        if (rgb_indicator_state) {
            rgb_indicator_config.raw = eeconfig_read_kb();
            RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
            aw2023_LED_pwm(LED0, rgb.r);
            aw2023_LED_pwm(LED1, rgb.g);
            aw2023_LED_pwm(LED2, rgb.b);
        }
    } else
        return;
}

void rgb_indicator_decrease_hue(void) {
    if (rgb_indicator_config.enable) {
        rgb_indicator_sethsv(rgb_indicator_config.hsv.h - RGB_INDICATOR_HUE_STEP, rgb_indicator_config.hsv.s, rgb_indicator_config.hsv.v);
        if (rgb_indicator_state) {
            rgb_indicator_config.raw = eeconfig_read_kb();
            RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
            aw2023_LED_pwm(LED0, rgb.r);
            aw2023_LED_pwm(LED1, rgb.g);
            aw2023_LED_pwm(LED2, rgb.b);
        }
    } else
        return;
}

void rgb_indicator_increase_sat(void) {
    if (rgb_indicator_config.enable) {
        rgb_indicator_sethsv(rgb_indicator_config.hsv.h, qadd8(rgb_indicator_config.hsv.s, RGB_INDICATOR_SAT_STEP), rgb_indicator_config.hsv.v);
        if (rgb_indicator_state) {
            rgb_indicator_config.raw = eeconfig_read_kb();
            RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
            aw2023_LED_pwm(LED0, rgb.r);
            aw2023_LED_pwm(LED1, rgb.g);
            aw2023_LED_pwm(LED2, rgb.b);
        }
    } else
        return;
}

void rgb_indicator_decrease_sat(void) {
    if (rgb_indicator_config.enable) {
        rgb_indicator_sethsv(rgb_indicator_config.hsv.h, qsub8(rgb_indicator_config.hsv.s, RGB_INDICATOR_SAT_STEP), rgb_indicator_config.hsv.v);
        if (rgb_indicator_state) {
            rgb_indicator_config.raw = eeconfig_read_kb();
            RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
            aw2023_LED_pwm(LED0, rgb.r);
            aw2023_LED_pwm(LED1, rgb.g);
            aw2023_LED_pwm(LED2, rgb.b);
        }
    } else
        return;
}

void rgb_indicator_increase_val(void) {
    if (rgb_indicator_config.enable) {
        rgb_indicator_sethsv(rgb_indicator_config.hsv.h, rgb_indicator_config.hsv.s, qadd8(rgb_indicator_config.hsv.v, RGB_INDICATOR_VAL_STEP));
        if (rgb_indicator_state) {
            rgb_indicator_config.raw = eeconfig_read_kb();
            RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
            aw2023_LED_pwm(LED0, rgb.r);
            aw2023_LED_pwm(LED1, rgb.g);
            aw2023_LED_pwm(LED2, rgb.b);
        }
    } else
        return;
}

void rgb_indicator_decrease_val(void) {
    if (rgb_indicator_config.enable) {
        rgb_indicator_sethsv(rgb_indicator_config.hsv.h, rgb_indicator_config.hsv.s, qsub8(rgb_indicator_config.hsv.v, RGB_INDICATOR_VAL_STEP));
        if (rgb_indicator_state) {
            rgb_indicator_config.raw = eeconfig_read_kb();
            RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
            aw2023_LED_pwm(LED0, rgb.r);
            aw2023_LED_pwm(LED1, rgb.g);
            aw2023_LED_pwm(LED2, rgb.b);
        }
    } else
        return;
}

void rgb_indicator_effect_plain(bool state) {
    if (state) {
        aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        aw2023_LED_timing(LED0, T0_UNSET, T1_UNSET, T2_UNSET, T3_UNSET, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED0, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED1, T0_UNSET, T1_UNSET, T2_UNSET, T3_UNSET, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED1, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED2, T0_UNSET, T1_UNSET, T2_UNSET, T3_UNSET, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED2, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        rgb_indicator_config.raw = eeconfig_read_kb();
        RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
        aw2023_LED_pwm(LED0, rgb.r);
        aw2023_LED_pwm(LED1, rgb.g);
        aw2023_LED_pwm(LED2, rgb.b);
        aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
        rgb_indicator_state = true;
    } else {
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        rgb_indicator_state = false;
    }
}

void rgb_indicator_effect_fade_in(bool state) {
    if (state) {
        aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        aw2023_LED_timing(LED0, T0_UNSET, T1_260MS, T2_UNSET, T3_UNSET, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED0, FADEIN_ENABLE, FADEOUT_DISABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED1, T0_UNSET, T1_260MS, T2_UNSET, T3_UNSET, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED1, FADEIN_ENABLE, FADEOUT_DISABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED2, T0_UNSET, T1_260MS, T2_UNSET, T3_UNSET, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED2, FADEIN_ENABLE, FADEOUT_DISABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        rgb_indicator_config.raw = eeconfig_read_kb();
        RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
        aw2023_LED_pwm(LED0, rgb.r);
        aw2023_LED_pwm(LED1, rgb.g);
        aw2023_LED_pwm(LED2, rgb.b);
        aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
        rgb_indicator_state = true;
    } else {
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        rgb_indicator_state = false;
    }
}

void rgb_indicator_effect_fade_out(bool state) {
    if (state) {
        aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        aw2023_LED_timing(LED0, T0_UNSET, T1_UNSET, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED0, FADEIN_DISABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED1, T0_UNSET, T1_UNSET, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED1, FADEIN_DISABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED2, T0_UNSET, T1_UNSET, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED2, FADEIN_DISABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        rgb_indicator_config.raw = eeconfig_read_kb();
        RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
        aw2023_LED_pwm(LED0, rgb.r);
        aw2023_LED_pwm(LED1, rgb.g);
        aw2023_LED_pwm(LED2, rgb.b);
        aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
        rgb_indicator_state = true;
    } else {
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        rgb_indicator_state = false;
    }
}

void rgb_indicator_effect_fade_inout(bool state) {
    if (state) {
        aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        aw2023_LED_timing(LED0, T0_UNSET, T1_130MS, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED0, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED1, T0_UNSET, T1_130MS, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED1, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED2, T0_UNSET, T1_130MS, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED2, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        rgb_indicator_config.raw = eeconfig_read_kb();
        RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
        aw2023_LED_pwm(LED0, rgb.r);
        aw2023_LED_pwm(LED1, rgb.g);
        aw2023_LED_pwm(LED2, rgb.b);
        aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
        rgb_indicator_state = true;
    } else {
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        rgb_indicator_state = false;
    }
}

void rgb_indicator_effect_gradient(bool state) {
    if (state) {
        aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        aw2023_LED_timing(LED0, T0_40MS, T1_1040MS, T2_3100MS, T3_1040MS, T4_40MS, REPEAT_ENDLESS);
        aw2023_LED_config(LED0, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_PATTERN, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED1, T0_40MS, T1_1600MS, T2_3100MS, T3_1040MS, T4_40MS, REPEAT_ENDLESS);
        aw2023_LED_config(LED1, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_PATTERN, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED2, T0_40MS, T1_2100MS, T2_3100MS, T3_1040MS, T4_40MS, REPEAT_ENDLESS);
        aw2023_LED_config(LED2, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_PATTERN, RGB_INDICATOR_GLOBAL_CURRENT);
        rgb_indicator_config.raw = eeconfig_read_kb();
        RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
        aw2023_LED_pwm(LED0, rgb.r);
        aw2023_LED_pwm(LED1, rgb.g);
        aw2023_LED_pwm(LED2, rgb.b);
        aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
        rgb_indicator_state = true;
    } else {
        aw2023_LED_timing(LED0, T0_UNSET, T1_UNSET, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED0, FADEIN_DISABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED1, T0_UNSET, T1_UNSET, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED1, FADEIN_DISABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED2, T0_UNSET, T1_UNSET, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED2, FADEIN_DISABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        rgb_indicator_state = false;
    }
}

// void rgb_indicator_effect_blink(bool state) {
//     if (state) {
//         aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
//         aw2023_LED_pwm(LED0, 0x00);
//         aw2023_LED_pwm(LED1, 0x00);
//         aw2023_LED_pwm(LED2, 0x00);
//         aw2023_LED_timing(LED0, T0_UNSET, T0_510MS, T2_380MS, T3_260MS, T4_260MS, REPEAT_ENDLESS);
//         aw2023_LED_timing(LED1, T0_UNSET, T0_510MS, T2_380MS, T3_260MS, T4_260MS, REPEAT_ENDLESS);
//         aw2023_LED_timing(LED2, T0_UNSET, T0_510MS, T2_380MS, T3_260MS, T4_260MS, REPEAT_ENDLESS);
//         // aw2023_LED_timing_all(T0_130MS, T1_130MS, T2_380MS, T3_380MS, T4_130MS, REPEAT_ENDLESS);
//         aw2023_LED_config(LED0, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_PATTERN, RGB_INDICATOR_GLOBAL_CURRENT);
//         aw2023_LED_config(LED1, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_PATTERN, RGB_INDICATOR_GLOBAL_CURRENT);
//         aw2023_LED_config(LED2, FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_PATTERN, RGB_INDICATOR_GLOBAL_CURRENT);

//         // aw2023_LED_config_all(FADEIN_DISABLE, FADEOUT_DISABLE, LED_MODE_PATTERN, RGB_INDICATOR_GLOBAL_CURRENT);
//         rgb_indicator_config.raw = eeconfig_read_kb();
//         RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
//         aw2023_LED_pwm(LED0, rgb.r);
//         aw2023_LED_pwm(LED1, rgb.g);
//         aw2023_LED_pwm(LED2, rgb.b);
//         // aw2023_LED_pwm_all(rgb.r,rgb.g,rgb.b);
//         aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
//         rgb_indicator_state = true;
//     } else {
//         aw2023_LED_timing(LED0, T0_UNSET, T1_UNSET, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
//         aw2023_LED_config(LED0, FADEIN_DISABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
//         aw2023_LED_timing(LED1, T0_UNSET, T1_UNSET, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
//         aw2023_LED_config(LED1, FADEIN_DISABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
//         aw2023_LED_timing(LED2, T0_UNSET, T1_UNSET, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
//         aw2023_LED_config(LED2, FADEIN_DISABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
//         aw2023_LED_pwm(LED0, 0x00);
//         aw2023_LED_pwm(LED1, 0x00);
//         aw2023_LED_pwm(LED2, 0x00);
//         rgb_indicator_state = false;
//     }
// }

void rgb_indicator_effect_random_hue(bool state) {
    if (state) {
        aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        aw2023_LED_timing(LED0, T0_UNSET, T1_130MS, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED0, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED1, T0_UNSET, T1_130MS, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED1, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        aw2023_LED_timing(LED2, T0_UNSET, T1_130MS, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED2, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        rgb_indicator_config.raw = eeconfig_read_kb();
        HSV random_h             = rgb_indicator_config.hsv;
        // random_h.h               = rand() % 256;
        srand(timer_read32());
        random_h.h = rand() % 256;
        RGB rgb    = hsv_to_rgb(random_h);
        // uint8_t hue = rand() % 256;
        aw2023_LED_pwm(LED0, rgb.r);
        aw2023_LED_pwm(LED1, rgb.g);
        aw2023_LED_pwm(LED2, rgb.b);
        aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
        rgb_indicator_state = true;
    } else {
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_pwm(LED2, 0x00);
        rgb_indicator_state = false;
    }
}

void rgb_indicator_led0_fade_inout(bool state) {
    if (state) {
        // aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
        aw2023_LED_pwm(LED0, 0x00);
        aw2023_LED_timing(LED0, T0_UNSET, T1_130MS, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED0, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        // rgb_indicator_config.raw = eeconfig_read_kb();
        // RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
        aw2023_LED_pwm(LED0, 0xFF);
        aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
        // rgb_indicator_state = true;
    } else {
        aw2023_LED_pwm(LED0, 0x00);
        // aw2023_LED_pwm(LED1, 0x00);
        // aw2023_LED_pwm(LED2, 0x00);
        // rgb_indicator_state = false;
    }
}

void rgb_indicator_led1_fade_inout(bool state) {
    if (state) {
        // aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
        aw2023_LED_pwm(LED1, 0x00);
        aw2023_LED_timing(LED1, T0_UNSET, T1_130MS, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED1, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        // rgb_indicator_config.raw = eeconfig_read_kb();
        // RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
        aw2023_LED_pwm(LED1, 0xFF);
        aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
        // rgb_indicator_state = true;
    } else {
        aw2023_LED_pwm(LED1, 0x00);
        // aw2023_LED_pwm(LED1, 0x00);
        // aw2023_LED_pwm(LED2, 0x00);
        // rgb_indicator_state = false;
    }
}

void rgb_indicator_led2_fade_inout(bool state) {
    if (state) {
        // aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
        aw2023_LED_pwm(LED2, 0x00);
        aw2023_LED_timing(LED2, T0_UNSET, T1_130MS, T2_UNSET, T3_380MS, T4_UNSET, REPEAT_UNSET);
        aw2023_LED_config(LED2, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_MANUAL, RGB_INDICATOR_GLOBAL_CURRENT);
        // rgb_indicator_config.raw = eeconfig_read_kb();
        // RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
        aw2023_LED_pwm(LED2, 0xFF);
        aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
        // rgb_indicator_state = true;
    } else {
        aw2023_LED_pwm(LED2, 0x00);
        // aw2023_LED_pwm(LED1, 0x00);
        // aw2023_LED_pwm(LED2, 0x00);
        // rgb_indicator_state = false;
    }
}

void rgb_indicator_leds_blink(void) {
    // aw2023_LED_switch(LED_OFF, LED_OFF, LED_OFF);
    aw2023_LED_pwm(LED0, 0x00);
    aw2023_LED_pwm(LED1, 0x00);
    aw2023_LED_pwm(LED2, 0x00);
    aw2023_LED_timing(LED0, T0_UNSET, T1_130MS, T2_UNSET, T3_130MS, T4_40MS, REPEAT_TWICE);
    aw2023_LED_timing(LED1, T0_UNSET, T1_130MS, T2_UNSET, T3_130MS, T4_40MS, REPEAT_TWICE);
    aw2023_LED_timing(LED2, T0_UNSET, T1_130MS, T2_UNSET, T3_130MS, T4_40MS, REPEAT_TWICE);
    aw2023_LED_config(LED0, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_PATTERN, RGB_INDICATOR_GLOBAL_CURRENT);
    aw2023_LED_config(LED1, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_PATTERN, RGB_INDICATOR_GLOBAL_CURRENT);
    aw2023_LED_config(LED2, FADEIN_ENABLE, FADEOUT_ENABLE, LED_MODE_PATTERN, RGB_INDICATOR_GLOBAL_CURRENT);
    // rgb_indicator_config.raw = eeconfig_read_kb();
    // RGB rgb                  = hsv_to_rgb(rgb_indicator_config.hsv);
    aw2023_LED_pwm(LED0, 0xFF);
    aw2023_LED_pwm(LED1, 0xFF);
    aw2023_LED_pwm(LED2, 0xFF);
    aw2023_LED_switch(LED_ON, LED_ON, LED_ON);
    // rgb_indicator_state = true;
}