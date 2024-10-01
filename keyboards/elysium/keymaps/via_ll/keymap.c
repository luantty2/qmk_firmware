// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "blueism.h"
#include "battery.h"
#include "max1704x.h"

enum keycodes{
    BLUETOOTH_UNPAIR = QK_KB_0,
    DONGLE_UNPAIR,
    BAT_LVL,
    MODULE_RESET,
    GET_VER,
    SEL_BLE,  //Deprecated
    SEL_2G4,  //Deprecated
    ADVANCED_UNPAIR,
    // BT_ID_1,
    // BT_ID_2,
    // BT_ID_3,
    // BT_ID_4,
};

#define BT_UNPR BLUETOOTH_UNPAIR
#define DG_UNPR DONGLE_UNPAIR
#define M_RESET MODULE_RESET
#define AVD_UNP ADVANCED_UNPAIR

static char bat_str[2];
static uint16_t adv_unpair_key_timer;
static uint16_t sel_ble_key_timer;
static uint16_t sel_2g4_key_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,   KC_GRV,   KC_1,   KC_2,     KC_3,    KC_4,    KC_5,   KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_PGUP,  KC_TAB,   KC_Q,   KC_W,     KC_E,    KC_R,    KC_T,   KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_PGDN,  KC_CAPS,  KC_A,   KC_S,     KC_D,    KC_F,    KC_G,   KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_END,   KC_LSFT,  KC_Z,   KC_X,     KC_C,    KC_V,    KC_B,   KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_UP,    KC_RSFT,
        KC_LCTL,  KC_LGUI,  DG_UNPR,  KC_LALT,  KC_SPC,  KC_SPC,  MO(1),  KC_LEFT,  KC_DOWN,  KC_RIGHT
    ),
    [1] = LAYOUT(
        QK_BOOT,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,  _______,
        _______,  _______,  RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  M_RESET,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  AVD_UNP,  _______,  GET_VER,  BAT_LVL,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  GU_TOGG,  _______,  AG_TOGG,  _______,  _______,  _______,  _______,  _______,  _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_BOOT:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    eeconfig_init();
                    reset_keyboard();
                }
            } else {
                // Do something else when release
            }
            return false;
        case BLUETOOTH_UNPAIR:
            if (record->event.pressed) {
                // Do something when pressed
                // if (get_mods() & MOD_MASK_SHIFT) {
                //     blueism_unpair();
                // }
                blueism_ble_button_unpair();
            } else {
                // Do something else when release
            }
            return false;
        case DONGLE_UNPAIR:
            if (record->event.pressed) {
                // Do something when pressed
                // blueism_unpair();
                blueism_dongle_button_unpair();
            } else {
                // Do something else when release
            }
            return false;
        case BAT_LVL:
            if (record->event.pressed) {
                // Do something when pressed
                get_battery_lvl_str(bat_str, ARRAY_SIZE(bat_str), true);
                send_string(bat_str);
                // send_byte(get_battery_lvl());
            } else {
                // Do something else when release
            }
            return false;
        case MODULE_RESET:
            if (record->event.pressed) {
                // Do something when pressed

                    writePinLow(NRF_RESET);
                    // matrix_io_delay();
                    wait_ms(100);
                    writePinHigh(NRF_RESET);

                    reset_battery();
            } else {
                // Do something else when release
            }
            return false;
        case GET_VER:
            if (record->event.pressed) {
                // Do something when pressed
                tap_code(KC_1);
            } else {
                // Do something else when release
            }
            return false;
        case SEL_BLE:
            if (record->event.pressed) {
                // Do something when pressed
                blueism_select_ble();
            } else {
                // Do something else when release
            }
            return false;
        case SEL_2G4:
            if (record->event.pressed) {
                // Do something when pressed
                blueism_select_2g4();
            } else {
                // Do something else when release
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                // Do something when pressed
                // gext_battery_lvl_str(bat_str, ARRAY_SIZE(bat_str));
                // send_string(bat_str);
                // send_byte(get_battery_lvl());
                rgb_matrix_toggle();
                if (rgb_matrix_is_enabled()) {
                    writePinHigh(RGB_SHUTDOWN_PIN);
                } else {
                    writePinLow(RGB_SHUTDOWN_PIN);
                }

            } else {
                // Do something else when release
            }
            return false;
        case GU_TOGG:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    keymap_config.no_gui = !keymap_config.no_gui;
                    eeconfig_update_keymap(keymap_config.raw);
                }
            } else {
            }
            return false;
        case AG_TOGG:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    keymap_config.swap_lalt_lgui = !keymap_config.swap_lalt_lgui;
                    keymap_config.swap_ralt_rgui = keymap_config.swap_lalt_lgui;
                    eeconfig_update_keymap(keymap_config.raw);
                }
            } else {
            }
            return false;
        case AVD_UNP:
            if (record->event.pressed) {
                adv_unpair_key_timer = timer_read();
            } else {
                if (timer_elapsed(adv_unpair_key_timer) >= 5000) {
                    blueism_dongle_button_unpair();
                } else {
                    blueism_ble_button_unpair();
                }
                adv_unpair_key_timer = 0;
                // if(!adv_unpair_hold_triggered) {
                //     blueism_ble_button_unpair();
                // }
                // adv_unpair_hold_triggered = false;
                // chVTReset(&adv_unpair_key_timer);
            }
            return false;
        // case BT_ID_1:
        //     if (record->event.pressed) {
        //         blueism_select_ble();
        //         blueism_select_ble_id(0);
        //     } else {
        //         // Do something else when release
        //     }
        //     return false;
        // case BT_ID_2:
        //     if (record->event.pressed) {
        //         blueism_select_ble();
        //         blueism_select_ble_id(1);
        //     } else {
        //         // Do something else when release
        //     }
        //     return false;
        // case BT_ID_3:
        //     if (record->event.pressed) {
        //         blueism_select_ble();
        //         blueism_select_ble_id(2);
        //     } else {
        //         // Do something else when release
        //     }
        //     return false;
        // case BT_ID_4:
        //     if (record->event.pressed) {
        //         blueism_select_ble();
        //         blueism_select_ble_id(3);
        //     } else {
        //         // Do something else when release
        //     }
        //     return false;
        // case KC_F1:
        //     if (record->event.pressed) {
        //         if (get_mods() & MOD_MASK_SHIFT) {
        //             // blueism_select_ble();
        //             // wait_ms(100);
        //             // blueism_select_ble_id(0);
        //             blueism_select_ble();
        //         } else {
        //             tap_code(KC_F1);
        //         }
        //     } else {
        //         // Do something else when release
        //     }
        //     return false;
        case KC_F1:
            if (record->event.pressed) {
                sel_ble_key_timer = timer_read();
            } else {
                if (timer_elapsed(sel_ble_key_timer) >= 1500) {
                    blueism_select_ble();
                } else {
                    tap_code(KC_F1);
                }
                sel_ble_key_timer = 0;
                // if(!adv_unpair_hold_triggered) {
                //     blueism_ble_button_unpair();
                // }
                // adv_unpair_hold_triggered = false;
                // chVTReset(&adv_unpair_key_timer);
            }
            return false;
        // case KC_F2:
        //     if (record->event.pressed) {
        //         if (get_mods() & MOD_MASK_SHIFT) {
        //             blueism_select_ble();
        //             wait_ms(100);
        //             blueism_select_ble_id(1);
        //         } else {
        //             tap_code(KC_F2);
        //         }
        //     } else {
        //         // Do something else when release
        //     }
        //     return false;
        // case KC_F3:
        //     if (record->event.pressed) {
        //         if (get_mods() & MOD_MASK_SHIFT) {
        //             blueism_select_ble();
        //             wait_ms(100);
        //             blueism_select_ble_id(2);
        //         } else {
        //             tap_code(KC_F3);
        //         }
        //     } else {
        //         // Do something else when release
        //     }
        //     return false;
        // case KC_F4:
        //     if (record->event.pressed) {
        //         if (get_mods() & MOD_MASK_SHIFT) {
        //             blueism_select_ble();
        //             wait_ms(100);
        //             blueism_select_ble_id(3);
        //         } else {
        //             tap_code(KC_F4);
        //         }
        //     } else {
        //         // Do something else when release
        //     }
        //     return false;
        // case KC_F2:
        //     if (record->event.pressed) {
        //         if (get_mods() & MOD_MASK_SHIFT) {
        //             clear_keyboard();
        //             blueism_select_2g4();
        //         }
        //     } else {
        //         // Do something else when release
        //     }
        //     return false;
        case KC_F2:
            if (record->event.pressed) {
                sel_2g4_key_timer = timer_read();
            } else {
                if (timer_elapsed(sel_2g4_key_timer) >= 1500) {
                    blueism_select_2g4();
                } else {
                    tap_code(KC_F2);
                }
                sel_2g4_key_timer = 0;
                // if(!adv_unpair_hold_triggered) {
                //     blueism_ble_button_unpair();
                // }
                // adv_unpair_hold_triggered = false;
                // chVTReset(&adv_unpair_key_timer);
            }
            return false;
        // case NK_TOGG:
        //     if (record->event.pressed) {
        //         if(keymap_config.nkro){
        //             dprintf("nk on");
        //         }
        //     } else {
        //     }
        //     return false;
        // case KEYLOCK:
        //     static host_driver_t *host_driver = 0;

        //     if (record->event.pressed) {
        //         if (host_get_driver()) {
        //             host_driver = host_get_driver();
        //             clear_keyboard();
        //             host_set_driver(0);
        //             host_driver_disabled = true;
        //         } else {
        //             host_set_driver(host_driver);
        //             host_driver_disabled = false;
        //         }
        //     }
        //     return false;
        default:
            return true; // Process all other keyzcodes normally
    }
}
