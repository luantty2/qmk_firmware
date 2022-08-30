#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │ A │
     * └───┘
     */
    [0] = LAYOUT(
        S(KC_Z), KC_B,KC_C,
        KC_7,KC_8,KC_9,
        KC_4,KC_UP,KC_6,
        KC_LEFT,KC_DOWN,KC_RGHT
    )
};
