#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void apply_style_button(lv_obj_t *obj);
extern void apply_style_selectbutton(lv_obj_t *obj);
extern void apply_style_select_button_red_green(lv_obj_t *obj);
extern void apply_style_select_button90deg(lv_obj_t *obj);
extern void apply_style_blackpanel(lv_obj_t *obj);
extern void apply_style_bigfont_label(lv_obj_t *obj);
extern void apply_style_bigfont_normal(lv_obj_t *obj);
extern void apply_style_warning(lv_obj_t *obj);
extern void apply_style_title_(lv_obj_t *obj);
extern void apply_style_selector_small(lv_obj_t *obj);
extern void apply_style_slider(lv_obj_t *obj);
extern void apply_style_small_label(lv_obj_t *obj);
extern void apply_style_small_label_symbol(lv_obj_t *obj);
extern void apply_style_extra_small_label(lv_obj_t *obj);
extern void apply_style_small_header(lv_obj_t *obj);
extern void apply_style_button_text(lv_obj_t *obj);
extern void apply_style_button_text90deg(lv_obj_t *obj);
extern void apply_style_checkbox_default(lv_obj_t *obj);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/