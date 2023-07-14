// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#ifndef BK3632_SPI_SLAVE_SELECT_PIN
#    error "BT module slave select pin muse be assigned"
#endif

#ifndef BK3632_MOT_PIN
#    error "BT module MOT pin must be assigned"
#endif

#ifndef BK3632_SLEEP_PIN
#    error "BT module sleep pin must be assigned"
#endif

#ifndef BK3632_SPI_CLOCK_DIVISOR
#    define BK3632_SPI_CLOCK_DIVISOR 128
#endif

typedef int8_t bk3632_send_status_t;

#define BK3632_SEND_STATUS_SUCCESS (0)
#define BK3632_SEND_WAKEUP_ERROR (-1)
#define BK3632_SEND_SPI_TIMEOUT (-2)
#define BK3632_SEND_SPI_ERROR (-3)
#define BK3632_SEND_SPI_PARA_ERROR (-4)

typedef enum {
    BK3632_SPI_WIRELESS_MODE_BT_1,
    BK3632_SPI_WIRELESS_MODE_BT_2,
    BK3632_SPI_WIRELESS_MODE_BT_3,
    BK3632_SPI_WIRELESS_MODE_DONGLE,
} bk3632_spi_wireless_mode_t;

typedef enum {
    BK3632_SPI_WIRELESS_PARING,
    BK3632_SPI_WIRELESS_RECONNECTING,
    BK3632_SPI_WIRELESS_CONNECTED,
    BK3632_SPI_WIRELESS_DISCONNECTED,
} bk3632_spi_wireless_state_t;

void                 bk3632_spi_init(void);
bk3632_send_status_t bk3632_spi_send_cmd(uint8_t cmd, uint8_t* payload, uint8_t payload_len);
void                 bk3632_get_info(void);
bool                 bk3632_set_bt_name(void);
bool                 bk3632_switch_mode(bk3632_spi_wireless_mode_t mode, bool pair);
bool                 bk3632_spi_send_keyboard(report_keyboard_t* report);
void                 bk3632_spi_send_consumer(uint16_t report);
void                 bk3632_spi_send_system(uint16_t report);
void                 bk3632_spi_send_mouse(uint8_t* report);
