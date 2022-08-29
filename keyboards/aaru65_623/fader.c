/* Copyright 2022 luantty2
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fader.h"
#include "ms1100.h"
#include "eeprom.h"
#include "timer.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif

static int16_t  adc_pre_value    = 0;
static uint32_t fader_read_timer = 0;
static uint8_t  midi_cc_value    = 0;

void fader_init(void) {
    ms1100_init();
    // fader_config.raw = eeconfig_read_kb();
    fader_config.raw = eeprom_read_dword(EECONFIG_FADER);
}

void eeconfig_init_fader(void) {
    // rgb_indicator_mode(2);
    // rgb_indicator_sethsv(HSV_YELLOW);
    // rgb_indicator_config.enable = true;
    // rgb_indicator_config.select = false;
    // // rgb_indicator_select();
    // // eeconfig_update_kb(rgb_indicator_config.raw);

    // // rgb_indicator_config.mode   = 2;
    // rgb_indicator_mode(6);
    // rgb_indicator_sethsv(HSV_YELLOW);
    // // rgb_indicator_config.hsv.h  = 43;
    // // rgb_indicator_config.hsv.s  = 255;
    // // rgb_indicator_config.hsv.v  = 255;
    // // rgb_indicator_config.raw    = eeconfig_read_kb();
    // eeconfig_update_kb(rgb_indicator_config.raw); // Write default value to EEPROM now
    eeconfig_update_fader_default();
}

void eeconfig_update_fader(void) {
    // eeconfig_update_kb(fader_config.raw); // Write default value to EEPROM now
    eeprom_update_dword(EECONFIG_FADER, fader_config.raw);
}

void eeconfig_update_fader_default(void) {
    dprintf("fader update default [EEPROM]\n");
    // rgb_indicator_mode(2);
    // rgb_indicator_sethsv(HSV_YELLOW);
    fader_config.enable  = 1;
    fader_config.reverse = 0;
    fader_config.channel = 0;
    fader_config.cc      = 0;
    // rgb_indicator_select();
    // eeconfig_update_kb(rgb_indicator_config.raw);

    // rgb_indicator_config.mode   = 2;

    // rgb_indicator_mode(5);
    // rgb_indicator_sethsv(HSV_GOLD);
    // rgb_indicator_config.hsv.h  = 43;
    // rgb_indicator_config.hsv.s  = 255;
    // rgb_indicator_config.hsv.v  = 255;
    // rgb_indicator_config.raw    = eeconfig_read_kb();
    eeconfig_update_fader(); // Write default value to EEPROM now
}

void eeconfig_debug_fader(void) {
    dprintf("fader_config.enable = %d\n", fader_config.enable);
    dprintf("fader_config.reverse = %d\n", fader_config.reverse);
    dprintf("fader_config.channel = %d\n", fader_config.channel);
    dprintf("fader_config.cc = %d\n", fader_config.cc);
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

void fader_reverse(void) {
    if (fader_config.enable) {
        fader_config.reverse = !fader_config.reverse;
        eeconfig_update_fader();
        dprintf("fader reverse [EEPROM]: %u\n", fader_config.reverse);
    } else
        return;
}

void fader_setchannel(uint8_t channel) {
    if (fader_config.enable) {
        fader_config.channel = channel;
        eeconfig_update_fader();
        dprintf("fader channel [EEPROM]: %u\n", fader_config.channel);
    } else
        return;
}

void fader_setcc(uint8_t cc) {
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
        fader_setchannel(channel);
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
        fader_setchannel(channel);
    } else
        return;
}

void fader_increase_cc(void) {
    if (fader_config.enable) {
        uint8_t cc = fader_config.cc;
        if (fader_config.cc >= 127) {
            cc = 0;
        } else {
            cc += 1;
        }
        fader_setcc(cc);
    } else
        return;
}

void fader_decrease_cc(void) {
    if (fader_config.enable) {
        uint8_t cc = fader_config.cc;
        if (fader_config.cc <= 0) {
            cc = 127;
        } else {
            cc -= 1;
        }
        fader_setcc(cc);
    } else
        return;
}

uint8_t fader_get_val(void) {
    // return midi_cc_value;
    uint8_t adc_value = ms1100_read() >> 8;
    if (!fader_config.reverse) {
        return 0x7F - adc_value;
    } else
        return adc_value;
}

uint8_t fader_read(void) {
    if (fader_config.enable) {
        int16_t adc_value = ms1100_read();
        // Exit this function if the new value is not within the deadband
        if (abs(adc_value - adc_pre_value) < ADC_DEADBAND) return ADC_ERROR;
        adc_pre_value = adc_value;
        // Get the 7 bit value
        adc_value >>= 8;
        // uprintf("%d\n", adc_value);
        // fader_read_timer = timer_read();
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
            midi_cc_value = fader_read();
            // if (midi_cc_value != ADC_ERROR) midi_send_cc(device, fader_config.channel, fader_config.cc, midi_cc_value);
#ifdef RGB_MATRIX_ENABLE
            if (layer_state_is(1)) {
                HSV hsv = rgb_matrix_get_hsv();
                if (midi_cc_value != ADC_ERROR) {
                    midi_cc_value *= 2;
                    hsv.v = midi_cc_value;
                    rgb_matrix_sethsv(hsv.h, hsv.s, hsv.v);
                }
            } else {
                if (midi_cc_value != ADC_ERROR) midi_send_cc(device, fader_config.channel, fader_config.cc, midi_cc_value);
            }
#else
            if (midi_cc_value != ADC_ERROR) midi_send_cc(device, fader_config.channel, fader_config.cc, midi_cc_value);
#endif
        }
        fader_read_timer = timer_now;
    }
}

// #ifdef RGB_MATRIX_ENABLE
//     bool update_eeprom_complete= true;

//     void
// #endif