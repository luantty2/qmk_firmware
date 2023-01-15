// Copyright 2023 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

typedef struct hc165_key {
    int8_t driver;
    int8_t channel;
} __attribute__((packed)) hc165_key;