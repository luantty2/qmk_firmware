// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "config_blueism.h"
#include "uart.h"
#include "blueism.h"
#include "ringbuffer.h"
#include "stdio.h"
#include "lpm_stm32l43x.h"

#define BLUEISM_UART_BAUDRATE 115200
#define BLUEISM_UART_PACKET_LEN 16
#define BLUEISM_UART_PACKET_COMMON_LEN 5
#ifndef BLUEISM_UART_SEND_INTERVAL_MS
#    define BLUEISM_UART_SEND_INTERVAL_MS 3
#endif
#ifndef SEND_BUFFER_SIZE
#    define SEND_BUFFER_SIZE 256
#endif

RingBuffer     send_buffer;
static uint8_t send_buff_data[SEND_BUFFER_SIZE];
static uint8_t send_err_cnt;

static blueism_report_keyboard_t       blueism_report_keyboard;
static const blueism_report_keyboard_t empty_blueism_report_keyboard;
static blueism_report_mouse_t          blueism_report_mouse;
static blueism_report_mouse_t          last_blueism_report_mouse;
static blueism_report_consumer_t       blueism_report_consumer;
static const blueism_report_consumer_t empty_blueism_report_consumer;

static uint32_t send_timer;

void blueism_init(void) {
    ringBufferInit(&send_buffer, send_buff_data, sizeof(send_buff_data));
    uart_init(BLUEISM_UART_BAUDRATE);

    setPinOutput(BLUEISM_WAKEUP_PIN);
    writePinHigh(BLUEISM_WAKEUP_PIN);
    setPinInputHigh(BLUEISM_SLEEP_STATUS_PIN);
    setPinInput(VBUS_DETECT_PIN);
    setPinInput(BAT_DETECT_PIN);
}

blueism_send_status_t blueism_send_cmd(uint8_t cmd, uint8_t *payload, uint8_t payload_len) {
    if ((payload_len > BLUEISM_UART_PACKET_LEN - BLUEISM_UART_PACKET_COMMON_LEN)) {
        dprintf("Invalid payload length: %d\n", payload_len);
        return -BLUEISM_SEND_STATUS_FAILED;
    }
    uint8_t packet[BLUEISM_UART_PACKET_LEN] = {0};

    // Calculate checksum
    uint16_t checksum = 0;
    checksum += 0xAA;
    checksum += cmd;
    checksum += payload_len;
    for (uint8_t i = 0; i < payload_len; i++) {
        checksum += payload[i];
    }
    checksum -= 0x55;

    // Fill packet
    packet[0] = 0xAA;
    packet[1] = cmd;
    packet[2] = payload_len;
    memcpy(packet + 3, payload, payload_len);
    packet[BLUEISM_UART_PACKET_LEN - 2] = checksum & 0xFF;
    packet[BLUEISM_UART_PACKET_LEN - 1] = '\n';

#ifdef DEBUG_BLUEISM_UART_PACKET
    for (uint8_t i = 0; i < BLUEISM_UART_PACKET_LEN; i++) {
        dprintf("%02x ", packet[i]);
    }
    dprintf("\n");
#endif
    if (ringBufferFreeSpace(&send_buffer) < sizeof(packet)) {
        dprintf("Sending buffer has no free space\n");
        return -BLUEISM_SEND_STATUS_FAILED;
    }
    ringBufferAppendMultiple(&send_buffer, packet, sizeof(packet));
    return BLUEISM_SEND_STATUS_SUCCESS;
}

void blueism_send_keyboard(report_keyboard_t *report) {
    blueism_report_keyboard.mods = report->mods;
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        blueism_report_keyboard.keys[i] = report->keys[i];
    }
    uint8_t rep_kb_payload[sizeof(blueism_report_keyboard)];
    memcpy(rep_kb_payload, &blueism_report_keyboard, sizeof(blueism_report_keyboard));

    blueism_send_status_t ret = blueism_send_cmd(CMD_REPORT_KB, rep_kb_payload, sizeof(blueism_report_keyboard));
    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send keyboard report\n");
        send_err_cnt++;
    }
    blueism_report_keyboard = empty_blueism_report_keyboard;
}

void blueism_send_mouse(report_mouse_t *report) {
    blueism_report_mouse.buttons = report->buttons;
    blueism_report_mouse.x       = report->x;
    blueism_report_mouse.y       = report->y;
    blueism_report_mouse.v       = report->v;
    blueism_report_mouse.h       = report->h;

    if (memcmp(&last_blueism_report_mouse, &blueism_report_mouse, sizeof(blueism_report_mouse)) == 0) {
        return;
    }

    uint8_t rep_ms_payload[sizeof(blueism_report_mouse)];
    memcpy(rep_ms_payload, &blueism_report_mouse, sizeof(blueism_report_mouse));

    blueism_send_status_t ret = blueism_send_cmd(CMD_REPORT_MOUSE, rep_ms_payload, sizeof(blueism_report_mouse));
    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send mouse report\n");
        send_err_cnt++;
    }
    last_blueism_report_mouse = blueism_report_mouse;
}

void blueism_send_consumer(uint16_t usage) {
    blueism_report_consumer.usage_h = usage >> 8;
    blueism_report_consumer.usage_l = usage & 0xFF;
    uint8_t rep_consumer_payload[sizeof(blueism_report_consumer)];
    memcpy(rep_consumer_payload, &blueism_report_consumer, sizeof(blueism_report_consumer));
    blueism_send_status_t ret = blueism_send_cmd(CMD_REPORT_CONSUMER, rep_consumer_payload, sizeof(blueism_report_consumer));
    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send consumer report\n");
        send_err_cnt++;
    }
    blueism_report_consumer = empty_blueism_report_consumer;
}

void blueism_battery_update(uint8_t bat_level) {
    bat_level                 = MAX(MIN(bat_level, 100U), 0U);
    blueism_send_status_t ret = blueism_send_cmd(CMD_BT_BAT_UPDATE, &bat_level, sizeof(bat_level));
    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send battery update command\n");
        send_err_cnt++;
    }
}

void blueism_unpair() {
    blueism_send_status_t ret = blueism_send_cmd(CMD_BT_UNPAIR, NULL, 0);
    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send unpair command\n");
        send_err_cnt++;
    }
}

static inline bool blueism_sleep_status_check(void) {
    if (readPin(BLUEISM_SLEEP_STATUS_PIN) == 0) {
        return false;
    } else {
        return true;
    }
}

static inline void blueism_wakeup(void) {
    writePinLow(BLUEISM_WAKEUP_PIN);
    matrix_io_delay();
    writePinHigh(BLUEISM_WAKEUP_PIN);
}

bool vbus_detect(void) {
    if (readPin(VBUS_DETECT_PIN) == 0) {
        return false;
    } else {
        return true;
    }
}

bool bat_detect(void) {
    if (readPin(BAT_DETECT_PIN) == 0) {
        return false;
    } else {
        return true;
    }
}

void blueism_task(void) {
    uint32_t timer_now = timer_read();
    if (!ringBufferEmpty(&send_buffer) && (TIMER_DIFF_32(timer_now, send_timer) >= BLUEISM_UART_SEND_INTERVAL_MS)) {
        lpm_timer_reset();
        if (ringBufferLen(&send_buffer) % BLUEISM_UART_PACKET_LEN != 0) {
            dprintf("Corrupted data in sending buffer\n");
            ringBufferClear(&send_buffer);
        } else {
            uint8_t data[BLUEISM_UART_PACKET_LEN];
            ringBufferGetMultiple(&send_buffer, data, sizeof(data));
            if (!blueism_sleep_status_check()) {
                uart_transmit(data, sizeof(data));
            } else {
                blueism_wakeup();
                uart_transmit(data, sizeof(data));
            }
        }
        send_timer = timer_now;
    }
}
