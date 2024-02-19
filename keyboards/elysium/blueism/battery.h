// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

void battery_init(void);
void battery_task(void);
uint8_t get_battery_lvl(void);
void get_battery_lvl_str(char *bat_str, size_t size);
