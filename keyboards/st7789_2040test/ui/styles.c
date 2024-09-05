#include "styles.h"
#include "images.h"
#include "fonts.h"

//
// Style: button_default
//

void init_style_button_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff6f39ca));
    lv_style_set_bg_grad_dir(style, LV_GRAD_DIR_VER);
    lv_style_set_bg_grad_color(style, lv_color_hex(0xffe15c5c));
    lv_style_set_text_color(style, lv_color_hex(0xffe3e3e3));
    lv_style_set_text_letter_space(style, 1);
    lv_style_set_radius(style, 0);
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_shadow_width(style, 10);
    lv_style_set_shadow_ofs_y(style, 3);
    lv_style_set_shadow_spread(style, 1);
    lv_style_set_shadow_color(style, lv_color_hex(0xffeb34b9));
};

lv_style_t *get_style_button_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_button_default_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff2ac0e1));
    lv_style_set_bg_grad_color(style, lv_color_hex(0xffe47373));
};

lv_style_t *get_style_button_default_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_default_MAIN_PRESSED(style);
    }
    return style;
};

void add_style_button_default(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_button_default_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

void remove_style_button_default(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_button_default_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_button_default,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_button_default,
    };
    remove_style_funcs[styleIndex](obj);
}

