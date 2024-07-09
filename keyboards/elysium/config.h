// Copyright 2024 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// #define SD1_TX_PIN A9
// #define SD1_TX_PAL_MODE 7
// #define SD1_RX_PIN A10
// #define SD1_RX_PAL_MODE 7
// #define SERIAL_USART_DRIVER SD1

#define UART_DRIVER SD1
#define UART_TX_PIN A9
#define UART_TX_PAL_MODE 7
#define UART_RX_PIN A10
#define UART_RX_PAL_MODE 7

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B6
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PIN B7
#define I2C1_SDA_PAL_MODE 4

#define IS31FL3733_I2C_ADDRESS_1 IS31FL3733_I2C_ADDRESS_GND_GND
#define IS31FL3733_I2C_ADDRESS_2 IS31FL3733_I2C_ADDRESS_GND_SCL
#define DRIVER_SYNC_1 0b01
#define DRIVER_SYNC_2 0b10

#define RGB_MATRIX_DEFAULT_SPD 64
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

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
