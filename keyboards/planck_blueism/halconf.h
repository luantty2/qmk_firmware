// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#define HAL_USE_SERIAL TRUE
#define PAL_USE_CALLBACKS TRUE
#define SERIAL_BUFFERS_SIZE 256
// This enables interrupt-driven mode
#define PAL_USE_WAIT TRUE
#include_next <halconf.h>
