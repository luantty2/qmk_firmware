// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#include "quantum.h"
#include "analog.h"
#include "mzh_wire.h"

extern MidiDevice midi_device;

#define ADC_DEADBAND 8

#define CON_DEADZONE_ENABLE
#define CON1_DEADZONE_VAL 120
#define CON2_DEADZONE_VAL 105
#define CON3_DEADZONE_VAL 108

#define CON1_LED_GPIO B12
#define CON2_LED_GPIO B4
#define CON3_LED_GPIO B14
#define CONX_LED_GPIO A15
#define CONY_LED_GPIO A9

#define CON1_ADC_PIN A2
#define CON2_ADC_PIN A1
#define CON3_ADC_PIN A3
#define CONX_ADC_PIN B1
#define CONY_ADC_PIN B0

static uint16_t last_val_con1;
static uint16_t last_val_con2;
static uint16_t last_val_con3;

static uint16_t last_val_conx;
static uint16_t last_val_cony;

static uint32_t fader_read_timer = 0;

static bool con1_muted = false;
static bool con2_muted = false;
static bool con3_muted = false;
static bool conx_muted = false;
static bool cony_muted = false;

static bool con1_inverted = false;
static bool con2_inverted = false;
static bool con3_inverted = false;
static bool conx_inverted = false;
static bool cony_inverted = false;

static void process_fader(pin_t pin, uint16_t *last_val, uint8_t cc, bool inverted, uint16_t deadzone_val) {
    uint16_t val = analogReadPin(pin);

    if (inverted) {
        val = 1023 - val; // 反转 10-bit ADC 值
    }

#ifdef CON_DEADZONE_ENABLE
    if (deadzone_val > 0) {
        // Clamp top and bottom to create symmetric deadzones
        if (val <= deadzone_val) {
            val = deadzone_val;
        }
        if (val >= 1023 - deadzone_val) {
            val = 1023 - deadzone_val;
        }
        // Shift to 0 base
        val = val - deadzone_val;
    }
#endif

    if (abs(val - *last_val) > ADC_DEADBAND) {
        *last_val = val;
#ifdef CON_DEADZONE_ENABLE
        if (deadzone_val > 0) {
            // Map (0 .. 1023 - 2*Deadzone) to (0 .. 127)
            val = ((uint32_t)val * 127) / (1023 - 2 * deadzone_val);
        } else {
            val >>= 3;
        }
#else
        val >>= 3;
#endif
        midi_send_cc(&midi_device, 0, cc, val);
    }
}

static inline void init_led_pin(pin_t pin) {
    gpio_set_pin_output(pin);
    gpio_write_pin_high(pin);
}

// Helper to toggle mute state and update LED
static void toggle_channel_mute(int channel) {
    switch (channel) {
        case 0:
            con1_muted = !con1_muted;
            gpio_write_pin(CON1_LED_GPIO, !con1_muted);
            break;
        case 1:
            con2_muted = !con2_muted;
            gpio_write_pin(CON2_LED_GPIO, !con2_muted);
            break;
        case 2:
            con3_muted = !con3_muted;
            gpio_write_pin(CON3_LED_GPIO, !con3_muted);
            break;
        case 3:
            conx_muted = !conx_muted;
            gpio_write_pin(CONX_LED_GPIO, !conx_muted);
            break;
        case 4:
            cony_muted = !cony_muted;
            gpio_write_pin(CONY_LED_GPIO, !cony_muted);
            break;
    }
}

// Tap Dance Callbacks
void td_con1_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        toggle_channel_mute(0);
    } else if (state->count == 2) {
        con1_inverted = !con1_inverted;
    }
}
void td_con1_reset(tap_dance_state_t *state, void *user_data) {}

void td_con2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        toggle_channel_mute(1);
    } else if (state->count == 2) {
        con2_inverted = !con2_inverted;
    }
}
void td_con2_reset(tap_dance_state_t *state, void *user_data) {}

void td_con3_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        toggle_channel_mute(2);
    } else if (state->count == 2) {
        con3_inverted = !con3_inverted;
    }
}
void td_con3_reset(tap_dance_state_t *state, void *user_data) {}

void td_conx_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        toggle_channel_mute(3);
    } else if (state->count == 2) {
        conx_inverted = !conx_inverted;
    }
}
void td_conx_reset(tap_dance_state_t *state, void *user_data) {}

void td_cony_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        toggle_channel_mute(4);
    } else if (state->count == 2) {
        cony_inverted = !cony_inverted;
    }
}
void td_cony_reset(tap_dance_state_t *state, void *user_data) {}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CON1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_con1_finished, td_con1_reset),
    [TD_CON2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_con2_finished, td_con2_reset),
    [TD_CON3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_con3_finished, td_con3_reset),
    [TD_CONX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_conx_finished, td_conx_reset),
    [TD_CONY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_cony_finished, td_cony_reset),
};

void keyboard_post_init_kb(void) {
    init_led_pin(CON1_LED_GPIO);
    init_led_pin(CON2_LED_GPIO);
    init_led_pin(CON3_LED_GPIO);
    init_led_pin(CONX_LED_GPIO);
    init_led_pin(CONY_LED_GPIO);
}

void housekeeping_task_kb(void) {
    uint32_t timer_now = timer_read();
    if (TIMER_DIFF_32(timer_now, fader_read_timer) >= 10) {
        fader_read_timer = timer_now;
        if (!con1_muted) {
            process_fader(CON1_ADC_PIN, &last_val_con1, 105, con1_inverted, CON1_DEADZONE_VAL);
        }
        if (!con2_muted) {
            process_fader(CON2_ADC_PIN, &last_val_con2, 106, con2_inverted, CON2_DEADZONE_VAL);
        }
        if (!con3_muted) {
            process_fader(CON3_ADC_PIN, &last_val_con3, 107, con3_inverted, CON3_DEADZONE_VAL);
        }
        if (!conx_muted) {
            process_fader(CONX_ADC_PIN, &last_val_conx, 110, conx_inverted, 0);
        }
        if (!cony_muted) {
            process_fader(CONY_ADC_PIN, &last_val_cony, 111, cony_inverted, 0);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MUTE_CON1:
            if (record->event.pressed) {
                toggle_channel_mute(0);
                // Do something when pressed
            }
            return false; // Skip all further processing of this key
        case MUTE_CON2:
            if (record->event.pressed) {
                toggle_channel_mute(1);
            }
            return false;
        case MUTE_CON3:
            if (record->event.pressed) {
                toggle_channel_mute(2);
            }
            return false;
        case MUTE_CONX:
            if (record->event.pressed) {
                toggle_channel_mute(3);
            }
            return false;
        case MUTE_CONY:
            if (record->event.pressed) {
                toggle_channel_mute(4);
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}
