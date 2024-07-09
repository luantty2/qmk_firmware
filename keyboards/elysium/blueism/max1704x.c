// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "max1704x.h"
#include "i2c_master.h"

void max1704x_init(void) {
    i2c_init();
}

bool max1704x_get_soc(uint8_t *val) {
    i2c_status_t ret = i2c_readReg(MAX1704X_ADDRESS, MAX1704X_SOC_REG, val, 2, MAX1704X_TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("max1704x: failed to get SOC\n");
        return true;
    }
    return false;
}

bool max1704x_soft_reset(void) {
    uint8_t data[2];
    data[0]          = 0x54;
    data[1]          = 0x00;
    i2c_status_t ret = i2c_writeReg(MAX1704X_ADDRESS, MAX1704X_CMD_REG, data, 2, MAX1704X_TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("max1704x: failed to soft reset\n");
        return true;
    }
    return false;
}

bool max1704x_set_vreset(uint8_t vres_val) {
    uint8_t data[2];
    data[0]          = vres_val;
    data[1]          = 0x00;
    i2c_status_t ret = i2c_writeReg(MAX1704X_ADDRESS, MAX1704X_VRESET_REG, data, 2, MAX1704X_TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("max1704x: failed to set vreset\n");
        return true;
    }
    return false;
}

bool max1704x_read_vreset(uint8_t *vres_val) {
    i2c_status_t ret = i2c_readReg(MAX1704X_ADDRESS, MAX1704X_VRESET_REG, vres_val, 2, MAX1704X_TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        dprintf("max1704x: failed to read vreset\n");
        return true;
    }
    return false;
}
