// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "spi_master.h"
#include "bk3632_spi.h"

/*Read BK3632_SLEEP_PIN before sending packets to BT module*/
/*Delay 3000us if BK3632_SLEEP_PIN is low*/
#define SLEEP_WAIT_TIME 3000
/*Delay 100us if BK3632_SLEEP_PIN is high*/
#define NORMAL_WAIT_TIME 100
#define PACKET_MAX_BYTE 32
/*The interval of packet sent by MCU must be greater than 300us*/
#define PACKET_SEND_INTERVAL_WAIT_TIME 300

#define CMD_MODE 0x01
#define CMD_REPORT 0x02
#define CMD_TEST 0x03
#define CMD_RESET 0x04
#define CMD_MOUSE_MEDIA 0x05
#define CMD_WIRED 0x06
#define CMD_WIRED_LED 0x07
#define CMD_BT_NAME 0x08
#define CMD_SLEEP 0x09
#define CMD_STATUS 0x0A

static uint16_t packet_send_interval_wait_count = 0;

const uint8_t PROGMEM bt_5_name_payload[28] = {0, 11, 98, 116, 32, 116, 101, 115, 116, 32, 53, 46, 48};
const uint8_t PROGMEM bt_3_name_payload[28] = {1, 11, 98, 116, 32, 116, 101, 115, 116, 32, 51, 46, 48};

void bk3632_spi_init(void) {
    spi_init();
    setPinOutput(BK3632_MOT_PIN);
    writePinHigh(BK3632_MOT_PIN);
    setPinInput(BK3632_SLEEP_PIN);
    wait_ms(500); // wait for the module to init
}

bk3632_send_status_t bk3632_spi_send_cmd(uint8_t cmd, uint8_t* payload, uint8_t payload_len) {
    /*350us packet sending interval*/
    while (packet_send_interval_wait_count < PACKET_SEND_INTERVAL_WAIT_TIME + 10) {
        wait_us(10);
        packet_send_interval_wait_count += 10;
    }
    packet_send_interval_wait_count = 0;

    uint8_t packet[PACKET_MAX_BYTE] = {0};
    memset(packet, 0, PACKET_MAX_BYTE);

    /*assert MOT pin low*/
    writePinLow(BK3632_MOT_PIN);
    matrix_io_delay();

    /*sleep pin low = sleeping, need to wait for 3ms, otherwise wait for 100us*/
    if (readPin(BK3632_SLEEP_PIN)) {
        wait_us(NORMAL_WAIT_TIME);
    } else {
        wait_us(SLEEP_WAIT_TIME);
    }
    if (readPin(BK3632_SLEEP_PIN)) {
        dprintf("bk3632_spi_send_cmd::FAILED::Failed to wake up BT module from sleep\n");
        return BK3632_SEND_WAKEUP_ERROR;
    }

    /*calculate checksum*/
    uint16_t checksum   = 0;
    uint8_t  packet_len = payload_len + 1; // cmd byte
    checksum += 0xAA;
    checksum += packet_len;
    checksum += cmd;
    for (uint8_t i = 0; i < payload_len; i++) {
        checksum += payload[i];
    }
    checksum = 0x55 - checksum;

    /*fill packet*/
    uint8_t byte_count   = 0;
    packet[byte_count++] = 0xAA;
    packet[byte_count++] = packet_len;
    packet[byte_count++] = cmd;
    memcpy(packet + byte_count, payload, payload_len);
    byte_count += payload_len;
    packet[byte_count++] = checksum & 0xFF;

#if 1
    dprintf("bytes: %d\n", byte_count);
    for (uint8_t u = 0; u < byte_count; u++) {
        dprintf("%04x\n", packet[u]);
    }
#endif
    // return 0;

    if (spi_start(BK3632_SPI_SLAVE_SELECT_PIN, false, 3, BK3632_SPI_CLOCK_DIVISOR)) {
        spi_status_t ret = spi_transmit(packet, byte_count);
        if (ret != SPI_STATUS_SUCCESS) {
            switch (ret) {
                case SPI_STATUS_TIMEOUT:
                    dprintf("bk3632_spi_send_cmd::FAILED::SPI timeout\n");
                    return BK3632_SEND_SPI_TIMEOUT;
                case SPI_STATUS_ERROR:
                    dprintf("bk3632_spi_send_cmd::FAILED::SPI error occurs\n");
                    return BK3632_SEND_SPI_ERROR;
                default:
                    dprintf("bk3632_spi_send_cmd::FAILED::SPI unknown error occurs\n");
                    return BK3632_SEND_SPI_ERROR;
            }
        }
        spi_stop();
        matrix_io_delay();
        /*assert MOT pin high*/
        writePinHigh(BK3632_MOT_PIN);
        matrix_io_delay();
        return BK3632_SEND_STATUS_SUCCESS;
    } else {
        dprintf("bk3632_spi_send_cmd::FAILED::SPI parameters invalid\n");
        return BK3632_SEND_SPI_PARA_ERROR;
    }
}

void bk3632_get_info(void) {
    uint8_t payload[2] = {0x00, 0x00};
    bk3632_spi_send_cmd(CMD_STATUS, payload, 2);
}

bool bk3632_set_bt_name(void) {
    uint8_t payload[28];
    memcpy(payload, bt_5_name_payload, 28);
    bk3632_send_status_t ret = bk3632_spi_send_cmd(CMD_BT_NAME, payload, 28);
    if (ret != BK3632_SEND_STATUS_SUCCESS) {
        dprintf("bk3632_set_bt_name::FAILED::Failed to set BT 5 name\n");
        return false;
    }
    memcpy(payload, bt_3_name_payload, 28);
    ret = bk3632_spi_send_cmd(CMD_BT_NAME, payload, 28);
    if (ret != BK3632_SEND_STATUS_SUCCESS) {
        dprintf("bk3632_set_bt_name::FAILED::Failed to set BT 3 name\n");
        return false;
    }
    return true;
}

bool bk3632_switch_mode(bk3632_spi_wireless_mode_t mode, bool pair) {
    uint8_t              payload[2] = {0x00, 0x00};
    bk3632_send_status_t ret;
    switch (mode) {
        case BK3632_SPI_WIRELESS_MODE_BT_1:
            payload[1] = 0x01;
            if (pair) {
                payload[0] = 0x01;
            }
            ret = bk3632_spi_send_cmd(CMD_MODE, payload, 2);
            if (ret != BK3632_SEND_STATUS_SUCCESS) {
                dprintf("bk3632_switch_mode::FAILED::Failed to switch to BT 1\n");
                return false;
            }
            return true;
            break;
        case BK3632_SPI_WIRELESS_MODE_BT_2:
            payload[1] = 0x02;
            if (pair) {
                payload[0] = 0x01;
            }
            ret = bk3632_spi_send_cmd(CMD_MODE, payload, 2);
            if (ret != BK3632_SEND_STATUS_SUCCESS) {
                dprintf("bk3632_switch_mode::FAILED::Failed to switch to BT 2\n");
                return false;
            }
            return true;
            break;
        case BK3632_SPI_WIRELESS_MODE_BT_3:
            payload[1] = 0x03;
            if (pair) {
                payload[0] = 0x01;
            }
            ret = bk3632_spi_send_cmd(CMD_MODE, payload, 2);
            if (ret != BK3632_SEND_STATUS_SUCCESS) {
                dprintf("bk3632_switch_mode::FAILED::Failed to switch to BT 3\n");
                return false;
            }
            return true;
            break;
        case BK3632_SPI_WIRELESS_MODE_DONGLE:
            payload[1] = 0x00;
            if (pair) {
                payload[0] = 0x01;
            }
            ret = bk3632_spi_send_cmd(CMD_MODE, payload, 2);
            if (ret != BK3632_SEND_STATUS_SUCCESS) {
                dprintf("bk3632_switch_mode::FAILED::Failed to switch to dongle mode\n");
                return false;
            }
            return true;
            break;
        default:
            dprintf("bk3632_switch_mode::FAILED::Invalid mode\n");
            return false;
            break;
    }
}

bool bk3632_spi_send_keyboard(report_keyboard_t* report) {
    uint8_t payload[28] = {0};
    payload[0]          = report->mods;
    payload[1]          = report->keys[0];
    payload[2]          = report->keys[1];
    payload[3]          = report->keys[2];
    payload[4]          = report->keys[3];
    payload[5]          = report->keys[4];
    payload[6]          = 0;
    if (payload[1] != 0 && payload[2] != 0 && payload[3] != 0 && payload[4] != 0 && payload[5] != 0) {
        payload[7] = report->keys[5];
    }
    bk3632_send_status_t ret = bk3632_spi_send_cmd(CMD_REPORT, payload, 28);
    if (ret != BK3632_SEND_STATUS_SUCCESS) {
        dprintf("bk3632_spi_send_keyboard::FAILED::Failed to send keyboard report\n");
        return false;
    }
    return true;
}
