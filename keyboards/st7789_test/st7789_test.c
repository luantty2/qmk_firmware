// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "qp_lvgl.h"

lv_obj_t *roller1;

static void event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t       *obj  = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected month: %s\n", buf);
    }
}

/**
 * An infinite roller with the name of the months
 */
void lv_example_roller_1(void) {
    lv_roller_set_options(roller1,
                          "January\n"
                          "February\n"
                          "March\n"
                          "April\n"
                          "May\n"
                          "June\n"
                          "July\n"
                          "August\n"
                          "September\n"
                          "October\n"
                          "November\n"
                          "December",
                          LV_ROLLER_MODE_INFINITE);

    lv_roller_set_visible_row_count(roller1, 4);
    lv_obj_center(roller1);
    lv_obj_add_event_cb(roller1, event_handler, LV_EVENT_ALL, NULL);

    // for (uint8_t i = 0; i < 10; i++) {
    //     lv_roller_set_selected(roller1, i, LV_ANIM_ON);
    //     // wait_ms(2000);
    // }
}

void keyboard_post_init_kb(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    painter_device_t display = qp_st7789_make_spi_device(LCD_WIDTH, LCD_HEIGHT, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, 3);
    qp_set_viewport_offsets(display, 0, 34); // offset x, offset y.

    if (!qp_init(display, QP_ROTATION_90) || !qp_power(display, true) || !qp_lvgl_attach(display)) {
        dprintf("display init unsuccessful\n");
    }

    roller1 = lv_roller_create(lv_scr_act());

    lv_example_roller_1();

    // lv_disp_t  *lv_display = lv_disp_get_default();
    // lv_theme_t *lv_theme   = lv_theme_default_init(lv_display, lv_palette_main(LV_PALETTE_AMBER), lv_palette_main(LV_PALETTE_BLUE), true, LV_FONT_DEFAULT);

    // lv_disp_set_theme(lv_display, lv_theme);

    /*Change the active screen's background color*/
    // lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);
    // /*Create a white label, set its text and align it to the center*/
    // lv_obj_t *label = lv_label_create(lv_scr_act());
    // lv_label_set_text(label, "Hello world");
    // lv_obj_set_style_text_color(lv_scr_act (), lv_color_hex(0xffffff), LV_PART_MAIN);
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    keyboard_post_init_user();
}


static uint32_t key_timer;
static uint8_t i;

void housekeeping_task_kb(void){
    uint32_t timer_now = timer_read();
    if ((TIMER_DIFF_32(timer_now, key_timer) >= 1500)) {
        lv_roller_set_selected(roller1, i++, LV_ANIM_ON);
        key_timer = timer_now;
    }
}

