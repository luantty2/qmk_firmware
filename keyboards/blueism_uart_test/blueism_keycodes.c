// Copyright 2026 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "blueism_keycodes.h"
#include "bluetooth.h"
#include "outputselect.h"
#include "blueism_uart.h"

bool process_record_blueism(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_BLUETOOTH_PROFILE1:
                blueism_uart_select_ble_id(0);
                return false;
            case QK_BLUETOOTH_PROFILE2:
                blueism_uart_select_ble_id(1);
                return false;
            case QK_BLUETOOTH_PROFILE3:
                blueism_uart_select_ble_id(2);
                return false;
            case QK_BLUETOOTH_PROFILE4:
                blueism_uart_select_ble_id(3);
                return false;
            case QK_BLUETOOTH_UNPAIR:
                blueism_uart_erase_current_peer();
                return false;
            case QK_OUTPUT_2P4GHZ:
                blueism_uart_select_dongle();
                return false;
            case BLUEISM_PING:
                blueism_uart_send_ping();
                return false;
            case BLUEISM_RESET:
                blueism_uart_send_reset();
                return false;
            case BLUEISM_GET_VERSION:
                blueism_uart_send_get_version();
                return false;
        }
    }
    return true;
}
