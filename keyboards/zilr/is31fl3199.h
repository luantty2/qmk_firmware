/* Copyright 2021 luantty2
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
#pragma once
#include QMK_KEYBOARD_H

/*Device address*/
#ifndef IS31FL3199_ADDRESS
#    define IS31FL3199_ADDRESS (0x64 << 1)
#endif
/*registers*/
/*The Shutdown Register sets software shutdown mode of IS31FL3199. */
#define SHUTDOWN_REGISTER 0x00
/*The LED Control Registers store the on or off state of each channel LED. */
#define LED_CONTROL_REGISTER_1 0x01
#define LED_CONTROL_REGISTER_2 0x02
/*The Configuration Register 1 sets operation mode. */
#define CONFIGURATION_REGISTER_1 0x03
/*The Configuration Register 2 stores the intensity control settings for all of the LEDs and the control mode. */
#define CONFIGURATION_REGISTER_2 0x04
/*The Ramping Mode Register sets the ramping function. */
#define RAMPING_MODE_REGISTER 0x05
/*The Breathing Mark Register sets the breathing mark function.*/
#define BREATHING_MARK_REGISTER 0x06
/*The PWM Registers can modulate RGB light with 256 different items. */
#define PWM_REGISTER_OUT1 0x07
#define PWM_REGISTER_OUT2 0x08
#define PWM_REGISTER_OUT3 0x09
#define PWM_REGISTER_OUT4 0x0A
#define PWM_REGISTER_OUT5 0x0B
#define PWM_REGISTER_OUT6 0x0C
#define PWM_REGISTER_OUT7 0x0D
#define PWM_REGISTER_OUT8 0x0E
#define PWM_REGISTER_OUT9 0x0F
/*A write operation of “0000 0000” data to the Data Update Register is required to update the registers (01h~02h, 07h~0Fh).*/
#define DATA_UPDATE_REGISTER 0x10
/*The T0 Registers set the T0 time in One Shot Programming Mode. */
#define T0_REGISTER_OUT1 0x11
#define T0_REGISTER_OUT2 0x12
#define T0_REGISTER_OUT3 0x13
#define T0_REGISTER_OUT4 0x14
#define T0_REGISTER_OUT5 0x15
#define T0_REGISTER_OUT6 0x16
#define T0_REGISTER_OUT7 0x17
#define T0_REGISTER_OUT8 0x18
#define T0_REGISTER_OUT9 0x19
/*The T1~T3 Registers set the T1~T3 time in One Shot Programming Mode. */
#define T1_T2_T3_REGISTER_RGB1 0x1A
#define T1_T2_T3_REGISTER_RGB2 0x1B
#define T1_T2_T3_REGISTER_RGB3 0x1C
/*The T4 Registers set the T4 time in One Shot Programming Mode. */
#define T4_REGISTER_OUT1 0x1D
#define T4_REGISTER_OUT2 0x1E
#define T4_REGISTER_OUT3 0x1F
#define T4_REGISTER_OUT4 0x20
#define T4_REGISTER_OUT5 0x21
#define T4_REGISTER_OUT6 0x22
#define T4_REGISTER_OUT7 0x23
#define T4_REGISTER_OUT8 0x24
#define T4_REGISTER_OUT9 0x25
/*A write operation of “0000 0000” data to the Time Update Register is required to update the registers (11h~25h).*/
#define TIME_UPDATE_REGISTER 0x26
/*Once user writes “0000 0000” data to the Reset Register, IS31FL3199 will reset all registers to default value. */
#define RESET_REGISTER 0xFF

/*configuration defines*/
#define RGB1_MODE_PWM 0x00
#define RGB1_MODE_ONESHOT 0x10
#define RGB2_MODE_PWM 0x00
#define RGB2_MODE_ONESHOT 0x20
#define RGB3_MODE_PWM 0x00
#define RGB3_MODE_ONESHOT 0x40

#define CURRENT_20MA 0x00
#define CURRENT_10MA 0x20

#define RGB1_RAMPING_DISABLE 0x00
#define RGB1_RAMPING_ENABLE 0x10
#define RGB2_RAMPING_DISABLE 0x00
#define RGB2_RAMPING_ENABLE 0x20
#define RGB3_RAMPING_DISABLE 0x00
#define RGB3_RAMPING_ENABLE 0x40

#define RGB1_HOLD_T2 0x00
#define RGB1_HOLD_T4 0x01
#define RGB2_HOLD_T2 0x00
#define RGB2_HOLD_T4 0x02
#define RGB3_HOLD_T2 0x00
#define RGB3_HOLD_T4 0x04

/*Timer parameters
 */
/*
              --------
           ╱            ╲
         ╱                ╲
--------                    --------
|  T0  |  T1  |  T2  |  T3  |  T4  |
*/
#define T0_260MS 0b01
#define T0_520MS 0b10001
#define T0_1040MS 0b100001
#define T0_2080MS 0b110001

#define T1_T3_DT_FALSE 0x00
#define T1_T3_DT_TRUE 0x80

#define T1_T3_260MS 0b00
#define T1_T3_520MS 0b01
#define T1_T3_1040MS 0x10
#define T1_T3_2080MS 0x11
#define T1_T3_4160MS 0x100

#define T2_260MS 0b01
#define T2_520MS 0b10
#define T2_1040MS 0b11
#define T2_2080MS 0b100
#define T2_4160MS 0b101

#define T4_260MS 0b01
#define T4_520MS 0b10001
#define T4_1040MS 0b100001
#define T4_2080MS 0b110001

/*other*/
#define RGB1 0x01
#define RGB2 0x02
#define RGB3 0x03

/*Indicator*/
#define INDICATOR_ON true
#define INDICATOR_OFF false
typedef struct indicator_led_data {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t t1;
    uint8_t t3;
} indicator_led_data;

/*I2C correspondence*/
#define IS31FL3199_TIMEOUT 100

void is31fl3199_init(void);
void is31fl3199_reset(void);
void is31fl3199_limit_current(uint8_t current);
void is31fl3199_rgb_timing(uint8_t rgb, uint8_t t0, uint8_t t1_t3, uint8_t t2, uint8_t t4, uint8_t t1_t3_dt);
void is31fl3199_rgb_mode_config(uint8_t rgb, uint8_t mode);
void is31fl3199_rgb_ramping(uint8_t rgb, uint8_t ramping);
void is31fl3199_rgb_ramping_hold(uint8_t rgb, uint8_t hold);
void is31fl3199_rgb_pwm(uint8_t rgb, uint8_t pwm);