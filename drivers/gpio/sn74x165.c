/* Copyright 2022
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

#include "sn74x165.h"
#include "spi_master.h"
#include "gpio.h"

spi_status_t res;

/* get length */
uint8_t sn74x165_length(void) {
    return SN74X165_LENGTH;
}
/*
    init first
*/
void sn74x165_init(void) {
    spi_init();
}

bool sn74x165_spi_receive(uint8_t* out) {
    sn74x165_pulsePinLow(SN74X165_LATCH_PIN);
    if (!spi_start(SN74X165_SPI_SLAVE_SELECT_PIN, SN74X165_SPI_LSBFIRST, SN74X165_SPI_MODE, SN74X165_SPI_CLOCK_DIVISOR)) {
        uprint("sn74x165 spi can't start \n");
        spi_stop();
        return false;
    }
    res = spi_receive(out, SN74X165_LENGTH);
    if (res != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }
    spi_stop();
    return true;
}

void sn74x165_pulsePinLow(uint8_t pin) {
    writePinHigh(pin);
    matrix_io_delay();
    writePinLow(pin);
}