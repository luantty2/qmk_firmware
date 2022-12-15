// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


#define MATRIX_SHIFT_REGISTER_COUNT 2
#define SPI_MATRIX_CHIP_SELECT_PIN A4
#define SPI_MATRIX_DIVISOR 32
#define SHIFTREG_MATRIX_LATCH A2
#define SHIFTREG_MATRIX_CLK A5
// #define SHIFTREG_MATRIX_DATA A6

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
// #define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN A7
// #define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN A6
// #define SPI_MISO_PAL_MODE 5

#define DEBUG_MATRIX_SCAN_RATE
#define FORCE_NKRO

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



// Value to place in RTC backup register 10 for persistent bootloader mode
#define RTC_BOOTLOADER_FLAG 0x424C

// Value to place in RTC backup register 10 for instant reboot mode
#define RTC_BOOTLOADER_JUST_UPLOADED 0x424D
