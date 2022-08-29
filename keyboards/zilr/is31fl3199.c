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
#include "is31fl3199.h"
#include "i2c_master.h"

void is31fl3199_init(void) {
    i2c_init();
    is31fl3199_limit_current(CURRENT_10MA);
}

void is31fl3199_reset(void) {
    uint8_t config = 0x00;
    i2c_writeReg(IS31FL3199_ADDRESS, RESET_REGISTER, &config, 1, IS31FL3199_TIMEOUT);
}

void is31fl3199_limit_current(uint8_t current) {
    i2c_writeReg(IS31FL3199_ADDRESS, CONFIGURATION_REGISTER_2, &current, 1, IS31FL3199_TIMEOUT);
}

// /*Turn LEDs on or off*/
// void aw2023_LED_switch(bool led0_enable, bool led1_enable, bool led2_enable) {
//     uint8_t led0_config, led1_config, led2_config, lctr_config;
//     led0_config = led0_enable ? LED0_ON : LED0_OFF;
//     led1_config = led1_enable ? LED1_ON : LED1_OFF;
//     led2_config = led2_enable ? LED2_ON : LED2_OFF;
//     lctr_config = led0_config | led1_config | led2_config;
//     i2c_writeReg(AW2023_ADDRESS, LCTR, &lctr_config, 1, AW2023_TIMEOUT);
// }

/*Set timer parameters for specified LED*/
void is31fl3199_rgb_timing(uint8_t rgb, uint8_t t0, uint8_t t1_t3, uint8_t t2, uint8_t t4, uint8_t t1_t3_dt) {
    uint8_t t1_t2_t3_config = t1_t3 | t2 | t1_t3_dt;
    switch (rgb) {
        case RGB1:
            i2c_writeReg(IS31FL3199_ADDRESS, T0_REGISTER_OUT1, &t0, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T0_REGISTER_OUT2, &t0, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T0_REGISTER_OUT3, &t0, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T1_T2_T3_REGISTER_RGB1, &t1_t2_t3_config, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T4_REGISTER_OUT1, &t4, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T4_REGISTER_OUT2, &t4, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T4_REGISTER_OUT3, &t4, 1, IS31FL3199_TIMEOUT);
            break;
        case RGB2:
            i2c_writeReg(IS31FL3199_ADDRESS, T0_REGISTER_OUT4, &t0, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T0_REGISTER_OUT5, &t0, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T0_REGISTER_OUT6, &t0, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T1_T2_T3_REGISTER_RGB2, &t1_t2_t3_config, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T4_REGISTER_OUT4, &t4, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T4_REGISTER_OUT5, &t4, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T4_REGISTER_OUT6, &t4, 1, IS31FL3199_TIMEOUT);
            break;
        case RGB3:
            i2c_writeReg(IS31FL3199_ADDRESS, T0_REGISTER_OUT7, &t0, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T0_REGISTER_OUT8, &t0, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T0_REGISTER_OUT9, &t0, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T1_T2_T3_REGISTER_RGB3, &t1_t2_t3_config, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T4_REGISTER_OUT7, &t4, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T4_REGISTER_OUT8, &t4, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, T4_REGISTER_OUT9, &t4, 1, IS31FL3199_TIMEOUT);
            break;
        default:
            break;
    }
}

// void aw2023_LED_timing_all(uint8_t t0, uint8_t t1, uint8_t t2, uint8_t t3, uint8_t t4, uint8_t repeat) {
//     uint8_t led_t0_config = t1 | t2;
//     uint8_t led_t1_config = t3 | t4;
//     uint8_t led_t2_config = t0 | repeat;
//     // i2c_writeReg(AW2023_ADDRESS, LED0T0, &led_t0_config, 1, AW2023_TIMEOUT);
//     // i2c_writeReg(AW2023_ADDRESS, LED0T1, &led_t1_config, 1, AW2023_TIMEOUT);
//     // i2c_writeReg(AW2023_ADDRESS, LED0T2, &led_t2_config, 1, AW2023_TIMEOUT);
//     uint8_t data_set[10];
//     data_set[0] = LED0T0;
//     data_set[1] = led_t0_config;
//     // data_set[2] = LED0T1;
//     data_set[2] = led_t1_config;
//     // data_set[4] = LED0T2;
//     data_set[3] = led_t2_config;

//     // data_set[6]  = LED1T0;
//     data_set[4]  = led_t0_config;
//     // data_set[8]  = LED1T1;
//     data_set[5]  = led_t1_config;
//     // data_set[10] = LED1T2;
//     data_set[6] = led_t2_config;

//     // data_set[12] = LED2T0;
//     data_set[7] = led_t0_config;
//     // data_set[14] = LED2T1;
//     data_set[8] = led_t1_config;
//     // data_set[16] = LED2T2;
//     data_set[9] = led_t2_config;
//     i2c_transmit(AW2023_ADDRESS, data_set, 10, AW2023_TIMEOUT);
// }

// void is31fl3199_rgb_ramp(uint8_t rgb, uint8_t t0, uint8_t t1_t3, uint8_t t2, uint8_t t4, bool t1_t3_dt) {
void is31fl3199_rgb_mode_config(uint8_t rgb, uint8_t mode) {
    switch (rgb) {
        case RGB1:
            i2c_writeReg(IS31FL3199_ADDRESS, CONFIGURATION_REGISTER_1, &mode, 1, IS31FL3199_TIMEOUT);
            break;
        case RGB2:
            i2c_writeReg(IS31FL3199_ADDRESS, CONFIGURATION_REGISTER_1, &mode, 1, IS31FL3199_TIMEOUT);
            break;
        case RGB3:
            i2c_writeReg(IS31FL3199_ADDRESS, CONFIGURATION_REGISTER_1, &mode, 1, IS31FL3199_TIMEOUT);
            break;
        default:
            break;
    }
}

void is31fl3199_rgb_ramping(uint8_t rgb, uint8_t ramping) {
    switch (rgb) {
        case RGB1:
            i2c_writeReg(IS31FL3199_ADDRESS, RAMPING_MODE_REGISTER, &ramping, 1, IS31FL3199_TIMEOUT);
            break;
        case RGB2:
            i2c_writeReg(IS31FL3199_ADDRESS, RAMPING_MODE_REGISTER, &ramping, 1, IS31FL3199_TIMEOUT);
            break;
        case RGB3:
            i2c_writeReg(IS31FL3199_ADDRESS, RAMPING_MODE_REGISTER, &ramping, 1, IS31FL3199_TIMEOUT);
            break;
        default:
            break;
    }
}

void is31fl3199_rgb_ramping_hold(uint8_t rgb, uint8_t hold) {
    uint8_t config;
    switch (rgb) {
        case RGB1:
            config = RGB1_RAMPING_ENABLE | hold;
            i2c_writeReg(IS31FL3199_ADDRESS, RAMPING_MODE_REGISTER, &config, 1, IS31FL3199_TIMEOUT);
            break;
        case RGB2:
            config = RGB2_RAMPING_ENABLE | hold;
            i2c_writeReg(IS31FL3199_ADDRESS, RAMPING_MODE_REGISTER, &config, 1, IS31FL3199_TIMEOUT);
            break;
        case RGB3:
            config = RGB2_RAMPING_ENABLE | hold;
            i2c_writeReg(IS31FL3199_ADDRESS, RAMPING_MODE_REGISTER, &config, 1, IS31FL3199_TIMEOUT);
            break;
        default:
            break;
    }
}

void is31fl3199_rgb_pwm(uint8_t rgb, uint8_t pwm) {
    switch (rgb) {
        case RGB1:
            i2c_writeReg(IS31FL3199_ADDRESS, PWM_REGISTER_OUT1, &pwm, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, PWM_REGISTER_OUT2, &pwm, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, PWM_REGISTER_OUT3, &pwm, 1, IS31FL3199_TIMEOUT);
            break;
        case RGB2:
            i2c_writeReg(IS31FL3199_ADDRESS, PWM_REGISTER_OUT4, &pwm, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, PWM_REGISTER_OUT5, &pwm, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, PWM_REGISTER_OUT6, &pwm, 1, IS31FL3199_TIMEOUT);
            break;
        case RGB3:
            i2c_writeReg(IS31FL3199_ADDRESS, PWM_REGISTER_OUT7, &pwm, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, PWM_REGISTER_OUT8, &pwm, 1, IS31FL3199_TIMEOUT);
            i2c_writeReg(IS31FL3199_ADDRESS, PWM_REGISTER_OUT9, &pwm, 1, IS31FL3199_TIMEOUT);
            break;
        default:
            break;
    }
}