/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#define TIMER_1 500
#define TIMER_2 200
#define TIMER_3 100
#define TIMER_4 67
#define TIMER_5 100
#define TIMER_NO 0

void     shuttle_init(void);
bool     shuttle_read(void);
uint8_t  shuttle_get_pos(void);
uint16_t shuttle_get_timer(void);
void     shuttle_behavior(void);
bool     shuttle_in_deadzone(void);
bool     shuttle_in_continouszone(void);