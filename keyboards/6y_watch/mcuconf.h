// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_LSE_ENABLED
#define STM32_LSE_ENABLED TRUE

// #undef STM32_LSI_ENABLED
// #define STM32_LSI_ENABLED TRUE

#undef STM32_RTCSEL
#define STM32_RTCSEL STM32_RTCSEL_LSE

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 2

#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE 12

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE
