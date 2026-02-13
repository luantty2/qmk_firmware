// Copyright 2024 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "bluetooth.h"
#include "outputselect.h"
#include "uart.h"

#define BLUEISM_UART_PACKET_MAX_LEN 96
#define BLUEISM_UART_HEADER_LEN 2
#define BLUEISM_UART_META_LEN 3 // Cmd + Len + CRC
#define BLUEISM_UART_PAYLOAD_MAX_LEN (BLUEISM_UART_PACKET_MAX_LEN - (BLUEISM_UART_HEADER_LEN + BLUEISM_UART_META_LEN))

typedef int8_t blueism_send_status_t;

#define BLUEISM_SEND_STATUS_SUCCESS (0)
#define BLUEISM_SEND_STATUS_FAILED (1)

#define CMD_REPORT_HID_6KRO 0x31
#define CMD_REPORT_HID_NKRO 0x32
#define CMD_REPORT_HID_CONSUMER_CTRL 0x33
#define CMD_REPORT_HID_SYSTEM_CTRL 0x34
#define CMD_REPORT_HID_MOUSE 0x35
#define CMD_BLE_CTRL 0x21
#define SUBCMD_BLE_CTRL_SELECT_ID   0
#define SUBCMD_BLE_CTRL_ERASE_BOND  1

#define WAKEUP_PIN A4
#define SLEEPING_STATE_DETECT_PIN A5

#define CAPS_LED_CALLBACK_PIN A7
#define CAPS_LED_PIN C13

typedef struct {
    uint8_t mods;
    uint8_t keys[KEYBOARD_REPORT_KEYS];
} __attribute__((packed)) blueism_report_keyboard_t;

typedef struct {
    uint8_t mods;
    uint8_t bits[NKRO_REPORT_BITS];
} __attribute__((packed)) blueism_report_nkro_keyboard_t;

typedef struct {
    uint8_t usage_high;
    uint8_t usage_low;
} __attribute__((packed)) blueism_report_system_ctrl_t;

typedef struct {
    uint8_t usage_high;
    uint8_t usage_low;
} __attribute__((packed)) blueism_report_consumer_ctrl_t;

typedef struct {
    uint8_t buttons;
    int8_t  wheel;
    uint8_t xy_packed[3];
} __attribute__((packed)) blueism_report_mouse_t;
#if defined(MOUSE_EXTENDED_REPORT)
#    error "MOUSE_EXTENDED_REPORT is not supported by Blueism."
#endif
#if defined(WHEEL_EXTENDED_REPORT)
#    error "WHEEL_EXTENDED_REPORT is not supported by Blueism."
#endif

static blueism_report_keyboard_t      blueism_report_keyboard;
static blueism_report_nkro_keyboard_t blueism_report_nkro_keyboard;
static blueism_report_system_ctrl_t   blueism_report_system_ctrl;
static blueism_report_consumer_ctrl_t blueism_report_consumer_ctrl;
static blueism_report_mouse_t         blueism_report_mouse;

void palCallback_caps_detected(void *arg) {
    gpio_write_pin(CAPS_LED_PIN, gpio_read_pin(CAPS_LED_CALLBACK_PIN) ? 0 : 1);
}

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    set_output(OUTPUT_BLUETOOTH);

    palSetLineMode(UART_CTS_PIN, PAL_MODE_ALTERNATE(UART_CTS_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
    palSetLineMode(UART_RTS_PIN, PAL_MODE_ALTERNATE(UART_RTS_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
    uart_init(460800);
    gpio_set_pin_input(WAKEUP_PIN); // High-Z
    gpio_set_pin_input_low(SLEEPING_STATE_DETECT_PIN);

    // Caps LED Sync
    gpio_set_pin_input(CAPS_LED_CALLBACK_PIN);
    gpio_set_pin_output(CAPS_LED_PIN);
    gpio_write_pin_high(CAPS_LED_PIN);
    palEnableLineEvent(CAPS_LED_CALLBACK_PIN, PAL_EVENT_MODE_BOTH_EDGES);
    palSetLineCallback(CAPS_LED_CALLBACK_PIN, palCallback_caps_detected, NULL);

    keyboard_post_init_user();
}

#define UART_HEADER_BYTE1 0xAA
#define UART_HEADER_BYTE2 0x42
#define CRC8_POLYNOMIAL 0x07

static uint8_t crc8_byte_update(uint8_t crc, uint8_t data_byte) {
    crc ^= data_byte;
    for (int i = 0; i < 8; i++) {
        if ((crc & 0x80) != 0) {
            crc = (crc << 1) ^ CRC8_POLYNOMIAL;
        } else {
            crc <<= 1;
        }
    }
    return crc;
}

blueism_send_status_t blueism_send_cmd(uint8_t cmd, uint8_t *payload, uint8_t payload_len) {
    if (payload_len > BLUEISM_UART_PAYLOAD_MAX_LEN) {
        dprintf("Invalid payload length: %d\n", payload_len);
        return -BLUEISM_SEND_STATUS_FAILED;
    }

    uint8_t packet[BLUEISM_UART_PACKET_MAX_LEN];
    uint8_t idx = 0;

    packet[idx++] = UART_HEADER_BYTE1;
    packet[idx++] = UART_HEADER_BYTE2;
    packet[idx++] = cmd;
    packet[idx++] = payload_len;

    if (payload_len > 0 && payload) {
        memcpy(&packet[idx], payload, payload_len);
        idx += payload_len;
    }

    uint8_t crc = 0;
    crc         = crc8_byte_update(crc, cmd);
    crc         = crc8_byte_update(crc, payload_len);
    for (int i = 0; i < payload_len; i++) {
        crc = crc8_byte_update(crc, payload[i]);
    }

    packet[idx++] = crc;

    for (uint8_t i = 0; i < idx; i++) {
        dprintf("%02x ", packet[i]);
    }
    dprintf("\n");

    if (gpio_read_pin(SLEEPING_STATE_DETECT_PIN) == 0) {
        gpio_set_pin_output_open_drain(WAKEUP_PIN);
        gpio_write_pin_low(WAKEUP_PIN);
        wait_ms(1);
        gpio_set_pin_input(WAKEUP_PIN); // Back to High-Z
        wait_ms(50);
    }

    uart_transmit(packet, idx);
    return BLUEISM_SEND_STATUS_SUCCESS;
}

void blueism_send_keyboard(report_keyboard_t *report) {
    blueism_report_keyboard.mods = report->mods;
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        blueism_report_keyboard.keys[i] = report->keys[i];
    }

    blueism_send_status_t ret = blueism_send_cmd(CMD_REPORT_HID_6KRO, (uint8_t *)&blueism_report_keyboard, sizeof(blueism_report_keyboard_t));
    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send keyboard report\n");
    }
}

void blueism_send_nkro(report_nkro_t *report) {
    blueism_report_nkro_keyboard.mods = report->mods;
    for (uint8_t i = 0; i < NKRO_REPORT_BITS; i++) {
        blueism_report_nkro_keyboard.bits[i] = report->bits[i];
    }

    blueism_send_status_t ret = blueism_send_cmd(CMD_REPORT_HID_NKRO, (uint8_t *)&blueism_report_nkro_keyboard, sizeof(blueism_report_nkro_keyboard_t));
    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send NKRO keyboard report\n");
    }
}

void blueism_send_system(uint16_t usage) {
    blueism_report_system_ctrl.usage_high = (uint8_t)((usage >> 8) & 0xFF);
    blueism_report_system_ctrl.usage_low  = (uint8_t)(usage & 0xFF);

    blueism_send_status_t ret = blueism_send_cmd(CMD_REPORT_HID_SYSTEM_CTRL, (uint8_t *)&blueism_report_system_ctrl, sizeof(blueism_report_system_ctrl_t));

    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send System Control report\n");
    }
}

void blueism_send_consumer(uint16_t usage) {
    blueism_report_consumer_ctrl.usage_high = (uint8_t)((usage >> 8) & 0xFF);
    blueism_report_consumer_ctrl.usage_low  = (uint8_t)(usage & 0xFF);

    blueism_send_status_t ret = blueism_send_cmd(CMD_REPORT_HID_CONSUMER_CTRL, (uint8_t *)&blueism_report_consumer_ctrl, sizeof(blueism_report_consumer_ctrl_t));

    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send Consumer Control report\n");
    }
}

void blueism_send_mouse(report_mouse_t *report) {
    blueism_report_mouse.buttons = report->buttons;
    blueism_report_mouse.wheel   = report->v;

    int16_t x = (int16_t)report->x;
    int16_t y = (int16_t)report->y;

    blueism_report_mouse.xy_packed[0] = (uint8_t)(x & 0xFF);
    blueism_report_mouse.xy_packed[1] = (uint8_t)(((x >> 8) & 0x0F) | ((y & 0x0F) << 4));
    blueism_report_mouse.xy_packed[2] = (uint8_t)((y >> 4) & 0xFF);

    blueism_send_status_t ret = blueism_send_cmd(CMD_REPORT_HID_MOUSE, (uint8_t *)&blueism_report_mouse, sizeof(blueism_report_mouse_t));

    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send Mouse report\n");
    }
}

void blueism_select_id(uint8_t id) {
    uint8_t payload[2];
    payload[0] = SUBCMD_BLE_CTRL_SELECT_ID;
    payload[1] = id;

    blueism_send_status_t ret = blueism_send_cmd(CMD_BLE_CTRL, payload, 2);

    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send Select ID command\n");
    }
}

void blueism_erase_peer(void) {
    uint8_t payload;
    payload = SUBCMD_BLE_CTRL_ERASE_BOND;

    blueism_send_status_t ret = blueism_send_cmd(CMD_BLE_CTRL, &payload, 1);

    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send Erase Peer command\n");
    }
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
    blueism_send_keyboard(report);
}

void bluetooth_send_nkro(report_nkro_t *report) {
    blueism_send_nkro(report);
}

void bluetooth_send_system(uint16_t usage) {
    blueism_send_system(usage);
}

void bluetooth_send_consumer(uint16_t usage) {
    blueism_send_consumer(usage);
}

void bluetooth_send_mouse(report_mouse_t *report) {
    blueism_send_mouse(report);
}

bool bluetooth_can_send_nkro(void) {
    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_BLUETOOTH_PROFILE1:
                blueism_select_id(0);
                return false;
            case QK_BLUETOOTH_PROFILE2:
                blueism_select_id(1);
                return false;
            case QK_BLUETOOTH_PROFILE3:
                blueism_select_id(2);
                return false;
            case QK_BLUETOOTH_PROFILE4:
                blueism_select_id(3);
                return false;
            case QK_BLUETOOTH_UNPAIR:
                blueism_erase_peer();
                return false;
        }
    }
    return process_record_user(keycode, record);
}
