#include QMK_KEYBOARD_H

#include "i2c_master.h"
#include "debug.h"

#define TIMEOUT 50


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_BSPC,  KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        KC_P4,    KC_P5,    KC_P6,
        KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        KC_P0,    LT(1, KC_PDOT)
    ),
};

void do_scan(void) {
    dprintf("Scanning...\n");

    uint8_t data= 0xC5;
    i2c_status_t status=i2c_write_register(0x36 << 1, 0xFE, &data, 1, 100);
    if(status!=I2C_STATUS_SUCCESS){
        dprintf("FAILED\n");
    }


}

uint16_t scan_timer = 0;

void matrix_scan_user(void) {
    if (timer_elapsed(scan_timer) > 5000) {
        do_scan();
        scan_timer = timer_read();
    }
}

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;

    i2c_init();
    scan_timer = timer_read();
}
