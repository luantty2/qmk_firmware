#include QMK_KEYBOARD_H

enum custom_keycodes_via {
    Z_FIT = USER00,
    Z_IN, //1
    Z_OUT,  //2
    PRE_E,  //3
    NXT_E,  //4
    PL_PS,  //5
    STOP,  //6
    RVS,  //7
    BLADE,  //8
    TM_IN,  //9
    TM_OUT,  //10
    INS,  //11
    APED,  //12
    OVWTE,  //13
    MK_IN,  //14
    MK_OUT  //15
};

enum custom_keycodes {
    MACOS_MISSION_CONTROL = SAFE_RANGE,
    MACOS_LAUNCHPAD,
    MACOS_SEARCH,
    MACOS_DICTATION,
    MACOS_DO_NOT_DISTURB,

};

#define M_MC    MACOS_MISSION_CONTROL
#define M_LPAD   MACOS_LAUNCHPAD
#define M_SEAR   MACOS_SEARCH
#define M_DICT   MACOS_DICTATION
#define M_DND    MACOS_DO_NOT_DISTURB

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SCRL, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        USER00, USER01, USER02, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, USER03, USER04,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_END, KC_PGDN, KC_P7, KC_P8, KC_P9, KC_PPLS, USER05, USER06, USER07,
        USER08, USER09, USER10, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P4, KC_P5, KC_P6,
        USER11, USER12, USER13, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3, KC_PENT,
        USER14, USER15, KC_LCTL, KC_LWIN, KC_LALT, KC_SPC, KC_RALT, KC_RWIN, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT
    ),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BRID, KC_BRIU, M_MC, M_SEAR, M_DICT, M_DND, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case Z_FIT:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(S(KC_Z));
                // host_consumer_send(0x221);
            }
            // else {
            //     host_consumer_send(0);
            // }
            return true;
        case Z_IN:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(G(KC_EQL));
            }
            return true;
        case Z_OUT:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(G(KC_MINS));
            }
            return true;
        case PRE_E:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_SCLN);
            }
            return true;
        case NXT_E:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_QUOT);
            }
            return true; 
        case PL_PS:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_L);
            }
            return true; 
        case STOP:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_K);
            }
            return true; 
        case RVS:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_J);
            }
            return true; 
        case BLADE:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(G(KC_B));
            }
            return true; 
        case TM_IN:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(A(KC_LBRC));
            }
            return true; 
        case TM_OUT:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(A(KC_RBRC));
            }
            return true; 
        case INS:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_W);
            }
            return true; 
        case APED:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_E);
            }
            return true; 
        case OVWTE:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_D);
            }
            return true; 
        case MK_IN:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_I);
            }
            return true; 
        case MK_OUT:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_O);
            }
            return true; 
         default:
            return true; // Process all other keycodes normally
    }
    return true;
};

// bool encoder_update_user(uint8_t index, bool clockwise) {
//     if (index == 0) { /* First encoder */
//         if (clockwise) {
//             // tap_code_delay(C(KC_PPLS), 10);
//             tap_code16(C(KC_PPLS));
//         } else {
//             // tap_code_delay(C(KC_PMNS), 10);
//             tap_code16(C(KC_PMNS));
//         }
//     } else if (index == 1) { /* Second encoder */
//         if (clockwise) {
//             tap_code_delay(KC_RGHT, 10);
//         } else {
//             tap_code_delay(KC_LEFT, 10);
//         }
//     } else if (index == 2) { /* Second encoder */
//         if (clockwise) {
//             tap_code_delay(KC_RGHT, 10);
//         } else {
//             tap_code_delay(KC_LEFT, 10);
//         }
//     }
//     return false;
// }

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(C(KC_PMNS), C(KC_PPLS)), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [1] = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO) },
    [2] = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO) },
    [3] = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO) },
};
#endif