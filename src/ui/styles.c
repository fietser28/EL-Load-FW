#include "styles.h"
#include "images.h"
#include "fonts.h"


#include "screens.h"

//
// Style: button
//

void init_style_button_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_radius(style, 6);
    lv_style_set_text_color(style, lv_color_hex(0xffffff00));
    lv_style_set_bg_color(style, lv_color_hex(0xff818181));
    lv_style_set_text_font(style, &lv_font_montserrat_24);
    lv_style_set_pad_top(style, 4);
    lv_style_set_pad_bottom(style, 4);
    lv_style_set_pad_left(style, 4);
    lv_style_set_pad_right(style, 4);
    lv_style_set_shadow_width(style, 0);
    lv_style_set_border_color(style, lv_color_hex(0xffffff00));
    lv_style_set_border_opa(style, 0);
    lv_style_set_border_width(style, 1);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
    lv_style_set_border_post(style, true);
};

lv_style_t *get_style_button_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_button_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffcccccc));
    lv_style_set_text_opa(style, 255);
};

lv_style_t *get_style_button_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_MAIN_DISABLED(style);
    }
    return style;
};

void add_style_button(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_button_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

void remove_style_button(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_button_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

//
// Style: selectbutton
//

void init_style_selectbutton_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_radius(style, 6);
    lv_style_set_text_color(style, lv_color_hex(0xffffff00));
    lv_style_set_bg_color(style, lv_color_hex(0xff818181));
    lv_style_set_text_font(style, &lv_font_montserrat_24);
    lv_style_set_shadow_width(style, 0);
};

lv_style_t *get_style_selectbutton_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_selectbutton_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_selectbutton_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffcccccc));
    lv_style_set_bg_color(style, lv_color_hex(0xff222222));
};

lv_style_t *get_style_selectbutton_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_selectbutton_MAIN_DISABLED(style);
    }
    return style;
};

void add_style_selectbutton(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_selectbutton_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_selectbutton_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

void remove_style_selectbutton(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_selectbutton_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_selectbutton_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

//
// Style: selectButtonRedGreen
//

void init_style_select_button_red_green_MAIN_DEFAULT(lv_style_t *style) {
    init_style_selectbutton_MAIN_DEFAULT(style);
    
    lv_style_set_align(style, LV_ALIGN_TOP_LEFT);
    lv_style_set_bg_color(style, lv_color_hex(0xff03bd2b));
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_select_button_red_green_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_select_button_red_green_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_select_button_red_green_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffca0202));
    lv_style_set_text_color(style, lv_color_hex(0xffffff00));
};

lv_style_t *get_style_select_button_red_green_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_select_button_red_green_MAIN_CHECKED(style);
    }
    return style;
};

void init_style_select_button_red_green_MAIN_DISABLED(lv_style_t *style) {
    init_style_selectbutton_MAIN_DISABLED(style);
    
};

lv_style_t *get_style_select_button_red_green_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_select_button_red_green_MAIN_DISABLED(style);
    }
    return style;
};

void add_style_select_button_red_green(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_select_button_red_green_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_select_button_red_green_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_select_button_red_green_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

void remove_style_select_button_red_green(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_select_button_red_green_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_select_button_red_green_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_select_button_red_green_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

//
// Style: selectButton90deg
//

void init_style_select_button90deg_MAIN_DEFAULT(lv_style_t *style) {
    init_style_selectbutton_MAIN_DEFAULT(style);
    
    lv_style_set_align(style, LV_ALIGN_TOP_LEFT);
    lv_style_set_border_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(0xffffffff));
    lv_style_set_border_width(style, 0);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
    lv_style_set_border_post(style, true);
    lv_style_set_radius(style, 4);
};

lv_style_t *get_style_select_button90deg_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_select_button90deg_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_select_button90deg_MAIN_DISABLED(lv_style_t *style) {
    init_style_selectbutton_MAIN_DISABLED(style);
    
    lv_style_set_bg_color(style, lv_color_hex(0xff000000));
    lv_style_set_bg_opa(style, 0);
};

lv_style_t *get_style_select_button90deg_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_select_button90deg_MAIN_DISABLED(style);
    }
    return style;
};

void add_style_select_button90deg(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_select_button90deg_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_select_button90deg_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

void remove_style_select_button90deg(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_select_button90deg_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_select_button90deg_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

//
// Style: blackpanel
//

void init_style_blackpanel_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff000000));
    lv_style_set_radius(style, 0);
    lv_style_set_border_width(style, 0);
};

lv_style_t *get_style_blackpanel_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_blackpanel_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_blackpanel(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_blackpanel_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_blackpanel(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_blackpanel_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: bigfont_label
//

void init_style_bigfont_label_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_font(style, &ui_font_ubunto_mono_30);
    lv_style_set_text_color(style, lv_color_hex(0xff00ffff));
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
};

lv_style_t *get_style_bigfont_label_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bigfont_label_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_bigfont_label(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_bigfont_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_bigfont_label(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_bigfont_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: bigfont Normal
//

void init_style_bigfont_normal_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff00ffff));
    lv_style_set_text_font(style, &lv_font_montserrat_30);
    lv_style_set_bg_color(style, lv_color_hex(0xff111111));
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 0);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_bigfont_normal_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bigfont_normal_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_bigfont_normal(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_bigfont_normal_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_bigfont_normal(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_bigfont_normal_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: warning
//

void init_style_warning_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_radius(style, 4);
    lv_style_set_border_width(style, 3);
    lv_style_set_bg_color(style, lv_color_hex(0xfff78000));
    lv_style_set_border_color(style, lv_color_hex(0xffffffff));
};

lv_style_t *get_style_warning_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_warning_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_warning(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_warning_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_warning(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_warning_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Title 
//

void init_style_title__MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff5060a0));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_text_color(style, lv_color_hex(0xffcccccc));
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_title__MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_title__MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_title_(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_title__MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_title_(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_title__MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: slider
//

void init_style_slider_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff818181));
    lv_style_set_bg_opa(style, 75);
};

lv_style_t *get_style_slider_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_slider_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff818181));
};

lv_style_t *get_style_slider_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_slider_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffffff00));
};

lv_style_t *get_style_slider_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_slider_KNOB_DEFAULT(style);
    }
    return style;
};

void add_style_slider(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_slider_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_slider_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_slider_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

void remove_style_slider(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_slider_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_slider_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_slider_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

//
// Style: small label
//

void init_style_small_label_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffcccccc));
    lv_style_set_text_font(style, &ui_font_ubuntu_mono_20);
};

lv_style_t *get_style_small_label_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_small_label_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_small_label(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_small_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_small_label(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_small_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: small label_symbol
//

void init_style_small_label_symbol_MAIN_DEFAULT(lv_style_t *style) {
    init_style_small_label_MAIN_DEFAULT(style);
    
    lv_style_set_text_font(style, &lv_font_montserrat_20);
};

lv_style_t *get_style_small_label_symbol_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_small_label_symbol_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_small_label_symbol(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_small_label_symbol_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_small_label_symbol(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_small_label_symbol_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: extra small label
//

void init_style_extra_small_label_MAIN_DEFAULT(lv_style_t *style) {
    init_style_small_label_MAIN_DEFAULT(style);
    
    lv_style_set_text_font(style, &lv_font_montserrat_14);
};

lv_style_t *get_style_extra_small_label_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_extra_small_label_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_extra_small_label(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_extra_small_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_extra_small_label(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_extra_small_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: small header
//

void init_style_small_header_MAIN_DEFAULT(lv_style_t *style) {
    init_style_small_label_MAIN_DEFAULT(style);
    
    lv_style_set_text_font(style, &lv_font_montserrat_20);
    lv_style_set_bg_color(style, lv_color_hex(0xff5060a0));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_small_header_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_small_header_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_small_header(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_small_header_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_small_header(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_small_header_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: buttonText
//

void init_style_button_text_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_CENTER);
};

lv_style_t *get_style_button_text_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_text_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_text(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_text_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_text(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_text_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: buttonText90deg
//

void init_style_button_text90deg_MAIN_DEFAULT(lv_style_t *style) {
    init_style_button_text_MAIN_DEFAULT(style);
    
    lv_style_set_text_font(style, &ui_font_ubuntu_mono_20);
    lv_style_set_transform_pivot_x(style, 12);
    lv_style_set_transform_pivot_y(style, 16);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_bg_opa(style, 0);
    lv_style_set_transform_rotation(style, 2700);
};

lv_style_t *get_style_button_text90deg_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_text90deg_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_button_text90deg(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_button_text90deg_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_button_text90deg(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_button_text90deg_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: checkbox_default
//

void init_style_checkbox_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffcccccc));
    lv_style_set_text_font(style, &ui_font_ubuntu_mono_20);
};

lv_style_t *get_style_checkbox_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_checkbox_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_checkbox_default_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(0xffffff00));
    lv_style_set_bg_color(style, lv_color_hex(0xff818181));
};

lv_style_t *get_style_checkbox_default_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_checkbox_default_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_checkbox_default_INDICATOR_CHECKED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffffff00));
    lv_style_set_bg_color(style, lv_color_hex(0xff818181));
};

lv_style_t *get_style_checkbox_default_INDICATOR_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_checkbox_default_INDICATOR_CHECKED(style);
    }
    return style;
};

void add_style_checkbox_default(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_checkbox_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_checkbox_default_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_checkbox_default_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
};

void remove_style_checkbox_default(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_checkbox_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_checkbox_default_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_checkbox_default_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
};

//
// Style: screen_background
//

void init_style_screen_background_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff000000));
};

lv_style_t *get_style_screen_background_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_screen_background_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_screen_background(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_screen_background_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_screen_background(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_screen_background_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: transparant_overlay
//

void init_style_transparant_overlay_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_opa(style, 64);
    lv_style_set_border_side(style, LV_BORDER_SIDE_NONE);
    lv_style_set_radius(style, 0);
};

lv_style_t *get_style_transparant_overlay_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_transparant_overlay_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_transparant_overlay(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_transparant_overlay_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_transparant_overlay(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_transparant_overlay_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: selector small
//

void init_style_selector_small_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff818181));
    lv_style_set_text_color(style, lv_color_hex(0xffffff00));
};

lv_style_t *get_style_selector_small_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_selector_small_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_selector_small_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffcccccc));
    lv_style_set_bg_color(style, lv_color_hex(0xff111111));
};

lv_style_t *get_style_selector_small_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_selector_small_MAIN_DISABLED(style);
    }
    return style;
};

void init_style_selector_small_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_outline_width(style, 2);
    lv_style_set_outline_color(style, lv_color_hex(0xff0000ff));
};

lv_style_t *get_style_selector_small_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_selector_small_MAIN_FOCUSED(style);
    }
    return style;
};

void add_style_selector_small(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_selector_small_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_selector_small_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_add_style(obj, get_style_selector_small_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

void remove_style_selector_small(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_selector_small_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_selector_small_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_remove_style(obj, get_style_selector_small_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

//
// Style: selector_with_disable
//

void init_style_selector_with_disable_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(0xffffff00));
    lv_style_set_bg_color(style, lv_color_hex(0xff818181));
    lv_style_set_text_font(style, &lv_font_montserrat_18);
    lv_style_set_border_width(style, 0);
};

lv_style_t *get_style_selector_with_disable_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_selector_with_disable_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_selector_with_disable_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff111111));
    lv_style_set_text_color(style, lv_color_hex(0xffcccccc));
};

lv_style_t *get_style_selector_with_disable_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_selector_with_disable_MAIN_DISABLED(style);
    }
    return style;
};

void init_style_selector_with_disable_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_outline_width(style, 2);
    lv_style_set_outline_color(style, lv_color_hex(0xff0000ff));
};

lv_style_t *get_style_selector_with_disable_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_selector_with_disable_MAIN_FOCUSED(style);
    }
    return style;
};

void init_style_selector_with_disable_SELECTED_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff404040));
    lv_style_set_bg_opa(style, 0);
};

lv_style_t *get_style_selector_with_disable_SELECTED_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_selector_with_disable_SELECTED_DEFAULT(style);
    }
    return style;
};

void add_style_selector_with_disable(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_selector_with_disable_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_selector_with_disable_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_add_style(obj, get_style_selector_with_disable_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(obj, get_style_selector_with_disable_SELECTED_DEFAULT(), LV_PART_SELECTED | LV_STATE_DEFAULT);
};

void remove_style_selector_with_disable(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_selector_with_disable_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_selector_with_disable_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_remove_style(obj, get_style_selector_with_disable_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_remove_style(obj, get_style_selector_with_disable_SELECTED_DEFAULT(), LV_PART_SELECTED | LV_STATE_DEFAULT);
};

//
// Style: spinbox_default
//

void init_style_spinbox_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff111111));
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
    lv_style_set_border_width(style, 0);
    lv_style_set_text_color(style, lv_color_hex(0xffffff00));
    lv_style_set_text_font(style, &ui_font_ubunto_mono_30);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
    lv_style_set_radius(style, 0);
};

lv_style_t *get_style_spinbox_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_spinbox_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_spinbox_default_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_outline_width(style, 2);
    lv_style_set_outline_color(style, lv_color_hex(0xff0000ff));
};

lv_style_t *get_style_spinbox_default_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_spinbox_default_MAIN_FOCUSED(style);
    }
    return style;
};

void init_style_spinbox_default_CURSOR_FOCUSED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xffffff00));
    lv_style_set_bg_color(style, lv_color_hex(0xff0000ff));
};

lv_style_t *get_style_spinbox_default_CURSOR_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_spinbox_default_CURSOR_FOCUSED(style);
    }
    return style;
};

void init_style_spinbox_default_CURSOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff111111));
    lv_style_set_text_color(style, lv_color_hex(0xffffff00));
};

lv_style_t *get_style_spinbox_default_CURSOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_spinbox_default_CURSOR_DEFAULT(style);
    }
    return style;
};

void add_style_spinbox_default(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_spinbox_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_spinbox_default_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(obj, get_style_spinbox_default_CURSOR_FOCUSED(), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_obj_add_style(obj, get_style_spinbox_default_CURSOR_DEFAULT(), LV_PART_CURSOR | LV_STATE_DEFAULT);
};

void remove_style_spinbox_default(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_spinbox_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_spinbox_default_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_remove_style(obj, get_style_spinbox_default_CURSOR_FOCUSED(), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_obj_remove_style(obj, get_style_spinbox_default_CURSOR_DEFAULT(), LV_PART_CURSOR | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_button,
        add_style_selectbutton,
        add_style_select_button_red_green,
        add_style_select_button90deg,
        add_style_blackpanel,
        add_style_bigfont_label,
        add_style_bigfont_normal,
        add_style_warning,
        add_style_title_,
        add_style_slider,
        add_style_small_label,
        add_style_small_label_symbol,
        add_style_extra_small_label,
        add_style_small_header,
        add_style_button_text,
        add_style_button_text90deg,
        add_style_checkbox_default,
        add_style_screen_background,
        add_style_transparant_overlay,
        add_style_selector_small,
        add_style_selector_with_disable,
        add_style_spinbox_default,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_button,
        remove_style_selectbutton,
        remove_style_select_button_red_green,
        remove_style_select_button90deg,
        remove_style_blackpanel,
        remove_style_bigfont_label,
        remove_style_bigfont_normal,
        remove_style_warning,
        remove_style_title_,
        remove_style_slider,
        remove_style_small_label,
        remove_style_small_label_symbol,
        remove_style_extra_small_label,
        remove_style_small_header,
        remove_style_button_text,
        remove_style_button_text90deg,
        remove_style_checkbox_default,
        remove_style_screen_background,
        remove_style_transparant_overlay,
        remove_style_selector_small,
        remove_style_selector_with_disable,
        remove_style_spinbox_default,
    };
    remove_style_funcs[styleIndex](obj);
}

