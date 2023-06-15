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


typedef enum {
    BK3632_SPI_WIRELESS_MODE_BT,
    BK3632_SPI_WIRELESS_MODE_DONGLE,
    BK3632_SPI_WIRELESS_MODE_INVALID,
} bk3632_spi_wireless_mode_t;

typedef enum {
    BK3632_SPI_WIRELESS_PARING,
    BK3632_SPI_WIRELESS_RECONNECTING,
    BK3632_SPI_WIRELESS_CONNECTED,
    BK3632_SPI_WIRELESS_DISCONNECTED,
} bk3632_spi_wireless_state_t;

void bk3642_spi_init(void);
void bk3642_spi_send_cmd(uint8_t cmd, uint8_t* payload, uint8_t payload_len);
void bk3642_spi_send_keyboard(uint8_t* report);
void bk3642_spi_send_consumer(uint16_t report);
void bk3642_spi_send_system(uint16_t report);
void bk3642_spi_send_mouse(uint8_t* report);
