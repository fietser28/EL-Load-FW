#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "styles.h"
#include "ui.h"

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_mode_selector(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(1, 1, 1);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        int32_t value = lv_dropdown_get_selected(ta);
        if (tick_value_change_obj != ta) {
            assignIntegerProperty(1, 1, 3, value, "Failed to assign Selected in Dropdown widget");
        }
    }
}

static void event_handler_cb_main_on_off_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(1, 0, 1);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(1, 0, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_button_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        action_toggle_record(e);
    }
}

static void event_handler_cb_main_button_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        action_clear_power(e);
    }
}

static void event_handler_cb_main_set_value_area(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_FOCUSED) {
        action_text_area_disable_blink(e);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        const char *value = lv_textarea_get_text(ta);
        if (tick_value_change_obj != ta) {
            assignStringProperty(1, 20, 2, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_main_label_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(1, 21, 1);
    }
}

static void event_handler_cb_main_button_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(1, 25, 1);
    }
}

static void event_handler_cb_main_button_4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(1, 27, 1);
    }
}

static void event_handler_cb_main_button_5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(1, 30, 1);
    }
}

static void event_handler_cb_main_button_6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(1, 32, 1);
    }
}

static void event_handler_cb_main_button_7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(1, 34, 1);
    }
}

static void event_handler_cb_main_button_8(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(1, 51, 1);
    }
}

static void event_handler_cb_set_value_isetkeyb(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_READY) {
        flowPropagateValue(2, 1, 1);
    }
    if (event == LV_EVENT_CANCEL) {
        flowPropagateValue(2, 1, 2);
    }
}

static void event_handler_cb_set_value_isetkey_value(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_FOCUSED) {
        action_text_area_disable_blink(e);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        const char *value = lv_textarea_get_text(ta);
        if (tick_value_change_obj != ta) {
            assignStringProperty(2, 3, 2, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_settings_button_9(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(4, 1, 1);
    }
}

static void event_handler_cb_settings_button_10(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(4, 3, 1);
    }
}

static void event_handler_cb_settings_textarea_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        const char *value = lv_textarea_get_text(ta);
        if (tick_value_change_obj != ta) {
            assignStringProperty(4, 5, 2, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_settings_button_11(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(4, 7, 1);
    }
}

static void event_handler_cb_nlpc_nlpc_home(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(5, 5, 1);
    }
}

static void event_handler_cb_nlpc_roller_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        int32_t value = lv_roller_get_selected(ta);
        if (tick_value_change_obj != ta) {
            assignIntegerProperty(5, 13, 2, value, "Failed to assign Selected in Roller widget");
        }
    }
}

static void event_handler_cb_nlpc_nlpc_home_cancel(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(5, 14, 1);
    }
}

static void event_handler_cb_nlpc_nlpc_home_cancel_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(5, 16, 1);
    }
}

static void event_handler_cb_nlpc_textarea_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        const char *value = lv_textarea_get_text(ta);
        if (tick_value_change_obj != ta) {
            assignStringProperty(5, 18, 2, value, "Failed to assign Text in Textarea widget");
        }
    }
}

void create_screen_startup() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.startup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_blackpanel(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 42);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "DCL8010");
            apply_style_bigfont_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_startup() {
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // modeSelector
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.mode_selector = obj;
            lv_obj_set_pos(obj, 4, 4);
            lv_obj_set_size(obj, 130, 38);
            lv_dropdown_set_options(obj, "Mode CC\nMode CV\nMode CP\nMode CR");
            lv_obj_add_event_cb(obj, event_handler_cb_main_mode_selector, LV_EVENT_ALL, 0);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff111111), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            // ON-OFF button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.on_off_button = obj;
            lv_obj_set_pos(obj, -4, 4);
            lv_obj_set_size(obj, 109, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_main_on_off_button, LV_EVENT_ALL, 0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_button(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff03bd2b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffca0202), LV_PART_MAIN | LV_STATE_CHECKED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_2 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_3 = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 160, 36);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            apply_style_bigfont_label(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_4 = obj;
            lv_obj_set_pos(obj, 160, 46);
            lv_obj_set_size(obj, 160, 36);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            apply_style_bigfont_label(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_5 = obj;
            lv_obj_set_pos(obj, 0, 82);
            lv_obj_set_size(obj, 160, 36);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            apply_style_bigfont_label(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_6 = obj;
            lv_obj_set_pos(obj, 160, 82);
            lv_obj_set_size(obj, 160, 36);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            apply_style_bigfont_label(obj);
        }
        {
            // Power Panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.power_panel = obj;
            lv_obj_set_pos(obj, 0, 120);
            lv_obj_set_size(obj, 320, 47);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, -11, 1);
                    lv_obj_set_size(obj, 32, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_button_1, LV_EVENT_ALL, 0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_7 = obj;
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, 24, 24);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // Ah
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ah = obj;
                    lv_obj_set_pos(obj, 14, -12);
                    lv_obj_set_size(obj, 155, 21);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    apply_style_small_label(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // Wh
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wh = obj;
                    lv_obj_set_pos(obj, 14, 9);
                    lv_obj_set_size(obj, 155, 21);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    apply_style_small_label(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // montime
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.montime = obj;
                    lv_obj_set_pos(obj, 174, 0);
                    lv_obj_set_size(obj, 92, 21);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    apply_style_small_label(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    lv_obj_set_pos(obj, 11, 1);
                    lv_obj_set_size(obj, 32, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_button_2, LV_EVENT_ALL, 0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_RIGHT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_8 = obj;
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, 24, 24);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 167);
            lv_obj_set_size(obj, 320, 73);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // iset
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.iset = obj;
                    lv_obj_set_pos(obj, -15, -12);
                    lv_obj_set_size(obj, 160, 69);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_blackpanel(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // isetlabel
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.isetlabel = obj;
                            lv_obj_set_pos(obj, 0, -10);
                            lv_obj_set_size(obj, 160, 27);
                            apply_style_small_label(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // setValueArea
                            lv_obj_t *obj = lv_textarea_create(parent_obj);
                            objects.set_value_area = obj;
                            lv_obj_set_pos(obj, -9, 14);
                            lv_obj_set_size(obj, 118, 33);
                            lv_textarea_set_max_length(obj, 8);
                            lv_textarea_set_one_line(obj, true);
                            lv_textarea_set_password_mode(obj, false);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_set_value_area, LV_EVENT_ALL, 0);
                            apply_style_bigfont_normal(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_CURSOR | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_opa(obj, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.label_1 = obj;
                            lv_obj_set_pos(obj, 109, 14);
                            lv_obj_set_size(obj, 38, 36);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_label_1, LV_EVENT_ALL, 0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // Von panel
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.von_panel = obj;
                    lv_obj_set_pos(obj, 145, -12);
                    lv_obj_set_size(obj, 160, 70);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_blackpanel(obj);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, -14, -15);
                            lv_obj_set_size(obj, 79, 70);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            apply_style_blackpanel(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // vonlabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.vonlabel = obj;
                                    lv_obj_set_pos(obj, 1, -12);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_label_set_text(obj, "Von:");
                                    apply_style_small_label(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    lv_obj_set_pos(obj, -12, 12);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_button_3, LV_EVENT_ALL, 0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    apply_style_button(obj);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.label_9 = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 79, 21);
                                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    lv_obj_set_pos(obj, -12, 36);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_button_4, LV_EVENT_ALL, 0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    apply_style_button(obj);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.label_10 = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 79, 21);
                                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 65, -15);
                            lv_obj_set_size(obj, 80, 70);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            apply_style_blackpanel(obj);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    lv_obj_set_pos(obj, -13, -14);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_button_5, LV_EVENT_ALL, 0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    apply_style_button(obj);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.label_11 = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 78, 21);
                                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    lv_obj_set_pos(obj, -13, 10);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_button_6, LV_EVENT_ALL, 0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    apply_style_button(obj);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.label_12 = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 78, 21);
                                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    lv_obj_set_pos(obj, -13, 34);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_button_7, LV_EVENT_ALL, 0);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    apply_style_button(obj);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.label_13 = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 78, 21);
                                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // wheel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wheel = obj;
            lv_obj_set_pos(obj, 135, 27);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 143, 4);
            lv_obj_set_size(obj, 58, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_main_button_8, LV_EVENT_ALL, 0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_14 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 24, 24);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_main() {
    {
        bool new_val = evalBooleanProperty(1, 1, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.mode_selector, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.mode_selector;
            if (new_val) lv_obj_add_state(objects.mode_selector, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.mode_selector, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(1, 1, 3, "Failed to evaluate Selected in Dropdown widget");
        int32_t cur_val = lv_dropdown_get_selected(objects.mode_selector);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.mode_selector;
            lv_dropdown_set_selected(objects.mode_selector, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(1, 0, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.on_off_button, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button;
            if (new_val) lv_obj_add_state(objects.on_off_button, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.on_off_button, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 2, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_2;
            lv_label_set_text(objects.label_2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 3, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_3);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_3;
            lv_label_set_text(objects.label_3, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 4, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_4);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_4;
            lv_label_set_text(objects.label_4, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 5, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_5);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_5;
            lv_label_set_text(objects.label_5, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 6, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_6);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_6;
            lv_label_set_text(objects.label_6, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 11, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_7);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_7;
            lv_label_set_text(objects.label_7, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 12, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah;
            lv_label_set_text(objects.ah, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 13, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wh);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wh;
            lv_label_set_text(objects.wh, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 14, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.montime);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.montime;
            lv_label_set_text(objects.montime, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 16, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_8);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_8;
            lv_label_set_text(objects.label_8, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 19, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.isetlabel);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.isetlabel;
            lv_label_set_text(objects.isetlabel, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 20, 2, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.set_value_area);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.set_value_area;
            lv_textarea_set_text(objects.set_value_area, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 21, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_1;
            lv_label_set_text(objects.label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 26, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_9);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_9;
            lv_label_set_text(objects.label_9, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 28, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_10);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_10;
            lv_label_set_text(objects.label_10, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 31, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_11);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_11;
            lv_label_set_text(objects.label_11, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 33, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_12);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_12;
            lv_label_set_text(objects.label_12, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 35, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_13);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_13;
            lv_label_set_text(objects.label_13, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(1, 37, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.wheel;
            if (new_val) lv_obj_add_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(1, 52, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_14);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_14;
            lv_label_set_text(objects.label_14, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_set_value() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.set_value = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    {
        lv_obj_t *parent_obj = obj;
        {
            // isetkeyb
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.isetkeyb = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 170);
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
            lv_obj_add_event_cb(obj, event_handler_cb_set_value_isetkeyb, LV_EVENT_ALL, 0);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc1c1c1), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // isetkey
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.isetkey = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 69);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_blackpanel(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // isetlkeyabel
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.isetlkeyabel = obj;
                    lv_obj_set_pos(obj, 0, -10);
                    lv_obj_set_size(obj, 320, 27);
                    apply_style_small_label(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // isetkeyValue
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.isetkey_value = obj;
                    lv_obj_set_pos(obj, -13, 14);
                    lv_obj_set_size(obj, 320, 43);
                    lv_textarea_set_accepted_chars(obj, "0123456789.");
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, event_handler_cb_set_value_isetkey_value, LV_EVENT_ALL, 0);
                    apply_style_bigfont_digital(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff888888), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 50, LV_PART_CURSOR | LV_STATE_DEFAULT);
                }
            }
        }
    }
    lv_keyboard_set_textarea(objects.isetkeyb, objects.isetkey_value);
}

void tick_screen_set_value() {
    {
        bool new_val = evalBooleanProperty(2, 0, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.isetkey, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.isetkey;
            if (new_val) lv_obj_add_flag(objects.isetkey, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.isetkey, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(2, 2, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.isetlkeyabel);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.isetlkeyabel;
            lv_label_set_text(objects.isetlkeyabel, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(2, 3, 2, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.isetkey_value);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.isetkey_value;
            lv_textarea_set_text(objects.isetkey_value, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_graph() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.graph = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_chart_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 192);
        }
    }
}

void tick_screen_graph() {
}

void create_screen_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 203, 190);
            lv_obj_set_size(obj, 100, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_button_9, LV_EVENT_ALL, 0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_15 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 10, 190);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_button_10, LV_EVENT_ALL, 0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Calibration");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.textarea_1 = obj;
            lv_obj_set_pos(obj, 10, 19);
            lv_obj_set_size(obj, 293, 101);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_textarea_1, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 11, 140);
            lv_obj_set_size(obj, 187, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_button_11, LV_EVENT_ALL, 0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "NLPC windows");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_settings() {
    {
        const char *new_val = evalTextProperty(4, 0, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_15);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_15;
            lv_label_set_text(objects.label_15, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(4, 5, 2, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.textarea_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.textarea_1;
            lv_textarea_set_text(objects.textarea_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_nlpc() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.nlpc = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_blackpanel(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 140);
            lv_obj_set_size(obj, 169, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "PL Frequency:");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home = obj;
            lv_obj_set_pos(obj, 225, 190);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_nlpc_nlpc_home, LV_EVENT_ALL, 0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_16 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_17 = obj;
            lv_obj_set_pos(obj, 25, 36);
            lv_obj_set_size(obj, 279, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 69);
            lv_obj_set_size(obj, 20, 25);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "1");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 298, 70);
            lv_obj_set_size(obj, 20, 25);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "60");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 25, 12);
            lv_obj_set_size(obj, 279, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Measurement Averaging");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_18 = obj;
            lv_obj_set_pos(obj, 43, 108);
            lv_obj_set_size(obj, 254, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.roller_1 = obj;
            lv_obj_set_pos(obj, 192, 130);
            lv_obj_set_size(obj, 80, 44);
            lv_roller_set_options(obj, "50 Hz\n60 Hz", LV_ROLLER_MODE_NORMAL);
            lv_obj_add_event_cb(obj, event_handler_cb_nlpc_roller_1, LV_EVENT_ALL, 0);
        }
        {
            // NLPC_HOME_CANCEL
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_cancel = obj;
            lv_obj_set_pos(obj, 115, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_nlpc_nlpc_home_cancel, LV_EVENT_ALL, 0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_19 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // NLPC_HOME_CANCEL_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_cancel_1 = obj;
            lv_obj_set_pos(obj, 5, 192);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_nlpc_nlpc_home_cancel_1, LV_EVENT_ALL, 0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_20 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.textarea_2 = obj;
            lv_obj_set_pos(obj, 90, 59);
            lv_obj_set_size(obj, 150, 49);
            lv_textarea_set_accepted_chars(obj, "0123456789");
            lv_textarea_set_max_length(obj, 5);
            lv_textarea_set_placeholder_text(obj, "2");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_nlpc_textarea_2, LV_EVENT_ALL, 0);
            apply_style_bigfont_normal(obj);
        }
    }
}

void tick_screen_nlpc() {
    {
        const char *new_val = evalTextProperty(5, 6, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_16);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_16;
            lv_label_set_text(objects.label_16, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(5, 8, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_17);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_17;
            lv_label_set_text(objects.label_17, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(5, 12, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_18);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_18;
            lv_label_set_text(objects.label_18, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(5, 13, 2, "Failed to evaluate Selected in Roller widget");
        int32_t cur_val = lv_roller_get_selected(objects.roller_1);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.roller_1;
            lv_roller_set_selected(objects.roller_1, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(5, 15, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_19);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_19;
            lv_label_set_text(objects.label_19, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(5, 17, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_20);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_20;
            lv_label_set_text(objects.label_20, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(5, 18, 2, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.textarea_2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.textarea_2;
            lv_textarea_set_text(objects.textarea_2, new_val);
            tick_value_change_obj = NULL;
        }
    }
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_startup();
    create_screen_main();
    create_screen_set_value();
    create_screen_graph();
    create_screen_settings();
    create_screen_nlpc();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_startup,
    tick_screen_main,
    tick_screen_set_value,
    tick_screen_graph,
    tick_screen_settings,
    tick_screen_nlpc,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
