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
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 1, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        int32_t value = lv_dropdown_get_selected(ta);
        if (tick_value_change_obj != ta) {
            assignIntegerProperty(flowState, 1, 3, value, "Failed to assign Selected in Dropdown widget");
        }
    }
}

static void event_handler_cb_main_on_off_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 0, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 0, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 4, 0);
    }
}

static void event_handler_cb_main_obj6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 10, 0);
    }
}

static void event_handler_cb_main_obj7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        action_toggle_record(e);
    }
}

static void event_handler_cb_main_obj9(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        action_clear_power(e);
    }
}

static void event_handler_cb_main_set_value_area(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_FOCUSED) {
        action_text_area_disable_blink(e);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 22, 1);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        const char *value = lv_textarea_get_text(ta);
        if (tick_value_change_obj != ta) {
            assignStringProperty(flowState, 22, 2, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_main_obj11(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 23, 0);
    }
}

static void event_handler_cb_main_obj12(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 27, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 27, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_obj14(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 29, 0);
    }
}

static void event_handler_cb_main_obj16(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 32, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 32, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_obj19(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 45, 0);
    }
}

static void event_handler_cb_settings_obj24(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 1, 0);
    }
}

static void event_handler_cb_settings_obj26(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 3, 0);
    }
}

static void event_handler_cb_settings_obj28(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 6, 0);
    }
}

static void event_handler_cb_settings_obj31(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 10, 0);
    }
}

static void event_handler_cb_settings_obj33(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 12, 0);
    }
}

static void event_handler_cb_events_obj36(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 0, 0);
    }
}

static void event_handler_cb_events_obj38(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        const char *value = lv_textarea_get_text(ta);
        if (tick_value_change_obj != ta) {
            assignStringProperty(flowState, 4, 2, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_protections_obj40(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 0, 0);
    }
}

static void event_handler_cb_protections_obj42(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 8, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 8, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj44(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 10, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 10, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj46(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 18, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 18, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj48(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 20, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 20, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj50(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 22, 0);
    }
}

static void event_handler_cb_protections_obj51(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 24, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 24, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj53(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 26, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 26, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_calibration_obj57(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        int32_t value = lv_dropdown_get_selected(ta);
        if (tick_value_change_obj != ta) {
            assignIntegerProperty(flowState, 0, 3, value, "Failed to assign Selected in Dropdown widget");
        }
    }
}

static void event_handler_cb_calibration_obj58(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 4, 0);
    }
}

static void event_handler_cb_calibration_obj62(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 9, 0);
    }
}

static void event_handler_cb_calibration_obj63(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 11, 0);
    }
}

static void event_handler_cb_calibration_obj64(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
}

static void event_handler_cb_calibration_obj65(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 13, 0);
    }
}

static void event_handler_cb_calibration_obj67(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 15, 0);
    }
}

static void event_handler_cb_calibration_obj68(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
}

static void event_handler_cb_calibration_obj70(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 19, 0);
    }
}

static void event_handler_cb_calibration_obj71(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 20, 0);
    }
}

static void event_handler_cb_calibration_obj72(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 28, 0);
    }
}

static void event_handler_cb_calibration_obj73(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 29, 0);
    }
}

static void event_handler_cb_nlpc_nlp_c_home(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 5, 0);
    }
}

static void event_handler_cb_nlpc_nlp_c_hom_e_cancel(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 11, 0);
    }
}

static void event_handler_cb_nlpc_nlp_c_hom_e_cance_l_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 13, 0);
    }
}

static void event_handler_cb_nlpc_obj80(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 15, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        int32_t value = lv_slider_get_value(ta);
        if (tick_value_change_obj != ta) {
            assignIntegerProperty(flowState, 15, 2, value, "Failed to assign Value in Slider widget");
        }
    }
}

static void event_handler_cb_nlpc_obj81(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 19, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        int32_t value = lv_dropdown_get_selected(ta);
        if (tick_value_change_obj != ta) {
            assignIntegerProperty(flowState, 19, 2, value, "Failed to assign Selected in Dropdown widget");
        }
    }
}

static void event_handler_cb_question_yn_obj84(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 0, 0);
    }
}

static void event_handler_cb_question_yn_obj85(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 3, 0);
    }
}

static void event_handler_cb_keyboard_old_kbtext(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        const char *value = lv_textarea_get_text(ta);
        if (tick_value_change_obj != ta) {
            assignStringProperty(flowState, 0, 2, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_keyboard_kbtext2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        const char *value = lv_textarea_get_text(ta);
        if (tick_value_change_obj != ta) {
            assignStringProperty(flowState, 2, 2, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_keyboard_obj23(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_READY) {
        flowPropagateValue(flowState, 3, 0);
    }
    if (event == LV_EVENT_CANCEL) {
        flowPropagateValue(flowState, 3, 1);
    }
}

void create_screen_startup() {
    void *flowState = getFlowState(0, 0);
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
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 3, 42);
            lv_obj_set_size(obj, 314, 194);
            lv_label_set_text(obj, "");
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff222222), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_startup() {
    void *flowState = getFlowState(0, 0);
    {
        const char *new_val = evalTextProperty(flowState, 6, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj0);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj0;
            lv_label_set_text(objects.obj0, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 1);
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
            lv_dropdown_set_options(obj, "Mode CC\nMode CV\nMode CP\nMode CR\nSHORT");
            lv_obj_add_event_cb(obj, event_handler_cb_main_mode_selector, LV_EVENT_ALL, flowState);
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
            lv_obj_add_event_cb(obj, event_handler_cb_main_on_off_button, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_button(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff03bd2b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffca0202), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff111111), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DISABLED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 320, 72);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_blackpanel(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj2 = obj;
                    lv_obj_set_pos(obj, -13, -10);
                    lv_obj_set_size(obj, 160, 36);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj2, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj3 = obj;
                    lv_obj_set_pos(obj, 147, -13);
                    lv_obj_set_size(obj, 160, 36);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj4 = obj;
                    lv_obj_set_pos(obj, -13, 23);
                    lv_obj_set_size(obj, 160, 36);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj5 = obj;
                    lv_obj_set_pos(obj, 147, 23);
                    lv_obj_set_size(obj, 160, 36);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 320, 72);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj6, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_blackpanel(obj);
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
                    objects.obj7 = obj;
                    lv_obj_set_pos(obj, -11, 1);
                    lv_obj_set_size(obj, 32, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj7, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj8 = obj;
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, 24, 24);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
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
                    lv_label_set_text(obj, "");
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
                    lv_label_set_text(obj, "");
                    apply_style_small_label(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // montime
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.montime = obj;
                    lv_obj_set_pos(obj, 172, 0);
                    lv_obj_set_size(obj, 92, 21);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    apply_style_small_label(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj9 = obj;
                    lv_obj_set_pos(obj, 11, 1);
                    lv_obj_set_size(obj, 32, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj9, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_RIGHT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj10 = obj;
                            lv_obj_set_pos(obj, 1, 0);
                            lv_obj_set_size(obj, 24, 24);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // Main-Lower panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_lower_panel = obj;
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
                            lv_label_set_text(obj, "");
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
                            lv_obj_add_event_cb(obj, event_handler_cb_main_set_value_area, LV_EVENT_ALL, flowState);
                            apply_style_bigfont_normal(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ubunto_mono_30, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                            objects.obj11 = obj;
                            lv_obj_set_pos(obj, 109, 14);
                            lv_obj_set_size(obj, 38, 36);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj11, LV_EVENT_ALL, flowState);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_ubunto_mono_30, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                                    objects.obj12 = obj;
                                    lv_obj_set_pos(obj, -12, 12);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj12, LV_EVENT_ALL, flowState);
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
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffca0202), LV_PART_MAIN | LV_STATE_CHECKED);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj13 = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 79, 21);
                                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                            lv_label_set_text(obj, "");
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.obj14 = obj;
                                    lv_obj_set_pos(obj, -12, 36);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj14, LV_EVENT_ALL, flowState);
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
                                            objects.obj15 = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 79, 21);
                                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                            lv_label_set_text(obj, "");
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
                                    objects.obj16 = obj;
                                    lv_obj_set_pos(obj, -2, -9);
                                    lv_obj_set_size(obj, 55, 34);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj16, LV_EVENT_ALL, flowState);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    apply_style_select_button_red_green(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj17 = obj;
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, 78, 24);
                                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                            lv_label_set_text(obj, "");
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj18 = obj;
                                    lv_obj_set_pos(obj, 0, 21);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_label_set_text(obj, "");
                                    apply_style_small_label(obj);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_pad_top(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            objects.obj19 = obj;
            lv_obj_set_pos(obj, 143, 4);
            lv_obj_set_size(obj, 58, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj19, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj20 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 24, 24);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj21 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_style_value_t value;
            value.num = 0;
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_LEFT, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_TOP, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_RIGHT, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_LEFT, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_BG_OPA, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_BORDER_WIDTH, value, LV_PART_MAIN);
            create_user_widget_keyboard(obj, getFlowState(flowState, 62), 31);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
    }
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 1);
    {
        bool new_val = evalBooleanProperty(flowState, 1, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.mode_selector, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.mode_selector;
            if (new_val) lv_obj_add_state(objects.mode_selector, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.mode_selector, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 1, 3, "Failed to evaluate Selected in Dropdown widget");
        int32_t cur_val = lv_dropdown_get_selected(objects.mode_selector);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.mode_selector;
            lv_dropdown_set_selected(objects.mode_selector, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 0, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.on_off_button, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button;
            if (new_val) lv_obj_add_state(objects.on_off_button, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.on_off_button, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 0, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.on_off_button, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button;
            if (new_val) lv_obj_add_state(objects.on_off_button, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.on_off_button, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj1;
            lv_label_set_text(objects.obj1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj2;
            lv_label_set_text(objects.obj2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj3);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj3;
            lv_label_set_text(objects.obj3, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 6, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj4);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj4;
            lv_label_set_text(objects.obj4, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj5);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj5;
            lv_label_set_text(objects.obj5, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 10, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj6, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj6;
            if (new_val) lv_obj_add_flag(objects.obj6, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj6, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 13, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj8);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj8;
            lv_label_set_text(objects.obj8, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 14, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah;
            lv_label_set_text(objects.ah, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 15, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wh);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wh;
            lv_label_set_text(objects.wh, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.montime);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.montime;
            lv_label_set_text(objects.montime, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj10);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj10;
            lv_label_set_text(objects.obj10, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 21, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.isetlabel);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.isetlabel;
            lv_label_set_text(objects.isetlabel, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 2, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.set_value_area);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.set_value_area;
            lv_textarea_set_text(objects.set_value_area, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 23, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj11);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj11;
            lv_label_set_text(objects.obj11, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 27, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj12, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj12;
            if (new_val) lv_obj_add_state(objects.obj12, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj12, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 28, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj13);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj13;
            lv_label_set_text(objects.obj13, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 30, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj15);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj15;
            lv_label_set_text(objects.obj15, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 32, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj16, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj16;
            if (new_val) lv_obj_add_state(objects.obj16, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj16, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 33, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj17);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj17;
            lv_label_set_text(objects.obj17, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 34, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj18);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj18;
            lv_label_set_text(objects.obj18, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 37, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.wheel;
            if (new_val) lv_obj_add_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 46, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj20);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj20;
            lv_label_set_text(objects.obj20, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 62, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj21, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj21;
            if (new_val) lv_obj_add_flag(objects.obj21, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj21, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 62), 31);
}

void create_screen_settings() {
    void *flowState = getFlowState(0, 2);
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
            objects.obj24 = obj;
            lv_obj_set_pos(obj, 210, 190);
            lv_obj_set_size(obj, 100, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj24, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj25 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj26 = obj;
            lv_obj_set_pos(obj, 10, 190);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj26, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj27 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj28 = obj;
            lv_obj_set_pos(obj, 10, 96);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj28, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj29 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj30 = obj;
            lv_obj_set_pos(obj, 1, 0);
            lv_obj_set_size(obj, 320, 25);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff5060a0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj31 = obj;
            lv_obj_set_pos(obj, 10, 142);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj31, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj32 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj33 = obj;
            lv_obj_set_pos(obj, 10, 50);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj33, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj34 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_settings() {
    void *flowState = getFlowState(0, 2);
    {
        const char *new_val = evalTextProperty(flowState, 0, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj25);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj25;
            lv_label_set_text(objects.obj25, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj27);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj27;
            lv_label_set_text(objects.obj27, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj29);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj29;
            lv_label_set_text(objects.obj29, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 9, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj30);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj30;
            lv_label_set_text(objects.obj30, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj32);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj32;
            lv_label_set_text(objects.obj32, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 13, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj34);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj34;
            lv_label_set_text(objects.obj34, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_events() {
    void *flowState = getFlowState(0, 3);
    lv_obj_t *obj = lv_obj_create(0);
    objects.events = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj35 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 25);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj36 = obj;
            lv_obj_set_pos(obj, 225, 200);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_events_obj36, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj37 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.obj38 = obj;
            lv_obj_set_pos(obj, 3, 26);
            lv_obj_set_size(obj, 314, 161);
            lv_textarea_set_max_length(obj, 500);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_events_obj38, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_events() {
    void *flowState = getFlowState(0, 3);
    {
        const char *new_val = evalTextProperty(flowState, 1, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj35);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj35;
            lv_label_set_text(objects.obj35, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj37);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj37;
            lv_label_set_text(objects.obj37, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 2, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.obj38);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj38;
            lv_textarea_set_text(objects.obj38, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_protections() {
    void *flowState = getFlowState(0, 4);
    lv_obj_t *obj = lv_obj_create(0);
    objects.protections = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj39 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 26);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj40 = obj;
            lv_obj_set_pos(obj, 212, 200);
            lv_obj_set_size(obj, 90, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj40, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj41 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 90, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 36);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Current (OCP):");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 76);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Voltage (OVP):");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 22, 120);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Power (OPP):");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 22, 150);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Temperature: \n(OTP)  ");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj42 = obj;
            lv_obj_set_pos(obj, 160, 32);
            lv_obj_set_size(obj, 142, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj42, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj43 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 142, 30);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj44 = obj;
            lv_obj_set_pos(obj, 160, 73);
            lv_obj_set_size(obj, 142, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj44, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj45 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 142, 30);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj46 = obj;
            lv_obj_set_pos(obj, 160, 117);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj46, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj47 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 65, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj48 = obj;
            lv_obj_set_pos(obj, 237, 117);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj48, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj49 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 65, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj50 = obj;
            lv_obj_set_pos(obj, 22, 200);
            lv_obj_set_size(obj, 164, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj50, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 164, 22);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Clear protection");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj51 = obj;
            lv_obj_set_pos(obj, 160, 156);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj51, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj52 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 65, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj53 = obj;
            lv_obj_set_pos(obj, 237, 156);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj53, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj54 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 65, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj55 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_style_value_t value;
            value.num = 0;
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_LEFT, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_TOP, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_RIGHT, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_LEFT, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_BG_OPA, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_BORDER_WIDTH, value, LV_PART_MAIN);
            create_user_widget_keyboard(obj, getFlowState(flowState, 28), 69);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
    }
}

void tick_screen_protections() {
    void *flowState = getFlowState(0, 4);
    {
        const char *new_val = evalTextProperty(flowState, 1, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj39);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj39;
            lv_label_set_text(objects.obj39, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj41);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj41;
            lv_label_set_text(objects.obj41, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 8, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj42, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj42;
            if (new_val) lv_obj_add_state(objects.obj42, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj42, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 9, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj43);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj43;
            lv_label_set_text(objects.obj43, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 10, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj44, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj44;
            if (new_val) lv_obj_add_state(objects.obj44, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj44, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj45);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj45;
            lv_label_set_text(objects.obj45, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 18, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj46, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj46;
            if (new_val) lv_obj_add_state(objects.obj46, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj46, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj47);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj47;
            lv_label_set_text(objects.obj47, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj48, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj48;
            if (new_val) lv_obj_add_state(objects.obj48, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj48, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 21, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj49);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj49;
            lv_label_set_text(objects.obj49, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 22, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj50, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj50;
            if (new_val) lv_obj_add_state(objects.obj50, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj50, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 24, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj51, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj51;
            if (new_val) lv_obj_add_state(objects.obj51, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj51, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 25, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj52);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj52;
            lv_label_set_text(objects.obj52, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 26, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj53, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj53;
            if (new_val) lv_obj_add_state(objects.obj53, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj53, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 27, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj54);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj54;
            lv_label_set_text(objects.obj54, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 28, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj55, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj55;
            if (new_val) lv_obj_add_flag(objects.obj55, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj55, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 28), 69);
}

void create_screen_calibration() {
    void *flowState = getFlowState(0, 5);
    lv_obj_t *obj = lv_obj_create(0);
    objects.calibration = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj56 = obj;
            lv_obj_set_pos(obj, 0, 1);
            lv_obj_set_size(obj, 320, 27);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.obj57 = obj;
            lv_obj_set_pos(obj, 0, 28);
            lv_obj_set_size(obj, 320, LV_SIZE_CONTENT);
            lv_dropdown_set_options(obj, "Current Monitor\nVoltage Monitor\nCurrent Set\nVon Set\nVoltage Set\nOCP set\nOVP set");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj57, LV_EVENT_ALL, flowState);
            apply_style_selector_small(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 26, 102);
            lv_obj_set_size(obj, 82, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Set:");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj58 = obj;
            lv_obj_set_pos(obj, 166, 98);
            lv_obj_set_size(obj, 97, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj58, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    objects.obj59 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 79, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 140);
            lv_obj_set_size(obj, 109, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Measured:");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj60 = obj;
            lv_obj_set_pos(obj, 0, 70);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_label_set_text(obj, "");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj61 = obj;
            lv_obj_set_pos(obj, 160, 172);
            lv_obj_set_size(obj, 109, 25);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj62 = obj;
            lv_obj_set_pos(obj, 10, 206);
            lv_obj_set_size(obj, 90, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj62, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 90, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Recal");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj63 = obj;
            lv_obj_set_pos(obj, 198, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj63, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj64 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 45, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj64, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj65 = obj;
            lv_obj_set_pos(obj, 126, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj65, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj66 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 45, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj67 = obj;
            lv_obj_set_pos(obj, 269, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj67, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj68 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 45, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj68, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj69 = obj;
            lv_obj_set_pos(obj, 151, 140);
            lv_obj_set_size(obj, 127, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 172);
            lv_obj_set_size(obj, 109, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Point:");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj70 = obj;
            lv_obj_set_pos(obj, 136, 173);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj70, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            apply_style_small_label_symbol(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj71 = obj;
            lv_obj_set_pos(obj, 268, 172);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj71, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            apply_style_small_label_symbol(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj72 = obj;
            lv_obj_set_pos(obj, 278, 140);
            lv_obj_set_size(obj, 25, 25);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj72, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            apply_style_small_label_symbol(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_pivot_x(obj, 11, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_pivot_y(obj, 11, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj73 = obj;
            lv_obj_set_pos(obj, 114, 140);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj73, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            apply_style_small_label_symbol(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj74 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_style_value_t value;
            value.num = 0;
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_LEFT, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_TOP, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_RIGHT, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_LEFT, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_BG_OPA, value, LV_PART_MAIN);
            lv_obj_set_local_style_prop(obj, LV_STYLE_BORDER_WIDTH, value, LV_PART_MAIN);
            create_user_widget_keyboard(obj, getFlowState(flowState, 30), 93);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
    }
}

void tick_screen_calibration() {
    void *flowState = getFlowState(0, 5);
    {
        const char *new_val = evalTextProperty(flowState, 1, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj56);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj56;
            lv_label_set_text(objects.obj56, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 0, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj57, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj57;
            if (new_val) lv_obj_add_state(objects.obj57, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj57, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 0, 3, "Failed to evaluate Selected in Dropdown widget");
        int32_t cur_val = lv_dropdown_get_selected(objects.obj57);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj57;
            lv_dropdown_set_selected(objects.obj57, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj59);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj59;
            lv_label_set_text(objects.obj59, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj60);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj60;
            lv_label_set_text(objects.obj60, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 8, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj61);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj61;
            lv_label_set_text(objects.obj61, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 11, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj63, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj63;
            if (new_val) lv_obj_add_state(objects.obj63, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj63, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 12, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj64, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj64;
            if (new_val) lv_obj_add_state(objects.obj64, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj64, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj64);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj64;
            lv_label_set_text(objects.obj64, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 13, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj65, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj65;
            if (new_val) lv_obj_add_state(objects.obj65, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj65, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 14, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj66);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj66;
            lv_label_set_text(objects.obj66, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 15, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj67, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj67;
            if (new_val) lv_obj_add_state(objects.obj67, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj67, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 16, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj68, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj68;
            if (new_val) lv_obj_add_state(objects.obj68, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj68, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj68);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj68;
            lv_label_set_text(objects.obj68, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj69);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj69;
            lv_label_set_text(objects.obj69, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 19, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj70, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj70;
            if (new_val) lv_obj_add_state(objects.obj70, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj70, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj70);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj70;
            lv_label_set_text(objects.obj70, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj71, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj71;
            if (new_val) lv_obj_add_state(objects.obj71, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj71, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj71);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj71;
            lv_label_set_text(objects.obj71, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 28, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj72);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj72;
            lv_label_set_text(objects.obj72, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 29, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj73, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj73;
            if (new_val) lv_obj_add_flag(objects.obj73, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj73, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 29, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj73);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj73;
            lv_label_set_text(objects.obj73, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 30, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj74, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj74;
            if (new_val) lv_obj_add_flag(objects.obj74, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj74, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 30), 93);
    {
        float timeline_position = getTimelinePosition(flowState);
        
        static struct {
            float last_timeline_position;
            int32_t obj_obj72_rotate_init_value;
        } anim_state = { -1 };
        
        if (anim_state.last_timeline_position == -1) {
            anim_state.last_timeline_position = 0;
            anim_state.obj_obj72_rotate_init_value = lv_obj_get_style_prop(objects.obj72, LV_PART_MAIN, LV_STYLE_TRANSFORM_ANGLE).num;
        }
        
        if (timeline_position != anim_state.last_timeline_position) {
            anim_state.last_timeline_position = timeline_position;
            
            {
                lv_obj_t *obj = objects.obj72;
                
                float rotate_value = anim_state.obj_obj72_rotate_init_value;
                
                while (1) {
                    // keyframe #1
                    if (timeline_position < 0) {
                        break;
                    }
                    if (timeline_position >= 0 && timeline_position < 1) {
                        float t = (timeline_position - 0) / 1;
                        // rotate
                        rotate_value += eez_linear(t) * (3600 - rotate_value);
                        break;
                    }
                    rotate_value = 3600;
                    
                    break;
                }
                
                lv_style_value_t value;
                
                value.num = (int32_t)roundf(rotate_value);
                lv_obj_set_local_style_prop(obj, LV_STYLE_TRANSFORM_ANGLE, value, LV_PART_MAIN);
            }
        }
        }
    }
    
    void create_screen_nlpc() {
        void *flowState = getFlowState(0, 6);
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
                lv_obj_set_pos(obj, 1, 34);
                lv_obj_set_size(obj, 94, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "PL Freq:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                // NLPC_HOME
                lv_obj_t *obj = lv_btn_create(parent_obj);
                objects.nlp_c_home = obj;
                lv_obj_set_pos(obj, 225, 190);
                lv_obj_set_size(obj, 90, 38);
                lv_obj_add_event_cb(obj, event_handler_cb_nlpc_nlp_c_home, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj75 = obj;
                        lv_obj_set_pos(obj, 0, 0);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj76 = obj;
                lv_obj_set_pos(obj, 108, 156);
                lv_obj_set_size(obj, 212, 24);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 24);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Measurement Averaging");
                apply_style_small_header(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj77 = obj;
                lv_obj_set_pos(obj, 101, 73);
                lv_obj_set_size(obj, 219, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                // NLPC_HOME_CANCEL
                lv_obj_t *obj = lv_btn_create(parent_obj);
                objects.nlp_c_hom_e_cancel = obj;
                lv_obj_set_pos(obj, 115, 191);
                lv_obj_set_size(obj, 90, 38);
                lv_obj_add_event_cb(obj, event_handler_cb_nlpc_nlp_c_hom_e_cancel, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj78 = obj;
                        lv_obj_set_pos(obj, 0, 0);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                // NLPC_HOME_CANCEL_1
                lv_obj_t *obj = lv_btn_create(parent_obj);
                objects.nlp_c_hom_e_cance_l_1 = obj;
                lv_obj_set_pos(obj, 8, 191);
                lv_obj_set_size(obj, 90, 38);
                lv_obj_add_event_cb(obj, event_handler_cb_nlpc_nlp_c_hom_e_cance_l_1, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj79 = obj;
                        lv_obj_set_pos(obj, 3, -1);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_slider_create(parent_obj);
                objects.obj80 = obj;
                lv_obj_set_pos(obj, 141, 117);
                lv_obj_set_size(obj, 166, 10);
                lv_slider_set_range(obj, 1, 100);
                lv_obj_add_event_cb(obj, event_handler_cb_nlpc_obj80, LV_EVENT_ALL, flowState);
                apply_style_slider(obj);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                lv_obj_set_pos(obj, 1, 73);
                lv_obj_set_size(obj, 94, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "ADC:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                lv_obj_set_pos(obj, 1, 110);
                lv_obj_set_size(obj, 94, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "NPLC:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                lv_obj_set_pos(obj, 1, 156);
                lv_obj_set_size(obj, 94, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Samples:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_dropdown_create(parent_obj);
                objects.obj81 = obj;
                lv_obj_set_pos(obj, 101, 28);
                lv_obj_set_size(obj, 80, 36);
                lv_dropdown_set_options(obj, "50 Hz\n60 Hz");
                lv_obj_add_event_cb(obj, event_handler_cb_nlpc_obj81, LV_EVENT_ALL, flowState);
                apply_style_selector_small(obj);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj82 = obj;
                lv_obj_set_pos(obj, 101, 110);
                lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "");
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE);
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_obj_create(parent_obj);
                objects.obj83 = obj;
                lv_obj_set_pos(obj, 0, 2);
                lv_obj_set_size(obj, 320, 240);
                lv_style_value_t value;
                value.num = 0;
                lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_LEFT, value, LV_PART_MAIN);
                lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_TOP, value, LV_PART_MAIN);
                lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_RIGHT, value, LV_PART_MAIN);
                lv_obj_set_local_style_prop(obj, LV_STYLE_PAD_LEFT, value, LV_PART_MAIN);
                lv_obj_set_local_style_prop(obj, LV_STYLE_BG_OPA, value, LV_PART_MAIN);
                lv_obj_set_local_style_prop(obj, LV_STYLE_BORDER_WIDTH, value, LV_PART_MAIN);
                create_user_widget_question_yn(obj, getFlowState(flowState, 25), 106);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            }
        }
    }
    
    void tick_screen_nlpc() {
        void *flowState = getFlowState(0, 6);
        {
            const char *new_val = evalTextProperty(flowState, 6, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj75);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj75;
                lv_label_set_text(objects.obj75, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 8, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj76);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj76;
                lv_label_set_text(objects.obj76, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 10, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj77);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj77;
                lv_label_set_text(objects.obj77, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 11, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.nlp_c_hom_e_cancel, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.nlp_c_hom_e_cancel;
                if (new_val) lv_obj_add_flag(objects.nlp_c_hom_e_cancel, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.nlp_c_hom_e_cancel, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 12, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj78);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj78;
                lv_label_set_text(objects.obj78, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 13, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.nlp_c_hom_e_cance_l_1, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.nlp_c_hom_e_cance_l_1;
                if (new_val) lv_obj_add_flag(objects.nlp_c_hom_e_cance_l_1, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.nlp_c_hom_e_cance_l_1, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 14, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj79);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj79;
                lv_label_set_text(objects.obj79, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            int32_t new_val = evalIntegerProperty(flowState, 15, 2, "Failed to evaluate Value in Slider widget");
            int32_t cur_val = lv_slider_get_value(objects.obj80);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj80;
                lv_slider_set_value(objects.obj80, new_val, LV_ANIM_OFF);
                tick_value_change_obj = NULL;
            }
        }
        {
            int32_t new_val = evalIntegerProperty(flowState, 19, 2, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj81);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj81;
                lv_dropdown_set_selected(objects.obj81, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 20, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj82);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj82;
                lv_label_set_text(objects.obj82, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 25, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj83, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj83;
                if (new_val) lv_obj_add_flag(objects.obj83, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj83, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        tick_user_widget_question_yn(getFlowState(flowState, 25), 106);
    }
    
    void create_user_widget_question_yn(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
        lv_obj_t *obj = parent_obj;
        {
            lv_obj_t *parent_obj = obj;
            {
                lv_obj_t *obj = lv_obj_create(parent_obj);
                lv_obj_set_pos(obj, 31, 28);
                lv_obj_set_size(obj, 260, 180);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_warning(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_btn_create(parent_obj);
                        ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                        lv_obj_set_pos(obj, 0, 115);
                        lv_obj_set_size(obj, 100, 32);
                        lv_obj_add_event_cb(obj, event_handler_cb_question_yn_obj84, LV_EVENT_ALL, flowState);
                        lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                        lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                        apply_style_button(obj);
                        {
                            lv_obj_t *parent_obj = obj;
                            {
                                lv_obj_t *obj = lv_label_create(parent_obj);
                                lv_obj_set_pos(obj, -4, -4);
                                lv_obj_set_size(obj, 100, 32);
                                lv_label_set_text(obj, "Yes");
                                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            }
                        }
                    }
                    {
                        lv_obj_t *obj = lv_btn_create(parent_obj);
                        ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                        lv_obj_set_pos(obj, 130, 115);
                        lv_obj_set_size(obj, 100, 32);
                        lv_obj_add_event_cb(obj, event_handler_cb_question_yn_obj85, LV_EVENT_ALL, flowState);
                        lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                        lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                        apply_style_button(obj);
                        {
                            lv_obj_t *parent_obj = obj;
                            {
                                lv_obj_t *obj = lv_label_create(parent_obj);
                                lv_obj_set_pos(obj, -4, -4);
                                lv_obj_set_size(obj, 100, 32);
                                lv_label_set_text(obj, "No");
                                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            }
                        }
                    }
                }
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                lv_obj_set_pos(obj, 90, 120);
                lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                lv_label_set_text(obj, "Are you sure?");
                apply_style_small_label(obj);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                lv_obj_set_pos(obj, 47, 43);
                lv_obj_set_size(obj, 230, 64);
                lv_label_set_text(obj, "");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }
    
    void tick_user_widget_question_yn(void *flowState, int startWidgetIndex) {
        {
            const char *new_val = evalTextProperty(flowState, 9, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 2]);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 2];
                lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 2], new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    
    void create_user_widget_keyboard_old(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
        lv_obj_t *obj = parent_obj;
        {
            lv_obj_t *parent_obj = obj;
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                lv_obj_set_pos(obj, 1, 1);
                lv_obj_set_size(obj, 320, 25);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
                lv_label_set_text(obj, "");
                apply_style_small_header(obj);
            }
            {
                // KBtext
                lv_obj_t *obj = lv_textarea_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                lv_obj_set_pos(obj, 0, 34);
                lv_obj_set_size(obj, 260, 36);
                lv_textarea_set_max_length(obj, 128);
                lv_textarea_set_one_line(obj, true);
                lv_textarea_set_password_mode(obj, false);
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_old_kbtext, LV_EVENT_ALL, flowState);
            }
            {
                lv_obj_t *obj = lv_keyboard_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                lv_obj_set_pos(obj, 0, 70);
                lv_obj_set_size(obj, 320, 170);
                lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_color(obj, lv_color_hex(0xff222222), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
    }
    
    void tick_user_widget_keyboard_old(void *flowState, int startWidgetIndex) {
        {
            const char *new_val = evalTextProperty(flowState, 1, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 1]);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 1];
                lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 1], new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 0, 2, "Failed to evaluate Text in Textarea widget");
            const char *cur_val = lv_textarea_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 0]);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 0];
                lv_textarea_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 0], new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    
    void create_user_widget_keyboard(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
        lv_obj_t *obj = parent_obj;
        {
            lv_obj_t *parent_obj = obj;
            {
                lv_obj_t *obj = lv_obj_create(parent_obj);
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 240);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 25);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
                lv_label_set_text(obj, "");
                apply_style_small_header(obj);
            }
            {
                // kbtext2
                lv_obj_t *obj = lv_textarea_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                lv_obj_set_pos(obj, 0, 25);
                lv_obj_set_size(obj, 280, 50);
                lv_textarea_set_max_length(obj, 128);
                lv_textarea_set_one_line(obj, true);
                lv_textarea_set_password_mode(obj, false);
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_kbtext2, LV_EVENT_ALL, flowState);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_DEFAULT);
                lv_obj_set_style_border_opa(obj, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_keyboard_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                lv_obj_set_pos(obj, 0, 70);
                lv_obj_set_size(obj, 320, 170);
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_obj23, LV_EVENT_ALL, flowState);
                lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
        }
        lv_keyboard_set_textarea(((lv_obj_t **)&objects)[startWidgetIndex + 2], ((lv_obj_t **)&objects)[startWidgetIndex + 0]);
    }
    
    void tick_user_widget_keyboard(void *flowState, int startWidgetIndex) {
        {
            const char *new_val = evalTextProperty(flowState, 0, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 1]);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 1];
                lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 1], new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 2, 2, "Failed to evaluate Text in Textarea widget");
            const char *cur_val = lv_textarea_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 0]);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 0];
                lv_textarea_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 0], new_val);
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
    create_screen_settings();
    create_screen_events();
    create_screen_protections();
    create_screen_calibration();
    create_screen_nlpc();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_startup,
    tick_screen_main,
    tick_screen_settings,
    tick_screen_events,
    tick_screen_protections,
    tick_screen_calibration,
    tick_screen_nlpc,
    0,
    0,
    0,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}


size_t get_num_screens() {
    return sizeof(tick_screen_funcs) / sizeof(tick_screen_func_t);
}

lv_obj_t *get_screen_obj(size_t screen_index) {
    return ((lv_obj_t **)(&objects))[screen_index];
}

