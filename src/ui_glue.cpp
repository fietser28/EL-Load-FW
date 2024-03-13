// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <lvgl.h>
#include "state.h"
#include "main.h"
#include "ui/vars.h"
#include "ui/structs.h"

#include "ui/screens.h"

extern "C" {

dcl::measuredStateStruct localstatecopy;
dcl::setStateStruct localsetcopy;

const u_int16_t logsize = 512;
char logtxt[logsize];
uint16_t logpointer = 0;

} // extern "C"

void printlogval(int val1, int val2, int val3, int val4) {
    snprintf(logtxt, 60, "pin1: %d\npin2: %d\nenccount:  %d\ngpio:  %d", val1, val2, val3, val4);
}

void printlogstr(const char* txt) {
    uint16_t written = snprintf(logtxt + logpointer, logsize - 1 - logpointer, "%s\n", txt);
    if (written > 0 && written < logsize - 1 - logpointer) {
        logpointer = logpointer + written;
    } else if (written > logsize - logpointer) {
        logpointer = logsize - 1;
    } 
}

void clearlog() {
    logpointer = 0;
    logtxt[0] = '\x00';
}

///// Encoder / key functions.
///// Waiting for studio/EEZ flow support for this.

lv_group_t *encoder_group;
lv_group_t *onoff_group;

static lv_obj_tree_walk_res_t walk_cb(lv_obj_t *obj, void *) {
    // TODO: Make more generic, currently all textarea's are encoder selectable...
    if (obj->class_p == &lv_textarea_class || obj->class_p == &lv_slider_class) {
        lv_group_add_obj(encoder_group, obj);
        if (lv_group_get_focused(encoder_group) == 0) {
            lv_group_focus_obj(obj);
        }
    }
    return LV_OBJ_TREE_WALK_NEXT;
}

static lv_obj_tree_walk_res_t walk_cb_on_off(lv_obj_t *obj, void *) {
    // TODO: Make more generic, hardcoded name
    if (obj == objects.on_of_f_button) {
        lv_group_add_obj(onoff_group, obj);
        if (lv_group_get_focused(onoff_group) == 0) {
            lv_group_focus_obj(obj);
        }
    }
    return LV_OBJ_TREE_WALK_NEXT;
}

static void update_groups(lv_obj_t *obj) {
    lv_group_remove_all_objs(encoder_group);
    lv_obj_tree_walk(obj, walk_cb, 0);

    lv_group_remove_all_objs(onoff_group);
    lv_obj_tree_walk(obj, walk_cb_on_off, 0);
}

static void on_screen_loaded_cb(lv_obj_t *screen_obj) {
    update_groups(screen_obj);
    lv_group_set_editing(encoder_group, true);
    lv_group_set_editing(onoff_group, true);
}

static void on_screen_loaded_cb(lv_event_t *e) {
    on_screen_loaded_cb(e->target);
}

static void on_screen_unload_cb(lv_event_t *e) 
{
    lv_group_remove_all_objs(encoder_group);
    lv_group_remove_all_objs(onoff_group);
}

//static void on_encoder_apply(lv_event_t *e) {
//    lv_group_focus_next(encoder_group);
//}

void ui_init_encoder_group() {
    encoder_group = lv_group_create();
    onoff_group = lv_group_create();
    lv_group_set_default(encoder_group);

    for (size_t screen_index = 0; screen_index < get_num_screens(); screen_index++) 
    {
        lv_obj_add_event_cb(get_screen_obj(screen_index), on_screen_loaded_cb, LV_EVENT_SCREEN_LOADED, 0);
        lv_obj_add_event_cb(get_screen_obj(screen_index), on_screen_unload_cb, LV_EVENT_SCREEN_UNLOAD_START, 0);
    }

    on_screen_loaded_cb(get_screen_obj(0));
}

// Calibration glue
void copy_cal_values_from_state(CalibrationValueConfiguration *cal_values, calType_e caltype)
{
    CalibrationValueConfiguration calconfig = state.cal.Imon->getCalConfig();
    switch (caltype)
    {
    case calType_e::calType_e_Imon_High:
        calconfig = state.cal.Imon->getCalConfig();
        break;
    case calType_e::calType_e_Imon_Low:
        calconfig = state.cal.ImonLow->getCalConfig();
        break;
    case calType_e::calType_e_Umon_High:
        calconfig = state.cal.Umon->getCalConfig();
        break;
    case calType_e::calType_e_Umon_Low:
        calconfig = state.cal.UmonLow->getCalConfig();
        break;
    case calType_e::calType_e_Iset_High:
        calconfig = state.cal.Iset->getCalConfig();
        break;        
    case calType_e::calType_e_Iset_Low:
        calconfig = state.cal.IsetLow->getCalConfig();
        break;        
    case calType_e::calType_e_Von_High:
        calconfig = state.cal.Von->getCalConfig();
        break;
    case calType_e::calType_e_Von_Low:
        calconfig = state.cal.VonLow->getCalConfig();
        break;
    case calType_e::calType_e_Uset_High:
        calconfig = state.cal.Uset->getCalConfig();
        break;
    case calType_e::calType_e_Uset_Low:
        calconfig = state.cal.Uset->getCalConfig();
        break;
    case calType_e::calType_e_OCPset_High:
        calconfig = state.cal.OCPset->getCalConfig();
        break;
    case calType_e::calType_e_OCPset_Low:
        calconfig = state.cal.OCPsetLow->getCalConfig();
        break;
    case calType_e::calType_e_OVPset_High:
        calconfig = state.cal.OVPset->getCalConfig();
        break;
    case calType_e::calType_e_OVPset_Low:
        calconfig = state.cal.OVPsetLow->getCalConfig();
        break;
    default:
        // Should not happen. Avoid uncontrolled memcpy
        // TODO: Add some kind of assert.
        return;
    }
    memcpy(cal_values, &calconfig, sizeof(CalibrationValueConfiguration));
};

void copy_cal_values_to_state(CalibrationValueConfiguration *cal_values, calType_e caltype)
{
    CalibrationValueConfiguration *calconfig = state.cal.Imon->getCalConfigRef();
    switch (caltype)
    {
    case calType_e::calType_e_Imon_High:
        calconfig = state.cal.Imon->getCalConfigRef();
        break;
    case calType_e::calType_e_Imon_Low:
        calconfig = state.cal.ImonLow->getCalConfigRef();
        break;
    case calType_e::calType_e_Umon_High:
        calconfig = state.cal.Umon->getCalConfigRef();
        break;
    case calType_e::calType_e_Umon_Low:
        calconfig = state.cal.UmonLow->getCalConfigRef();
        break;
    case calType_e::calType_e_Iset_High:
        calconfig = state.cal.Iset->getCalConfigRef();
        break;
    case calType_e::calType_e_Iset_Low:
        calconfig = state.cal.IsetLow->getCalConfigRef();
        break;
    case calType_e::calType_e_Von_High:
        calconfig = state.cal.Von->getCalConfigRef(); 
        break;
    case calType_e::calType_e_Von_Low:
        calconfig = state.cal.VonLow->getCalConfigRef(); 
        break;
    case calType_e::calType_e_Uset_High:
        calconfig = state.cal.Uset->getCalConfigRef();
        break;
    case calType_e::calType_e_Uset_Low:
        calconfig = state.cal.UsetLow->getCalConfigRef();
        break;
    case calType_e::calType_e_OCPset_High:
        calconfig = state.cal.OCPset->getCalConfigRef();
        break;
    case calType_e::calType_e_OCPset_Low:
        calconfig = state.cal.OCPsetLow->getCalConfigRef();
        break;
    case calType_e::calType_e_OVPset_High:
        calconfig = state.cal.OVPset->getCalConfigRef();
        break;
    case calType_e::calType_e_OVPset_Low:
        calconfig = state.cal.OVPsetLow->getCalConfigRef();
        break;
    default:
        // Should not happen. Avoid uncontrolled memcpy
        // TODO: Add some kind of assert.
        return;
    }
    memcpy(calconfig, cal_values, sizeof(CalibrationValueConfiguration));
}

void write_cal_to_eeprom(calType_e caltype)
{
    CalibrationValueConfiguration *calconfig;  // = state.cal.Imon->getCalConfigRef();
    uint32_t startaddress;
    switch (caltype)
    {
    case calType_e::calType_e_Imon_High:
        calconfig = state.cal.Imon->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_IMON_H;
        break;
    case calType_e::calType_e_Imon_Low:
        calconfig = state.cal.ImonLow->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_IMON_L;
        break;
    case calType_e::calType_e_Umon_High:
        calconfig = state.cal.Umon->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_UMON_H;
        break;
    case calType_e::calType_e_Umon_Low:
        calconfig = state.cal.UmonLow->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_UMON_L;
        break;
    case calType_e::calType_e_Iset_High:
        calconfig = state.cal.Iset->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_ISET_H;
        break;
    case calType_e::calType_e_Iset_Low:
        calconfig = state.cal.IsetLow->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_ISET_L;
        break;
    case calType_e::calType_e_Von_High:
        calconfig = state.cal.Von->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_VON_H;
        break;
    case calType_e::calType_e_Von_Low:
        calconfig = state.cal.VonLow->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_VON_L;
        break;
    case calType_e::calType_e_Uset_High:
        calconfig = state.cal.Uset->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_USET_H;
        break;
    case calType_e::calType_e_Uset_Low:
        calconfig = state.cal.UsetLow->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_USET_L;
        break;
    case calType_e::calType_e_OCPset_High:
        calconfig = state.cal.OCPset->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_OCP_H;
        break;
    case calType_e::calType_e_OCPset_Low:
        calconfig = state.cal.OCPsetLow->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_OCP_L;
        break;
    case calType_e::calType_e_OVPset_High:
        calconfig = state.cal.OVPset->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_OVP_H;
        break;
    case calType_e::calType_e_OVPset_Low:
        calconfig = state.cal.OVPsetLow->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_OVP_L;
        break;
    default:
        startaddress = 0xF00; //Dummy
        // TODO: Add assert of some kind.
        return;
        break;
    }
    myeeprom.calibrationValuesWrite(calconfig, startaddress);
}

