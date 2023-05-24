// Copyright 2023 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akeypad.h"
#include "spi_master.h"


#define NO_DRIVER -1
#define NO_CHANNEL -1
#define NO_KEY {NO_DRIVER, NO_CHANNEL}

const hc165_key hc165_keys[MATRIX_ROWS][8 * sizeof(matrix_row_t)] = {
    {{0, 5}, {0, 6}, {0, 7}, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY},
    {{0, 4}, {0, 0}, {1, 7}, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY},
    {{0, 2}, {0, 3}, {1, 5}, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY},
    {{0, 1}, {1, 2}, {1, 0}, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY}
};

uint8_t last_hc165_data[MATRIX_SHIFT_REGISTER_COUNT] = {0, 0};
uint8_t hc165_data[MATRIX_SHIFT_REGISTER_COUNT]      = {0, 0};

void toggle_pin_high(pin_t pin) {
    writePinHigh(pin);
    matrix_io_delay();
    writePinLow(pin);
}

void toggle_pin_low(pin_t pin) {
    writePinLow(pin);
    matrix_io_delay();
    writePinHigh(pin);
}

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    // USB mux selection pin.
    // low = USB HS, high = USB FS.
    setPinOutput(USB_MUX_SEL_PIN);
    writePinLow(USB_MUX_SEL_PIN);

    keyboard_post_init_user();
}

void matrix_init_custom(void) {
    setPinOutput(SPI_MATRIX_CHIP_SELECT_PIN);
    setPinOutput(SHIFTREG_MATRIX_LATCH);
    writePinHigh(SHIFTREG_MATRIX_LATCH);
    spi_init();
}

// void debounce_init(uint8_t num_rows) {}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    matrix_row_t current_row_value = 0;
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;

    for (uint8_t col_index = 0; col_index < 8 * sizeof(matrix_row_t); col_index++, row_shifter <<= 1) {
        if (hc165_keys[current_row][col_index].driver != NO_DRIVER) {
            // get a bit from a byte: byte & (1<<pos)
            current_row_value |= (hc165_data[hc165_keys[current_row][col_index].driver] & (0x01 << (hc165_keys[current_row][col_index].channel))) ? 0 : row_shifter;
        }
    }

    current_matrix[current_row] = current_row_value;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    toggle_pin_low(SHIFTREG_MATRIX_LATCH);
    spi_start(SPI_MATRIX_CHIP_SELECT_PIN, false, 0, SPI_MATRIX_DIVISOR);
    spi_receive((uint8_t*)hc165_data, MATRIX_SHIFT_REGISTER_COUNT);
    spi_stop();

    matrix_has_changed = memcmp(last_hc165_data, hc165_data, sizeof(hc165_data)) != 0;
    if (matrix_has_changed) {
        memcpy(last_hc165_data, hc165_data, sizeof(hc165_data));
        for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
            matrix_read_cols_on_row(current_matrix, current_row);
        }
    }

    return matrix_has_changed;
}

/*
Test polling rate
*/
/*
void auto_clicking(void) {
    register_code(KC_A);
    wait_us(50);
    unregister_code(KC_A);
}

static uint32_t key_timer;

void polling_test(void) {
    uint32_t timer_now = timer_read();
    if (TIMER_DIFF_32(timer_now, key_timer) >= 1000) {
        auto_clicking();
        key_timer = timer_now;
    }
}

void housekeeping_task_kb(void) {
    polling_test();
}
*/
