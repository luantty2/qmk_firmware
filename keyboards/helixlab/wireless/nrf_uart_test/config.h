// Copyright 2023 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SD1_TX_PIN A9
#define SD1_TX_PAL_MODE 7
#define SD1_RX_PIN A10
#define SD1_RX_PAL_MODE 7
#define SERIAL_USART_DRIVER SD1    // USART driver of TX pin.

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
