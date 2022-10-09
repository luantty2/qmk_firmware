// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include QMK_KEYBOARD_H

#define FADE_IN_LENGTH 500

void rgb_matrix_set_target_v(void);
bool rgb_matrix_fade_in(void);