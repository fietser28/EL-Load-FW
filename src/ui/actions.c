#include "lvgl.h"
#include "actions.h"
#include "vars.h"
#include "ui_glue.h"


void action_getrollerindex(lv_event_t * e) {
    lv_obj_t *roller = lv_event_get_target(e);
    uint16_t myindex = lv_roller_get_selected(roller);
    //set_var_roller1index(myindex);
}

void action_getdropdownindex(lv_event_t * e) {
    lv_obj_t *dropdown = lv_event_get_target(e);
    uint16_t myindex = lv_dropdown_get_selected(dropdown);
    //set_var_dropdownmodeindex(myindex);
}

void action_clear_power(lv_event_t * e) {
    clearPower();
}

void action_toggle_record(lv_event_t * e) {
    toggleRecord();
}

void action_text_area_disable_blink(lv_event_t * e) {
    lv_obj_t *textarea = lv_event_get_target(e);
    if (lv_obj_check_type(textarea, &lv_textarea_class)) {
        lv_obj_set_style_anim_time(textarea, 0, LV_PART_CURSOR | LV_STATE_FOCUSED);
        lv_obj_refresh_style(textarea, LV_PART_CURSOR, LV_STYLE_PROP_ANY);
    }
};


void action_grab_encoder(lv_event_t * e) {
    lv_group_remove_all_objs(encoder_group);
    lv_obj_t *obj = lv_event_get_target(e);
    if (obj->class_p == &lv_btn_class || obj->class_p == &lv_keyboard_class || obj->class_p == &lv_textarea_class) {
        lv_group_add_obj(encoder_group, obj);
        lv_group_focus_obj(obj);
    }
}

// Calibration page

void action_cal_refresh_measured(lv_event_t *e) 
{
    if (cal_calType == 0) {
        cal_measured = localstatecopy.avgCurrentRaw;
    }
    if (cal_calType == 1) {
        cal_measured = localstatecopy.avgVoltRaw;
    }
    //TODO: Add others. 

    cal_values.points[cal_curpoint].adc = cal_measured;
}

void action_cal_reset_values(lv_event_t *e)
{
    copy_cal_values_from_state(&cal_values, cal_calType);
    if (cal_curpoint > cal_values.numPoints -1) {
        set_var_cal_curpoint(0);
    } else {
        set_var_cal_curpoint(cal_curpoint);
    }
}

void action_cal_store_values(lv_event_t *e)
{
    copy_cal_values_to_state(&cal_values, cal_calType);
}
