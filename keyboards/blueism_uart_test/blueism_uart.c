// Copyright 2026 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "uart.h"
#include "outputselect.h"
#include "blueism_config.h"
#include "blueism_uart.h"

static blueism_hid_6kro_payload_t          tx_6kro_payload;
static blueism_hid_nkro_payload_t          tx_nkro_payload;
static blueism_hid_system_ctrl_payload_t   tx_system_ctrl_payload;
static blueism_hid_consumer_ctrl_payload_t tx_consumer_ctrl_payload;
static blueism_hid_mouse_payload_t         tx_mouse_payload;

typedef enum {
    BLUEISM_UART_RX_WAIT_HEADER1,
    BLUEISM_UART_RX_WAIT_HEADER2,
    BLUEISM_UART_RX_CMD,
    BLUEISM_UART_RX_LEN,
    BLUEISM_UART_RX_PAYLOAD,
    BLUEISM_UART_RX_CRC,
} blueism_uart_rx_state_t;

typedef struct {
    blueism_uart_rx_state_t state;
    uint8_t                 cmd;
    uint8_t                 expected_len;
    uint8_t                 current_len;
    uint8_t                 payload[BLUEISM_UART_RX_PAYLOAD_MAX_LEN];
    uint8_t                 crc;
} blueism_uart_rx_parser_t;

static blueism_uart_rx_parser_t blueism_uart_rx_parser;

static void blueism_uart_rx_parser_reset(void) {
    blueism_uart_rx_parser.state          = BLUEISM_UART_RX_WAIT_HEADER1;
    blueism_uart_rx_parser.cmd            = 0;
    blueism_uart_rx_parser.expected_len   = 0;
    blueism_uart_rx_parser.current_len    = 0;
    blueism_uart_rx_parser.crc            = 0;
}

static void blueism_apply_hid_led_state(uint8_t led_state) {
    bool caps_on = (led_state & BLUEISM_HID_LED_CAPS_LOCK) != 0;

    gpio_write_pin(CAPS_LED_OUTPUT_PIN, caps_on ? !CAPS_LED_ACTIVE_LOW : CAPS_LED_ACTIVE_LOW);
}

void blueism_init(void) {
    set_output(BLUEISM_DEFAULT_OUTPUT);

    palSetLineMode(UART_CTS_PIN, PAL_MODE_ALTERNATE(UART_CTS_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
    palSetLineMode(UART_RTS_PIN, PAL_MODE_ALTERNATE(UART_RTS_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
    uart_init(BLUEISM_UART_BAUDRATE);
    gpio_set_pin_input(BLUEISM_NRF_WAKEUP_PIN); // High-Z
    gpio_set_pin_input_low(BLUEISM_NRF_SLEEP_STATUS_PIN);

    gpio_set_pin_output(CAPS_LED_OUTPUT_PIN);
    gpio_write_pin_high(CAPS_LED_OUTPUT_PIN);

    blueism_uart_rx_parser_reset();
}

static uint8_t crc8_byte_update(uint8_t crc, uint8_t data_byte) {
    crc ^= data_byte;
    for (int i = 0; i < 8; i++) {
        if ((crc & 0x80) != 0) {
            crc = (crc << 1) ^ BLUEISM_UART_CRC8_POLYNOMIAL;
        } else {
            crc <<= 1;
        }
    }
    return crc;
}

static void blueism_uart_rx_handle_packet(uint8_t cmd, const uint8_t *payload, uint8_t payload_len) {
    switch (cmd) {
        case BLUEISM_UART_CMD_SYS_PING:
            if (payload_len == 4 && memcmp(payload, "PONG", 4) == 0) {
                dprintf("Blueism UART pong received\n");
            } else {
                dprintf("Blueism UART ping response with unexpected payload len=%u\n", payload_len);
            }
            break;
        case BLUEISM_UART_CMD_SYS_GET_VERSION:
            if (payload_len == 4) {
                dprintf("Blueism nRF version %u.%u.%u.%u\n",
                        payload[0], payload[1], payload[2], payload[3]);
            } else {
                dprintf("Blueism UART version response with unexpected payload len=%u\n", payload_len);
            }
            break;
        case BLUEISM_UART_CMD_HID_KEYBOARD_LEDS:
            if (payload_len == 1) {
                blueism_apply_hid_led_state(payload[0]);
                dprintf("Blueism HID LED state=0x%02X\n", payload[0]);
            } else {
                dprintf("Blueism UART HID LED state with unexpected payload len=%u\n", payload_len);
            }
            break;
        default:
            dprintf("Blueism UART RX unknown cmd=0x%02X len=%u\n", cmd, payload_len);
            break;
    }
}

static void blueism_uart_rx_input_byte(uint8_t byte) {
    switch (blueism_uart_rx_parser.state) {
        case BLUEISM_UART_RX_WAIT_HEADER1:
            if (byte == BLUEISM_UART_FRAME_HEADER_BYTE1) {
                blueism_uart_rx_parser.state = BLUEISM_UART_RX_WAIT_HEADER2;
            }
            break;

        case BLUEISM_UART_RX_WAIT_HEADER2:
            if (byte == BLUEISM_UART_FRAME_HEADER_BYTE2) {
                blueism_uart_rx_parser.state = BLUEISM_UART_RX_CMD;
            } else if (byte == BLUEISM_UART_FRAME_HEADER_BYTE1) {
                blueism_uart_rx_parser.state = BLUEISM_UART_RX_WAIT_HEADER2;
            } else {
                blueism_uart_rx_parser_reset();
            }
            break;

        case BLUEISM_UART_RX_CMD:
            blueism_uart_rx_parser.cmd            = byte;
            blueism_uart_rx_parser.crc            = crc8_byte_update(blueism_uart_rx_parser.crc, byte);
            blueism_uart_rx_parser.state          = BLUEISM_UART_RX_LEN;
            break;

        case BLUEISM_UART_RX_LEN:
            blueism_uart_rx_parser.expected_len   = byte;
            blueism_uart_rx_parser.current_len    = 0;
            blueism_uart_rx_parser.crc            = crc8_byte_update(blueism_uart_rx_parser.crc, byte);

            if (blueism_uart_rx_parser.expected_len == 0) {
                blueism_uart_rx_parser.state = BLUEISM_UART_RX_CRC;
            } else if (blueism_uart_rx_parser.expected_len > BLUEISM_UART_RX_PAYLOAD_MAX_LEN) {
                dprintf("Blueism UART RX payload too large: %u\n", blueism_uart_rx_parser.expected_len);
                blueism_uart_rx_parser_reset();
            } else {
                blueism_uart_rx_parser.state = BLUEISM_UART_RX_PAYLOAD;
            }
            break;

        case BLUEISM_UART_RX_PAYLOAD:
            blueism_uart_rx_parser.payload[blueism_uart_rx_parser.current_len++] = byte;
            blueism_uart_rx_parser.crc = crc8_byte_update(blueism_uart_rx_parser.crc, byte);

            if (blueism_uart_rx_parser.current_len == blueism_uart_rx_parser.expected_len) {
                blueism_uart_rx_parser.state = BLUEISM_UART_RX_CRC;
            }
            break;

        case BLUEISM_UART_RX_CRC:
            if (byte == blueism_uart_rx_parser.crc) {
                blueism_uart_rx_handle_packet(blueism_uart_rx_parser.cmd, blueism_uart_rx_parser.payload, blueism_uart_rx_parser.expected_len);
            } else {
                dprintf("Blueism UART RX CRC mismatch calc=0x%02X recv=0x%02X\n", blueism_uart_rx_parser.crc, byte);
            }
            blueism_uart_rx_parser_reset();
            break;
    }
}

static void blueism_uart_rx_task(void) {
    while (uart_available()) {
        blueism_uart_rx_input_byte(uart_read());
    }
}

void housekeeping_task_blueism(void) {
    blueism_uart_rx_task();
}

blueism_uart_tx_status_t blueism_uart_send_packet(uint8_t cmd, const uint8_t *payload, uint8_t payload_len) {
    if (payload_len > BLUEISM_UART_TX_PAYLOAD_MAX_LEN) {
        dprintf("Invalid payload length: %d\n", payload_len);
        return -BLUEISM_UART_TX_FAILED;
    }

    uint8_t tx_packet[BLUEISM_UART_TX_PACKET_MAX_LEN];
    uint8_t tx_len = 0;

    tx_packet[tx_len++] = BLUEISM_UART_FRAME_HEADER_BYTE1;
    tx_packet[tx_len++] = BLUEISM_UART_FRAME_HEADER_BYTE2;
    tx_packet[tx_len++] = cmd;
    tx_packet[tx_len++] = payload_len;

    if (payload_len > 0 && payload) {
        memcpy(&tx_packet[tx_len], payload, payload_len);
        tx_len += payload_len;
    }

    uint8_t crc = 0;
    crc         = crc8_byte_update(crc, cmd);
    crc         = crc8_byte_update(crc, payload_len);
    for (int i = 0; i < payload_len; i++) {
        crc = crc8_byte_update(crc, payload[i]);
    }

    tx_packet[tx_len++] = crc;

    for (uint8_t i = 0; i < tx_len; i++) {
        dprintf("%02x ", tx_packet[i]);
    }
    dprintf("\n");

    if (gpio_read_pin(BLUEISM_NRF_SLEEP_STATUS_PIN) == 0) {
        gpio_set_pin_output_open_drain(BLUEISM_NRF_WAKEUP_PIN);
        gpio_write_pin_low(BLUEISM_NRF_WAKEUP_PIN);
        wait_ms(BLUEISM_NRF_WAKE_PULSE_MS);
        gpio_set_pin_input(BLUEISM_NRF_WAKEUP_PIN); // Back to High-Z
        wait_ms(BLUEISM_NRF_WAKE_DELAY_MS);
    }

    uart_transmit(tx_packet, tx_len);
    return BLUEISM_UART_TX_OK;
}

void blueism_uart_send_ping(void) {
    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_SYS_PING, NULL, 0);

    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send Ping command\n");
    }
}

void blueism_uart_send_reset(void) {
    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_SYS_RESET, NULL, 0);

    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send Reset command\n");
    }
}

void blueism_uart_send_get_version(void) {
    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_SYS_GET_VERSION, NULL, 0);

    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send Get Version command\n");
    }
}

void blueism_uart_send_keyboard_report(report_keyboard_t *report) {
    tx_6kro_payload.mods = report->mods;
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        tx_6kro_payload.keys[i] = report->keys[i];
    }

    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_HID_6KRO, (const uint8_t *)&tx_6kro_payload, sizeof(blueism_hid_6kro_payload_t));
    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send keyboard report\n");
    }
}

void blueism_uart_send_nkro_report(report_nkro_t *report) {
    tx_nkro_payload.mods = report->mods;
    for (uint8_t i = 0; i < NKRO_REPORT_BITS; i++) {
        tx_nkro_payload.bits[i] = report->bits[i];
    }

    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_HID_NKRO, (const uint8_t *)&tx_nkro_payload, sizeof(blueism_hid_nkro_payload_t));
    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send NKRO keyboard report\n");
    }
}

void blueism_uart_send_system_report(uint16_t usage) {
    tx_system_ctrl_payload.usage_high = (uint8_t)((usage >> 8) & 0xFF);
    tx_system_ctrl_payload.usage_low  = (uint8_t)(usage & 0xFF);

    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_HID_SYSTEM_CTRL, (const uint8_t *)&tx_system_ctrl_payload, sizeof(blueism_hid_system_ctrl_payload_t));

    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send System Control report\n");
    }
}

void blueism_uart_send_consumer_report(uint16_t usage) {
    tx_consumer_ctrl_payload.usage_high = (uint8_t)((usage >> 8) & 0xFF);
    tx_consumer_ctrl_payload.usage_low  = (uint8_t)(usage & 0xFF);

    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_HID_CONSUMER_CTRL, (const uint8_t *)&tx_consumer_ctrl_payload, sizeof(blueism_hid_consumer_ctrl_payload_t));

    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send Consumer Control report\n");
    }
}

void blueism_uart_send_mouse_report(report_mouse_t *report) {
    tx_mouse_payload.buttons = report->buttons;
    tx_mouse_payload.wheel   = report->v;

    int16_t x = (int16_t)report->x;
    int16_t y = (int16_t)report->y;

    tx_mouse_payload.xy_packed[0] = (uint8_t)(x & 0xFF);
    tx_mouse_payload.xy_packed[1] = (uint8_t)(((x >> 8) & 0x0F) | ((y & 0x0F) << 4));
    tx_mouse_payload.xy_packed[2] = (uint8_t)((y >> 4) & 0xFF);

    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_HID_MOUSE, (const uint8_t *)&tx_mouse_payload, sizeof(blueism_hid_mouse_payload_t));

    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send Mouse report\n");
    }
}

void blueism_uart_select_ble_id(uint8_t id) {
    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_BLE_SELECT_ID, &id, 1);

    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send Select ID command\n");
    }
}

void blueism_uart_erase_current_peer(void) {
    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_BLE_ERASE_BOND, NULL, 0);

    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send Erase Peer command\n");
    }
}

void blueism_uart_select_dongle(void) {
    blueism_uart_tx_status_t ret = blueism_uart_send_packet(BLUEISM_UART_CMD_BLE_SELECT_DONGLE, NULL, 0);

    if (ret != BLUEISM_UART_TX_OK) {
        dprintf("Failed to send Select Dongle command\n");
    }
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
    blueism_uart_send_keyboard_report(report);
}

void bluetooth_send_nkro(report_nkro_t *report) {
    blueism_uart_send_nkro_report(report);
}

void bluetooth_send_system(uint16_t usage) {
    blueism_uart_send_system_report(usage);
}

void bluetooth_send_consumer(uint16_t usage) {
    blueism_uart_send_consumer_report(usage);
}

void bluetooth_send_mouse(report_mouse_t *report) {
    blueism_uart_send_mouse_report(report);
}

bool bluetooth_can_send_nkro(void) {
    return true;
}
