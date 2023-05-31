#include QMK_KEYBOARD_H

enum layers{
  MAC_BASE,
  MAC_FUNC,
  WIN_BASE,
  WIN_FUNC,
};

enum custom_keycodes_via {
    Z_FIT = QK_KB_0,
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
    MK_OUT,  //15

    MACOS_MISSION_CONTROL,
    MACOS_LAUNCHPAD,
    MACOS_SEARCH,
    MACOS_DICTATION,
    MACOS_DO_NOT_DISTURB,

    TO_WIN,
    TO_MACOS,

    MACOS_LOPT,
    MACOS_ROPT,
    MACOS_LCMD,
    MACOS_RCMD,

    FUNC_TOG,
};

#define M_MC    MACOS_MISSION_CONTROL
#define M_LPAD   MACOS_LAUNCHPAD
#define M_SEAR   MACOS_SEARCH
#define M_DICT   MACOS_DICTATION
#define M_DND    MACOS_DO_NOT_DISTURB

typedef union {
  uint32_t raw;
  struct {
    bool     func_toggle :1;
  };
} func_config_t;

func_config_t func_config;

static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_ESC, KC_BRID, KC_BRIU, M_MC, M_SEAR, M_DICT, M_DND, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR, KC_SCRL, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        Z_FIT, Z_IN, Z_OUT, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, PRE_E, NXT_E,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_END, KC_PGDN, KC_P7, KC_P8, KC_P9, KC_PPLS, PL_PS, STOP, RVS,
        BLADE, TM_IN, TM_OUT, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P4, KC_P5, KC_P6,
        INS, APED, OVWTE, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3, KC_PENT,
        MK_IN, MK_OUT, KC_LCTL, MACOS_LOPT, MACOS_LCMD, KC_SPC, MACOS_RCMD, MACOS_ROPT, MO(MAC_FUNC), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT
    ),
    [MAC_FUNC] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, FUNC_TOG, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO_WIN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [WIN_BASE] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SCRL, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        Z_FIT, Z_IN, Z_OUT, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP, KC_NUM, KC_PSLS, KC_PAST, KC_PMNS, PRE_E, NXT_E,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_END, KC_PGDN, KC_P7, KC_P8, KC_P9, KC_PPLS, PL_PS, STOP, RVS,
        BLADE, TM_IN, TM_OUT, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_P4, KC_P5, KC_P6,
        INS, APED, OVWTE, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_P1, KC_P2, KC_P3, KC_PENT,
        MK_IN, MK_OUT, KC_LCTL, KC_LWIN, KC_LALT, KC_SPC, KC_RALT, KC_RWIN, MO(WIN_FUNC), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT
    ),
    [WIN_FUNC] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO_MACOS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
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
            return false;
        case Z_IN:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(G(KC_EQL));
            }
            return false;
        case Z_OUT:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(G(KC_MINS));
            }
            return false;
        case PRE_E:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_SCLN);
            }
            return false;
        case NXT_E:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_QUOT);
            }
            return false; 
        case PL_PS:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_L);
            }
            return false; 
        case STOP:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_K);
            }
            return false; 
        case RVS:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_J);
            }
            return false; 
        case BLADE:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(G(KC_B));
            }
            return false; 
        case TM_IN:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(A(KC_LBRC));
            }
            return false; 
        case TM_OUT:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code16(A(KC_RBRC));
            }
            return false; 
        case INS:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_W);
            }
            return false; 
        case APED:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_E);
            }
            return false; 
        case OVWTE:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_D);
            }
            return false; 
        case MK_IN:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_I);
            }
            return false; 
        case MK_OUT:
            if (record->event.pressed) {
                // midi_send_cc(&midi_device, midi_config.channel, 24, MIDI_CC_ON);
                tap_code(KC_O);
            }
            return false; 
        case KC_BRID:
            if (func_config.func_toggle) {
                if (record->event.pressed) {
                    register_code(KC_F1);
                }
                else {
                    unregister_code(KC_F1);
                }
                return false;
            } else {
                return true;
            }
        case KC_BRIU:
            if (func_config.func_toggle) {
                if (record->event.pressed) {
                    register_code(KC_F2);
                }
                else {
                    unregister_code(KC_F2);
                }
                return false;
            } else {
                return true;
            }
        case MACOS_MISSION_CONTROL:
            if (record->event.pressed) {
                if (func_config.func_toggle) {
                    register_code(KC_F3);
                } else {
                    host_consumer_send(0x29F);
                }
            } else {
                if (func_config.func_toggle) {
                    unregister_code(KC_F3);
                } else {
                    host_consumer_send(0);
                }
            }
            return false;
        case MACOS_LAUNCHPAD:
            if (record->event.pressed) {
                if (func_config.func_toggle) {
                    register_code(KC_F3);
                } else {
                    host_consumer_send(0x2A0);
                }
            } else {
                if (func_config.func_toggle) {
                    unregister_code(KC_F3);
                } else {
                    host_consumer_send(0);
                }
            }
        case MACOS_SEARCH:
            if (record->event.pressed) {
                if (func_config.func_toggle) {
                    register_code(KC_F4);
                } else {
                    host_consumer_send(0x221);
                }
            } else {
                if (func_config.func_toggle) {
                    unregister_code(KC_F4);
                } else {
                    host_consumer_send(0);
                }
            }
            return false;
        case MACOS_DICTATION:
            if (record->event.pressed) {
                if (func_config.func_toggle) {
                    register_code(KC_F5);
                } else {
                    host_consumer_send(0xCF);
                }
            } else {
                if (func_config.func_toggle) {
                    unregister_code(KC_F5);
                } else {
                    host_consumer_send(0);
                }
            }
            return false;
        case MACOS_DO_NOT_DISTURB:
            if (record->event.pressed) {
                if (func_config.func_toggle) {
                    register_code(KC_F6);
                } else {
                    host_system_send(0x9B);
                }
            } else {
                if (func_config.func_toggle) {
                    unregister_code(KC_F6);
                } else {
                    host_system_send(0);
                }
            }
            return false;
        case KC_MPRV:
            if (func_config.func_toggle) {
                if (record->event.pressed) {
                    register_code(KC_F7);
                }
                else {
                    unregister_code(KC_F7);
                }
                return false;
            } else {
                return true;
            }
        case KC_MPLY:
            if (func_config.func_toggle) {
                if (record->event.pressed) {
                    register_code(KC_F8);
                }
                else {
                    unregister_code(KC_F8);
                }
                return false;
            } else {
                return true;
            }
        case KC_MNXT:
            if (func_config.func_toggle) {
                if (record->event.pressed) {
                    register_code(KC_F9);
                }
                else {
                    unregister_code(KC_F9);
                }
                return false;
            } else {
                return true;
            }
        case KC_MUTE:
            if (func_config.func_toggle) {
                if (record->event.pressed) {
                    register_code(KC_F10);
                }
                else {
                    unregister_code(KC_F10);
                }
                return false;
            } else {
                return true;
            }
        case KC_VOLD:
            if (func_config.func_toggle) {
                if (record->event.pressed) {
                    register_code(KC_F11);
                }
                else {
                    unregister_code(KC_F11);
                }
                return false;
            } else {
                return true;
            }
        case KC_VOLU:
            if (func_config.func_toggle) {
                if (record->event.pressed) {
                    register_code(KC_F12);
                }
                else {
                    unregister_code(KC_F12);
                }
                return false;
            } else {
                return true;
            }  
        case TO_WIN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(2);
                rgb_indicator_leds_blink();
            }
            return false;
        case TO_MACOS:
            if (record->event.pressed) {
                set_single_persistent_default_layer(0);
                rgb_indicator_leds_blink();
            }
            return false;
        case MACOS_LOPT:
        case MACOS_ROPT:
        case MACOS_LCMD:
        case MACOS_RCMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - MACOS_LOPT]);
            } else {
                unregister_code(mac_keycode[keycode - MACOS_LOPT]);
            }
            return false;  // Skip all further processing of this key
        case FUNC_TOG:
            if (record->event.pressed) {
                func_config.func_toggle ^= 1;
                 eeconfig_update_user(func_config.raw);
            }
            return false;
         default:
            return true; // Process all other keycodes normally
    }
    return true;
};

void keyboard_post_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  func_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  func_config.raw = 0;
  func_config.func_toggle = false;
  eeconfig_update_user(func_config.raw); // Write default value to EEPROM now
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(C(KC_PMNS), C(KC_PPLS)), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [1] = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO) },
    [2] = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO) },
    [3] = { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO) },
};
#endif