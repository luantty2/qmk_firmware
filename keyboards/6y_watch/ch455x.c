// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "ch455x.h"
#include "i2c_master.h"

void ch455x_write(uint8_t reg, uint8_t *data) {
    i2c_status_t status = i2c_write_register(CH455X_ADDRESS, reg, data, 1, CH455X_TIMEOUT);
    if(status!=I2C_STATUS_SUCCESS){
        dprintf("ch455x::failed writing data");
    }
}

void ch455x_init(void) {
    i2c_init();
    uint8_t data = 0b01111001;
    ch455x_write(CH455X_REG_DIG_3, &data);
}
