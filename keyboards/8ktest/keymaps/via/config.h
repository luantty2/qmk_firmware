// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// #define FEE_PAGE_BASE_ADDRESS 0x08004000

#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6
#define SPI_DRIVER SPID1

#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A3
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 8
#define EXTERNAL_EEPROM_BYTE_COUNT 2048
#define EXTERNAL_EEPROM_PAGE_SIZE 16


// #define FEE_PAGE_SIZE 0x4000
// #define FEE_PAGE_COUNT 1
// #define FEE_MCU_FLASH_SIZE 512
// #define FEE_FLASH_BASE 0x8000000
// #        define FEE_PAGE_BASE_ADDRESS ((uintptr_t)(FEE_FLASH_BASE) + FEE_MCU_FLASH_SIZE * 1024 - (FEE_PAGE_COUNT * FEE_PAGE_SIZE))
// #define DYNAMIC_KEYMAP_LAYER_COUNT 3
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
