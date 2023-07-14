// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

typedef int8_t blueism_send_status_t;

#define BLUEISM_SEND_STATUS_SUCCESS (0)

typedef enum {
    BLUEISM_WIRELESS_MODE_BT_1,
    BLUEISM_WIRELESS_MODE_BT_2,
    BLUEISM_WIRELESS_MODE_BT_3,
    BLUEISM_WIRELESS_MODE_DONGLE,
} blueism_wireless_mode_t;

typedef enum {
    BLUEISM_WIRELESS_PARING,
    BLUEISM_WIRELESS_RECONNECTING,
    BLUEISM_WIRELESS_CONNECTED,
    BLUEISM_WIRELESS_DISCONNECTED,
} blueism_wireless_state_t;

void                  blueism_init(void);
blueism_send_status_t blueism_send_cmd(uint8_t cmd, uint8_t* payload, uint8_t payload_len);
bool                  blueism_send_keyboard(report_keyboard_t* report);
