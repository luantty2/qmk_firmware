// Copyright 2024 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN A9
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PIN A10
#define I2C1_SDA_PAL_MODE 4

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
