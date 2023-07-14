// Copyright 2018-2022 weimao (@luantty2)
// SPDX-License-Identifier: GPL-3.0-or-later
#define SEND_BUFFER_MASK(rb) (rb->buffer_mask)
#define REPORT_PACKET_SIZE 16

typedef size_t send_buffer_size_t;

typedef struct report_data_t {
    uint8_t data[REPORT_PACKET_SIZE];
} report_data_t;

typedef struct send_buffer_t {
    /** Buffer memory. */
    report_data_t *buffer;
    /** Buffer mask. */
    send_buffer_size_t buffer_mask;
    /** Index of tail. */
    send_buffer_size_t tail_index;
    /** Index of head. */
    send_buffer_size_t head_index;
} send_buffer_t;

void        send_buffer_init(send_buffer_t *buffer, report_data_t *buf, size_t buf_size);
void        send_buffer_queue(send_buffer_t *buffer, report_data_t data);
uint8_t     send_buffer_dequeue(send_buffer_t *buffer, report_data_t *data);
uint8_t     send_buffer_peek(send_buffer_t *buffer, report_data_t *data, send_buffer_size_t index);
inline bool send_buffer_is_empty(send_buffer_t *buffer) {
    return (buffer->head_index == buffer->tail_index);
}

inline bool send_buffer_is_full(send_buffer_t *buffer) {
    return ((buffer->head_index - buffer->tail_index) & SEND_BUFFER_MASK(buffer)) == SEND_BUFFER_MASK(buffer);
}

inline send_buffer_size_t send_buffer_num_items(send_buffer_t *buffer) {
    return ((buffer->head_index - buffer->tail_index) & SEND_BUFFER_MASK(buffer));
}
