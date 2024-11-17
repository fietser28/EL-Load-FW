#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: button
lv_style_t *get_style_button_MAIN_DEFAULT();
lv_style_t *get_style_button_MAIN_DISABLED();
void add_style_button(lv_obj_t *obj);
void remove_style_button(lv_obj_t *obj);

// Style: selectbutton
lv_style_t *get_style_selectbutton_MAIN_DEFAULT();
lv_style_t *get_style_selectbutton_MAIN_DISABLED();
void add_style_selectbutton(lv_obj_t *obj);
void remove_style_selectbutton(lv_obj_t *obj);

// Style: selectButtonRedGreen
lv_style_t *get_style_select_button_red_green_MAIN_DEFAULT();
lv_style_t *get_style_select_button_red_green_MAIN_CHECKED();
lv_style_t *get_style_select_button_red_green_MAIN_DISABLED();
void add_style_select_button_red_green(lv_obj_t *obj);
void remove_style_select_button_red_green(lv_obj_t *obj);

// Style: selectButton90deg
lv_style_t *get_style_select_button90deg_MAIN_DEFAULT();
lv_style_t *get_style_select_button90deg_MAIN_DISABLED();
void add_style_select_button90deg(lv_obj_t *obj);
void remove_style_select_button90deg(lv_obj_t *obj);

// Style: blackpanel
lv_style_t *get_style_blackpanel_MAIN_DEFAULT();
void add_style_blackpanel(lv_obj_t *obj);
void remove_style_blackpanel(lv_obj_t *obj);

// Style: bigfont_label
lv_style_t *get_style_bigfont_label_MAIN_DEFAULT();
void add_style_bigfont_label(lv_obj_t *obj);
void remove_style_bigfont_label(lv_obj_t *obj);

// Style: bigfont Normal
lv_style_t *get_style_bigfont_normal_MAIN_DEFAULT();
void add_style_bigfont_normal(lv_obj_t *obj);
void remove_style_bigfont_normal(lv_obj_t *obj);

// Style: warning
lv_style_t *get_style_warning_MAIN_DEFAULT();
void add_style_warning(lv_obj_t *obj);
void remove_style_warning(lv_obj_t *obj);

// Style: Title 
lv_style_t *get_style_title__MAIN_DEFAULT();
void add_style_title_(lv_obj_t *obj);
void remove_style_title_(lv_obj_t *obj);

// Style: slider
lv_style_t *get_style_slider_MAIN_DEFAULT();
lv_style_t *get_style_slider_INDICATOR_DEFAULT();
lv_style_t *get_style_slider_KNOB_DEFAULT();
void add_style_slider(lv_obj_t *obj);
void remove_style_slider(lv_obj_t *obj);

// Style: small label
lv_style_t *get_style_small_label_MAIN_DEFAULT();
void add_style_small_label(lv_obj_t *obj);
void remove_style_small_label(lv_obj_t *obj);

// Style: small label_symbol
lv_style_t *get_style_small_label_symbol_MAIN_DEFAULT();
void add_style_small_label_symbol(lv_obj_t *obj);
void remove_style_small_label_symbol(lv_obj_t *obj);

// Style: extra small label
lv_style_t *get_style_extra_small_label_MAIN_DEFAULT();
void add_style_extra_small_label(lv_obj_t *obj);
void remove_style_extra_small_label(lv_obj_t *obj);

// Style: small header
lv_style_t *get_style_small_header_MAIN_DEFAULT();
void add_style_small_header(lv_obj_t *obj);
void remove_style_small_header(lv_obj_t *obj);

// Style: buttonText
lv_style_t *get_style_button_text_MAIN_DEFAULT();
void add_style_button_text(lv_obj_t *obj);
void remove_style_button_text(lv_obj_t *obj);

// Style: buttonText90deg
lv_style_t *get_style_button_text90deg_MAIN_DEFAULT();
void add_style_button_text90deg(lv_obj_t *obj);
void remove_style_button_text90deg(lv_obj_t *obj);

// Style: checkbox_default
lv_style_t *get_style_checkbox_default_MAIN_DEFAULT();
lv_style_t *get_style_checkbox_default_INDICATOR_DEFAULT();
lv_style_t *get_style_checkbox_default_INDICATOR_CHECKED();
void add_style_checkbox_default(lv_obj_t *obj);
void remove_style_checkbox_default(lv_obj_t *obj);

// Style: checkbox_small
lv_style_t *get_style_checkbox_small_MAIN_DEFAULT();
lv_style_t *get_style_checkbox_small_INDICATOR_DEFAULT();
lv_style_t *get_style_checkbox_small_INDICATOR_CHECKED();
void add_style_checkbox_small(lv_obj_t *obj);
void remove_style_checkbox_small(lv_obj_t *obj);

// Style: screen_background
lv_style_t *get_style_screen_background_MAIN_DEFAULT();
void add_style_screen_background(lv_obj_t *obj);
void remove_style_screen_background(lv_obj_t *obj);

// Style: transparant_overlay
lv_style_t *get_style_transparant_overlay_MAIN_DEFAULT();
void add_style_transparant_overlay(lv_obj_t *obj);
void remove_style_transparant_overlay(lv_obj_t *obj);

// Style: selector small
lv_style_t *get_style_selector_small_MAIN_DEFAULT();
lv_style_t *get_style_selector_small_MAIN_DISABLED();
lv_style_t *get_style_selector_small_MAIN_FOCUSED();
void add_style_selector_small(lv_obj_t *obj);
void remove_style_selector_small(lv_obj_t *obj);

// Style: selector_with_disable
lv_style_t *get_style_selector_with_disable_MAIN_DEFAULT();
lv_style_t *get_style_selector_with_disable_MAIN_DISABLED();
lv_style_t *get_style_selector_with_disable_MAIN_FOCUSED();
lv_style_t *get_style_selector_with_disable_SELECTED_DEFAULT();
void add_style_selector_with_disable(lv_obj_t *obj);
void remove_style_selector_with_disable(lv_obj_t *obj);

// Style: spinbox_default
lv_style_t *get_style_spinbox_default_MAIN_DEFAULT();
lv_style_t *get_style_spinbox_default_MAIN_FOCUSED();
lv_style_t *get_style_spinbox_default_CURSOR_FOCUSED();
lv_style_t *get_style_spinbox_default_CURSOR_DEFAULT();
void add_style_spinbox_default(lv_obj_t *obj);
void remove_style_spinbox_default(lv_obj_t *obj);

// Style: label_red
lv_style_t *get_style_label_red_MAIN_DEFAULT();
void add_style_label_red(lv_obj_t *obj);
void remove_style_label_red(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/