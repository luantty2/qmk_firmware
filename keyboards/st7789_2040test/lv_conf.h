// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <lv_conf.h>

// #undef LV_FONT_DEFAULT
// #define LV_FONT_DEFAULT &lv_font_montserrat_28

// #undef LV_FONT_MONTSERRAT_14
// #define LV_FONT_MONTSERRAT_14 0

// #undef LV_FONT_MONTSERRAT_28
// #define LV_FONT_MONTSERRAT_28 1

// #undef LV_FONT_MONTSERRAT_48
// #define LV_FONT_MONTSERRAT_48 1

// #undef LV_DISP_DEF_REFR_PERIOD
// #define LV_DISP_DEF_REFR_PERIOD 5
// #undef LV_MEM_SIZE
// #define LV_MEM_SIZE (300U * 1024U)
// #undef LV_MEM_BUF_MAX_NUM
// #define LV_MEM_BUF_MAX_NUM 128
#undef LV_THEME_DEFAULT_DARK
#define LV_THEME_DEFAULT_DARK 1
#undef LV_USE_PERF_MONITOR
#define LV_USE_PERF_MONITOR 1

#undef LV_THEME_DEFAULT_TRANSITION_TIME
#define LV_THEME_DEFAULT_TRANSITION_TIME 80
#undef LV_DISP_DEF_REFR_PERIOD
#define LV_DISP_DEF_REFR_PERIOD 20      /*[ms]*/
// #undef LV_USE_GPU_STM32_DMA2D
// #define LV_USE_GPU_STM32_DMA2D 0
