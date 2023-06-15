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

static uint16_t packet_send_interval_wait_count = 0;

void bk3642_spi_init(void) {
    spi_init();
    setPinOutput(BK3632_MOT_PIN);
    writePinHigh(BK3632_MOT_PIN);
    setPinInput(BK3632_SLEEP_PIN);
    wait_ms(1000); // wait for the module to init
}

void bk3642_spi_send_cmd(uint8_t cmd, uint8_t* payload, uint8_t payload_len) {
    /*350 us packet sending interval*/
    while (packet_send_interval_wait_count < PACKET_SEND_INTERVAL_WAIT_TIME + 50) {
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

    /*calculate checksum*/
    uint16_t checksum   = 0;
    uint8_t  packet_len = payload_len + 1;
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
    packet[byte_count] = checksum & 0xFF;
}
