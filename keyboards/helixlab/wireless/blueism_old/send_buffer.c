// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "send_buffer.h"

void send_buffer_init(send_buffer_t *buffer, report_data_t *buf, size_t buf_size) {
    // _Static_assert((buf_size & (buf_size - 1)) == 0, "hello");
    buffer->buffer      = buf;
    buffer->buffer_mask = buf_size - 1;
    buffer->tail_index  = 0;
    buffer->head_index  = 0;
}

void send_buffer_queue(send_buffer_t *buffer, report_data_t data) {
    /* Is buffer full? */
    if (send_buffer_is_full(buffer)) {
        /* Is going to overwrite the oldest data */
        /* Increase tail index */
        buffer->tail_index = ((buffer->tail_index + 1) & SEND_BUFFER_MASK(buffer));
    }

    /* Place data in buffer */
    buffer->buffer[buffer->head_index] = data;
    buffer->head_index                 = ((buffer->head_index + 1) & SEND_BUFFER_MASK(buffer));
}

uint8_t send_buffer_dequeue(send_buffer_t *buffer, report_data_t *data) {
    if (send_buffer_is_empty(buffer)) {
        /* No items */
        return 0;
    }
    *data              = buffer->buffer[buffer->tail_index];
    buffer->tail_index = ((buffer->tail_index + 1) & SEND_BUFFER_MASK(buffer));
    return 1;
}

uint8_t send_buffer_peek(send_buffer_t *buffer, report_data_t *data, send_buffer_size_t index) {
    if (index >= send_buffer_num_items(buffer)) {
        /* No items at index */
        return 0;
    }
    /* Add index to pointer */
    send_buffer_size_t data_index = ((buffer->tail_index + index) & SEND_BUFFER_MASK(buffer));
    *data                         = buffer->buffer[data_index];
    return 1;
}

extern inline bool               send_buffer_is_empty(send_buffer_t *buffer);
extern inline bool               send_buffer_is_full(send_buffer_t *buffer);
extern inline send_buffer_size_t send_buffer_num_items(send_buffer_t *buffer);
