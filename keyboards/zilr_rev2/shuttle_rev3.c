// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "shuttle_rev3.h"
#include "pca9557.h"

#define PCA9557_ADDRESS (0b0011000 << 1)

static uint8_t pca9557_pin_state = 0;

void shuttle_init(void) {
    pca9557_init(PCA9557_ADDRESS);
    pca9557_set_config(PCA9557_ADDRESS, 0xFF);
}

void shuttle_read(void) {
    pca9557_readPins(PCA9557_ADDRESS, &pca9557_pin_state);
}

int8_t shuttle_get_pos(void) {
    uint8_t state_bits = pca9557_pin_state & 0x0F;
    switch (state_bits) {
        case 0b1111:
        case 0b0111:
            return SHUTTLE_POS_N10_10;
            break;
        case 0b1101:
            return SHUTTLE_POS_10_20;
            break;
        case 0b1001:
            return SHUTTLE_POS_20_30;
            break;
        case 0b1011:
            return SHUTTLE_POS_30_40;
            break;
        case 0b1010:
            return SHUTTLE_POS_40_50;
            break;
        case 0b1000:
            return SHUTTLE_POS_50_60;
            break;
        case 0b1100:
            return SHUTTLE_POS_60_70;
            break;
        case 0b1110:
            return SHUTTLE_POS_70_80;
            break;
        case 0b0101:
            return SHUTTLE_POS_N10_N20;
            break;
        case 0b0001:
            return SHUTTLE_POS_N20_N30;
            break;
        case 0b0011:
            return SHUTTLE_POS_N30_N40;
            break;
        case 0b0010:
            return SHUTTLE_POS_N40_N50;
            break;
        case 0b0000:
            return SHUTTLE_POS_N50_N60;
            break;
        case 0b0100:
            return SHUTTLE_POS_N60_N70;
            break;
        case 0b0110:
            return SHUTTLE_POS_N70_N80;
            break;
        default:
            return SHUTTLE_POS_N10_10;
            break;
    }
}

uint8_t shuttle_get_zone(void) {
    int8_t  shuttle_pos = shuttle_get_pos();
    uint8_t shuttle_zone;
    switch (shuttle_pos) {
        case SHUTTLE_POS_N10_10:
            shuttle_zone = SHUTTLE_ZONE_IDLE;
            return shuttle_zone;
            break;
        case SHUTTLE_POS_10_20:
            shuttle_zone = SHUTTLE_ZONE_2X;
            return shuttle_zone;
            break;
        case SHUTTLE_POS_20_30:
        case SHUTTLE_POS_30_40:
            shuttle_zone = SHUTTLE_ZONE_5X;
            return shuttle_zone;
            break;
        case SHUTTLE_POS_40_50:
            shuttle_zone = SHUTTLE_ZONE_10X;
            return shuttle_zone;
            break;
        case SHUTTLE_POS_50_60:
            shuttle_zone = SHUTTLE_ZONE_15X;
            return shuttle_zone;
            break;
        case SHUTTLE_POS_60_70:
        case SHUTTLE_POS_70_80:
            shuttle_zone = SHUTTLE_ZONE_SX;
            return shuttle_zone;
            break;
        case SHUTTLE_POS_N10_N20:
            shuttle_zone = SHUTTLE_ZONE_N2X;
            return shuttle_zone;
            break;
        case SHUTTLE_POS_N20_N30:
        case SHUTTLE_POS_N30_N40:
            shuttle_zone = SHUTTLE_ZONE_N5X;
            return shuttle_zone;
            break;
        case SHUTTLE_POS_N40_N50:
            shuttle_zone = SHUTTLE_ZONE_N10X;
            return shuttle_zone;
            break;
        case SHUTTLE_POS_N50_N60:
            shuttle_zone = SHUTTLE_ZONE_N15X;
            return shuttle_zone;
            break;
        case SHUTTLE_POS_N60_N70:
        case SHUTTLE_POS_N70_N80:
            shuttle_zone = SHUTTLE_ZONE_NSX;
            return shuttle_zone;
            break;
        default:
            shuttle_zone = SHUTTLE_ZONE_IDLE;
            return shuttle_zone;
            break;
    }
}