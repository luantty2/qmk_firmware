// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#undef PRODUCT_ID
#define PRODUCT_ID 0x4458

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 4
#ifdef RGB_MATRIX_ENABLE
#    define VIA_QMK_RGBLIGHT_ENABLE
#endif
