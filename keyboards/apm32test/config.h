// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x8888
#define DEVICE_VER 0x0001
#define MANUFACTURER luantty2
#define PRODUCT apm32test

// key matrix size
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

// key matrix pins
#define MATRIX_ROW_PINS { B15 }
#define MATRIX_COL_PINS { B14 }
#define UNUSED_PINS

// COL2ROW or ROW2COL
#define DIODE_DIRECTION COL2ROW
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
