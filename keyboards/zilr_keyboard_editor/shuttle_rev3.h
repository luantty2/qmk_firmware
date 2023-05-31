// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#define SHUTTLE_POS_N10_10 0
#define SHUTTLE_POS_10_20 1
#define SHUTTLE_POS_20_30 2
#define SHUTTLE_POS_30_40 3
#define SHUTTLE_POS_40_50 4
#define SHUTTLE_POS_50_60 5
#define SHUTTLE_POS_60_70 6
#define SHUTTLE_POS_70_80 7

#define SHUTTLE_POS_N10_N20 -1
#define SHUTTLE_POS_N20_N30 -2
#define SHUTTLE_POS_N30_N40 -3
#define SHUTTLE_POS_N40_N50 -4
#define SHUTTLE_POS_N50_N60 -5
#define SHUTTLE_POS_N60_N70 -6
#define SHUTTLE_POS_N70_N80 -7

#define SHUTTLE_ZONE_IDLE 0
#define SHUTTLE_ZONE_2X 1
#define SHUTTLE_ZONE_5X 2
#define SHUTTLE_ZONE_10X 3
#define SHUTTLE_ZONE_15X 4
#define SHUTTLE_ZONE_SX 5
#define SHUTTLE_ZONE_N2X 6
#define SHUTTLE_ZONE_N5X 7
#define SHUTTLE_ZONE_N10X 8
#define SHUTTLE_ZONE_N15X 9
#define SHUTTLE_ZONE_NSX 10

void     shuttle_init(void);
void     shuttle_read(void);
int8_t  shuttle_get_pos(void);
uint8_t shuttle_get_zone(void);