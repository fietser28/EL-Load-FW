#include "styles.h"
#include "images.h"
#include "fonts.h"

void apply_style_button(lv_obj_t *obj) {
    lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_post(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DISABLED);
};
void apply_style_selectbutton(lv_obj_t *obj) {
    lv_obj_set_style_radius(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff222222), LV_PART_MAIN | LV_STATE_DISABLED);
};
void apply_style_select_button_red_green(lv_obj_t *obj) {
    apply_style_selectbutton(obj);
    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff03bd2b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffca0202), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_CHECKED);
};
void apply_style_select_button90deg(lv_obj_t *obj) {
    apply_style_selectbutton(obj);
    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_post(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
};
void apply_style_blackpanel(lv_obj_t *obj) {
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_bigfont_label(lv_obj_t *obj) {
    lv_obj_set_style_text_font(obj, &ui_font_ubunto_mono_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_bigfont_normal(lv_obj_t *obj) {
    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff111111), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_warning(lv_obj_t *obj) {
    lv_obj_set_style_radius(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff78000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_title_(lv_obj_t *obj) {
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff5060a0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_slider(lv_obj_t *obj) {
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 75, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff00), LV_PART_KNOB | LV_STATE_DEFAULT);
};
void apply_style_small_label(lv_obj_t *obj) {
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_20, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_small_label_symbol(lv_obj_t *obj) {
    apply_style_small_label(obj);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_extra_small_label(lv_obj_t *obj) {
    apply_style_small_label(obj);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_small_header(lv_obj_t *obj) {
    apply_style_small_label(obj);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff5060a0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_button_text(lv_obj_t *obj) {
    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_button_text90deg(lv_obj_t *obj) {
    apply_style_button_text(obj);
    lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_transform_pivot_x(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_transform_pivot_y(obj, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_checkbox_default(lv_obj_t *obj) {
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(obj, lv_color_hex(0xffffff00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_INDICATOR | LV_STATE_CHECKED);
};
void apply_style_screen_background(lv_obj_t *obj) {
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_transparant_overlay(lv_obj_t *obj) {
    lv_obj_set_style_bg_opa(obj, 64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
};
void apply_style_selector_small(lv_obj_t *obj) {
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff111111), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_FOCUSED);
};
void apply_style_selector_with_disable(lv_obj_t *obj) {
    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff111111), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff404040), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
};
void apply_style_spinbox_default(lv_obj_t *obj) {
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff111111), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &ui_font_ubunto_mono_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000ff), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff111111), LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_DEFAULT);
};

