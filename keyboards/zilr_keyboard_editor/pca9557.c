// Copyright 2020 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "i2c_master.h"
#include "pca9557.h"
#include "debug.h"

#define TIMEOUT 100

enum {
    CMD_INPUT = 0,
    CMD_OUTPUT,
    CMD_INVERSION,
    CMD_CONFIG,
};

void pca9557_init(uint8_t slave_addr) {
    static uint8_t s_init = 0;
    if (!s_init) {
        i2c_init();
        s_init = 1;
    }
}

bool pca9557_set_config(uint8_t slave_addr, uint8_t conf) {
    i2c_status_t ret = i2c_writeReg(slave_addr, CMD_CONFIG, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9557_set_config::FAILED\n");
        return false;
    }

    return true;
}

bool pca9557_set_output(uint8_t slave_addr, uint8_t conf) {
    i2c_status_t ret = i2c_writeReg(slave_addr, CMD_OUTPUT, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9557_set_output::FAILED\n");
        return false;
    }

    return true;
}

bool pca9557_readPins(uint8_t slave_addr, uint8_t* out) {
    i2c_status_t ret = i2c_readReg(slave_addr, CMD_INPUT, out, sizeof(uint8_t), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9557_readPins::FAILED\n");
        return false;
    }

    return true;
}