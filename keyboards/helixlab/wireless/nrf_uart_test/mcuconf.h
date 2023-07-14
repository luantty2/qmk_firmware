// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include_next <mcuconf.h>

//48mhz
// #undef STM32_PLLP_VALUE
// #define STM32_PLLP_VALUE 8


#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE
