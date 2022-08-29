// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include_next <mcuconf.h>

// Used for RGB
// #undef STM32_ADC_USE_ADC1
// #define STM32_ADC_USE_ADC1 TRUE

// // Used for EEPROM
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

// #undef STM32_SPI_USE_SPI2
// #define STM32_SPI_USE_SPI2 TRUE

// #undef STM32_I2C_USE_DMA
// #define STM32_I2C_USE_DMA FALSE
#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE
#undef STM32_I2C_I2C2_RX_DMA_STREAM 
#define STM32_I2C_I2C2_RX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 5)
#undef STM32_I2C_I2C2_TX_DMA_STREAM 
#define STM32_I2C_I2C2_TX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 4)

// // Used for RGB
// #undef STM32_PWM_USE_TIM3
// #define STM32_PWM_USE_TIM3 TRUE