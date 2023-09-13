// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

typedef int8_t blueism_send_status_t;

#define BLUEISM_SEND_STATUS_SUCCESS (0)
#define BLUEISM_SEND_STATUS_FAILED (1)

#define CMD_BT_UNPAIR 0x26
#define CMD_BT_BAT_UPDATE 0x00
#define CMD_REPORT_KB 0x31
#define CMD_REPORT_MOUSE 0x00
#define CMD_REPORT_CONSUMER 0x32

typedef struct {
    uint8_t mods;
    uint8_t keys[KEYBOARD_REPORT_KEYS];
} __attribute__((packed)) blueism_report_keyboard_t;

typedef struct {
    uint8_t buttons;
    int8_t  x;
    int8_t  y;
    int8_t  v;
    int8_t  h;
#ifdef MOUSE_EXTENDED_REPORT
#    error
#endif
} __attribute__((packed)) blueism_report_mouse_t;

typedef struct {
    uint8_t usage_h;
    uint8_t usage_l;
} __attribute__((packed)) blueism_report_consumer_t;

void                  blueism_init(void);
void                  blueism_task(void);
blueism_send_status_t blueism_send_cmd(uint8_t cmd, uint8_t* payload, uint8_t payload_len);
void                  blueism_send_keyboard(report_keyboard_t* report);
void                  blueism_send_mouse(report_mouse_t* report);
void                  blueism_send_consumer(uint16_t usage);
void                  blueism_battery_update(uint8_t bat_level);
void                  blueism_unpair(void);
