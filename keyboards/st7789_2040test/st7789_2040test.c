// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "qp_lvgl.h"

// lv_obj_t *roller1;

// static void event_handler(lv_event_t *e) {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t       *obj  = lv_event_get_target(e);
//     if (code == LV_EVENT_VALUE_CHANGED) {
//         char buf[32];
//         lv_roller_get_selected_str(obj, buf, sizeof(buf));
//         LV_LOG_USER("Selected month: %s\n", buf);
//     }
// }

/**
 * An infinite roller with the name of the months
 */
// void lv_example_roller_1(void) {
//     lv_roller_set_options(roller1,
//                           "January\n"
//                           "February\n"
//                           "March\n"
//                           "April\n"
//                           "May\n"
//                           "June\n"
//                           "July\n"
//                           "August\n"
//                           "September\n"
//                           "October\n"
//                           "November\n"
//                           "December",
//                           LV_ROLLER_MODE_INFINITE);

//     lv_roller_set_visible_row_count(roller1, 4);
//     lv_obj_center(roller1);
//     lv_obj_add_event_cb(roller1, event_handler, LV_EVENT_ALL, NULL);

//     // for (uint8_t i = 0; i < 10; i++) {
//     //     lv_roller_set_selected(roller1, i, LV_ANIM_ON);
//     //     // wait_ms(2000);
//     // }
// }

// static lv_obj_t * chart1;
// static lv_chart_series_t * ser1;
// static lv_chart_series_t * ser2;

// static void draw_event_cb(lv_event_t * e)
// {
//     lv_obj_t * obj = lv_event_get_target(e);

//     /*Add the faded area before the lines are drawn*/
//     lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
//     if(dsc->part == LV_PART_ITEMS) {
//         if(!dsc->p1 || !dsc->p2) return;

//         /*Add a line mask that keeps the area below the line*/
//         lv_draw_mask_line_param_t line_mask_param;
//         lv_draw_mask_line_points_init(&line_mask_param, dsc->p1->x, dsc->p1->y, dsc->p2->x, dsc->p2->y, LV_DRAW_MASK_LINE_SIDE_BOTTOM);
//         int16_t line_mask_id = lv_draw_mask_add(&line_mask_param, NULL);

//         /*Add a fade effect: transparent bottom covering top*/
//         lv_coord_t h = lv_obj_get_height(obj);
//         lv_draw_mask_fade_param_t fade_mask_param;
//         lv_draw_mask_fade_init(&fade_mask_param, &obj->coords, LV_OPA_COVER, obj->coords.y1 + h / 8, LV_OPA_TRANSP,obj->coords.y2);
//         int16_t fade_mask_id = lv_draw_mask_add(&fade_mask_param, NULL);

//         /*Draw a rectangle that will be affected by the mask*/
//         lv_draw_rect_dsc_t draw_rect_dsc;
//         lv_draw_rect_dsc_init(&draw_rect_dsc);
//         draw_rect_dsc.bg_opa = LV_OPA_20;
//         draw_rect_dsc.bg_color = dsc->line_dsc->color;

//         lv_area_t a;
//         a.x1 = dsc->p1->x;
//         a.x2 = dsc->p2->x - 1;
//         a.y1 = LV_MIN(dsc->p1->y, dsc->p2->y);
//         a.y2 = obj->coords.y2;
//         lv_draw_rect(dsc->draw_ctx, &draw_rect_dsc, &a);

//         /*Remove the masks*/
//         lv_draw_mask_free_param(&line_mask_param);
//         lv_draw_mask_free_param(&fade_mask_param);
//         lv_draw_mask_remove_id(line_mask_id);
//         lv_draw_mask_remove_id(fade_mask_id);
//     }
//     /*Hook the division lines too*/
//     else if(dsc->part == LV_PART_MAIN) {
//         if(dsc->line_dsc == NULL || dsc->p1 == NULL || dsc->p2 == NULL) return;

//         /*Vertical line*/
//         if(dsc->p1->x == dsc->p2->x) {
//             dsc->line_dsc->color  = lv_palette_lighten(LV_PALETTE_GREY, 1);
//             if(dsc->id == 3) {
//                 dsc->line_dsc->width  = 2;
//                 dsc->line_dsc->dash_gap  = 0;
//                 dsc->line_dsc->dash_width  = 0;
//             }
//             else {
//                 dsc->line_dsc->width = 1;
//                 dsc->line_dsc->dash_gap  = 6;
//                 dsc->line_dsc->dash_width  = 6;
//             }
//         }
//         /*Horizontal line*/
//         else {
//             if(dsc->id == 2) {
//                 dsc->line_dsc->width  = 2;
//                 dsc->line_dsc->dash_gap  = 0;
//                 dsc->line_dsc->dash_width  = 0;
//             }
//             else {
//                 dsc->line_dsc->width = 2;
//                 dsc->line_dsc->dash_gap  = 6;
//                 dsc->line_dsc->dash_width  = 6;
//             }

//             if(dsc->id == 1  || dsc->id == 3) {
//                 dsc->line_dsc->color  = lv_palette_main(LV_PALETTE_GREEN);
//             } else {
//                 dsc->line_dsc->color  = lv_palette_lighten(LV_PALETTE_GREY, 1);
//             }
//         }
//     }
// }

// static void add_data(lv_timer_t * timer)
// {
//     LV_UNUSED(timer);
//     static uint32_t cnt = 0;
//     lv_chart_set_next_value(chart1, ser1, lv_rand(20, 90));

//     if(cnt % 4 == 0) lv_chart_set_next_value(chart1, ser2, lv_rand(40, 60));

//     cnt++;
// }

// static void set_value(void *bar, int32_t v)
// {
//     lv_bar_set_value(bar, v, LV_ANIM_OFF);
// }

// static void event_cb(lv_event_t * e)
// {
//     lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
//     if(dsc->part != LV_PART_INDICATOR) return;

//     lv_obj_t * obj= lv_event_get_target(e);

//     lv_draw_label_dsc_t label_dsc;
//     lv_draw_label_dsc_init(&label_dsc);
//     label_dsc.font = LV_FONT_DEFAULT;

//     char buf[8];
//     lv_snprintf(buf, sizeof(buf), "%d", (int)lv_bar_get_value(obj));

//     lv_point_t txt_size;
//     lv_txt_get_size(&txt_size, buf, label_dsc.font, label_dsc.letter_space, label_dsc.line_space, LV_COORD_MAX, label_dsc.flag);

//     lv_area_t txt_area;
//     /*If the indicator is long enough put the text inside on the right*/
//     if(lv_area_get_width(dsc->draw_area) > txt_size.x + 20) {
//         txt_area.x2 = dsc->draw_area->x2 - 5;
//         txt_area.x1 = txt_area.x2 - txt_size.x + 1;
//         label_dsc.color = lv_color_white();
//     }
//     /*If the indicator is still short put the text out of it on the right*/
//     else {
//         txt_area.x1 = dsc->draw_area->x2 + 5;
//         txt_area.x2 = txt_area.x1 + txt_size.x - 1;
//         label_dsc.color = lv_color_black();
//     }

//     txt_area.y1 = dsc->draw_area->y1 + (lv_area_get_height(dsc->draw_area) - txt_size.y) / 2;
//     txt_area.y2 = txt_area.y1 + txt_size.y - 1;

//     lv_draw_label(dsc->draw_ctx, &label_dsc, &txt_area, buf, NULL);
// }

static void row_gap_anim(void * obj, int32_t v)
{
    lv_obj_set_style_pad_row(obj, v, 0);
}

static void column_gap_anim(void * obj, int32_t v)
{
    lv_obj_set_style_pad_column(obj, v, 0);
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

    // roller1 = lv_roller_create(lv_scr_act());

    // lv_example_roller_1();

        /*Create a chart1*/
    // chart1 = lv_chart_create(lv_scr_act());
    // lv_obj_set_size(chart1, 200, 150);
    // lv_obj_center(chart1);
    // lv_chart_set_type(chart1, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

    // lv_chart_set_div_line_count(chart1, 5, 7);

    // lv_obj_add_event_cb(chart1, draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    // lv_chart_set_update_mode(chart1, LV_CHART_UPDATE_MODE_CIRCULAR);

    // /*Add two data series*/
    // ser1 = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    // ser2 = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_SECONDARY_Y);

    // uint32_t i;
    // for(i = 0; i < 10; i++) {
    //     lv_chart_set_next_value(chart1, ser1, lv_rand(20, 90));
    //     lv_chart_set_next_value(chart1, ser2, lv_rand(30, 70));
    // }

    // lv_timer_create(add_data, 200, NULL);

    //     lv_obj_t * bar = lv_bar_create(lv_scr_act());
    // lv_obj_add_event_cb(bar, event_cb, LV_EVENT_DRAW_PART_END, NULL);
    // lv_obj_set_size(bar, 200, 20);
    // lv_obj_center(bar);

    // lv_anim_t a;
    // lv_anim_init(&a);
    // lv_anim_set_var(&a, bar);
    // lv_anim_set_values(&a, 0, 100);
    // lv_anim_set_exec_cb(&a, set_value);
    // lv_anim_set_time(&a, 2000);
    // lv_anim_set_playback_time(&a, 2000);
    // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    // lv_anim_start(&a);


    /*60x60 cells*/
    static lv_coord_t col_dsc[] = {60, 60, 60, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {45, 45, 45, LV_GRID_TEMPLATE_LAST};

    /*Create a container with grid*/
    lv_obj_t * cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(cont, 300, 220);
    lv_obj_center(cont);
    lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);

    lv_obj_t * label;
    lv_obj_t * obj;
    uint32_t i;
    for(i = 0; i < 9; i++) {
        uint8_t col = i % 3;
        uint8_t row = i / 3;

        obj = lv_obj_create(cont);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, 1,
                                 LV_GRID_ALIGN_STRETCH, row, 1);
        label = lv_label_create(obj);
        lv_label_set_text_fmt(label, "%d,%d", col, row);
        lv_obj_center(label);
    }

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, cont);
    lv_anim_set_values(&a, 0, 10);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);

    lv_anim_set_exec_cb(&a, row_gap_anim);
    lv_anim_set_time(&a, 500);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_start(&a);

    lv_anim_set_exec_cb(&a, column_gap_anim);
    lv_anim_set_time(&a, 3000);
    lv_anim_set_playback_time(&a, 3000);
    lv_anim_start(&a);
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


// static uint32_t key_timer;
// static uint8_t i;

// void housekeeping_task_kb(void){
//     uint32_t timer_now = timer_read();
//     if ((TIMER_DIFF_32(timer_now, key_timer) >= 1500)) {
//         lv_roller_set_selected(roller1, i++, LV_ANIM_ON);
//         key_timer = timer_now;
//     }
// }

