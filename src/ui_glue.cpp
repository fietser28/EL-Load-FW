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

void set_imon_nplc(int32_t value) {
    state.setImonNPLC((uint16_t)value);
}

void set_umon_nplc(int32_t value) {
    state.setUmonNPLC((uint16_t)value);
}

} // extern "C"

void printlogval(int val1, int val2, int val3, int val4) {
    snprintf(logtxt, 60, "pin1: %d\npin2: %d\nenccount:  %d\ngpio:  %d", val1, val2, val3, val4);
}

///// Encoder / key functions.

lv_group_t *encoder_group;
lv_group_t *onoff_group;

static lv_obj_tree_walk_res_t walk_cb(lv_obj_t *obj, void *) {
    // TODO: Make more generic, currently all textarea's are encoder selectable...
    if (obj->class_p == &lv_textarea_class) {
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

static void on_screen_loaded(lv_event_t *e) {
    update_groups(e->target);
    lv_group_set_editing(encoder_group, true);
    lv_group_set_editing(onoff_group, true);
}

static void on_screen_unload(lv_event_t *e) 
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

    lv_obj_add_event_cb(objects.startup, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.startup, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    lv_obj_add_event_cb(objects.main, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.main, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    lv_obj_add_event_cb(objects.set_value, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.set_value, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    lv_obj_add_event_cb(objects.settings, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.settings, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    lv_obj_add_event_cb(objects.settings, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.settings, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

    lv_obj_add_event_cb(objects.nlpc, on_screen_loaded, LV_EVENT_SCREEN_LOADED, 0);
    lv_obj_add_event_cb(objects.nlpc, on_screen_unload, LV_EVENT_SCREEN_UNLOAD_START, 0);

//    lv_obj_add_event_cb(objects.keyboard_1, on_encoder_apply, LV_EVENT_READY, 0);

    update_groups(objects.main);

}
