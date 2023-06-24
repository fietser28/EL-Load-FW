#include "lvgl.h"
#include "main.h"
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

extern "C" {

void action_clear_power(lv_event_t * e) {
    state.clearPower();
}

void action_toggle_record(lv_event_t * e) {
    state.toggleRecord();  

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
        cal_values.points[cal_curpoint].adc = (int32_t)cal_measured;
    }
    if (cal_calType == 1) {
        cal_measured = localstatecopy.avgVoltRaw;
        cal_values.points[cal_curpoint].adc = (int32_t)cal_measured;
    }
    if (cal_calType == 2) { // Iset
        cal_measured = localstatecopy.Imon;
        cal_values.points[cal_curpoint].value = cal_measured;
    }
    if (cal_calType == 3) { // VonSet, after do_search action.
        cal_measured = localstatecopy.Umon;
        cal_values.points[cal_curpoint].value = cal_measured;
        cal_values.points[cal_curpoint].dac = (int32_t)cal_set;
    }
    if (cal_calType == 4) { // Uset
        cal_measured = localstatecopy.Umon;
        cal_values.points[cal_curpoint].value = cal_measured;
    }
    //TODO: Add others. 

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
    write_cal_to_eeprom(cal_calType);
}

void action_cal_set_dac(lv_event_t *e) 
{
    if (cal_calType == 2) { // Iset
        state.setIset(cal_set, true);
    }
    
    if (cal_calType == 3) { // VonSet
        state.setVonset(cal_set, true);
    }

    if (cal_calType == 4) { // Uset
        state.setUset(cal_set, true);
    }
}

} // extern "C"