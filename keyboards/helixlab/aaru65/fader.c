// Copyright 2022 luantty2 (@luantty2)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "fader.h"
#include "ads1100.h"
#include "eeprom.h"
#include "timer.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif

#define FADER_POS_ORIGIN 0
#define FADER_POS_UPPER 1
#define FADER_POS_LOWER 2

static int16_t  adc_pre_value              = 0;
static uint32_t fader_read_timer           = 0;
static uint32_t fader_continuous_timer     = 0;
static bool     upper_singleshot_processed = false;
static bool     lower_singleshot_processed = false;
static bool     upper_layer_processed      = false;
static bool     lower_layer_processed      = false;
static bool     origin_layer_processed     = false;
static uint8_t  fader_pos                  = 0;
// static uint8_t  midi_cc_value              = 0;
static uint8_t adc_value = 0;

void fader_init(void) {
    ads1100_init();
    fader_config.raw       = eeprom_read_dword(EECONFIG_FADER);
    fader_extra_config.raw = eeprom_read_dword(EECONFIG_FADER_EXTRA);
}

void eeconfig_init_fader(void) {
    eeconfig_update_fader_default();
    eeconfig_update_fader_extra_default();
}

void eeconfig_update_fader(void) {
    eeprom_update_dword(EECONFIG_FADER, fader_config.raw);
}

void eeconfig_update_fader_extra(void) {
    eeprom_update_dword(EECONFIG_FADER_EXTRA, fader_extra_config.raw);
}

void eeconfig_update_fader_default(void) {
    dprintf("fader update default [EEPROM]\n");
    fader_config.enable  = 1;
    fader_config.mode    = 0;
    fader_config.reverse = 0;
    fader_config.channel = 0;
    fader_config.cc      = 0;
    fader_config.trigger = 0;
    fader_config.layer_0 = 1;
    fader_config.layer_1 = 1;
    eeconfig_update_fader();
}

void eeconfig_update_fader_extra_default(void) {
    dprintf("fader extra update default [EEPROM]\n");
    fader_extra_config.kc_0 = KC_NO;
    fader_extra_config.kc_1 = KC_NO;
    eeconfig_update_fader_extra();
}

void eeconfig_debug_fader(void) {
    dprintf("fader_config.enable = %d\n", fader_config.enable);
    dprintf("fader_config.mode = %d\n", fader_config.mode);
    dprintf("fader_config.reverse = %d\n", fader_config.reverse);
    dprintf("fader_config.channel = %d\n", fader_config.channel);
    dprintf("fader_config.cc = %d\n", fader_config.cc);
    dprintf("fader_config.trigger = %d\n", fader_config.trigger);
    dprintf("fader_config.layer_0 = %d\n", fader_config.layer_0);
    dprintf("fader_config.layer_1 = %d\n", fader_config.layer_1);
}

void fader_enable(void) {
    fader_config.enable = 1;
    eeconfig_update_fader();
    dprintf("fader enable [EEPROM]: %u\n", fader_config.enable);
}

void fader_disable(void) {
    fader_config.enable = 0;
    eeconfig_update_fader();
    dprintf("fader enable [EEPROM]: %u\n", fader_config.enable);
}

void fader_enable_toggle(void) {
    fader_config.enable = !fader_config.enable;
    if (fader_config.enable)
        fader_enable();
    else
        fader_disable();
}

void fader_mode_midi(void) {
    fader_config.mode = 0;
    eeconfig_update_fader();
    dprintf("fader mode [EEPROM]: %u\n", fader_config.mode);
}

void fader_mode_custom(void) {
    fader_config.mode = 1;
    eeconfig_update_fader();
    dprintf("fader mode [EEPROM]: %u\n", fader_config.mode);
}

void fader_mode_toggle(void) {
    fader_config.mode = !fader_config.mode;
    if (fader_config.mode)
        fader_mode_custom();
    else
        fader_mode_midi();
}

void fader_reverse(void) {
    if (fader_config.enable) {
        fader_config.reverse = !fader_config.reverse;
        eeconfig_update_fader();
        dprintf("fader reverse [EEPROM]: %u\n", fader_config.reverse);
    } else
        return;
}

void fader_set_channel(uint8_t channel) {
    if (fader_config.enable) {
        fader_config.channel = channel;
        eeconfig_update_fader();
        dprintf("fader channel [EEPROM]: %u\n", fader_config.channel);
    } else
        return;
}

void fader_set_cc(uint8_t cc) {
    if (fader_config.enable) {
        fader_config.cc = cc;
        eeconfig_update_fader();
        dprintf("fader cc [EEPROM]: %u\n", fader_config.cc);
    } else
        return;
}

void fader_increase_channel(void) {
    if (fader_config.enable) {
        uint8_t channel = fader_config.channel;
        if (fader_config.channel >= 15) {
            channel = 0;
        } else {
            channel += 1;
        }
        fader_set_channel(channel);
    } else
        return;
}

void fader_decrease_channel(void) {
    if (fader_config.enable) {
        uint8_t channel = fader_config.channel;
        if (fader_config.channel <= 0) {
            channel = 15;
        } else {
            channel -= 1;
        }
        fader_set_channel(channel);
    } else
        return;
}

void fader_increase_cc(void) {
    if (fader_config.enable) {
        uint8_t cc = fader_config.cc;
        if (fader_config.cc >= 0x7F) {
            cc = 0;
        } else {
            cc += 1;
        }
        fader_set_cc(cc);
    } else
        return;
}

void fader_decrease_cc(void) {
    if (fader_config.enable) {
        uint8_t cc = fader_config.cc;
        if (fader_config.cc <= 0) {
            cc = 0x7F;
        } else {
            cc -= 1;
        }
        fader_set_cc(cc);
    } else
        return;
}

uint8_t fader_get_val(void) {
    uint8_t adc_value = ads1100_read() >> 8;
    if (!fader_config.reverse) {
        return 0x7F - adc_value;
    } else
        return adc_value;
}

void fader_trigger_singleshot(void) {
    fader_config.trigger = 0;
    eeconfig_update_fader();
    dprintf("fader trigger [EEPROM]: %u\n", fader_config.trigger);
}

void fader_trigger_continuous(void) {
    fader_config.trigger = 1;
    eeconfig_update_fader();
    dprintf("fader trigger [EEPROM]: %u\n", fader_config.trigger);
}

void fader_trigger_layer(void) {
    fader_config.trigger = 2;
    eeconfig_update_fader();
    dprintf("fader trigger [EEPROM]: %u\n", fader_config.trigger);
}

uint8_t fader_read(void) {
    if (fader_config.enable) {
        int16_t adc_value = ads1100_read();
        if (abs(adc_value - adc_pre_value) < ADC_DEADBAND) {
            return ADC_ERROR;
        }
        adc_pre_value = adc_value;
        adc_value >>= 8;
        if (!fader_config.reverse) {
            return 0x7F - adc_value;
        } else
            return adc_value;
    }
    return ADC_ERROR;
}

void fader_run(MidiDevice* device) {
    uint32_t timer_now = timer_read();
    if (TIMER_DIFF_32(timer_now, fader_read_timer) >= FADER_SAMPLE_RATE) {
        if (fader_config.enable) {
            adc_value = fader_read();
            if (fader_config.mode == 0) {
#ifdef RGB_MATRIX_ENABLE
                if (layer_state_is(1)) {
                    HSV hsv = rgb_matrix_get_hsv();
                    if (adc_value != ADC_ERROR) {
                        adc_value *= 2;
                        hsv.v = adc_value;
                        rgb_matrix_sethsv(hsv.h, hsv.s, hsv.v);
                    }
                } else {
                    if (adc_value != ADC_ERROR) {
                        midi_send_cc(device, fader_config.channel, fader_config.cc, adc_value);
                    }
                }
#else
                if (adc_value != ADC_ERROR) {
                    midi_send_cc(device, fader_config.channel, fader_config.cc, adc_value);
                }
#endif
            } else {
                // adc_value = fader_read();
                if (adc_value >= 0 && adc_value < 12) {
                    fader_pos = FADER_POS_LOWER;
                } else if (adc_value >= 12 && adc_value < 107) {
                    fader_pos = FADER_POS_ORIGIN;
                } else if (adc_value >= 107 && adc_value <= 127) {
                    fader_pos = FADER_POS_UPPER;
                }
                if (fader_config.enable && fader_config.mode == 1 && fader_config.trigger == 3) {
#ifdef RGB_MATRIX_ENABLE
                    HSV hsv = rgb_matrix_get_hsv();
                    if (adc_value != ADC_ERROR && hsv.v != adc_value * 2) {
                        adc_value *= 2;
                        hsv.v = adc_value;
                        rgb_matrix_sethsv(hsv.h, hsv.s, hsv.v);
                    }
#endif
                }
            }
        }
        fader_read_timer = timer_now;
    }
}

void fader_custom_singleshot_handler(void) {
    if (fader_config.enable && fader_config.mode == 1 && fader_config.trigger == 0) {
        switch (fader_pos) {
            case FADER_POS_UPPER:
                if (!upper_singleshot_processed) {
                    register_code16(fader_extra_config.kc_0);
                    wait_ms(5);
                    unregister_code16(fader_extra_config.kc_0);
                    upper_singleshot_processed = true;
                }
                break;
            case FADER_POS_ORIGIN:
                upper_singleshot_processed = false;
                lower_singleshot_processed = false;
                break;
            case FADER_POS_LOWER:
                if (!lower_singleshot_processed) {
                    register_code16(fader_extra_config.kc_1);
                    wait_ms(5);
                    unregister_code16(fader_extra_config.kc_1);
                    lower_singleshot_processed = true;
                }
                break;
            default:
                break;
        }
    }
}

void fader_custom_continuous_handler(void) {
    uint32_t timer_now = timer_read();
    if (TIMER_DIFF_32(timer_now, fader_continuous_timer) >= CONTINUOUS_TRIGGER_TIMER) {
        if (fader_config.enable && fader_config.mode == 1 && fader_config.trigger == 1) {
            switch (fader_pos) {
                case FADER_POS_UPPER:
                    register_code16(fader_extra_config.kc_0);
                    wait_ms(5);
                    unregister_code16(fader_extra_config.kc_0);
                    break;
                case FADER_POS_ORIGIN:
                    break;
                case FADER_POS_LOWER:
                    register_code16(fader_extra_config.kc_1);
                    wait_ms(5);
                    unregister_code16(fader_extra_config.kc_1);
                    break;
                default:
                    break;
            }
        }
        fader_continuous_timer = timer_now;
    }
}

void fader_custom_layer_handler(void) {
    if (fader_config.enable && fader_config.mode == 1 && fader_config.trigger == 2) {
        switch (fader_pos) {
            case FADER_POS_UPPER:
                if (!upper_layer_processed) {
                    upper_layer_processed  = true;
                    origin_layer_processed = false;
                    layer_off(0);
                    layer_on(fader_config.layer_0);
                }
                break;
            case FADER_POS_ORIGIN:
                upper_layer_processed = false;
                lower_layer_processed = false;
                if (!origin_layer_processed) {
                    origin_layer_processed = true;
                    layer_off(fader_config.layer_0);
                    layer_off(fader_config.layer_1);
                    layer_on(0);
                }
                break;
            case FADER_POS_LOWER:
                if (!lower_layer_processed) {
                    lower_layer_processed  = true;
                    origin_layer_processed = false;
                    layer_off(0);
                    layer_on(fader_config.layer_1);
                }
                break;
            default:
                break;
        }
    }
}
