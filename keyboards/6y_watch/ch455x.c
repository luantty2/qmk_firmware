// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "ch455x.h"
#include "i2c_master.h"

void ch455x_write(uint8_t reg, uint8_t *data) {
    i2c_status_t status = i2c_transmit(reg, data, 1, CH455X_TIMEOUT);
    if (status != I2C_STATUS_SUCCESS) {
        dprintf("ch455x::failed writing data\n");
    }
}

void ch455x_sleep(void) {
    uint8_t data = 0b00010100;
    ch455x_write(CH455X_REG_CMD, &data);
}

void ch455x_wakeup(void) {
    uint8_t data = 0b00010001;
    ch455x_write(CH455X_REG_CMD, &data);
}

void ch455x_init(void) {
    i2c_init();
    ch455x_wakeup();
}
