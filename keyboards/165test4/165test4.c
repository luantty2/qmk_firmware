// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "165test4.h"
#include "spi_master.h"

#define NO_DRIVER 255

const hc165_key hc165_keys[MATRIX_ROWS][8 * sizeof(matrix_row_t)] = {

    {{0, 5}, {0, 6}, {0, 7}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}},
    {{0, 4}, {0, 0}, {1, 7}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}},
    {{0, 2}, {0, 3}, {1, 5}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}},

    {{0, 1}, {1, 2}, {1, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}, {NO_DRIVER, 0}}

};

uint8_t last_driver_data[MATRIX_SHIFT_REGISTER_COUNT] = {0, 0};
uint8_t driver_data[MATRIX_SHIFT_REGISTER_COUNT]      = {0, 0};

void pulsePinHigh(pin_t pin) {
    writePinHigh(pin);
    matrix_io_delay();
    writePinLow(pin);
}

void pulsePinLow(pin_t pin) {
    writePinLow(pin);
    matrix_io_delay();
    writePinHigh(pin);
}

void keyboard_post_init_kb(void) {
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    keyboard_post_init_user();
}

void matrix_init_custom(void) {
    // SPI Matrix cs
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN);
    writePinLow(SPI_MATRIX_CHIP_SELECT_PIN);

    // spi matrix latch
    setPinOutput(SHIFTREG_MATRIX_LATCH);
    writePinHigh(SHIFTREG_MATRIX_LATCH);

    // spi matrix clock
    // writePinLow(SHIFTREG_MATRIX_CLK);
    // setPinOutput(SHIFTREG_MATRIX_CLK);

    // GPIO READ pin
    // setPinInput(SHIFTREG_MATRIX_DATA);
    // setPinInput(SHIFTREG_MATRIX_DATA);

    spi_init();
}

// void sort_matrix(matrix_row_t matrix[]) {}

// bool matrix_scan_custom(matrix_row_t current_matrix[]) {
//     static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

//     pulsePinLow(SHIFTREG_MATRIX_LATCH);

//     // Read from SPI the matrix
//     spi_start(SPI_MATRIX_CHIP_SELECT_PIN, false, 0, SPI_MATRIX_DIVISOR);
//     spi_receive((uint8_t*)temp_matrix, MATRIX_SHIFT_REGISTER_COUNT * sizeof(matrix_row_t));
//     spi_stop();

//     // // Read from the encoder pushbutton
//     // temp_matrix[5] = readPin(ENCODER_PUSHBUTTON_PIN) ? 1 : 0;

//     // Check if we've changed, return the last-read data
//     bool changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
//     if (changed) {
//         memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
//     }
//     return changed;
// }

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // bool matrix_has_changed = false;

    // matrix_row_t last_row_value    = current_matrix[current_row];
    matrix_row_t current_row_value = 0;
    //"#define MATRIX_ROW_SHIFTER ((matrix_row_t)1)"
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;

    for (uint8_t col_index = 0; col_index < 8 * sizeof(matrix_row_t); col_index++, row_shifter <<= 1) {
        // if (col_orders[current_row][col_index] != NO_PIN) {
        //     //     current_row_value |= 0;
        //     // } else {
        //     select_mux(current_row, col_index);
        //     matrix_io_delay();
        //     current_row_value |= readPin(hc4067_row_pins[current_row]) ? 0 : row_shifter;
        // }
        if (hc165_keys[current_row][col_index].driver != NO_DRIVER) {
            // current_row_value |= readPin(hc4067_row_pins[current_row]) ? 0 : row_shifter;

            // get a bit from a byte: byte & (1<<pos)
            current_row_value |= (driver_data[hc165_keys[current_row][col_index].driver] & (0x01 << (hc165_keys[current_row][col_index].channel))) ? 0 : row_shifter;
        }
    }
    // if ((last_row_value != current_row_value)) {
    //     matrix_has_changed |= true;
    // }
    // matrix_has_changed = memcmp(current_matrix[current_row], current_row_value, sizeof(current_row_value)) != 0;
    // if (matrix_has_changed) {
    //     memcpy(current_matrix[current_row], current_row_value, sizeof(current_row_value));
    // }
    current_matrix[current_row] = current_row_value;
    // return matrix_has_changed;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    pulsePinLow(SHIFTREG_MATRIX_LATCH);

    // spi read:
    //  spi mode 1:Leading edge rising	Sample on trailing edge

    spi_start(SPI_MATRIX_CHIP_SELECT_PIN, false, 0, 64);
    spi_receive((uint8_t*)driver_data, MATRIX_SHIFT_REGISTER_COUNT);
    spi_stop();

    // memcpy(last_driver_data, driver_data, sizeof(driver_data));

    matrix_has_changed = memcmp(last_driver_data, driver_data, sizeof(driver_data)) != 0;
    if (matrix_has_changed) {
        memcpy(last_driver_data, driver_data, sizeof(driver_data));
        for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
            // matrix_read_cols_on_row(current_matrix, current_row);
            matrix_read_cols_on_row(current_matrix, current_row);
        }
    }
    return matrix_has_changed;
    //---

    // goio read:

    // for (uint8_t sr = 0; sr < MATRIX_SHIFT_REGISTER_COUNT; sr++) {
    //     for (uint8_t bit = 0; bit < 8; bit++) {
    //         matrix_io_delay();
    //         // if (readPin(SHIFTREG_MATRIX_DATA)) {
    //         //     driver_data[sr] |= (0x01) << bit;
    //         // }
    //         // if (!readPin(SHIFTREG_MATRIX_DATA)) {
    //         //     dprintf("zero");
    //         // }
    //         driver_data[sr] |= readPin(SHIFTREG_MATRIX_DATA) << bit;
    //         pulsePinHigh(SHIFTREG_MATRIX_CLK);
    //     }
    // }

    //---

    // dprintf(" %d\n", driver_data[0]&(0x01<<2));

    // for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
    //     // matrix_read_cols_on_row(current_matrix, current_row);
    //     matrix_has_changed |= matrix_read_cols_on_row(current_matrix, current_row);
    // }

    // return matrix_has_changed;
    // return false;
}

// static uint32_t fader_read_timer = 0;

// void matrix_scan_kb() {
//     uint32_t timer_now = timer_read();
//     if (TIMER_DIFF_32(timer_now, fader_read_timer) >= 1000) {
//         dprintf(" %d\n", driver_data[0]);
//         dprintf(" %d\n", driver_data[1]);
//         // dprintf(" %d\n", driver_data[0] & (0x01 << 0));
//         // dprintf(" %d\n", driver_data[0] & (0x01 << 1));
//         // dprintf(" %d\n", driver_data[0] & (0x01 << 2));
//         // dprintf(" %d\n", driver_data[0] & (0x01 << 3));
//         // dprintf(" %d\n", driver_data[0] & (0x01 << 4));
//         // dprintf(" %d\n", driver_data[0] & (0x01 << 5));
//         // dprintf(" %d\n", driver_data[0] & (0x01 << 6));
//         // dprintf(" %d\n", driver_data[0] & (0x01 << 7));
//         fader_read_timer = timer_now;
//     }
// }