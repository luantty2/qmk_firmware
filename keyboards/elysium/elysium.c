// Copyright 2023 weimao (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#ifdef RGB_INDICATOR_ENABLE
#    include "rgb_indicator.h"
#endif

void eeconfig_init_kb(void) {
#ifdef RGB_INDICATOR_ENABLE
    eeconfig_init_rgb_indicator();
#endif
}

void keyboard_post_init_kb(void) {
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    // USB mux selection pin.
    // low = USB HS, high = USB FS.
    setPinOutput(USB_MUX_SEL_PIN);
    writePinLow(USB_MUX_SEL_PIN);
#ifdef RGB_INDICATOR_ENABLE
    rgb_indicator_init();
#endif

    keyboard_post_init_user();
}

bool led_update_kb(led_t led_state) {
#ifdef RGB_INDICATOR_ENABLE
    bool res = led_update_user(led_state);
    if (res) {
        rgb_indicator_toggle(led_state.caps_lock);
    }
    return res;
#else
    return false;
#endif
}

#ifdef VIA_ENABLE
#    ifdef RGB_INDICATOR_ENABLE
enum via_rgbled_value {
    id_rgbind_enable = 1,
    id_rgbind_select = 2,
    id_rgbind_mode   = 3,
    id_rgbind_hs     = 4,
};

void rgbind_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_rgbind_enable:
            rgb_indicator_config.enable = *value_data;
            break;
        case id_rgbind_select:
            rgb_indicator_select_toggle();
            break;
        case id_rgbind_mode:
            rgb_indicator_config.mode = *value_data;
            break;
        case id_rgbind_hs:
            rgb_indicator_config.hsv.h = value_data[0];
            rgb_indicator_config.hsv.s = value_data[1];
            break;
    }
}

void rgbind_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_rgbind_enable:
            value_data[0] = rgb_indicator_config.enable ? 1 : 0;
            break;
        case id_rgbind_select:
            break;
        case id_rgbind_mode:
            value_data[0] = rgb_indicator_config.mode;
            break;
        case id_rgbind_hs:
            value_data[0] = rgb_indicator_config.hsv.h;
            value_data[1] = rgb_indicator_config.hsv.s;
            break;
    }
}

void rgbind_config_save(void) {
    eeconfig_update_rgb_indicator();
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);
    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value:
                rgbind_config_set_value(value_id_and_data);
                break;
            case id_custom_get_value:
                rgbind_config_get_value(value_id_and_data);
                break;
            case id_custom_save:
                rgbind_config_save();
                break;
            default:
                // Unhandled message.
                *command_id = id_unhandled;
                break;
        }
        return;
    }
    // Return the unhandled state
    *command_id = id_unhandled;
    // DO NOT call raw_hid_send(data,length) here, let caller do this
}
#    endif
#endif
