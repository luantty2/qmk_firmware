#include QMK_KEYBOARD_H

enum custom_keycodes {
    DICTATION = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │ A │
     * └───┘
     */
    [0] = LAYOUT(TG(1), KC_B, KC_C, KC_7, KC_8, KC_9, KC_4, KC_UP, KC_6, KC_LEFT, KC_DOWN, KC_RGHT),
    [1] = LAYOUT(TG(0), KC_B, KC_C, KC_7, KC_8, KC_9, KC_4, KC_WH_U, KC_6, KC_BTN2, KC_WH_D, KC_BTN3)};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DICTATION:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                // tap_code16(S(KC_Z));
                host_system_send(0x9B);
            }
            else {
                host_system_send(0);
            }
            return true;
    }
    return true;
};