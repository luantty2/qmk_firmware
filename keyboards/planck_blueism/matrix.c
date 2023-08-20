// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include <hal_pal.h>

/*
 * In this keyboard, row is input and col is output
 */
// #define GPIOB_BITMASK (1 << 13 | 1 << 14 | 1 << 15) // B13, B14, B15
// #define GPIOB_OFFSET 13
// #define GPIOB_COUNT 3
// #define GPIOA_BITMASK (1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8 ) // A0, A1, A2, A3, A4, A5, A6, A7, A8
// #define GPIOA_OFFSET 0
// #define GPIOA_COUNT 9
#define GPIOB_BITMASK (1 << 0 | 1 << 1 | 1 << 5 | 1 << 12) // B0, B1, B5, B12
#define GPIOB_OFFSET 0

// static uint8_t row_map[4] = {0, 1, 3 , 2};

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_wait_for_pin(pin_t pin, uint8_t target_state) {
    rtcnt_t start = chSysGetRealtimeCounterX();
    rtcnt_t end   = start + 5000;
    while (chSysIsCounterWithinX(chSysGetRealtimeCounterX(), start, end)) {
        if (readPin(pin) == target_state) {
            break;
        }
    }
}

void matrix_wait_for_port(stm32_gpio_t *port, uint32_t target_bitmask) {
    rtcnt_t start = chSysGetRealtimeCounterX();
    rtcnt_t end   = start + 5000;
    while (chSysIsCounterWithinX(chSysGetRealtimeCounterX(), start, end)) {
        if ((palReadPort(port) & target_bitmask) == target_bitmask) {
            break;
        }
    }
}

void matrix_init_custom(void) {
    for (int i = 0; i < MATRIX_ROWS; ++i) {
        setPinInputHigh(row_pins[i]);
    }
    for (int i = 0; i < MATRIX_COLS; ++i) {
        setPinInputHigh(col_pins[i]);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    static matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

    for (int current_col = 0; current_col < MATRIX_COLS; ++current_col) {
        // Keep track of the pin we're working with
        pin_t curr_col_pin = col_pins[current_col];

        // Setup the output column pin
        setPinOutput(curr_col_pin);
        writePinLow(curr_col_pin);
        matrix_wait_for_pin(curr_col_pin, 0);

        // Read the row ports
        // uint32_t gpio_b = palReadPort(GPIOB);
        // uint32_t gpio_c = palReadPort(GPIOC);
        uint32_t readback = 0;
        for (int i = 0; i < MATRIX_ROWS; ++i) {
            if (readPin(row_pins[i])) {
                readback |= (1ul << i);
            } else {
                readback &= ~(1ul << i);
            }
        }
        readback = ~(readback);

        // Unselect the row pin
        setPinInputHigh(curr_col_pin);

        // Construct the packed bitmask for the pins
        // uint32_t readback = ~(((gpio_b & GPIOB_BITMASK) >> GPIOB_OFFSET) | (((gpio_c & GPIOC_BITMASK) >> GPIOC_OFFSET) << GPIOB_COUNT));
        // uint32_t readback = ~(((gpio_b & GPIOB_BITMASK) >> GPIOB_OFFSET));

        // Inject values into the matrix
        for (int i = 0; i < MATRIX_ROWS; ++i) {
            if (readback & (1 << i)) {
                temp_matrix[i] |= (1ul << current_col);
            } else {
                temp_matrix[i] &= ~(1ul << current_col);
            }
        }

        // Wait for readback of the unselected column to go high
        matrix_wait_for_pin(curr_col_pin, 1);

        // Wait for readback of each port to go high -- unselecting the row would have been completed
        matrix_wait_for_port(GPIOB, GPIOB_BITMASK);
        // matrix_wait_for_port(GPIOC, GPIOC_BITMASK);
    }

    // Check if we've changed, return the last-read data
    bool changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
    if (changed) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    return changed;
}

void matrix_wait_for_interrupt(void) {
    // Set up row/col pins and attach callback
    for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
        setPinOutput(col_pins[i]);
        writePinLow(col_pins[i]);
    }
    for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
        setPinInputHigh(row_pins[i]);
        palEnableLineEvent(row_pins[i], PAL_EVENT_MODE_BOTH_EDGES);
    }

    // Wait for an interrupt
    __WFI();

    // Now that the interrupt has woken us up, reset all the row/col pins back to defaults
    for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
        palDisableLineEvent(row_pins[i]);
        writePinHigh(row_pins[i]);
        setPinInputHigh(row_pins[i]);
    }
    for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
        writePinHigh(col_pins[i]);
        setPinInputHigh(col_pins[i]);
    }
}

// bool matrix_scan_custom(matrix_row_t current_matrix[]) {
//     static matrix_row_t temp_matrix[MATRIX_COLS] = {0};

//     for (int current_row = 0; current_row < MATRIX_ROWS; ++current_row) {
//         // Keep track of the pin we're working with
//         pin_t curr_row_pin = row_pins[current_row];

//         // Setup the output row pin
//         setPinOutput(curr_row_pin);
//         writePinLow(curr_row_pin);
//         matrix_wait_for_pin(curr_row_pin, 0);

//         // Read the col ports
//         uint32_t gpio_b = palReadPort(GPIOB);
//         uint32_t gpio_a = palReadPort(GPIOA);

//         // Unselect the row pin
//         setPinInputHigh(curr_row_pin);

//         // Construct the packed bitmask for the pins
//         // uint32_t readback = ~(((gpio_b & GPIOB_BITMASK) >> GPIOB_OFFSET) | (((gpio_a & GPIOA_BITMASK) >> GPIOA_OFFSET) << GPIOB_COUNT));
//         uint32_t readback = ~(((gpio_a & GPIOA_BITMASK) >> GPIOA_OFFSET) | (((gpio_b & GPIOB_BITMASK) >> GPIOB_OFFSET) << GPIOA_COUNT));

//         // Inject values into the matrix
//         for (int i = 0; i < MATRIX_COLS; ++i) {
//             if (readback & (1 << i)) {
//                 temp_matrix[i] |= (1ul << current_row);
//             } else {
//                 temp_matrix[i] &= ~(1ul << current_row);
//             }
//         }

//         // Wait for readback of the unselected row to go high
//         matrix_wait_for_pin(curr_row_pin, 1);

//         // Wait for readback of each port to go high -- unselecting the row would have been completed
//         matrix_wait_for_port(GPIOB, GPIOB_BITMASK);
//         matrix_wait_for_port(GPIOA, GPIOA_BITMASK);
//     }

//     // Check if we've changed, return the last-read data
//     bool changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix)) != 0;
//     if (changed) {
//         memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
//     }
//     return changed;
// }

// void matrix_wait_for_interrupt(void) {
//     // Set up row/col pins and attach callback
//     for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
//         setPinOutput(row_pins[i]);
//         writePinLow(row_pins[i]);
//     }
//     for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
//         setPinInputHigh(col_pins[i]);
//         palEnableLineEvent(col_pins[i], PAL_EVENT_MODE_BOTH_EDGES);
//     }

//     // Wait for an interrupt
//     __WFI();

//     // Now that the interrupt has woken us up, reset all the row/col pins back to defaults
//     for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
//         palDisableLineEvent(col_pins[i]);
//         writePinHigh(col_pins[i]);
//         setPinInputHigh(col_pins[i]);
//     }
//     for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
//         writePinHigh(row_pins[i]);
//         setPinInputHigh(row_pins[i]);
//     }
// }

void housekeeping_task_kb(void) {
    if (last_input_activity_elapsed() > 250) {
        matrix_wait_for_interrupt();
    }
}
