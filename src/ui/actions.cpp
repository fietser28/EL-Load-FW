// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "lvgl.h"
#include "main.h"
#include "actions.h"
#include "vars.h"
#include "structs.h"
#include "ui_glue.h"
#include "ranges.h"
#include "scpi-def.h"

/*
void action_getrollerindex(lv_event_t * e) {
    lv_obj_t *roller = lv_event_get_target(e);
    uint16_t myindex = lv_roller_get_selected(roller);
    //set_var_roller1index(myindex);
}
*/

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
    if (cal_calType == calType_e::calType_e_Imon_High) {
        cal_measured = localstatecopy.avgCurrentRaw;
        cal_values.points[cal_curpoint].adc = (int32_t)cal_measured;
    }
    if (cal_calType == calType_e::calType_e_Umon_High) {
        cal_measured = localstatecopy.avgVoltRaw;
        cal_values.points[cal_curpoint].adc = (int32_t)cal_measured;
    }
    if (cal_calType == calType_e::calType_e_Iset_High) { // Iset
        cal_measured = localstatecopy.Imon;
        cal_values.points[cal_curpoint].value = cal_measured;
    }
    if (cal_calType == calType_e::calType_e_Von_High) { // VonSet, after do_search action.
        cal_measured = localstatecopy.Umon;
        cal_values.points[cal_curpoint].value = cal_measured;
        cal_values.points[cal_curpoint].dac = (int32_t)cal_set;
    }
    if (cal_calType == calType_e::calType_e_Uset_High) { // Uset
        cal_measured = localstatecopy.Umon;
        cal_values.points[cal_curpoint].value = cal_measured;
    }
    if (cal_calType == calType_e::calType_e_OCPset_High) { // OCPSet, after do_search action.
        cal_measured = localstatecopy.Imon;
        cal_values.points[cal_curpoint].value = cal_measured;
        cal_values.points[cal_curpoint].dac = (int32_t)cal_set;
    }
    if (cal_calType == calType_e::calType_e_OVPset_High) { // VonSet, after do_search action.
        cal_measured = localstatecopy.Umon;
        cal_values.points[cal_curpoint].value = cal_measured;
        cal_values.points[cal_curpoint].dac = (int32_t)cal_set;
    }
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

// Used by SCPI. TODO: rearrange to move to cal.cpp
void action_cal_set_dac(lv_event_t *e) 
{
    if (cal_calType == calType_e_Iset_High || cal_calType == calType_e_Iset_Low) { // Iset
        state.setIset(cal_set, true);
    }
    
    if (cal_calType == calType_e_Von_High || cal_calType == calType_e_Von_Low) { // VonSet
        state.setVonset(cal_set, true);
    }

    if (cal_calType == calType_e_Uset_High || cal_calType == calType_e_Uset_Low) { // Uset
        state.setUset(cal_set, true);
    }

    if (cal_calType == calType_e_OCPset_High || cal_calType == calType_e_OCPset_Low) {
        state.setOCP(cal_set, true);
    }

    if (cal_calType == calType_e_OVPset_High || cal_calType == calType_e_OVPset_Low) {
        state.setOVP(cal_set, true);
    }
}

void action_cal_store_defaults(lv_event_t * e)
{
    if (myeeprom.magicWrite()) {
        printlogstr("INFO: EEPROM magic written.");
        write_cal_to_eeprom(calType_e::calType_e_Imon_High);
        write_cal_to_eeprom(calType_e::calType_e_Imon_Low);
        write_cal_to_eeprom(calType_e::calType_e_Umon_High);
        write_cal_to_eeprom(calType_e::calType_e_Umon_Low);
        write_cal_to_eeprom(calType_e::calType_e_Iset_High);
        write_cal_to_eeprom(calType_e::calType_e_Iset_Low);
        write_cal_to_eeprom(calType_e::calType_e_Uset_High);
        write_cal_to_eeprom(calType_e::calType_e_Uset_Low);
        write_cal_to_eeprom(calType_e::calType_e_Von_High);
        write_cal_to_eeprom(calType_e::calType_e_Von_Low);
        write_cal_to_eeprom(calType_e::calType_e_OCPset_High);
        write_cal_to_eeprom(calType_e::calType_e_OCPset_Low);
        write_cal_to_eeprom(calType_e::calType_e_OVPset_High);
        write_cal_to_eeprom(calType_e::calType_e_OVPset_Low);
        printlogstr("INFO: Default cal values stored.");
    } else {
        printlogstr("ERROR: Unable to write EEPROM magic.");        
    }
}

void action_display_off(lv_event_t * e) {
    digitalWrite(TFT_BL, LOW);
};

void action_display_on(lv_event_t * e) {
      digitalWrite(TFT_BL, HIGH);
};

void action_get_type_data(lv_event_t * e) {

    ranges_e range = (ranges_e)flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_RANGE_TYPE).getInt();
    
    setPropertiesValue properties = flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_RANGE_PROPERTIES);

    properties.setName(ranges[range].setName);
    properties.setUnit(ranges[range].unitName);
    properties.setValueMin(ranges[range].minValue);
    properties.setValueMax(ranges[range].maxValue);
    properties.setValueDefault(ranges[range].defValue);
};

void action_clear_capacity_limits(lv_event_t * e) {
    state.clearCapacityLimit();
};


void action_scpi_busy_incr(lv_event_t * e) { dcl::scpi::scpi_busy_inc(); };
void action_scpi_busy_decr(lv_event_t * e) { dcl::scpi::scpi_busy_dec(); };

} // extern "C"