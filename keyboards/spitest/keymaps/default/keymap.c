#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │ A │
     * └───┘
     */
    [0] = LAYOUT(
        KC_A
    )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_A:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(OUT_BT);
                tap_code(KC_A);
            }
            return true;
         default:
            return true; // Process all other keycodes normally
    }
    return true;
};