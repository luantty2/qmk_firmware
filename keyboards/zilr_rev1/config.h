// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// #define DEBUG_MATRIX_SCAN_RATE

// #define RGBLIGHT_ANIMATIONS

// #define RGBLED_NUM 3
// #define RGB_DI_PIN B15
// #define WS2812_SPI SPID2 // default: SPID1
// #define WS2812_SPI_MOSI_PAL_MODE 0 // MOSI pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5
// #define WS2812_SPI_SCK_PIN B13 // Required for F072, may be for others -- SCK pin, see the respective datasheet for the appropriate values for your MCU. default: unspecified
// #define WS2812_SPI_SCK_PAL_MODE 0 // SCK pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6
#define SPI_SCK_PAL_MODE 0
#define SPI_MOSI_PAL_MODE 0
#define SPI_MISO_PAL_MODE 0

#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN B13
#define I2C1_SDA_PIN B14
#define I2C1_SCL_PAL_MODE 5
#define I2C1_SDA_PAL_MODE 5

#define ENCODERS_PAD_A { A8, C1 }
#define ENCODERS_PAD_B { A9, C0 }
#define ENCODER_RESOLUTIONS { 4, 4 }


#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A4
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 4
#define EXTERNAL_EEPROM_BYTE_COUNT 2048 // assuming MB85RS64, should be 2048 for MB85RS16
#define EXTERNAL_EEPROM_PAGE_SIZE 16

/* Set I2C speed to 400kHz, 300ns Tr, 14ns Tf */
// #define I2C1_TIMINGR_PRESC   0x1U
// #define I2C1_TIMINGR_SCLDEL  0x9U
// #define I2C1_TIMINGR_SDADEL  0x0U
// #define I2C1_TIMINGR_SCLH   0x0cU
// #define I2C1_TIMINGR_SCLL   0x22U

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
