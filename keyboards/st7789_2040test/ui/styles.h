#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: button_default
lv_style_t *get_style_button_default_MAIN_DEFAULT(void);
lv_style_t *get_style_button_default_MAIN_PRESSED(void);
void add_style_button_default(lv_obj_t *obj);
void remove_style_button_default(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/
