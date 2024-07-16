// Copyright 2023 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE                    8
#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE                    336
#undef STM32_PLLP_VALUE
#define STM32_PLLP_VALUE                    2
#undef STM32_PLLQ_VALUE
#define STM32_PLLQ_VALUE                    7

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#undef STM32_USB_USE_OTG1
#define STM32_USB_USE_OTG1                  FALSE
#undef STM32_USB_USE_OTG2
#define STM32_USB_USE_OTG2                  TRUE
