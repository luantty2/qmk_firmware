// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// #define DEBUG_MATRIX_SCAN_RATE

#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN B13
#define I2C1_SDA_PIN B14
#define I2C1_SCL_PAL_MODE 5
#define I2C1_SDA_PAL_MODE 5

#define ENCODERS_PAD_A { A8, C0 }
#define ENCODERS_PAD_B { A9, C1 }
#define ENCODER_RESOLUTIONS { 4, 4 }