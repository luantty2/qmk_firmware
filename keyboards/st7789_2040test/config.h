// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* SPI config for display/touchpad */
// #define SPI_DRIVER SPID1
// #define SPI_SCK_PIN A5
// #define SPI_SCK_PAL_MODE 5
// #define SPI_MOSI_PIN A7
// #define SPI_MOSI_PAL_MODE 5
// #define SPI_MISO_PIN A6 // not in use
// #define SPI_MISO_PAL_MODE 5 // not in use

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP4

#define LCD_RST_PIN  GP7
#define LCD_CS_PIN GP8
#define LCD_DC_PIN GP9
#define LCD_WIDTH 172
#define LCD_HEIGHT 320
#define LCD_SPI_DIVISOR 4
#define QUANTUM_PAINTER_LVGL_USE_CUSTOM_CONF


#define QP_LVGL_TASK_PERIOD 5
#define DEBOUNCE 5

// #define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 16384
