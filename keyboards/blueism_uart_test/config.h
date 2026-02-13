// Copyright 2024 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define UART_DRIVER SD2
#define UART_TX_PIN A2
#define UART_TX_PAL_MODE 7
#define UART_RX_PIN A3
#define UART_RX_PAL_MODE 7
#define UART_CTS_PIN A0
#define UART_CTS_PAL_MODE 7
#define UART_RTS_PIN A1
#define UART_RTS_PAL_MODE 7

#define UART_CR3 USART_CR3_RTSE | USART_CR3_CTSE
