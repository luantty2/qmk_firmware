// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "mzh_wire.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TD(TD_CON1), TD(TD_CON2), TD(TD_CON3), TD(TD_CONX), TD(TD_CONY)
    )
};
