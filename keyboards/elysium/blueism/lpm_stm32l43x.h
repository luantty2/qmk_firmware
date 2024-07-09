// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

typedef enum {
    PM_RUN,
    PM_SLEEP,
    PM_STOP1,
} pm_t;

void enter_power_mode_stop1(void);
void lpm_init(void);
void lpm_timer_stop(void);
void lpm_timer_reset(void);
void pm_reset(void);
// void vbus_reset(void);
