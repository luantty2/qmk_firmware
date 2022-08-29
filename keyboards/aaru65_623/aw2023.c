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
#include "aw2023.h"
#include "i2c_master.h"

void aw2023_init(void) {
    i2c_init();
    aw2023_reset();
    /*set GCR1.CHIPEN=1 to enable the device*/
    uint8_t config = 0x01;
    i2c_writeReg(AW2023_ADDRESS, GCR1, &config, 1, AW2023_TIMEOUT);
    aw2023_limit_current(IMAX_10MA);
}

void aw2023_reset(void) {
    /*Reset control. Write 0x55 will reset internal logic and register.*/
    uint8_t config = 0x55;
    i2c_writeReg(AW2023_ADDRESS, RSTR, &config, 1, AW2023_TIMEOUT);
}

void aw2023_limit_current(uint8_t current) {
    i2c_writeReg(AW2023_ADDRESS, GCR2, &current, 1, AW2023_TIMEOUT);
}

/*Turn LEDs on or off*/
void aw2023_LED_switch(bool led0_enable, bool led1_enable, bool led2_enable) {
    uint8_t led0_config, led1_config, led2_config, lctr_config;
    led0_config = led0_enable ? LED0_ON : LED0_OFF;
    led1_config = led1_enable ? LED1_ON : LED1_OFF;
    led2_config = led2_enable ? LED2_ON : LED2_OFF;
    lctr_config = led0_config | led1_config | led2_config;
    i2c_writeReg(AW2023_ADDRESS, LCTR, &lctr_config, 1, AW2023_TIMEOUT);
}
/*Set timer parameters for specified LED*/
void aw2023_LED_timing(uint8_t led, uint8_t t0, uint8_t t1, uint8_t t2, uint8_t t3, uint8_t t4, uint8_t repeat) {
    uint8_t led_t0_config = t1 | t2;
    uint8_t led_t1_config = t3 | t4;
    uint8_t led_t2_config = t0 | repeat;
    switch (led) {
        case LED0:
            i2c_writeReg(AW2023_ADDRESS, LED0T0, &led_t0_config, 1, AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED0T1, &led_t1_config, 1, AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED0T2, &led_t2_config, 1, AW2023_TIMEOUT);
            break;
        case LED1:
            i2c_writeReg(AW2023_ADDRESS, LED1T0, &led_t0_config, 1, AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED1T1, &led_t1_config, 1, AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED1T2, &led_t2_config, 1, AW2023_TIMEOUT);
            break;
        case LED2:
            i2c_writeReg(AW2023_ADDRESS, LED2T0, &led_t0_config, 1, AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED2T1, &led_t1_config, 1, AW2023_TIMEOUT);
            i2c_writeReg(AW2023_ADDRESS, LED2T2, &led_t2_config, 1, AW2023_TIMEOUT);
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

/*LED configuration*/
void aw2023_LED_config(uint8_t led, bool fadeOut_enable, bool fadeIn_enable, bool mode, uint8_t current) {
    uint8_t fadeOut_enable_config, fadeIn_enable_config, mode_config, lcfg_config;
    switch (led) {
        case LED0:
            fadeOut_enable_config = (fadeOut_enable == true) ? LED_FADEOUT_ENABLE : LED_FADEOUT_DISABLE;
            fadeIn_enable_config  = (fadeIn_enable == true) ? LED_FADEIN_ENABLE : LED_FADEIN_DISABLE;
            mode_config           = (mode == true) ? LED_MODE_PATTERN : LED_MODE_MANUAL;
            lcfg_config           = fadeOut_enable_config | fadeIn_enable_config | mode_config | current;
            i2c_writeReg(AW2023_ADDRESS, LCFG0, &lcfg_config, 1, AW2023_TIMEOUT);
            break;
        case LED1:
            fadeOut_enable_config = (fadeOut_enable == true) ? LED_FADEOUT_ENABLE : LED_FADEOUT_DISABLE;
            fadeIn_enable_config  = (fadeIn_enable == true) ? LED_FADEIN_ENABLE : LED_FADEIN_DISABLE;
            mode_config           = (mode == true) ? LED_MODE_PATTERN : LED_MODE_MANUAL;
            lcfg_config           = fadeOut_enable_config | fadeIn_enable_config | mode_config | current;
            i2c_writeReg(AW2023_ADDRESS, LCFG1, &lcfg_config, 1, AW2023_TIMEOUT);
            break;
        case LED2:
            fadeOut_enable_config = (fadeOut_enable == true) ? LED_FADEOUT_ENABLE : LED_FADEOUT_DISABLE;
            fadeIn_enable_config  = (fadeIn_enable == true) ? LED_FADEIN_ENABLE : LED_FADEIN_DISABLE;
            mode_config           = (mode == true) ? LED_MODE_PATTERN : LED_MODE_MANUAL;
            lcfg_config           = fadeOut_enable_config | fadeIn_enable_config | mode_config | current;
            i2c_writeReg(AW2023_ADDRESS, LCFG2, &lcfg_config, 1, AW2023_TIMEOUT);
        default:
            break;
    }
}

// void aw2023_LED_config_all(bool fadeOut_enable, bool fadeIn_enable, bool mode, uint8_t current) {
//     uint8_t fadeOut_enable_config, fadeIn_enable_config, mode_config, lcfg_config;
//     fadeOut_enable_config = (fadeOut_enable == true) ? LED_FADEOUT_ENABLE : LED_FADEOUT_DISABLE;
//     fadeIn_enable_config  = (fadeIn_enable == true) ? LED_FADEIN_ENABLE : LED_FADEIN_DISABLE;
//     mode_config           = (mode == true) ? LED_MODE_PATTERN : LED_MODE_MANUAL;
//     lcfg_config           = fadeOut_enable_config | fadeIn_enable_config | mode_config | current;
//     // i2c_writeReg(AW2023_ADDRESS, LCFG0, &lcfg_config, 1, AW2023_TIMEOUT);
//     uint8_t data_set[4];
//     data_set[0] = LCFG0;
//     data_set[1] = lcfg_config;
//     // data_set[2] = LCFG1;
//     data_set[2] = lcfg_config;
//     // data_set[4] = LCFG2;
//     data_set[3] = lcfg_config;
//     i2c_transmit(AW2023_ADDRESS, data_set, 4, AW2023_TIMEOUT);
// }

/*LED PWM configuration*/
void aw2023_LED_pwm(uint8_t led, uint8_t pwm) {
    uint8_t led_pwm_config = pwm;
    switch (led) {
        case LED0:
            i2c_writeReg(AW2023_ADDRESS, PWM0, &led_pwm_config, 1, AW2023_TIMEOUT);
            break;
        case LED1:
            i2c_writeReg(AW2023_ADDRESS, PWM1, &led_pwm_config, 1, AW2023_TIMEOUT);
            break;
        case LED2:
            i2c_writeReg(AW2023_ADDRESS, PWM2, &led_pwm_config, 1, AW2023_TIMEOUT);
            break;
        default:
            break;
    }
}

void aw2023_LED_pwm_all(uint8_t led0_pwm, uint8_t led1_pwm, uint8_t led2_pwm) {
    // uint8_t led_pwm_config = pwm;
        uint8_t data_set[4];
        data_set[0] = PWM0;
        data_set[1] = led0_pwm;
        // data_set[2] = LCFG1;
        data_set[2] = led1_pwm;
        // data_set[4] = LCFG2;
        data_set[3] = led2_pwm;
        i2c_transmit(AW2023_ADDRESS, data_set, 4, AW2023_TIMEOUT);
    // i2c_writeReg(AW2023_ADDRESS, PWM0, &led_pwm_config, 1, AW2023_TIMEOUT);
}

// void aw2023_LED0_pattern(void) {
//     /*disable leds*/
//     aw2023_switch(false, false, false);
//     /*set led0 timing*/
//     aw2023_LED0_timing(T0_1040MS, T1_380MS, T2_510MS, T3_260MS, T4_380MS, REPEAT_ENDLESS);
//     /*enable fade in and out, mode set to manual, minimum current*/
//     aw2023_LED0_config(false, false, true, LED_CURRENT_MIN);
//     /*this is needed*/
//     aw2023_LED0_pwm(0xFF);
//     /*enable led0*/
//     aw2023_switch(true, false, false);
// }

// void aw2023_LED0_manual(void) {
//     /*disable leds*/
//     aw2023_switch(false, false, false);
//     /*set led0 timing*/
//     aw2023_LED0_timing(T0_1040MS, T1_380MS, T2_510MS, T3_260MS, T4_380MS, REPEAT_ENDLESS);
//     /*enable fade in and out, mode set to manual, minimum current*/
//     aw2023_LED0_config(true, true, false, LED_CURRENT_MIN);
//     /*enable led0*/
//     aw2023_switch(true, false, false);
// }

// void aw2023_enter_manual(void) {
//     /*disable leds*/
//     aw2023_switch(false, false, false);

//     aw2023_LED0_pwm(0x00);
//     aw2023_LED1_pwm(0x00);
//     aw2023_LED2_pwm(0x00);

//     /*set led0 timing*/
//     aw2023_LED0_timing(T0_1040MS, T1_380MS, T2_510MS, T3_1040MS, T4_1040MS, REPEAT_ENDLESS);
//     /*enable fade in and out, mode set to manual, minimum current*/
//     aw2023_LED0_config(true, true, false, LED_CURRENT_MIN);
//     /*set led0 timing*/
//     aw2023_LED1_timing(T0_1040MS, T1_380MS, T2_510MS, T3_1040MS, T4_1040MS, REPEAT_ENDLESS);
//     /*enable fade in and out, mode set to manual, minimum current*/
//     aw2023_LED1_config(true, true, false, LED_CURRENT_MIN);
//     /*set led0 timing*/
//     aw2023_LED2_timing(T0_1040MS, T1_380MS, T2_510MS, T3_1040MS, T4_1040MS, REPEAT_ENDLESS);
//     /*enable fade in and out, mode set to manual, minimum current*/
//     aw2023_LED2_config(true, true, false, LED_CURRENT_MIN);

//     /*enable leds*/
//     aw2023_switch(true, true, true);
// }

// // Manually turn indicator on or off
// void aw2023_process_indicator(bool hehaviour, uint8_t r, uint8_t g, uint8_t b, uint8_t t1, uint8_t t3) {
//     // Turn indicator on
//     if (hehaviour == INDICATOR_ON) {
//         /*Disable all LEDs*/
//         aw2023_switch(false, false, false);
//         aw2023_LED0_pwm(0x00);
//         aw2023_LED1_pwm(0x00);
//         AW2023_LED2_pwm(0x00);
//         /*Set LED0 timing*/
//         aw2023_LED0_timing(T0_UNSET, t1, T2_UNSET, t3, T4_UNSET, REPRET_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         aw2023_LED0_config(true, true, false, LED_CURRENT_MIN);
//         /*Set LED1 timing*/
//         aw2023_LED1_timing(T0_UNSET, t1, T2_UNSET, t3, T4_UNSET, REPRET_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         aw2023_LED1_config(true, true, false, LED_CURRENT_MIN);
//         /*Set LED2 timing*/
//         aw2023_LED2_timing(T0_UNSET, t1, T2_UNSET, t3, T4_UNSET, REPRET_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         aw2023_LED2_config(true, true, false, LED_CURRENT_MIN);
//         /*Enable all LEDs*/
//         aw2023_switch(true, true, true);
//         aw2023_LED0_pwm(r);
//         aw2023_LED1_pwm(g);
//         AW2023_LED2_pwm(b);
//     } else {
//         aw2023_LED0_pwm(0x00);
//         aw2023_LED1_pwm(0x00);
//         AW2023_LED2_pwm(0x00);
//         aw2023_LED0_RGBBreath();
//     }
// }
// Manually turn indicator on or off
// void aw2023_process_indicator(bool hehaviour, indicator_led_data phase1_data, uint16_t wait, indicator_led_data phase2_data) {
//     // Turn indicator on
//     if (hehaviour == INDICATOR_ON) {
//         /*Disable all LEDs*/
//         aw2023_switch(false, false, false);
//         aw2023_LED0_pwm(0x00);
//         aw2023_LED1_pwm(0x00);
//         aw2023_LED2_pwm(0x00);
//         /*Set LED0 timing*/
//         aw2023_LED0_timing(T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         aw2023_LED0_config(true, true, false, phase1_data.r_led_current);
//         /*Set LED1 timing*/
//         aw2023_LED1_timing(T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         aw2023_LED1_config(true, true, false, phase1_data.g_led_current);
//         /*Set LED2 timing*/
//         aw2023_LED2_timing(T0_UNSET, phase1_data.t1, T2_UNSET, phase1_data.t3, T4_UNSET, REPEAT_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         aw2023_LED2_config(true, true, false, phase1_data.b_led_current);
//         /*Enable all LEDs*/
//         aw2023_switch(true, true, true);
//         aw2023_LED0_pwm(phase1_data.r);
//         aw2023_LED1_pwm(phase1_data.g);
//         aw2023_LED2_pwm(phase1_data.b);
//         // wait_ms(wait);
//         while (wait--) {
//             wait_ms(1);
//         }
//         aw2023_LED0_timing(T0_UNSET, phase2_data.t1, T2_UNSET, phase2_data.t3, T4_UNSET, REPEAT_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         aw2023_LED0_config(true, true, false, phase2_data.r_led_current);
//         /*Set LED1 timing*/
//         aw2023_LED1_timing(T0_UNSET, phase2_data.t1, T2_UNSET, phase2_data.t3, T4_UNSET, REPEAT_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         aw2023_LED1_config(true, true, false, phase2_data.g_led_current);
//         /*Set LED2 timing*/
//         aw2023_LED2_timing(T0_UNSET, phase2_data.t1, T2_UNSET, phase2_data.t3, T4_UNSET, REPEAT_UNSET);
//         /*Enable fade in and out, mode set to manual*/
//         aw2023_LED2_config(true, true, false, phase2_data.b_led_current);
//         aw2023_LED0_pwm(phase2_data.r);
//         aw2023_LED1_pwm(phase2_data.g);
//         aw2023_LED2_pwm(phase2_data.b);

//     } else {
//         aw2023_LED0_pwm(0x00);
//         aw2023_LED1_pwm(0x00);
//         aw2023_LED2_pwm(0x00);
//         aw2023_LED0_RGBBreath();
//     }
// }

// void aw2023_LED0_RGBBreath(void) {
//     /*disable leds*/
//     aw2023_switch(false, false, false);

//     ///*faster*/
//     // /*set led0 timing*/
//     // aw2023_LED0_timing(T0_2100MS, T1_1040MS, T2_40MS, T3_1040MS, T4_1040MS, REPRET_ENDLESS);
//     // /*enable fade in and out, mode set to manual, minimum current*/
//     // aw2023_LED0_config(false, false, true, LED_CURRENT_MIN);
//     // /*this is needed*/
//     // aw2023_LED0_pwm(0xC8);

//     // /*set led1 timing*/
//     // aw2023_LED1_timing(T0_40MS, T1_1040MS, T2_40MS, T3_1040MS, T4_1040MS, REPRET_ENDLESS);
//     // /*enable fade in and out, mode set to manual, minimum current*/
//     // aw2023_LED1_config(false, false, true, LED_CURRENT_MIN);
//     // /*this is needed*/
//     // aw2023_LED1_pwm(0xC8);

//     // /*set led2 timing*/
//     // aw2023_LED2_timing(T0_1040MS, T1_1040MS, T2_40MS, T3_1040MS, T4_1040MS, REPRET_ENDLESS);
//     // /*enable fade in and out, mode set to manual, minimum current*/
//     // aw2023_LED2_config(false, false, true, LED_CURRENT_MIN);
//     // /*this is needed*/
//     // AW2023_LED2_pwm(0xC8);

//     /*slower*/
//     /*set led0 timing*/
//     aw2023_LED0_timing(T0_6200MS, T1_3100MS, T2_40MS, T3_3100MS, T4_3100MS, REPEAT_ENDLESS);
//     /*enable fade in and out, mode set to manual, minimum current*/
//     aw2023_LED0_config(false, false, true, LED_CURRENT_11);
//     /*this is needed*/
//     aw2023_LED0_pwm(0xC8);

//     /*set led1 timing*/
//     aw2023_LED1_timing(T0_40MS, T1_3100MS, T2_40MS, T3_3100MS, T4_3100MS, REPEAT_ENDLESS);
//     /*enable fade in and out, mode set to manual, minimum current*/
//     aw2023_LED1_config(false, false, true, LED_CURRENT_MIN);
//     /*this is needed*/
//     aw2023_LED1_pwm(0xC8);

//     /*set led2 timing*/
//     aw2023_LED2_timing(T0_3100MS, T1_3100MS, T2_40MS, T3_3100MS, T4_3100MS, REPEAT_ENDLESS);
//     /*enable fade in and out, mode set to manual, minimum current*/
//     aw2023_LED2_config(false, false, true, LED_CURRENT_7);
//     /*this is needed*/
//     aw2023_LED2_pwm(0xC8);

//     /*enable led*/
//     aw2023_switch(true, true, true);
// }