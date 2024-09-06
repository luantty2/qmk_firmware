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
#define UART_CTS_PIN A11
#define UART_CTS_PAL_MODE 7
#define UART_RTS_PIN A12
#define UART_RTS_PAL_MODE 7

#define UART_CR3 USART_CR3_RTSE | USART_CR3_CTSE

#define DEBOUNCE 2

// #define ISSI_SCAL_RED 0x96
// #define ISSI_SCAL_GREEN 0xC8

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
