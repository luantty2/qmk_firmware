// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

void    battery_init(void);
uint8_t battery_fetch(void);
uint8_t battery_get(void);
void    reset_battery(void);
