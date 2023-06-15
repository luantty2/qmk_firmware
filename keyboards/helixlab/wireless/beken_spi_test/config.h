// Copyright 2023 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN A7
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN A6
#define SPI_MISO_PAL_MODE 5

#define BK3632_SPI_SLAVE_SELECT_PIN A4
#define BK3632_MOT_PIN A3
#define BK3632_SLEEP_PIN A2

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
