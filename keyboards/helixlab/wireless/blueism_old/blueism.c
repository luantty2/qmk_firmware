// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "uart.h"
#include "blueism.h"
// #include "send_buffer.h"
#include "ringbuffer.h"

#define PACKET_MAX_BYTE 16

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

// uint8_t rep_data[512];
// send_buffer_t send_buff;
// RingBuffer_t send_buff;
// ring_buffer buffer;
RingBuffer buffer;
static uint8_t buff_data[512];

void blueism_init(void) {
    uart_init(115200);
    ringBufferInit(&buffer, buff_data, 512);
    // buffer = buffer_init(512);
    // send_buffer_init(&send_buff, rep_data, sizeof(rep_data));
    // RingInitAlloc(&send_buff, 32, 16);
    // RingInit(&send_buff, rep_data, 32 ,16);
    wait_ms(100); // wait for the module to init
}

blueism_send_status_t blueism_send_cmd(uint8_t cmd, uint8_t *payload, uint8_t payload_len) {
    if (payload_len > PACKET_MAX_BYTE - 5) {
        return -1;
    }
    uint8_t packet[PACKET_MAX_BYTE] = {0};
    memset(packet, 0, PACKET_MAX_BYTE);

    /*calculate checksum*/
    uint16_t checksum = 0;
    checksum += 0xAA;
    checksum += cmd;
    checksum += payload_len;
    for (uint8_t i = 0; i < payload_len; i++) {
        checksum += payload[i];
    }
    checksum -= 0x55;

    /*fill packet*/
    packet[0] = 0xAA;
    packet[1] = cmd;
    packet[2] = payload_len;
    memcpy(packet + 3, payload, payload_len);
    packet[PACKET_MAX_BYTE - 2] = checksum & 0xFF;
    packet[PACKET_MAX_BYTE - 1] = 0x0A;
    // dprintf("checksum: %04x\n", packet[14]);

// #if 1
//     dprintf("bytes: %d\n", PACKET_MAX_BYTE);
//     for (uint8_t u = 0; u < PACKET_MAX_BYTE; u++) {
//         dprintf("%04x\n", packet[u]);
//     }
// #endif
    ringBufferAppendMultiple(&buffer, packet, 16);
    // dprintf("checksum in buffer value: %04x", packet[14]);
    // dprintf("buffer num: %d\n", ringBufferLen(&buffer));
    // ringBufferGetMultiple(&buffer, packet,16);
    // dprintf("buffer num: %d\n", ringBufferLen(&buffer));

    // buffer_push(buffer, packet, 16);
    // dprintf("buffer num: %d\n", buffer_data_size(buffer));

    // uint8_t data[16];
    // buffer_read(buffer, data, 16);
    // dprintf("data in buffer: %04x\n", data[15]);

    // RingWriteElement(&send_buff, packet);
    // RingWriteElements(&send_buff, packet,16);
    // printf("head index : %d\n", (uint16_t)RingGetHead(&send_buff));
    // dprintf("data in buffer: %d\n", (uint16_t)RingGetDataCnt(&send_buff));
    // uint8_t data[PACKET_MAX_BYTE];
    // RingReadElement(&send_buff, data);
    // dprintf("dequeued data, now in buffer: %d\n", (uint16_t)RingGetDataCnt(&send_buff));

    // report_data_t rep;
    // for (uint8_t v = 0; v < PACKET_MAX_BYTE; v++) {
    //     rep.data[v] = packet[v];
    // }
    // send_buffer_queue(&send_buff, rep);

    // // printf("data num in buffer : %d\n",send_buffer_num_items(&send_buff));
    // printf("head index : %d\n",send_buff.head_index);

    // blueism_report_buffer_append(packet,PACKET_MAX_BYTE);
    // uart_transmit(packet, PACKET_MAX_BYTE);
    // uint8_t data_to_send[4];
    // blueism_report_buffer_get(data_to_send, 4);
    return BLUEISM_SEND_STATUS_SUCCESS;
}

bool blueism_send_keyboard(report_keyboard_t *report) {
    uint8_t payload[7] = {0};
    payload[0]         = report->mods;
    payload[1]         = report->keys[0];
    payload[2]         = report->keys[1];
    payload[3]         = report->keys[2];
    payload[4]         = report->keys[3];
    payload[5]         = report->keys[4];
    payload[6]         = report->keys[5];
    // uint8_t *payload;
    // payload = &(report->mods);
    // // payload = report->mods;
    // uint8_t *keys = report->keys;
    // // *payload=
    // for (uint8_t i = 0; i < sizeof(report->keys); i++) {
    //     // payload = keys+i;
    //     *(payload + i) = *(keys + i);
    // }

    blueism_send_status_t ret = blueism_send_cmd(CMD_REPORT, payload, sizeof(payload));
    if (ret != BLUEISM_SEND_STATUS_SUCCESS) {
        dprintf("blueism_send_keyboard::FAILED::Failed to send keyboard report\n");
        return false;
    }
    return true;
}

// static int uid;
static uint32_t key_timer;

void blueism_task(void) {
    // if((ringBufferLen(&buffer)%16==0)&&(!ringBufferEmpty(&buffer))){
    //     uint8_t data[PACKET_MAX_BYTE];
    //     ringBufferGetMultiple(&buffer, data,16);
    //     dprintf("checksum in buffer value: %04x", data[14]);
    // }
    uint32_t timer_now = timer_read();
    if(!ringBufferEmpty(&buffer)&& (TIMER_DIFF_32(timer_now, key_timer) >= 3)){
        uint8_t data[PACKET_MAX_BYTE];
        ringBufferGetMultiple(&buffer, data,16);
        uart_transmit(data, PACKET_MAX_BYTE);
        dprintf("checksum sent: %04x\n", data[14]);
        key_timer = timer_now;
        // dprintf("checksum in buffer value: %04x", data[14]);
        // dprintf("buffer num: %d\n", ringBufferLen(&buffer));
    }
    // if(buffer_data_size(buffer)!=0){
    //     uint8_t data[PACKET_MAX_BYTE];
    //     buffer_read(buffer, data, 16);
    //     dprintf("checksum in buffer value: %04x", data[14]);
    //     }
    // if(buffer_data_size(buffer))
    // if (RingGetDataCnt(&send_buff) > 1) {
    //     uint8_t data[PACKET_MAX_BYTE];
    //     RingReadElement(&send_buff, data);
    //     // dprintf("bytes: %d\n", PACKET_MAX_BYTE);
    //     for (uint8_t u = 0; u < 16; u++) {
    //         dprintf("%04x\n", data[u]);
    //     }
    //     // dprintf("dequeued data in buffer: %04x\n", data[PACKET_MAX_BYTE-1]);
    // }
    // if(!send_buffer_is_empty(&send_buff)){
    //     report_data_t data;
    //     send_buffer_dequeue(&send_buff, &data);
    //     uid++;
    //     dprintf("dequeued data in buffer: %04x, uid: %d\n", data.data[PACKET_MAX_BYTE-2],uid);
    //     uart_transmit(data.data, PACKET_MAX_BYTE);
    // }
}

void housekeeping_task_kb(void) {
    blueism_task();
}
