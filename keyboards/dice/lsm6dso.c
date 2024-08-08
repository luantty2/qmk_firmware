// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "lsm6dso.h"
#include "lsm6dso_reg.h"
#include "i2c_master.h"

int32_t lsm6dso_i3c_disable_set(lsm6dso_ctx_t *ctx, lsm6dso_i3c_disable_t val)
{
  lsm6dso_i3c_bus_avb_t i3c_bus_avb;
  lsm6dso_ctrl9_xl_t ctrl9_xl;
  int32_t ret;

  ret = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, (uint8_t*)&ctrl9_xl, 1);
  if (ret == 0) {
    ctrl9_xl.i3c_disable = ((uint8_t)val & 0x80U) >> 7;
    ret = lsm6dso_write_reg(ctx, LSM6DSO_CTRL9_XL, (uint8_t*)&ctrl9_xl, 1);
  }
  if (ret == 0) {

    ret = lsm6dso_read_reg(ctx, LSM6DSO_I3C_BUS_AVB,
                           (uint8_t*)&i3c_bus_avb, 1);
  }
  if (ret == 0) {
    i3c_bus_avb.i3c_bus_avb_sel = (uint8_t)val & 0x03U;
    ret = lsm6dso_write_reg(ctx, LSM6DSO_I3C_BUS_AVB,
                            (uint8_t*)&i3c_bus_avb, 1);
  }

  return ret;
}

void lsm6dso_init(void) {
    i2c_init();
}
