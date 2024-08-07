// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "uart.h"
#include "blueism.h"
#include "ringbuffer.h"
#include "hid_leds.h"
#include "max1704x.h"
#include "usb_util.h"
#include "lpm_stm32l43x.h"
#include "stdio.h"

#define BLUEISM_UART_BAUDRATE 115200
#define BLUEISM_UART_PACKET_LEN 8
#define BLUEISM_UART_PACKET_COMMON_LEN 1
#ifndef BLUEISM_UART_SEND_INTERVAL_MS
#    define BLUEISM_UART_SEND_INTERVAL_MS 5
#endif
#ifndef SEND_BUFFER_SIZE
#    define SEND_BUFFER_SIZE
#endif

// #undef SD1_CR2
// #define SD1_CR2 USART_CR2_STOP1_BITS

RingBuffer     send_buffer;
static uint8_t send_buff_data[SEND_BUFFER_SIZE];
static uint8_t send_err_cnt;

static blueism_report_keyboard_t       blueism_report_keyboard;
static const blueism_report_keyboard_t empty_blueism_report_keyboard;
static blueism_report_mouse_t          blueism_report_mouse;
static blueism_report_mouse_t          last_blueism_report_mouse;
static blueism_report_consumer_t       blueism_report_consumer;
static const blueism_report_consumer_t empty_blueism_report_consumer;

// static uint32_t send_timer;

void blueism_init(void) {
#ifdef BOARD_PM
    lpm_init();
#endif
    // vbus_reset();
    ringBufferInit(&send_buffer, send_buff_data, sizeof(send_buff_data));
    uart_init(BLUEISM_UART_BAUDRATE);
    setPinOutput(WAKEUP_PIN);
    writePinLow(WAKEUP_PIN);
    matrix_io_delay();
    setPinInputHigh(WAKEUP_PIN);

    setPinInputHigh(SLEEP_STATUS_PIN);

    setPinInput(VBUS_DETECT_PIN);
#ifdef HIDS_LEDS_ENABLE
    // hid_leds_init();
#endif
    // setPinOutput(NRF_RESET);
    // writePinHigh(NRF_RESET);

    setPinOutput(NRF_BUTTON_UNPAIR_PIN);
    writePinHigh(NRF_BUTTON_UNPAIR_PIN);

    // setPinOutput(WIRELESS_MODE_SEL_PIN);
    // mode_config.raw = eeconfig_read_kb();
    // if (mode_config.is_ble) {
    //     writePinHigh(WIRELESS_MODE_SEL_PIN);
    // } else {
    //     writePinLow(WIRELESS_MODE_SEL_PIN);

    // }

#ifdef RGB_MATRIX_ENABLE
    setPinOutput(RGB_SHUTDOWN_PIN);
    if (rgb_matrix_is_enabled()) {
        writePinHigh(RGB_SHUTDOWN_PIN);
    } else {
        writePinLow(RGB_SHUTDOWN_PIN);
    }
#endif
}

// void eeconfig_init_kb(void) {
//     mode_config.raw    = 0;
//     mode_config.is_ble = true;           // We want this enabled by default
//     eeconfig_update_kb(mode_config.raw); // Write default value to EEPROM now

//     writePinHigh(WIRELESS_MODE_SEL_PIN);
// }

blueism_send_status_t blueism_send_cmd(uint8_t cmd, uint8_t *payload, uint8_t payload_len) {
    if ((payload_len > BLUEISM_UART_PACKET_LEN - BLUEISM_UART_PACKET_COMMON_LEN)) {
        dprintf("Invalid payload length: %d\n", payload_len);
        return -BLUEISM_SEND_STATUS_FAILED;
    }
    uint8_t packet[BLUEISM_UART_PACKET_LEN] = {0};

    // Calculate checksum
    // uint16_t checksum = 0;
    // checksum += 0xAA;
    // checksum += cmd;
    // checksum += payload_len;
    // for (uint8_t i = 0; i < payload_len; i++) {
    //     checksum += payload[i];
    // }
    // checksum -= 0x55;

    // Fill packet
    // packet[0] = 0xAA;
    packet[0] = cmd;
    // packet[2] = payload_len;
    memcpy(packet + 1, payload, payload_len);
    // packet[BLUEISM_UART_PACKET_LEN - 2] = checksum & 0xFF;
    // packet[BLUEISM_UART_PACKET_LEN - 1] = '\n';

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

void blueism_unpair(void) {
    blueism_send_status_t ret = blueism_send_cmd(CMD_BT_UNPAIR, NULL, 0);
    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("Failed to send unpair command\n");
        send_err_cnt++;
    }
}

void blueism_ble_button_unpair(void) {
    writePinLow(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(20);
    writePinHigh(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(20);
    writePinLow(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(20);
    writePinHigh(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(50);

    writePinLow(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(20);
    writePinHigh(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(20);
    writePinLow(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(20);
    writePinHigh(NRF_BUTTON_UNPAIR_PIN);
}

void blueism_dongle_button_unpair(void) {
    writePinLow(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(1100);
    writePinHigh(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(50);
    writePinLow(NRF_BUTTON_UNPAIR_PIN);

    writePinLow(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(20);
    writePinHigh(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(20);
    writePinLow(NRF_BUTTON_UNPAIR_PIN);
    wait_ms(20);
    writePinHigh(NRF_BUTTON_UNPAIR_PIN);
}

// void blueism_select_ble(void) {
//     mode_config.is_ble = true;
//     eeconfig_update_kb(mode_config.raw); // Writes the new status to EEPROM
//     writePinHigh(WIRELESS_MODE_SEL_PIN);
// }

// void blueism_select_2g4(void) {
//     mode_config.is_ble = false;
//     eeconfig_update_kb(mode_config.raw);
//     writePinLow(WIRELESS_MODE_SEL_PIN);
// }

void blueism_task(void) {
    static uint32_t send_timer;
    // send_timer = timer_read32();
    // uint32_t timer_now = timer_read();
    if (!ringBufferEmpty(&send_buffer) && timer_elapsed32(send_timer) >= BLUEISM_UART_SEND_INTERVAL_MS) {
        send_timer = timer_read32();
// #ifdef BOARD_PM
        lpm_timer_reset();
// #endif
#ifdef BOARD_PM
        // pm_reset();
#endif
        if (ringBufferLen(&send_buffer) % BLUEISM_UART_PACKET_LEN != 0) {
            dprintf("Corrupted data in sending buffer\n");
            ringBufferClear(&send_buffer);
        } else {
            uint8_t data[BLUEISM_UART_PACKET_LEN];
            // ringBufferGetMultiple(&send_buffer, data, sizeof(data));
            if (readPin(SLEEP_STATUS_PIN)) { // if sleeping
                setPinOutput(WAKEUP_PIN);
                writePinLow(WAKEUP_PIN);
                // wait_ms(20);
                matrix_io_delay();
                /*Do not send here, will stuck the BT module */
                // uart_transmit(data, sizeof(data));
                setPinInputHigh(WAKEUP_PIN);
                // dprintf("High, sleeping\n");

            } else {
                ringBufferGetMultiple(&send_buffer, data, sizeof(data));
                uart_transmit(data, sizeof(data));
                // dprintf("LOW, not sleeping\n");
            }
        }
        // send_timer = timer_now;
    }
}

// static uint32_t key_timer;

// void housekeeping_task_kb(void){
//     uint32_t timer_now = timer_read();
//     if ((TIMER_DIFF_32(timer_now, key_timer) >= 500)) {
//         if (!readPin(A14)) {
//             dprintf("LOW, not sleeping\n");
//         }else{
//             dprintf("High, sleeping\n");
//         }
//         key_timer = timer_now;
//     }
// }
