// Copyright 2026 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"
#include "blueism_uart_commands.h"

#define BLUEISM_UART_TX_PACKET_MAX_LEN 96
#define BLUEISM_UART_FRAME_HEADER_LEN 2
#define BLUEISM_UART_FRAME_META_LEN 3 // Cmd + Len + CRC
#define BLUEISM_UART_TX_PAYLOAD_MAX_LEN (BLUEISM_UART_TX_PACKET_MAX_LEN - (BLUEISM_UART_FRAME_HEADER_LEN + BLUEISM_UART_FRAME_META_LEN))
#define BLUEISM_UART_RX_PAYLOAD_MAX_LEN BLUEISM_UART_TX_PAYLOAD_MAX_LEN

#define BLUEISM_UART_FRAME_HEADER_BYTE1 0xAA
#define BLUEISM_UART_FRAME_HEADER_BYTE2 0x42
#define BLUEISM_UART_CRC8_POLYNOMIAL 0x07

typedef int8_t blueism_uart_tx_status_t;

#define BLUEISM_UART_TX_OK (0)
#define BLUEISM_UART_TX_FAILED (1)

#if defined(MOUSE_EXTENDED_REPORT)
#    error "MOUSE_EXTENDED_REPORT is not supported by Blueism."
#endif
#if defined(WHEEL_EXTENDED_REPORT)
#    error "WHEEL_EXTENDED_REPORT is not supported by Blueism."
#endif

typedef struct {
    uint8_t mods;
    uint8_t keys[KEYBOARD_REPORT_KEYS];
} __attribute__((packed)) blueism_hid_6kro_payload_t;

typedef struct {
    uint8_t mods;
    uint8_t bits[NKRO_REPORT_BITS];
} __attribute__((packed)) blueism_hid_nkro_payload_t;

typedef struct {
    uint8_t usage_high;
    uint8_t usage_low;
} __attribute__((packed)) blueism_hid_system_ctrl_payload_t;

typedef struct {
    uint8_t usage_high;
    uint8_t usage_low;
} __attribute__((packed)) blueism_hid_consumer_ctrl_payload_t;

typedef struct {
    uint8_t buttons;
    int8_t  wheel;
    uint8_t xy_packed[3];
} __attribute__((packed)) blueism_hid_mouse_payload_t;

blueism_uart_tx_status_t blueism_uart_send_packet(uint8_t cmd, const uint8_t *payload, uint8_t payload_len);
void blueism_init(void);
void housekeeping_task_blueism(void);
void blueism_uart_send_ping(void);
void blueism_uart_send_reset(void);
void blueism_uart_send_get_version(void);
void blueism_uart_select_ble_id(uint8_t id);
void blueism_uart_erase_current_peer(void);
void blueism_uart_select_dongle(void);
