// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "max1704x.h"
#include "i2c_master.h"

void max1704x_init(void) {
    i2c_init();
}

void max1704x_reset(void) {}

bool max1704x_get_soc(uint8_t *val) {
    // i2c_status_t ret = i2c_receive(MAX1704X_ADDRESS, val, 2, MAX1704X_TIMEOUT);
    i2c_status_t ret = i2c_readReg(MAX1704X_ADDRESS, MAX1704X_SOC_REG, val, 2, MAX1704X_TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("max1704x: failed to get SOC\n");
        return true;
    }
    return false;
}
