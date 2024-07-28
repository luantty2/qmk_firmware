// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define CH455X_ADDRESS (0x24 << 1)
#define CH455X_TIMEOUT 100
#define CH455X_REG_CMD 0X48
#define CH455X_REG_DIG_1 0x68
#define CH455X_REG_DIG_2 0x6A
#define CH455X_REG_DIG_3 0x6C
#define CH455X_REG_DIG_4 0x6E
#define CH455X_REG_KEY 0X4F

void ch455x_init(void);
void ch455x_write(uint8_t reg, uint8_t *data);
