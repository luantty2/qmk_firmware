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

#include "aaru65_h.h"
#include "version.h"
#include "debug_custom.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#    include <lib/lib8tion/lib8tion.h>
#    include "rgb_matrix_effects_custom.h"
#endif
#ifdef FADER_ENABLE
#    include "fader.h"
#endif

#ifdef FADER_ENABLE
extern MidiDevice midi_device;
// static int16_t    midi_cc_value = 0;
#endif
bool fade_has_done=false;

void eeconfig_init_kb(void) {
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
#ifdef FADER_ENABLE
    fader_init();
#endif
    // matrix_init_user();
    // rgb_matrix_fade_in();
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_target_v();
#endif
    wait_ms(100);
}

void matrix_scan_kb(void) {
#ifdef FADER_ENABLE
    // midi_cc_value = fader_read();
    // if (midi_cc_value != ADC_ERROR) midi_send_cc(&midi_device, 0, 7, midi_cc_value);
    fader_run(&midi_device);
#endif
    if(!fade_has_done)
    {
        if(rgb_matrix_fade_in()){
            fade_has_done=true;
        }
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DEVICE_INFO:
            if (record->event.pressed) {
                debug_custom();
            } else {
            }
            break;
#ifdef RGB_MATRIX_ENABLE
            case RGB_MATRIX_INDICATOR_ONLY:
            if (record->event.pressed) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_indicator_only);
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
    }
    return res;
}

void suspend_power_down_kb(void) {
    // code will run multiple times while keyboard is suspended
    // rgb_indicator_off();
}

// const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
//     /*row0*/
//     {0, J_1, K_1, L_1},
//     {0, J_2, K_2, L_2},
//     {0, J_3, K_3, L_3},
//     {0, J_4, K_4, L_4},
//     {0, J_5, K_5, L_5},
//     {0, J_6, K_6, L_6},
//     {0, J_7, K_7, L_7},
//     {0, J_8, K_8, L_8},
//     {0, J_9, K_9, L_9},
//     {0, J_10, K_10, L_10},
//     {0, J_11, K_11, L_11},
//     {0, J_12, K_12, L_12},
//     {0, J_13, K_13, L_13},
//     {0, J_14, K_14, L_14},
//     /*row1*/
//     {0, G_1, H_1, I_1},
//     {0, G_2, H_2, I_2},
//     {0, G_3, H_3, I_3},
//     {0, G_4, H_4, I_4},
//     {0, G_5, H_5, I_5},
//     {0, G_6, H_6, I_6},
//     {0, G_7, H_7, I_7},
//     {0, G_8, H_8, I_8},
//     {0, G_9, H_9, I_9},
//     {0, G_10, H_10, I_10},
//     {0, G_11, H_11, I_11},
//     {0, G_12, H_12, I_12},
//     {0, G_13, H_13, I_13},
//     {0, G_14, H_14, I_14},
//     /*row2*/
//     {0, D_1, E_1, F_1},
//     {0, D_2, E_2, F_2},
//     {0, D_3, E_3, F_3},
//     {0, D_4, E_4, F_4},
//     {0, D_5, E_5, F_5},
//     {0, D_6, E_6, F_6},
//     {0, D_7, E_7, F_7},
//     {0, D_8, E_8, F_8},
//     {0, D_9, E_9, F_9},
//     {0, D_10, E_10, F_10},
//     {0, D_11, E_11, F_11},
//     {0, D_12, E_12, F_12},
//     {0, D_13, E_13, F_13},
//     /*row3*/
//     {0, A_1, B_1, C_1},
//     {0, A_2, B_2, C_2},
//     {0, A_3, B_3, C_3},
//     {0, A_4, B_4, C_4},
//     {0, A_5, B_5, C_5},
//     {0, A_6, B_6, C_6},
//     {0, A_7, B_7, C_7},
//     {0, A_8, B_8, C_8},
//     {0, A_9, B_9, C_9},
//     {0, A_10, B_10, C_10},
//     {0, A_11, B_11, C_11},
//     {0, A_12, B_12, C_12},
//     {0, A_13, B_13, C_13},
//     /*row3*/
//     {1, B_1, A_1, C_1},
//     {1, B_2, A_2, C_2},
//     {1, B_3, A_3, C_3},
//     {1, B_4, A_4, C_4},
//     {1, B_5, A_5, C_5},
//     {1, B_6, A_6, C_6},
//     {1, B_7, A_7, C_7},
//     {1, B_8, A_8, C_8},
//     {1, B_9, A_9, C_9}
// };

// led_config_t g_led_config = {{
//                                 // {0,   1,   2,   3,       4,       5,        6,   7,       8,       9,   10,   11,   12,   13}, 
//                                 // {14,  15,  16,  17,      18,      19,       20,  21,      22,      23,  24,   25,   26,   27},
//                                 // {28,  29,  30,  31,      32,      33,       34,  35,      36,      37,  38,   39,   40,   NO_LED},
//                                 // {41,  42,  43,  44,      45,      46,       47,  48,      49,      50,  51,   52,   53,   NO_LED},
//                                 // {54,  55,  56,  NO_LED,  NO_LED,  NO_LED,   57,  NO_LED,  NO_LED,  58,  59,   60,   61,   62}
//                                 {NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,       NO_LED,        NO_LED,   NO_LED,       NO_LED,       NO_LED,   NO_LED,   NO_LED,   NO_LED, NO_LED  }, 
//                                 {NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,       NO_LED,        NO_LED,   NO_LED,       NO_LED,       NO_LED,   NO_LED,   NO_LED,   NO_LED, NO_LED },
//                                 {NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,       NO_LED,        NO_LED,   NO_LED,       NO_LED,       NO_LED,   NO_LED,   NO_LED,   NO_LED },
//                                 {NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,       NO_LED,        NO_LED,   NO_LED,       NO_LED,       NO_LED,   NO_LED,   NO_LED,   NO_LED},
//                                 {NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,       NO_LED,        NO_LED,   NO_LED,       NO_LED}
// },
//                             {
//                                 {0, 0},  {17, 0},  {34, 0},  {52, 0},  {69, 0},  {86, 0},  {103, 0},  {130, 0},  {138, 0},  {155, 0},  {172, 0},  {189, 0},  {206, 0},  {224, 0}, 
//                                 {0, 16}, {17, 16}, {34, 16}, {52, 16}, {69, 16}, {86, 16}, {103, 16}, {130, 16}, {138, 16}, {155, 16}, {172, 16}, {189, 16}, {206, 16}, {224, 16}, 
//                                 {0, 32}, {17, 32}, {34, 32}, {52, 32}, {69, 32}, {86, 32}, {103, 32}, {130, 32}, {138, 32}, {155, 32}, {172, 32}, {189, 32}, {206, 32}, 
//                                 {0, 48}, {17, 48}, {34, 48}, {52, 48}, {69, 48}, {86, 48}, {103, 48}, {130, 48}, {138, 48}, {155, 48}, {172, 48}, {189, 48}, {206, 48}, 
//                                 {0, 64}, {17, 64}, {34, 64},                               {103, 64},                       {155, 64}, {172, 64}, {189, 64}, {206, 64}, {224, 64}
// },
//                             {
//                                 4,4,4,4,4,4,4,4,4,4,4,4,4,4,
//                                 4,4,4,4,4,4,4,4,4,4,4,4,4,4,
//                                 4,4,4,4,4,4,4,4,4,4,4,4,4,
//                                 1,4,4,4,4,4,4,4,4,4,4,1,4,
//                                 1,1,1,      4,    1 ,1,4,4,4
// }
// };

const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, J_12, K_12, L_12},
    {0, J_10, K_10, L_10},
    {0, J_11, K_11, L_11},
    {0, J_14, K_14, L_14},
    {0, J_15, K_15, L_15},
    {0, J_13, K_13, L_13},
    {0, J_8, K_8, L_8},
    {0, J_7, K_7, L_7},
    {0, J_6, K_6, L_6},
    {0, J_5, K_5, L_5},
    {0, J_4, K_4, L_4},
    {0, J_3, K_3, L_3},
    {0, J_2, K_2, L_2},
    {0, J_1, K_1, L_1},

    {0, G_12, H_12, I_12},
    {0, G_10, H_10, I_10},
    {0, G_11, H_11, I_11},
    {0, G_14, H_14, I_14},
    {0, G_15, H_15, I_15},
    {0, G_13, H_13, I_13},
    {0, G_8, H_8, I_8},
    {0, G_7, H_7, I_7},
    {0, G_6, H_6, I_6},
    {0, G_5, H_5, I_5},
    {0, G_4, H_4, I_4},
    {0, G_3, H_3, I_3},
    {0, G_2, H_2, I_2},
    {0, G_1, H_1, I_1},

    {0, D_12, E_12, F_12},
    {0, D_10, E_10, F_10},
    {0, D_11, E_11, F_11},
    {0, D_14, E_14, F_14},
    {0, D_15, E_15, F_15},
    {0, D_13, E_13, F_13},
    {0, D_8, E_8, F_8},
    {0, D_7, E_7, F_7},
    {0, D_6, E_6, F_6},
    {0, D_5, E_5, F_5},
    {0, D_4, E_4, F_4},
    {0, D_3, E_3, F_3},
    {0, D_2, E_2, F_2},
    // {0, D_1, E_1, F_1},

    {0, A_12, B_12, C_12},
    {0, A_10, B_10, C_10},
    {0, A_11, B_11, C_11},
    {0, A_14, B_14, C_14},
    {0, A_15, B_15, C_15},
    {0, A_13, B_13, C_13},
    {0, A_8, B_8, C_8},
    {0, A_7, B_7, C_7},
    {0, A_6, B_6, C_6},
    {0, A_5, B_5, C_5},
    {0, A_4, B_4, C_4},
    {0, A_3, B_3, C_3},
    {0, A_2, B_2, C_2},
    // {0, A_1, B_1, C_1},

    {1, B_15, A_15, C_15},
    {1, B_14, A_14, C_14},
    {1, B_13, A_13, C_13},
    {1, B_7, A_7, C_7},
    {1, B_9, A_9, C_9},
    {1, B_8, A_8, C_8},
    {1, B_10, A_10, C_10},
    {1, B_11, A_11, C_11},
    {1, B_12, A_12, C_12}







    // {0, J_1, K_1, L_1},
    // {0, J_2, K_2, L_2},
    // {0, J_3, K_3, L_3},
    // {0, J_4, K_4, L_4},
    // {0, J_5, K_5, L_5},
    // {0, J_6, K_6, L_6},
    // {0, J_7, K_7, L_7},
    // {0, J_8, K_8, L_8},
    // {0, J_13, K_13, L_13},
    // {0, J_15, K_15, L_15},
    // {0, J_14, K_14, L_14},
    // {0, J_11, K_11, L_11},
    // {0, J_10, K_10, L_10},
    // {0, J_12, K_12, L_12},

    // {0, G_1, H_1, I_1},
    // {0, G_2, H_2, I_2},
    // {0, G_3, H_3, I_3},
    // {0, G_4, H_4, I_4},
    // {0, G_5, H_5, I_5},
    // {0, G_6, H_6, I_6},
    // {0, G_7, H_7, I_7},
    // {0, G_8, H_8, I_8},
    // {0, G_13, H_13, I_13},
    // {0, G_15, H_15, I_15},
    // {0, G_14, H_14, I_14},
    // {0, G_11, H_11, I_11},
    // {0, G_10, H_10, I_10},
    // {0, G_12, H_12, I_12},    

    // // {0, D_1, E_1, F_1},
    // {0, D_2, E_2, F_2},
    // {0, D_3, E_3, F_3},
    // {0, D_4, E_4, F_4},
    // {0, D_5, E_5, F_5},
    // {0, D_6, E_6, F_6},
    // {0, D_7, E_7, F_7},
    // {0, D_8, E_8, F_8},
    // {0, D_13, E_13, F_13},
    // {0, D_15, E_15, F_15},
    // {0, D_14, E_14, F_14},
    // {0, D_11, E_11, F_11},
    // {0, D_10, E_10, F_10},
    // {0, D_12, E_12, F_12},    

    // // {0, A_1, B_1, C_1},
    // {0, A_2, B_2, C_2},
    // {0, A_3, B_3, C_3},
    // {0, A_4, B_4, C_4},
    // {0, A_5, B_5, C_5},
    // {0, A_6, B_6, C_6},
    // {0, A_7, B_7, C_7},
    // {0, A_8, B_8, C_8},
    // {0, A_13, B_13, C_13},
    // {0, A_15, B_15, C_15},
    // {0, A_14, B_14, C_14},
    // {0, A_11, B_11, C_11},
    // {0, A_10, B_10, C_10},
    // {0, A_12, B_12, C_12},    
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
//   {13,      12,   11,  10,  9,   8,   7,   6,   5,   4,   3,   2,   1,   0},
//   {27,      26,   25,  24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14},
//   {40,   39,  38,  37,  36,  35,  34,  33,  32,  31,  30,  29,  28,NO_LED},
//   {53,   52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,NO_LED}
                                {0,   1,   2,   3,       4,       5,        6,   7,       8,       9,   10,   11,   12,   13}, 
                                {14,  15,  16,  17,      18,      19,       20,  21,      22,      23,  24,   25,   26,   27},
                                {28,  29,  30,  31,      32,      33,       34,  35,      36,      37,  38,   39,   40  ,NO_LED },
                                {41,  42,  43,  44,      45,      46,       47,  48,      49,      50,  51,   52,   53 ,NO_LED  },
                                // {54,  55,  56,  NO_LED,  NO_LED,  NO_LED,   57,  NO_LED,  NO_LED,  58,  59,   60,   61,   62}
                                {54,  55,  56,  NO_LED,  NO_LED,  NO_LED,   57,  NO_LED,  NO_LED,  58,  59,   60,   61,   62}
}, {
  // LED Index to Physical Position
//   {194, 0},  {179, 0},  {164, 0},  {149, 0},  {134, 0},  {119, 0},  {104, 0},  {89, 0},   {74, 0},  {59, 0},  {44, 0},  {29, 0},  {14, 0},  {0, 0},
//   {202, 16}, {187, 16}, {172, 16}, {157, 16}, {142, 16}, {127, 16}, {112, 16}, {97, 16}, {82, 16}, {67, 16}, {52, 16}, {37, 16}, {21, 16}, {6, 16},
//   {190, 32}, {175, 32}, {160, 32}, {145, 32}, {130, 32}, {115, 32}, {100, 32}, {85, 32},  {70, 32}, {55, 32}, {40, 32}, {25, 32}, {10, 32},
//   {209, 48}, {183, 48}, {168, 48}, {153, 48}, {138, 48}, {123, 48}, {108, 48}, {93, 48},  {78, 48}, {63, 48}, {48, 48}, {33, 48}, {18, 48}

                                // {0, 0},  {14, 0},  {29, 0},  {44, 0},  {59, 0},  {74, 0},  {89, 0},  {104, 0},  {119, 0},  {134, 0},  {149, 0},  {164, 0},  {179, 0},  {194, 0}, 
                                // {6, 16}, {32, 16}, {37, 16}, {52, 16}, {67, 16}, {82, 16}, {97, 16}, {112, 16}, {127, 16}, {142, 16}, {157, 16}, {172, 16}, {187, 16}, {202, 16}, 
                                // {10, 32}, {25, 32}, {40, 32}, {55, 32}, {70, 32}, {85, 32}, {100, 32}, {115, 32}, {130, 32}, {145, 32}, {160, 32}, {175, 32}, {190, 32}, 
                                // {18, 48}, {33, 48}, {48, 48}, {63, 48}, {78, 48}, {93, 48}, {108, 48}, {123, 48}, {138, 48}, {153, 48}, {168, 48}, {183, 48}, {209, 48}
                                {0, 0},  {14, 0},  {29, 0},  {44, 0},  {59, 0},  {74, 0},  {89, 0},  {104, 0},  {119, 0},  {134, 0},  {149, 0},  {164, 0},  {179, 0},  {194, 0}, 
                                {7, 16}, {22, 16}, {37, 16}, {52, 16}, {67, 16}, {82, 16}, {97, 16}, {112, 16}, {127, 16}, {142, 16}, {157, 16}, {172, 16}, {187, 16}, {202, 16}, 
                                {10, 32}, {25, 32}, {40, 32}, {55, 32}, {70, 32}, {85, 32}, {100, 32}, {115, 32}, {130, 32}, {145, 32}, {160, 32}, {175, 32}, {190, 32}, 
                                {18, 48}, {33, 48}, {48, 48}, {63, 48}, {78, 48}, {93, 48}, {108, 48}, {123, 48}, {138, 48}, {153, 48}, {168, 48}, {183, 48}, {209, 48},
                                // {12, 48}, {27, 48}, {42, 48}, {57, 48}, {72, 48}, {87, 48}, {102, 48}, {117, 48}, {132, 48}, {147, 48}, {162, 48}, {177, 48}, {206, 48},
                                {1, 64}, {16, 64}, {34, 64}, {92, 64}, {147, 64}, {162, 64}, {194, 64}, {209, 64}, {224, 64}
                                // {10, 48}, {25, 48}, {40, 48}, {55, 48}, {70, 48}, {85, 48}, {100, 48}, {115, 48}, {130, 48}, {145, 48}, {160, 48}, {175, 48}, {190, 48}, 
}, {
  // LED Index to Flag
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  8,4,4,4,4,4,4,4,4,4,4,4,4,
  1,4,4,4,4,4,4,4,4,4,4,1,4,
  1,1,1,4,1,1,4,4,4
} };

// void rgb_matrix_indicators_kb(void) {
//     // rgb_matrix_set_color(50, 0xff, 0xff, 0x00);
//     // if (host_keyboard_led_state().caps_lock) {
//         // rgb_matrix_set_color(28, 255,0,0);
//         // rgb_matrix_set_color(41, 0,0,255);
//         // rgb_matrix_set_color(53, 0,255,0);
//     // }
// }

void rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        // HSV hsv = {.h=rgb_matrix_get_hue(), .s=rgb_matrix_get_sat(), .v=rgb_matrix_get_val()};
        HSV hsv = rgb_matrix_get_hsv();
        // uint8_t mode=rgb_matrix_get_mode();
        RGB rgb;
        // switch (mode)
        // {
        // case 30:
        // case 32:
        //     hsv.h = 255;
        //     hsv.s = 255;
        //     hsv.v = 255;
        //     rgb = hsv_to_rgb(hsv);
        //     RGB_MATRIX_INDICATOR_SET_COLOR(28, rgb.r,rgb.g,rgb.b);
        //     break;
        
        // default:
            hsv.h=qadd8(hsv.h, 64);
            // hsv.s=255;
            rgb = hsv_to_rgb(hsv);
            RGB_MATRIX_INDICATOR_SET_COLOR(28, rgb.r,rgb.g,rgb.b);
            // break;
        // }
        } else {
        // RGB_MATRIX_INDICATOR_SET_COLOR(28, 0, 0, 0);                // rgb_matrix_get_hue
        // HSV hsv = rgb_matrix_get_hsv();
        // RGB rgb = hsv_to_rgb(hsv);
        // RGB_MATRIX_INDICATOR_SET_COLOR(28, rgb.r,rgb.g,rgb.b);
    }
}