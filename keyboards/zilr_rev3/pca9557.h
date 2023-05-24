// Copyright 2020 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * Init expander and any other dependent drivers
 */
void pca9557_init(uint8_t slave_addr);

/**
 * Configure input/output to a given port
 */
bool pca9557_set_config(uint8_t slave_addr, uint8_t conf);

/**
 * Write high/low to a given port
 */
bool pca9557_set_output(uint8_t slave_addr, uint8_t conf);

/**
 * Read state of a given port
 */
bool pca9557_readPins(uint8_t slave_addr, uint8_t* ret);