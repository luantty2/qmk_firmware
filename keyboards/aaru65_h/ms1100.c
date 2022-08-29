/* Copyright 2022 luantty2
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

#include "ms1100.h"
#include "i2c_master.h"
#include "wait.h"
#include "print.h"

void ms1100_init(void) {
    i2c_init();
    ms1100_write();
}

bool ms1100_test(void) {
    uint8_t      data[2];
    i2c_status_t status = i2c_receive(MS1100_ADDRESS, data, 2, MS1100_TIMEOUT);
    if (status == I2C_STATUS_SUCCESS) {
        return true;
    }
    return false;
}

int16_t ms1100_read(void) {
    uint8_t data[2];
    i2c_receive(MS1100_ADDRESS, data, 2, MS1100_TIMEOUT);
    uint16_t data_combined = (data[0] << 8) | data[1];
    if (data_combined > 0x7FFF) {
        data_combined = 0;
    } 
    // else if (data_combined < 0) {
    //     data_combined = 0;
    // }
    return (int16_t)data_combined;
}

void ms1100_write(void) {
    uint8_t data = MS1100_CONFIG;
    i2c_transmit(MS1100_ADDRESS, &data, 1, MS1100_TIMEOUT);
}