#include QMK_KEYBOARD_H

#define ZM_FIT S(KC_Z)
#define ZM_IN G(KC_EQL)
#define ZM_OUT G(KC_MINS)
#define PREV_EDIT KC_SCLN
#define NXT_EDIT KC_QUOT
#define PLY_PAUS KC_L
#define STOP KC_K
#define REVERSE KC_J
#define BLADE G(KC_B)
#define TRIM_IN A(KC_LBRC)
#define TRIM_OUT A(KC_RBRC)
#define INSERT KC_W
#define APPEND KC_E
#define OVWRITE KC_D
#define MARK_IN KC_I
#define MARK_OUT KC_O

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SCRL, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        ZM_FIT, ZM_IN, ZM_OUT, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, PREV_EDIT, NXT_EDIT,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_END, KC_PGDN, KC_P7, KC_P8, KC_P9, KC_PPLS, PLY_PAUS, STOP, REVERSE,
        BLADE, TRIM_IN, TRIM_OUT, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P4, KC_P5, KC_P6,
        INSERT, APPEND, OVWRITE, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3, KC_PENT, KC_NO,
        MARK_IN, MARK_OUT, KC_LCTL, KC_LWIN, KC_LALT, KC_SPC, KC_RALT, KC_RWIN, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            // tap_code_delay(C(KC_PPLS), 10);
            tap_code16(C(KC_PPLS));
        } else {
            // tap_code_delay(C(KC_PMNS), 10);
            tap_code16(C(KC_PMNS));
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code_delay(KC_RGHT, 10);
        } else {
            tap_code_delay(KC_LEFT, 10);
        }
    } else if (index == 2) { /* Second encoder */
        if (clockwise) {
            tap_code_delay(KC_RGHT, 10);
        } else {
            tap_code_delay(KC_LEFT, 10);
        }
    }
    return false;
}