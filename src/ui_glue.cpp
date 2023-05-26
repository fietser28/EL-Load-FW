#include <lvgl.h>
#include "state.h"
#include "main.h"

#include "ui/screens.h"

extern "C" {

dcl::measuredStateStruct localstatecopy;
dcl::setStateStruct localsetcopy;

}

extern "C" {
bool clearPower() {
    return state.clearPower();
}

bool toggleRecord() {
    return state.toggleRecord();  
}

void setOnOff(bool value)
{
    if (value) {
        state.setOn();
    } else {
        state.setOff();
    }
}

char logtxt[256];

void set_nplc(int32_t value) {
    state.setNPLC((uint32_t)value);
}

int32_t get_adc_osr() {
    return ADC_OSR;
}

} // extern "C"

void printlogval(int val1, int val2, int val3, int val4) {
    snprintf(logtxt, 60, "pin1: %d\npin2: %d\nenccount:  %d\ngpio:  %d", val1, val2, val3, val4);
}

void printlogstr(const char* txt) {
    snprintf(logtxt, 60, "%s\n", txt);
}

///// Encoder / key functions.

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
    if (obj == objects.on_off_button) {
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

/*
    //lv_obj_add_event_cb(objects.startup, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.startup, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    lv_obj_add_event_cb(objects.main, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.main, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    //lv_obj_add_event_cb(objects.set_value, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    //lv_obj_add_event_cb(objects.set_value, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    lv_obj_add_event_cb(objects.settings, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.settings, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    lv_obj_add_event_cb(objects.protections, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.protections, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    lv_obj_add_event_cb(objects.events, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.events, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    lv_obj_add_event_cb(objects.nlpc, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.nlpc, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

//    lv_obj_add_event_cb(objects.keyboard_1, on_encoder_apply, LV_EVENT_READY, 0);
*/

    for (size_t screen_index = 0; screen_index < get_num_screens(); screen_index++) 
    {
        lv_obj_add_event_cb(get_screen_obj(screen_index), on_screen_loaded_cb, LV_EVENT_SCREEN_LOADED, 0);
        lv_obj_add_event_cb(get_screen_obj(screen_index), on_screen_unload_cb, LV_EVENT_SCREEN_UNLOAD_START, 0);
    }

    //update_groups(objects.main);
    //update_groups(get_screen_obj(0)); // First screen is already loaded.

    on_screen_loaded_cb(get_screen_obj(0));
}

// Calibration glue
extern "C" {

void copy_cal_values_from_state(CalibrationValueConfiguration *cal_values, int32_t caltype)
{
    CalibrationValueConfiguration calconfig = state.cal.Imon->getCalConfig();
    switch (caltype)
    {
    case 0:
        calconfig = state.cal.Imon->getCalConfig();
        break;
    case 1:
        calconfig = state.cal.Umon->getCalConfig();
        break;
    case 2:
        calconfig = state.cal.Iset->getCalConfig();
        break;        
    //default:
        //return;
    //    break;
    }
    memcpy(cal_values, &calconfig, sizeof(CalibrationValueConfiguration));
};

void copy_cal_values_to_state(CalibrationValueConfiguration *cal_values, int32_t caltype)
{
    CalibrationValueConfiguration *calconfig = state.cal.Imon->getCalConfigRef();
    switch (caltype)
    {
    case 0:
        calconfig = state.cal.Imon->getCalConfigRef();
        break;
    case 1:
        calconfig = state.cal.Umon->getCalConfigRef();
        break;
    case 2:
        calconfig = state.cal.Iset->getCalConfigRef();
        break;        
    //default:
        //return;
    //    break;
    // TODO: Add others
    }
    memcpy(calconfig, cal_values, sizeof(CalibrationValueConfiguration));
}

void write_cal_to_eeprom(int32_t caltype)
{
    CalibrationValueConfiguration *calconfig = state.cal.Imon->getCalConfigRef();
    uint32_t startaddress;
    switch (caltype)
    {
    case 0:
        calconfig = state.cal.Imon->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_IMON;
        break;
    case 1:
        calconfig = state.cal.Umon->getCalConfigRef();
        startaddress = EEPROM_ADDR_CAL_ISET;
        break;
    //case 2:
    //    calconfig = state.cal.Iset->getCalConfigRef();
    //    break;        
    default:
        return;
        break;
    // TODO: Add others
    }
    myeeprom.calibrationValuesWrite(calconfig, startaddress);
}

}