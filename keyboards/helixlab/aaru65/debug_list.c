// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "debug_list.h"
#include "i2c_master.h"
#include "print.h"

void debug_custom(void) {
    dprintf("[DEVICE INFO]\n");
    dprintf("General\n");
    dprintf("   VID: %s\n", STR(VENDOR_ID));
    dprintf("   PID: %s\n", STR(PRODUCT_ID));
    dprintf("   VER: %s\n", STR(DEVICE_VER));
    dprintf("   Manufacturer: %s\n", STR(MANUFACTURER));
    dprintf("   Product: %s\n", STR(PRODUCT));
    dprintf("Firmware\n");
    dprintf("   QMK Ver: %s\n", STR(QMK_VERSION));
    dprintf("   Build Date: %s\n", STR(QMK_BUILDDATE));
    dprintf("   Keyboard: %s\n", STR(QMK_KEYBOARD));
    dprintf("   Keymap: %s\n", STR(QMK_KEYMAP));
    dprintf("Keyboard\n");
    dprintf("   Polling Rate: %sms\n", STR(USB_POLLING_INTERVAL_MS));
    dprintf("   NKRO: %d\n", keymap_config.nkro);
    dprintf("   Win Lock : %d\n", keymap_config.no_gui);
    dprintf("   Alt_Win Swap : %d\n", keymap_config.swap_lalt_lgui);
    dprintf("   Ctrl_Caps Swap : %d\n", keymap_config.swap_control_capslock);
#ifdef RGB_INDICATOR_ENABLE
    dprintf("RGB Indicator\n");
    dprintf("   RGB Indicator Enable: %d\n", rgb_indicator_config.enable);
    dprintf("   RGB Indicator Selection: %d\n", rgb_indicator_config.select);
    dprintf("   RGB Indicator Mode: %d\n", rgb_indicator_config.mode);
    dprintf("   RGB Indicator HSV: %d %d %d\n", rgb_indicator_config.hsv.h, rgb_indicator_config.hsv.s, rgb_indicator_config.hsv.v);
#endif
#ifdef RGB_MATRIX_ENABLE
    dprintf("RGB Matrix\n");
    dprintf("   RGB Matrix Enable: %d\n", rgb_matrix_is_enabled());
    dprintf("   RGB Matrix Mode: %d\n", rgb_matrix_get_mode());
    dprintf("   RGB Matrix HSV: %d %d %d\n", rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val());
    dprintf("   RGB Matrix Speed: %d\n", rgb_matrix_get_speed());
    dprintf("   RGB Matrix Indicator Only: %d\n", rgb_matrix_get_mode() == 41 ? 1 : 0);
#endif
#ifdef FADER_ENABLE
    dprintf("Fader\n");
    dprintf("   Fader Enable: %d\n", fader_config.enable);
    dprintf("   Fader Reverse: %d\n", fader_config.reverse);
    dprintf("   Fader Channel: %d\n", fader_config.channel);
    dprintf("   Fader CC: %d\n", fader_config.cc);
    dprintf("   Fader Value: %d\n", fader_get_val());
#endif
    dprintf("Driver\n");
#ifdef RGB_INDICATOR_ENABLE
    i2c_status_t i2c_status_aw2023 = i2c_start(AW2023_ADDRESS);
    if (i2c_status_aw2023 == I2C_STATUS_SUCCESS)
        dprintf("   RGB indicator driver is working\n");
    else
        dprintf("   RGB indicator driver is not working\n");
#endif
#ifdef FADER_ENABLE
    i2c_status_t i2c_status_ads1100 = i2c_start(ADS1100_ADDRESS);
    if (i2c_status_ads1100 == I2C_STATUS_SUCCESS)
        dprintf("   ADC driver is working\n");
    else
        dprintf("   ADC driver is not working\n");
#endif
#ifdef RGB_MATRIX_ENABLE
    i2c_status_t i2c_status_is31_1 = i2c_start(DRIVER_ADDR_1);
    if (i2c_status_is31_1 == I2C_STATUS_SUCCESS)
        dprintf("   RGB matrix driver 1 is working\n");
    else
        dprintf("   RGB matrix driver 1 is not working\n");
    i2c_status_t i2c_status_is31_2 = i2c_start(DRIVER_ADDR_2);
    if (i2c_status_is31_2 == I2C_STATUS_SUCCESS)
        dprintf("   RGB matrix driver 2 is working\n");
    else
        dprintf("   RGB matrix driver 2 is not working\n");
#endif
    dprintf("[END]\n");
}