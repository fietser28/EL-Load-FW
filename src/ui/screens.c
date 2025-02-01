#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

groups_t groups;
static bool groups_created = false;

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_startup_startup(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
        lv_group_add_obj(groups.encoder_group, objects.startup_ok);
    }
}

static void event_handler_cb_startup_startup_ok(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 15, 0, e);
    }
}

static void event_handler_cb_main_main(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
        lv_group_add_obj(groups.encoder_group, objects.myspinbox);
        lv_group_add_obj(groups.encoder_group, objects.mode_selector);
    }
    
    if (event == LV_EVENT_SCREEN_LOADED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 48, 0, e);
    }
}

static void event_handler_cb_main_mode_selector(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 49, 4, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 49, 0, e);
    }
}

static void event_handler_cb_main_on_off_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 50, 4, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 50, 0, e);
    }
}

static void event_handler_cb_main_range_current(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 53, 0, e);
    }
}

static void event_handler_cb_main_obj13(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
}

static void event_handler_cb_main_obj14(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 55, 0, e);
    }
}

static void event_handler_cb_main_range_volt(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 56, 0, e);
    }
}

static void event_handler_cb_main_obj15(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 60, 0, e);
    }
}

static void event_handler_cb_main_obj16(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 62, 0, e);
    }
}

static void event_handler_cb_main_obj17(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 64, 0, e);
    }
}

static void event_handler_cb_main_obj18(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 67, 0, e);
    }
}

static void event_handler_cb_main_wh(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 70, 0, e);
    }
}

static void event_handler_cb_main_obj19(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 72, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 72, 0, e);
    }
}

static void event_handler_cb_main_obj20(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 76, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 76, 0, e);
    }
}

static void event_handler_cb_main_myspinbox(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_spinbox_get_value(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 88, 6, value, "Failed to assign Value in Spinbox widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 88, 0, e);
    }
}

static void event_handler_cb_main_obj21(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 89, 0, e);
    }
}

static void event_handler_cb_main_obj22(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 93, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 93, 0, e);
    }
}

static void event_handler_cb_main_obj23(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 95, 0, e);
    }
}

static void event_handler_cb_main_obj24(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 98, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 98, 0, e);
    }
}

static void event_handler_cb_main_obj25(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 102, 0, e);
    }
}

static void event_handler_cb_main_range_volt_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 105, 0, e);
    }
}

static void event_handler_cb_main_obj26(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 109, 0, e);
    }
}

static void event_handler_cb_main_range_curr_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 112, 0, e);
    }
}

static void event_handler_cb_main_obj27(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 117, 0, e);
    }
}

static void event_handler_cb_capacity_capacity(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
    }
}

static void event_handler_cb_capacity_obj28(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 17, 0, e);
    }
}

static void event_handler_cb_capacity_obj29(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 20, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 20, 0, e);
    }
}

static void event_handler_cb_capacity_obj30(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 22, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 22, 0, e);
    }
}

static void event_handler_cb_capacity_obj31(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 24, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 24, 0, e);
    }
}

static void event_handler_cb_capacity_obj32(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 26, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 26, 0, e);
    }
}

static void event_handler_cb_capacity_on_off_button_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 35, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 35, 0, e);
    }
}

static void event_handler_cb_capacity_obj33(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_toggle_record(e);
    }
}

static void event_handler_cb_capacity_obj34(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 39, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 39, 0, e);
    }
}

static void event_handler_cb_capacity_obj35(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_clear_power(e);
    }
}

static void event_handler_cb_capacity_obj36(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        action_clear_capacity_limits(e);
    }
}

static void event_handler_cb_capacity_obj37(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 45, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_settings_settings(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
    }
}

static void event_handler_cb_settings_obj38(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 9, 0, e);
    }
}

static void event_handler_cb_settings_obj39(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 11, 0, e);
    }
}

static void event_handler_cb_settings_obj40(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 13, 0, e);
    }
}

static void event_handler_cb_settings_obj41(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 15, 0, e);
    }
}

static void event_handler_cb_settings_obj42(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 17, 0, e);
    }
}

static void event_handler_cb_settings_obj43(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 19, 0, e);
    }
}

static void event_handler_cb_settings_obj44(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 21, 0, e);
    }
}

static void event_handler_cb_settings_obj45(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 23, 0, e);
    }
}

static void event_handler_cb_settings_obj46(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 25, 0, e);
    }
}

static void event_handler_cb_settings_obj47(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 27, 0, e);
    }
}

static void event_handler_cb_settings_obj48(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 29, 0, e);
    }
}

static void event_handler_cb_events_events(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
        lv_group_add_obj(groups.encoder_group, objects.events_table);
    }
    
    if (event == LV_EVENT_SCREEN_LOADED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_events_obj49(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
}

static void event_handler_cb_events_obj50(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 6, 0, e);
    }
}

static void event_handler_cb_events_obj51(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 8, 0, e);
    }
}

static void event_handler_cb_ranges_ranges(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
        lv_group_add_obj(groups.encoder_group, objects.current_range);
        lv_group_add_obj(groups.encoder_group, objects.volt_range);
        lv_group_add_obj(groups.encoder_group, objects.sense);
        lv_group_add_obj(groups.encoder_group, objects.nlpc_back);
        lv_group_add_obj(groups.encoder_group, objects.nlpc_ok);
        lv_group_add_obj(groups.encoder_group, objects.nlpc_cancel);
        lv_group_add_obj(groups.encoder_group, objects.obj3__sure_but_yes);
        lv_group_add_obj(groups.encoder_group, objects.obj3__sure_but_no);
    }
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 9, 0, e);
    }
}

static void event_handler_cb_ranges_current_range(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 13, 4, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 13, 0, e);
    }
}

static void event_handler_cb_ranges_volt_range(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 14, 4, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 14, 0, e);
    }
}

static void event_handler_cb_ranges_sense(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 16, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 16, 0, e);
    }
}

static void event_handler_cb_ranges_nlpc_back(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 17, 0, e);
    }
}

static void event_handler_cb_ranges_nlpc_ok(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 19, 0, e);
    }
}

static void event_handler_cb_ranges_nlpc_cancel(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 21, 0, e);
    }
}

static void event_handler_cb_nplc_nplc(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
        lv_group_add_obj(groups.encoder_group, objects.nplc_nplc);
        lv_group_add_obj(groups.encoder_group, objects.pl_freq);
        lv_group_add_obj(groups.encoder_group, objects.obj4__sure_but_yes);
        lv_group_add_obj(groups.encoder_group, objects.obj4__sure_but_no);
    }
}

static void event_handler_cb_nplc_nlpc_home(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 16, 0, e);
    }
}

static void event_handler_cb_nplc_nlpc_home_cancel(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 21, 0, e);
    }
}

static void event_handler_cb_nplc_nlpc_home_cancel_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 23, 0, e);
    }
}

static void event_handler_cb_nplc_nplc_nplc(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 25, 3, value, "Failed to assign Value in Slider widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 25, 0, e);
    }
}

static void event_handler_cb_nplc_pl_freq(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 29, 3, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 29, 0, e);
    }
}

static void event_handler_cb_protections_protections(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
    }
}

static void event_handler_cb_protections_obj52(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 22, 0, e);
    }
}

static void event_handler_cb_protections_obj53(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 28, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 28, 0, e);
    }
}

static void event_handler_cb_protections_obj54(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 30, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 30, 0, e);
    }
}

static void event_handler_cb_protections_obj55(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 32, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 32, 0, e);
    }
}

static void event_handler_cb_protections_obj56(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 34, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 34, 0, e);
    }
}

static void event_handler_cb_protections_obj57(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 36, 0, e);
    }
}

static void event_handler_cb_protections_obj58(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 38, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 38, 0, e);
    }
}

static void event_handler_cb_protections_obj59(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 40, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 40, 0, e);
    }
}

static void event_handler_cb_protections_obj60(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 42, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_calibration_calibration(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
    }
}

static void event_handler_cb_calibration_obj61(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 32, 4, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
}

static void event_handler_cb_calibration_obj62(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 34, 0, e);
    }
}

static void event_handler_cb_calibration_obj63(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 39, 0, e);
    }
}

static void event_handler_cb_calibration_obj64(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 41, 0, e);
    }
}

static void event_handler_cb_calibration_obj65(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
}

static void event_handler_cb_calibration_obj66(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 43, 0, e);
    }
}

static void event_handler_cb_calibration_obj67(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 45, 0, e);
    }
}

static void event_handler_cb_calibration_obj68(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
}

static void event_handler_cb_calibration_obj69(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 49, 0, e);
    }
}

static void event_handler_cb_calibration_obj70(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 50, 0, e);
    }
}

static void event_handler_cb_calibration_obj71(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 51, 0, e);
    }
}

static void event_handler_cb_calibration_obj72(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 52, 0, e);
    }
}

static void event_handler_cb_fan_fan(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
        lv_group_add_obj(groups.encoder_group, objects.obj73);
        lv_group_add_obj(groups.encoder_group, objects.obj74);
        lv_group_add_obj(groups.encoder_group, objects.obj7__sure_but_yes);
        lv_group_add_obj(groups.encoder_group, objects.obj7__sure_but_no);
    }
}

static void event_handler_cb_fan_nlpc_home_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 16, 0, e);
    }
}

static void event_handler_cb_fan_nlpc_home_cancel_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 21, 0, e);
    }
}

static void event_handler_cb_fan_nlpc_home_cancel_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 23, 0, e);
    }
}

static void event_handler_cb_fan_obj73(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 25, 4, value, "Failed to assign Value in Slider widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 25, 0, e);
    }
}

static void event_handler_cb_fan_obj74(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 29, 3, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 29, 0, e);
    }
}

static void event_handler_cb_display_display(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
        lv_group_add_obj(groups.encoder_group, objects.obj8__sure_but_yes);
        lv_group_add_obj(groups.encoder_group, objects.obj8__sure_but_no);
    }
}

static void event_handler_cb_display_nlpc_home_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 20, 0, e);
    }
}

static void event_handler_cb_display_nlpc_home_cancel_4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 23, 0, e);
    }
}

static void event_handler_cb_display_nlpc_home_cancel_5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 25, 0, e);
    }
}

static void event_handler_cb_display_obj75(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 27, 4, value, "Failed to assign Value in Slider widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 27, 0, e);
    }
}

static void event_handler_cb_display_obj76(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 29, 3, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 29, 0, e);
    }
}

static void event_handler_cb_display_obj77(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 31, 0, e);
    }
}

static void event_handler_cb_display_display_off(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 34, 0, e);
    }
}

static void event_handler_cb_info_info(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
    }
}

static void event_handler_cb_info_nlpc_home_4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_sound_sound(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
        lv_group_add_obj(groups.encoder_group, objects.nplc_nplc_1);
        lv_group_add_obj(groups.encoder_group, objects.obj9__sure_but_yes);
        lv_group_add_obj(groups.encoder_group, objects.obj9__sure_but_no);
    }
    
    if (event == LV_EVENT_SCREEN_LOADED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 14, 0, e);
    }
}

static void event_handler_cb_sound_nlpc_home_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 15, 0, e);
    }
}

static void event_handler_cb_sound_nlpc_home_cancel_6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 18, 0, e);
    }
}

static void event_handler_cb_sound_nlpc_home_cancel_7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 20, 0, e);
    }
}

static void event_handler_cb_sound_nplc_nplc_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 22, 3, value, "Failed to assign Value in Slider widget");
            }
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 22, 0, e);
    }
}

static void event_handler_cb_sound_obj78(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 24, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 24, 0, e);
    }
}

static void event_handler_cb_sound_obj79(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 27, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 27, 0, e);
    }
}

static void event_handler_cb_sound_obj80(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 28, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 28, 0, e);
    }
}

static void event_handler_cb_sound_obj81(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 29, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 29, 0, e);
    }
}

static void event_handler_cb_sound_obj82(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 30, 0, e);
    }
}

static void event_handler_cb_sound_obj83(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 32, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 32, 0, e);
    }
}

static void event_handler_cb_stats_stats(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
    }
}

static void event_handler_cb_stats_stats_back(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_popup_popup(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        // group: encoder_group
        lv_group_remove_all_objs(groups.encoder_group);
    }
}

static void event_handler_cb_question_yn_sure_but_yes(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_question_yn_sure_but_no(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
}

static void event_handler_cb_keyboard_kbtext2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            if (tick_value_change_obj != ta) {
                assignStringProperty(flowState, 2, 3, value, "Failed to assign Text in Textarea widget");
            }
        }
    }
}

static void event_handler_cb_keyboard_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_READY) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
    if (event == LV_EVENT_CANCEL) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 1, e);
    }
}

static void event_handler_cb_keyboard_max_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 16, 0, e);
    }
}

static void event_handler_cb_keyboard_min_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 18, 0, e);
    }
}

static void event_handler_cb_stats_table_obj5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 0, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_stats_table_obj6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 8, 0, e);
    }
}

static void event_handler_cb_event_filter_select_obj7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 4, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
}

static void event_handler_cb_event_filter_select_obj8(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 5, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)1;
        flowPropagateValueLVGLEvent(flowState, 5, 0, e);
    }
}

static void event_handler_cb_event_filter_select_obj9(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 6, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)2;
        flowPropagateValueLVGLEvent(flowState, 6, 0, e);
    }
}

static void event_handler_cb_event_filter_select_obj10(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 7, 3, value, "Failed to assign Checked state");
        }
    }
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)3;
        flowPropagateValueLVGLEvent(flowState, 7, 0, e);
    }
}

void create_screen_startup() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.startup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_startup_startup, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 42);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "DCL8010");
            add_style_bigfont_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 47, 42);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Startup:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 58, 66);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "EEPROM:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 3, 90);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Calibration:");
            add_style_small_label(obj);
        }
        {
            // startup_start_status
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.startup_start_status = obj;
            lv_obj_set_pos(obj, 135, 42);
            lv_obj_set_size(obj, 185, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // startup_eeprom
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.startup_eeprom = obj;
            lv_obj_set_pos(obj, 135, 66);
            lv_obj_set_size(obj, 185, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // startup_calibration
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.startup_calibration = obj;
            lv_obj_set_pos(obj, 135, 90);
            lv_obj_set_size(obj, 185, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Startup_OK
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.startup_ok = obj;
            lv_obj_set_pos(obj, 219, 192);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_startup_startup_ok, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj84 = obj;
                    lv_obj_set_pos(obj, 3, -1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 78, 114);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Fans:");
            add_style_small_label(obj);
        }
        {
            // startup_fans
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.startup_fans = obj;
            lv_obj_set_pos(obj, 135, 114);
            lv_obj_set_size(obj, 185, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_startup() {
    void *flowState = getFlowState(0, 0);
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.startup_start_status);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.startup_start_status;
            lv_label_set_text(objects.startup_start_status, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 13, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.startup_eeprom);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.startup_eeprom;
            lv_label_set_text(objects.startup_eeprom, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 14, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.startup_calibration);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.startup_calibration;
            lv_label_set_text(objects.startup_calibration, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 15, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.startup_ok, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.startup_ok;
            if (new_val) lv_obj_add_flag(objects.startup_ok, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.startup_ok, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj84);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj84;
            lv_label_set_text(objects.obj84, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 18, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.startup_fans, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.startup_fans;
            if (new_val) lv_obj_add_flag(objects.startup_fans, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.startup_fans, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.startup_fans);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.startup_fans;
            lv_label_set_text(objects.startup_fans, new_val);
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
    lv_obj_add_event_cb(obj, event_handler_cb_main_main, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // modeSelector
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.mode_selector = obj;
            lv_obj_set_pos(obj, 2, 2);
            lv_obj_set_size(obj, 130, 38);
            lv_dropdown_set_options(obj, "Mode CC\nMode CV\nMode CP\nMode CR\nSHORT\nDVM");
            lv_obj_add_event_cb(obj, event_handler_cb_main_mode_selector, LV_EVENT_ALL, flowState);
            add_style_selector_with_disable(obj);
        }
        {
            // ON-OFF button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.on_off_button = obj;
            lv_obj_set_pos(obj, -2, 2);
            lv_obj_set_size(obj, 109, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_main_on_off_button, LV_EVENT_ALL, flowState);
            add_style_button(obj);
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
                    objects.obj88 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // Main-Measure
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_measure = obj;
            lv_obj_set_pos(obj, 0, 42);
            lv_obj_set_size(obj, 320, 63);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_blackpanel(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // RangeCurrent
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.range_current = obj;
                    lv_obj_set_pos(obj, -13, -13);
                    lv_obj_set_size(obj, 24, 37);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_range_current, LV_EVENT_ALL, flowState);
                    add_style_select_button90deg(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj13 = obj;
                            lv_obj_set_pos(obj, 2, 1);
                            lv_obj_set_size(obj, 21, 37);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj13, LV_EVENT_ALL, flowState);
                            add_style_button_text90deg(obj);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj14 = obj;
                    lv_obj_set_pos(obj, 11, -15);
                    lv_obj_set_size(obj, 126, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj14, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_bigfont_label(obj);
                }
                {
                    // RangeVolt
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.range_volt = obj;
                    lv_obj_set_pos(obj, 283, -13);
                    lv_obj_set_size(obj, 24, 37);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_range_volt, LV_EVENT_ALL, flowState);
                    add_style_select_button90deg(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj89 = obj;
                            lv_obj_set_pos(obj, 2, 1);
                            lv_obj_set_size(obj, 21, 37);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            add_style_button_text90deg(obj);
                        }
                    }
                }
                {
                    // SenseIndicator
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.sense_indicator = obj;
                    lv_obj_set_pos(obj, 163, 14);
                    lv_obj_set_size(obj, 120, 4);
                    add_style_blackpanel(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DISABLED);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj85 = obj;
                    lv_obj_set_pos(obj, 23, 1);
                    lv_obj_set_size(obj, 64, 64);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Sense");
                    add_style_button_text90deg(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_y(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_x(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj15 = obj;
                    lv_obj_set_pos(obj, 147, -15);
                    lv_obj_set_size(obj, 136, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj15, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_bigfont_label(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj90 = obj;
                    lv_obj_set_pos(obj, -13, 16);
                    lv_obj_set_size(obj, 150, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_bigfont_label(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj16 = obj;
                    lv_obj_set_pos(obj, 147, 16);
                    lv_obj_set_size(obj, 136, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj16, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_bigfont_label(obj);
                }
            }
        }
        {
            // Flex panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.flex_panel = obj;
            lv_obj_set_pos(obj, 0, 105);
            lv_obj_set_size(obj, 320, 64);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj17 = obj;
                    lv_obj_set_pos(obj, -13, 0);
                    lv_obj_set_size(obj, 16, 62);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj17, LV_EVENT_ALL, flowState);
                    add_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj91 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 16, 24);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj18 = obj;
                    lv_obj_set_pos(obj, 13, 0);
                    lv_obj_set_size(obj, 16, 63);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj18, LV_EVENT_ALL, flowState);
                    add_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_RIGHT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj92 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 16, 24);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // Capacity Panel
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.capacity_panel = obj;
                    lv_obj_set_pos(obj, 3, -15);
                    lv_obj_set_size(obj, 289, 63);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // Ah
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.ah = obj;
                            lv_obj_set_pos(obj, -8, -6);
                            lv_obj_set_size(obj, 140, 21);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // Wh
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wh = obj;
                            lv_obj_set_pos(obj, -8, 18);
                            lv_obj_set_size(obj, 140, 21);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_add_event_cb(obj, event_handler_cb_main_wh, LV_EVENT_ALL, flowState);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // montime
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.montime = obj;
                            lv_obj_set_pos(obj, 135, 1);
                            lv_obj_set_size(obj, 101, 21);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj19 = obj;
                            lv_obj_set_pos(obj, 11, 1);
                            lv_obj_set_size(obj, 38, 32);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj19, LV_EVENT_ALL, flowState);
                            add_style_select_button_red_green(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_RIGHT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj93 = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 36, 24);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_label_set_text(obj, "");
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                    }
                }
                {
                    // Stats panel
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.stats_panel = obj;
                    lv_obj_set_pos(obj, 3, -15);
                    lv_obj_set_size(obj, 289, 63);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // statMin
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.stat_min = obj;
                            lv_obj_set_pos(obj, 33, -14);
                            lv_obj_set_size(obj, 91, 20);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj20 = obj;
                            lv_obj_set_pos(obj, 11, 1);
                            lv_obj_set_size(obj, 38, 32);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj20, LV_EVENT_ALL, flowState);
                            add_style_selectbutton(obj);
                            lv_obj_set_style_align(obj, LV_ALIGN_RIGHT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.obj94 = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 36, 24);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_label_set_text(obj, "");
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // montime_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.montime_3 = obj;
                            lv_obj_set_pos(obj, 131, 10);
                            lv_obj_set_size(obj, 104, 20);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, -12, -14);
                            lv_obj_set_size(obj, 45, 20);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "min:");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, -12, 6);
                            lv_obj_set_size(obj, 45, 20);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "avg:");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // Ah_10
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.ah_10 = obj;
                            lv_obj_set_pos(obj, -12, 26);
                            lv_obj_set_size(obj, 45, 20);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "max:");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // statAvg
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.stat_avg = obj;
                            lv_obj_set_pos(obj, 33, 6);
                            lv_obj_set_size(obj, 91, 20);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // statMax
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.stat_max = obj;
                            lv_obj_set_pos(obj, 33, 26);
                            lv_obj_set_size(obj, 91, 20);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // montime_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.montime_4 = obj;
                            lv_obj_set_pos(obj, 131, -11);
                            lv_obj_set_size(obj, 104, 20);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "count:");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // Main-Lower panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_lower_panel = obj;
            lv_obj_set_pos(obj, 0, 168);
            lv_obj_set_size(obj, 320, 73);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // set_value
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.set_value = obj;
                    lv_obj_set_pos(obj, -15, -12);
                    lv_obj_set_size(obj, 160, 69);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_blackpanel(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // isetlabel_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.isetlabel_1 = obj;
                            lv_obj_set_pos(obj, 0, -10);
                            lv_obj_set_size(obj, 160, 27);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            add_style_small_label(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // myspinbox
                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                            objects.myspinbox = obj;
                            lv_obj_set_pos(obj, -7, 14);
                            lv_obj_set_size(obj, 116, 30);
                            lv_spinbox_set_rollover(obj, false);
                            lv_spinbox_set_digit_step_direction(obj, LV_DIR_RIGHT);
                            lv_spinbox_set_step(obj, 1);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_myspinbox, LV_EVENT_ALL, flowState);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            add_style_spinbox_default(obj);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj21 = obj;
                            lv_obj_set_pos(obj, 109, 14);
                            lv_obj_set_size(obj, 38, 36);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj21, LV_EVENT_ALL, flowState);
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
                    add_style_blackpanel(obj);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj95 = obj;
                            lv_obj_set_pos(obj, -14, -15);
                            lv_obj_set_size(obj, 79, 70);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_blackpanel(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // vonlabel
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.vonlabel = obj;
                                    lv_obj_set_pos(obj, 1, -12);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_label_set_text(obj, "Von:");
                                    add_style_small_label(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.obj22 = obj;
                                    lv_obj_set_pos(obj, -12, 12);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj22, LV_EVENT_ALL, flowState);
                                    add_style_button(obj);
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
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_CHECKED);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj96 = obj;
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
                                    objects.obj23 = obj;
                                    lv_obj_set_pos(obj, -12, 36);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj23, LV_EVENT_ALL, flowState);
                                    add_style_button(obj);
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
                                            objects.obj97 = obj;
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
                            // Protection and Temp
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.protection_and_temp = obj;
                            lv_obj_set_pos(obj, 65, -15);
                            lv_obj_set_size(obj, 80, 70);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_blackpanel(obj);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.obj24 = obj;
                                    lv_obj_set_pos(obj, -2, -7);
                                    lv_obj_set_size(obj, 55, 34);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj24, LV_EVENT_ALL, flowState);
                                    add_style_select_button_red_green(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj98 = obj;
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
                                    objects.obj99 = obj;
                                    lv_obj_set_pos(obj, 0, 21);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                                    lv_label_set_text(obj, "");
                                    add_style_small_label(obj);
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
            lv_obj_set_pos(obj, 133, 27);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj25 = obj;
            lv_obj_set_pos(obj, 11, 2);
            lv_obj_set_size(obj, 58, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj25, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj100 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 24, 24);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // Main-DVM
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_dvm = obj;
            lv_obj_set_pos(obj, 0, 43);
            lv_obj_set_size(obj, 320, 122);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_blackpanel(obj);
            lv_obj_set_style_pad_bottom(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // RangeVolt_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.range_volt_1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 58, 30);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_range_volt_1, LV_EVENT_ALL, flowState);
                    add_style_select_button90deg(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj101 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 58, 28);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            add_style_button_text(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj86 = obj;
                    lv_obj_set_pos(obj, 40, 40);
                    lv_obj_set_size(obj, 93, 25);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Sense");
                    add_style_button_text90deg(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_y(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_x(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_rotation(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj102 = obj;
                    lv_obj_set_pos(obj, 8, -12);
                    lv_obj_set_size(obj, 263, 61);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_bigfont_label(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_64, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj26 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 136, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj26, LV_EVENT_ALL, flowState);
                    add_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj103 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 136, 28);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            // Main-SHORT
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_short = obj;
            lv_obj_set_pos(obj, 0, 43);
            lv_obj_set_size(obj, 320, 122);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_blackpanel(obj);
            lv_obj_set_style_pad_bottom(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // RangeCurr_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.range_curr_1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 58, 30);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_range_curr_1, LV_EVENT_ALL, flowState);
                    add_style_select_button90deg(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj104 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 58, 28);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            add_style_button_text(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj87 = obj;
                    lv_obj_set_pos(obj, 40, 29);
                    lv_obj_set_size(obj, 93, 22);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Sense");
                    add_style_button_text90deg(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_y(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_x(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_rotation(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // vonlabel_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.vonlabel_1 = obj;
                    lv_obj_set_pos(obj, 40, 94);
                    lv_obj_set_size(obj, 93, 21);
                    lv_label_set_text(obj, "");
                    add_style_small_label(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj105 = obj;
                    lv_obj_set_pos(obj, 8, -12);
                    lv_obj_set_size(obj, 263, 61);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    add_style_bigfont_label(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_64, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj27 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 136, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj27, LV_EVENT_ALL, flowState);
                    add_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj106 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 136, 28);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_keyboard(obj, getFlowState(flowState, 119), 16);
        }
    }
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 1);
    {
        bool new_val = evalBooleanProperty(flowState, 49, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.mode_selector, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.mode_selector;
            if (new_val) lv_obj_add_state(objects.mode_selector, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.mode_selector, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.mode_selector) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 49, 4, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.mode_selector);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.mode_selector;
                lv_dropdown_set_selected(objects.mode_selector, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 50, 4, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.on_off_button, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button;
            if (new_val) lv_obj_add_state(objects.on_off_button, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.on_off_button, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 50, 5, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.on_off_button, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button;
            if (new_val) lv_obj_add_state(objects.on_off_button, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.on_off_button, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 50, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.on_off_button, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button;
            if (new_val) lv_obj_add_flag(objects.on_off_button, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.on_off_button, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 51, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj88);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj88;
            lv_label_set_text(objects.obj88, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 52, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.main_measure, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.main_measure;
            if (new_val) lv_obj_add_flag(objects.main_measure, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.main_measure, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 53, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.range_current, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.range_current;
            if (new_val) lv_obj_add_state(objects.range_current, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.range_current, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 54, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj13, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj13;
            if (new_val) lv_obj_add_state(objects.obj13, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj13, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 54, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj13);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj13;
            lv_label_set_text(objects.obj13, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 55, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj14);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj14;
            lv_label_set_text(objects.obj14, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 56, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.range_volt, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.range_volt;
            if (new_val) lv_obj_add_state(objects.range_volt, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.range_volt, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 57, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj89);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj89;
            lv_label_set_text(objects.obj89, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 58, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sense_indicator, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sense_indicator;
            if (new_val) lv_obj_add_flag(objects.sense_indicator, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.sense_indicator, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 59, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj85, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj85;
            if (new_val) lv_obj_add_flag(objects.obj85, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj85, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 60, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj15);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj15;
            lv_label_set_text(objects.obj15, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 61, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj90);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj90;
            lv_label_set_text(objects.obj90, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 62, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj16);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj16;
            lv_label_set_text(objects.obj16, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 63, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.flex_panel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.flex_panel;
            if (new_val) lv_obj_add_flag(objects.flex_panel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.flex_panel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 65, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj91);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj91;
            lv_label_set_text(objects.obj91, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 66, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj92);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj92;
            lv_label_set_text(objects.obj92, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 68, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.capacity_panel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.capacity_panel;
            if (new_val) lv_obj_add_flag(objects.capacity_panel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.capacity_panel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 69, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah;
            lv_label_set_text(objects.ah, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 70, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wh);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wh;
            lv_label_set_text(objects.wh, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 71, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.montime);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.montime;
            lv_label_set_text(objects.montime, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 72, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj19, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj19;
            if (new_val) lv_obj_add_state(objects.obj19, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj19, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 73, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj93);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj93;
            lv_label_set_text(objects.obj93, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 74, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.stats_panel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.stats_panel;
            if (new_val) lv_obj_add_flag(objects.stats_panel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.stats_panel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 75, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.stat_min);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.stat_min;
            lv_label_set_text(objects.stat_min, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 76, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj20, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj20;
            if (new_val) lv_obj_add_state(objects.obj20, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj20, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 77, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj94);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj94;
            lv_label_set_text(objects.obj94, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 78, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.montime_3);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.montime_3;
            lv_label_set_text(objects.montime_3, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 82, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.stat_avg);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.stat_avg;
            lv_label_set_text(objects.stat_avg, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 83, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.stat_max);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.stat_max;
            lv_label_set_text(objects.stat_max, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 86, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.set_value, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.set_value;
            if (new_val) lv_obj_add_flag(objects.set_value, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.set_value, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 87, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.isetlabel_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.isetlabel_1;
            lv_label_set_text(objects.isetlabel_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 88, 3, "Failed to evaluate Separator position in Spinbox widget");
        lv_spinbox_t* spinbox = (lv_spinbox_t *) objects.myspinbox;
        uint32_t cur_val = spinbox->dec_point_pos;
        if (new_val != cur_val) {
            tick_value_change_obj = objects.myspinbox;
            int32_t count = spinbox->digit_count;
            int32_t pos = new_val;
            if (count >= pos) {
                lv_spinbox_set_digit_format(objects.myspinbox, count, pos);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 88, 4, "Failed to evaluate Min in Spinbox widget");
        lv_spinbox_t* spinbox = (lv_spinbox_t *) objects.myspinbox;
        uint32_t cur_val = spinbox->range_min;
        if (new_val != cur_val) {
            tick_value_change_obj = objects.myspinbox;
            int32_t max = spinbox->range_max;
            int32_t min = new_val;
            if (min < max) {
                lv_spinbox_set_range(objects.myspinbox, min, max);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 88, 5, "Failed to evaluate Max in Spinbox widget");
        lv_spinbox_t* spinbox = (lv_spinbox_t *) objects.myspinbox;
        uint32_t cur_val = spinbox->range_max;
        if (new_val != cur_val) {
            tick_value_change_obj = objects.myspinbox;
            int32_t min = spinbox->range_min;
            int32_t max = new_val;
            if (min < max) {
                lv_spinbox_set_range(objects.myspinbox, min, max);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 88, 6, "Failed to evaluate Value in Spinbox widget");
        int32_t cur_val = lv_spinbox_get_value(objects.myspinbox);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.myspinbox;
            lv_spinbox_set_value(objects.myspinbox, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 89, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj21);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj21;
            lv_label_set_text(objects.obj21, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 91, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj95, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj95;
            if (new_val) lv_obj_add_flag(objects.obj95, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj95, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 93, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj22, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj22;
            if (new_val) lv_obj_add_state(objects.obj22, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj22, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 94, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj96);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj96;
            lv_label_set_text(objects.obj96, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 96, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj97);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj97;
            lv_label_set_text(objects.obj97, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 98, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj24, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj24;
            if (new_val) lv_obj_add_state(objects.obj24, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj24, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 100, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj98);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj98;
            lv_label_set_text(objects.obj98, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 99, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj99);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj99;
            lv_label_set_text(objects.obj99, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 101, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.wheel;
            if (new_val) lv_obj_add_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 103, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj100);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj100;
            lv_label_set_text(objects.obj100, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 104, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.main_dvm, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.main_dvm;
            if (new_val) lv_obj_add_flag(objects.main_dvm, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.main_dvm, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 105, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.range_volt_1, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.range_volt_1;
            if (new_val) lv_obj_add_state(objects.range_volt_1, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.range_volt_1, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 106, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj101);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj101;
            lv_label_set_text(objects.obj101, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 107, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj86, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj86;
            if (new_val) lv_obj_add_flag(objects.obj86, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj86, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 108, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj102);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj102;
            lv_label_set_text(objects.obj102, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 110, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj103);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj103;
            lv_label_set_text(objects.obj103, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 111, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.main_short, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.main_short;
            if (new_val) lv_obj_add_flag(objects.main_short, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.main_short, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 112, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.range_curr_1, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.range_curr_1;
            if (new_val) lv_obj_add_state(objects.range_curr_1, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.range_curr_1, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 113, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj104);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj104;
            lv_label_set_text(objects.obj104, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 114, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj87, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj87;
            if (new_val) lv_obj_add_flag(objects.obj87, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj87, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 115, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.vonlabel_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.vonlabel_1;
            lv_label_set_text(objects.vonlabel_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 116, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj105);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj105;
            lv_label_set_text(objects.obj105, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 118, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj106);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj106;
            lv_label_set_text(objects.obj106, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 119, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj0, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            if (new_val) lv_obj_add_flag(objects.obj0, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj0, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 119), 16);
}

void create_screen_capacity() {
    void *flowState = getFlowState(0, 2);
    lv_obj_t *obj = lv_obj_create(0);
    objects.capacity = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_capacity_capacity, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj108 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 25);
            lv_label_set_text(obj, "");
            add_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj28 = obj;
            lv_obj_set_pos(obj, -2, -2);
            lv_obj_set_size(obj, 55, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj28, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj109 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 174);
            lv_obj_set_size(obj, 202, 24);
            lv_label_set_text(obj, "Time limit: ");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj29 = obj;
            lv_obj_set_pos(obj, 204, 174);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj29, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj110 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 114, 22);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj30 = obj;
            lv_obj_set_pos(obj, 204, 149);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj30, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj111 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 114, 22);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj31 = obj;
            lv_obj_set_pos(obj, 204, 124);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj31, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj112 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 114, 22);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj32 = obj;
            lv_obj_set_pos(obj, 204, 100);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj32, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj113 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 114, 22);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 135);
            lv_obj_set_size(obj, 202, 24);
            lv_label_set_text(obj, "Capacity limit: ");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Ah_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ah_2 = obj;
            lv_obj_set_pos(obj, 0, 25);
            lv_obj_set_size(obj, 148, 21);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Ah_3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ah_3 = obj;
            lv_obj_set_pos(obj, 172, 25);
            lv_obj_set_size(obj, 148, 21);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Ah_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ah_4 = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 148, 21);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Ah_5
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ah_5 = obj;
            lv_obj_set_pos(obj, 0, 67);
            lv_obj_set_size(obj, 148, 21);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Ah_6
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ah_6 = obj;
            lv_obj_set_pos(obj, 172, 46);
            lv_obj_set_size(obj, 148, 21);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Ah_7
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ah_7 = obj;
            lv_obj_set_pos(obj, 172, 67);
            lv_obj_set_size(obj, 148, 21);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // ON-OFF button_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.on_off_button_1 = obj;
            lv_obj_set_pos(obj, 2, -2);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_on_off_button_1, LV_EVENT_ALL, flowState);
            add_style_button(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    objects.obj114 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj33 = obj;
            lv_obj_set_pos(obj, 2, -77);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj33, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj115 = obj;
                    lv_obj_set_pos(obj, 1, 0);
                    lv_obj_set_size(obj, 24, 24);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj34 = obj;
            lv_obj_set_pos(obj, -32, -2);
            lv_obj_set_size(obj, 55, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj34, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj116 = obj;
                    lv_obj_set_pos(obj, 0, -1);
                    lv_obj_set_size(obj, 78, 23);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj35 = obj;
            lv_obj_set_pos(obj, -142, -148);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj35, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj117 = obj;
                    lv_obj_set_pos(obj, 1, -1);
                    lv_obj_set_size(obj, 24, 24);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj36 = obj;
            lv_obj_set_pos(obj, 51, -2);
            lv_obj_set_size(obj, 88, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj36, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, -1);
                    lv_obj_set_size(obj, 88, 24);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Clear");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.obj37 = obj;
            lv_obj_set_pos(obj, 2, 97);
            lv_obj_set_size(obj, 187, 28);
            lv_checkbox_set_text(obj, "    Volt stop:");
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj37, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_checkbox_default(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj107 = obj;
            lv_obj_set_pos(obj, 0, 94);
            lv_obj_set_size(obj, 320, 2);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff828282), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_keyboard(obj, getFlowState(flowState, 47), 23);
        }
    }
}

void tick_screen_capacity() {
    void *flowState = getFlowState(0, 2);
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj108);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj108;
            lv_label_set_text(objects.obj108, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj109);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj109;
            lv_label_set_text(objects.obj109, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj29, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj29;
            if (new_val) lv_obj_add_state(objects.obj29, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj29, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 21, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj110);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj110;
            lv_label_set_text(objects.obj110, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 22, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj30, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj30;
            if (new_val) lv_obj_add_state(objects.obj30, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj30, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 23, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj111);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj111;
            lv_label_set_text(objects.obj111, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 24, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj31, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj31;
            if (new_val) lv_obj_add_state(objects.obj31, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj31, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 25, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj112);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj112;
            lv_label_set_text(objects.obj112, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 26, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj32, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj32;
            if (new_val) lv_obj_add_state(objects.obj32, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj32, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 27, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj113);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj113;
            lv_label_set_text(objects.obj113, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 29, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_2;
            lv_label_set_text(objects.ah_2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 30, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_3);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_3;
            lv_label_set_text(objects.ah_3, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 31, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_4);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_4;
            lv_label_set_text(objects.ah_4, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 32, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_5);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_5;
            lv_label_set_text(objects.ah_5, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 33, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_6);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_6;
            lv_label_set_text(objects.ah_6, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 34, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_7);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_7;
            lv_label_set_text(objects.ah_7, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 35, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.on_off_button_1, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button_1;
            if (new_val) lv_obj_add_state(objects.on_off_button_1, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.on_off_button_1, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 35, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.on_off_button_1, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button_1;
            if (new_val) lv_obj_add_state(objects.on_off_button_1, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.on_off_button_1, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 36, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj114);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj114;
            lv_label_set_text(objects.obj114, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 38, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj115);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj115;
            lv_label_set_text(objects.obj115, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 39, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj34, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj34;
            if (new_val) lv_obj_add_state(objects.obj34, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj34, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 40, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj116);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj116;
            lv_label_set_text(objects.obj116, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 42, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj117);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj117;
            lv_label_set_text(objects.obj117, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 43, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj36, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj36;
            if (new_val) lv_obj_add_flag(objects.obj36, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj36, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 45, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj37, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj37;
            if (new_val) lv_obj_add_state(objects.obj37, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj37, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 47, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj1, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj1;
            if (new_val) lv_obj_add_flag(objects.obj1, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj1, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 47), 23);
}

void create_screen_settings() {
    void *flowState = getFlowState(0, 3);
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_settings_settings, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj118 = obj;
            lv_obj_set_pos(obj, 1, 0);
            lv_obj_set_size(obj, 320, 25);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_header(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff5060a0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj38 = obj;
            lv_obj_set_pos(obj, 206, 206);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj38, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj119 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj39 = obj;
            lv_obj_set_pos(obj, 9, 206);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj39, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj120 = obj;
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
            objects.obj40 = obj;
            lv_obj_set_pos(obj, 9, 134);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj40, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj121 = obj;
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
            objects.obj41 = obj;
            lv_obj_set_pos(obj, 9, 170);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj41, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj122 = obj;
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
            objects.obj42 = obj;
            lv_obj_set_pos(obj, 9, 98);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj42, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj123 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    add_style_button_text(obj);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj43 = obj;
            lv_obj_set_pos(obj, 206, 170);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj43, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj124 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj44 = obj;
            lv_obj_set_pos(obj, 206, 134);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj44, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj125 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj45 = obj;
            lv_obj_set_pos(obj, 9, 62);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj45, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj126 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    add_style_button_text(obj);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj46 = obj;
            lv_obj_set_pos(obj, 9, 27);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj46, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj127 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    add_style_button_text(obj);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj47 = obj;
            lv_obj_set_pos(obj, 206, 98);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj47, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj128 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 28, 28);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj48 = obj;
            lv_obj_set_pos(obj, 206, 63);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj48, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj129 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_settings() {
    void *flowState = getFlowState(0, 3);
    {
        const char *new_val = evalTextProperty(flowState, 8, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj118);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj118;
            lv_label_set_text(objects.obj118, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj119);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj119;
            lv_label_set_text(objects.obj119, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj120);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj120;
            lv_label_set_text(objects.obj120, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 14, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj121);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj121;
            lv_label_set_text(objects.obj121, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj122);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj122;
            lv_label_set_text(objects.obj122, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj123);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj123;
            lv_label_set_text(objects.obj123, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj124);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj124;
            lv_label_set_text(objects.obj124, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj125);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj125;
            lv_label_set_text(objects.obj125, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj126);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj126;
            lv_label_set_text(objects.obj126, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 26, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj127);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj127;
            lv_label_set_text(objects.obj127, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 28, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj128);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj128;
            lv_label_set_text(objects.obj128, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 30, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj129);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj129;
            lv_label_set_text(objects.obj129, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_events() {
    void *flowState = getFlowState(0, 4);
    lv_obj_t *obj = lv_obj_create(0);
    objects.events = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_events_events, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj130 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 25);
            lv_label_set_text(obj, "");
            add_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj49 = obj;
            lv_obj_set_pos(obj, 239, 200);
            lv_obj_set_size(obj, 81, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_events_obj49, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj131 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // eventsTable
            lv_obj_t *obj = lv_table_create(parent_obj);
            objects.events_table = obj;
            lv_obj_set_pos(obj, 0, 25);
            lv_obj_set_size(obj, 320, 169);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ONE|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_AUTO);
            lv_obj_set_scroll_dir(obj, LV_DIR_VER);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_CENTER);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_CENTER);
            lv_obj_add_state(obj, LV_STATE_FOCUSED);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff222222), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_16, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff222222), LV_PART_ITEMS | LV_STATE_FOCUSED);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_ITEMS | LV_STATE_FOCUSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_ITEMS | LV_STATE_FOCUSED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_ITEMS | LV_STATE_CHECKED);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff222222), LV_PART_ITEMS | LV_STATE_CHECKED);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff222222), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff00), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 15, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 15, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj50 = obj;
            lv_obj_set_pos(obj, 0, 200);
            lv_obj_set_size(obj, 152, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_events_obj50, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj132 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj51 = obj;
            lv_obj_set_pos(obj, 180, 200);
            lv_obj_set_size(obj, 36, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_events_obj51, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj133 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_event_filter_select(obj, getFlowState(flowState, 10), 30);
        }
    }
}

void tick_screen_events() {
    void *flowState = getFlowState(0, 4);
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj130);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj130;
            lv_label_set_text(objects.obj130, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj131);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj131;
            lv_label_set_text(objects.obj131, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj132);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj132;
            lv_label_set_text(objects.obj132, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 9, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj133);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj133;
            lv_label_set_text(objects.obj133, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 10, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj2, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj2;
            if (new_val) lv_obj_add_flag(objects.obj2, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj2, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_event_filter_select(getFlowState(flowState, 10), 30);
}

void create_screen_ranges() {
    void *flowState = getFlowState(0, 5);
    lv_obj_t *obj = lv_obj_create(0);
    objects.ranges = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_ranges_ranges, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 6, 34);
            lv_obj_set_size(obj, 155, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Current range:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj134 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Ranges & Sense");
            add_style_small_header(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 91);
            lv_obj_set_size(obj, 160, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Volt range:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // current range
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.current_range = obj;
            lv_obj_set_pos(obj, 180, 29);
            lv_obj_set_size(obj, 102, 36);
            lv_dropdown_set_options(obj, "10A\n1A");
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_current_range, LV_EVENT_ALL, flowState);
            add_style_selector_small(obj);
        }
        {
            // volt range
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.volt_range = obj;
            lv_obj_set_pos(obj, 180, 85);
            lv_obj_set_size(obj, 102, 36);
            lv_dropdown_set_options(obj, "80V\n10V");
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_volt_range, LV_EVENT_ALL, flowState);
            add_style_selector_small(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 148);
            lv_obj_set_size(obj, 160, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Remote sense:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sense
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.sense = obj;
            lv_obj_set_pos(obj, 206, 148);
            lv_obj_set_size(obj, 50, 25);
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_sense, LV_EVENT_ALL, flowState);
        }
        {
            // NLPC_BACK
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_back = obj;
            lv_obj_set_pos(obj, 225, 190);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_nlpc_back, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj135 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // NLPC_OK
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_ok = obj;
            lv_obj_set_pos(obj, 8, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_nlpc_ok, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj136 = obj;
                    lv_obj_set_pos(obj, 3, -1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // NLPC_CANCEL
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_cancel = obj;
            lv_obj_set_pos(obj, 115, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_nlpc_cancel, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj137 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 0, 2);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_question_yn(obj, getFlowState(flowState, 23), 37);
        }
    }
}

void tick_screen_ranges() {
    void *flowState = getFlowState(0, 5);
    {
        bool new_val = evalBooleanProperty(flowState, 13, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.current_range, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.current_range;
            if (new_val) lv_obj_add_state(objects.current_range, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.current_range, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.current_range) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 13, 4, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.current_range);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.current_range;
                lv_dropdown_set_selected(objects.current_range, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 14, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.volt_range, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.volt_range;
            if (new_val) lv_obj_add_state(objects.volt_range, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.volt_range, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.volt_range) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 14, 4, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.volt_range);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.volt_range;
                lv_dropdown_set_selected(objects.volt_range, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 16, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.sense, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sense;
            if (new_val) lv_obj_add_state(objects.sense, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.sense, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 16, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.sense, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sense;
            if (new_val) lv_obj_add_state(objects.sense, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.sense, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 17, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.nlpc_back, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_back;
            if (new_val) lv_obj_add_state(objects.nlpc_back, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.nlpc_back, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj135);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj135;
            lv_label_set_text(objects.obj135, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 19, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.nlpc_ok, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_ok;
            if (new_val) lv_obj_add_state(objects.nlpc_ok, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.nlpc_ok, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 19, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_ok, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_ok;
            if (new_val) lv_obj_add_flag(objects.nlpc_ok, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_ok, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj136);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj136;
            lv_label_set_text(objects.obj136, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 21, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.nlpc_cancel, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_cancel;
            if (new_val) lv_obj_add_state(objects.nlpc_cancel, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.nlpc_cancel, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 21, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_cancel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_cancel;
            if (new_val) lv_obj_add_flag(objects.nlpc_cancel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_cancel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj137);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj137;
            lv_label_set_text(objects.obj137, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 23, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj3;
            if (new_val) lv_obj_add_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_question_yn(getFlowState(flowState, 23), 37);
}

void create_screen_nplc() {
    void *flowState = getFlowState(0, 6);
    lv_obj_t *obj = lv_obj_create(0);
    objects.nplc = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_nplc_nplc, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 34);
            lv_obj_set_size(obj, 94, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "PL Freq:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home = obj;
            lv_obj_set_pos(obj, 225, 190);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_nplc_nlpc_home, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj142 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj138 = obj;
            lv_obj_set_pos(obj, 108, 156);
            lv_obj_set_size(obj, 212, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj139 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Measurement Averaging");
            add_style_small_header(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj140 = obj;
            lv_obj_set_pos(obj, 101, 73);
            lv_obj_set_size(obj, 219, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME_CANCEL
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_cancel = obj;
            lv_obj_set_pos(obj, 115, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_nplc_nlpc_home_cancel, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj143 = obj;
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
            objects.nlpc_home_cancel_1 = obj;
            lv_obj_set_pos(obj, 8, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_nplc_nlpc_home_cancel_1, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj144 = obj;
                    lv_obj_set_pos(obj, 3, -1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // NPLC_NPLC
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.nplc_nplc = obj;
            lv_obj_set_pos(obj, 141, 117);
            lv_obj_set_size(obj, 166, 10);
            lv_slider_set_range(obj, 1, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_nplc_nplc_nplc, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            add_style_slider(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 73);
            lv_obj_set_size(obj, 94, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "ADC:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 110);
            lv_obj_set_size(obj, 94, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "NPLC:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 156);
            lv_obj_set_size(obj, 94, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Samples:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // PLFreq
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.pl_freq = obj;
            lv_obj_set_pos(obj, 101, 28);
            lv_obj_set_size(obj, 80, 36);
            lv_dropdown_set_options(obj, "50 Hz\n60 Hz");
            lv_obj_add_event_cb(obj, event_handler_cb_nplc_pl_freq, LV_EVENT_ALL, flowState);
            add_style_selector_small(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj141 = obj;
            lv_obj_set_pos(obj, 101, 110);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 0, 2);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_question_yn(obj, getFlowState(flowState, 31), 44);
        }
    }
}

void tick_screen_nplc() {
    void *flowState = getFlowState(0, 6);
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj142);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj142;
            lv_label_set_text(objects.obj142, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj138);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj138;
            lv_label_set_text(objects.obj138, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj140);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj140;
            lv_label_set_text(objects.obj140, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 21, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel;
            if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_home_cancel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj143);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj143;
            lv_label_set_text(objects.obj143, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 23, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_1, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel_1;
            if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_1, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_home_cancel_1, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj144);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj144;
            lv_label_set_text(objects.obj144, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 25, 3, "Failed to evaluate Value in Slider widget");
        int32_t cur_val = lv_slider_get_value(objects.nplc_nplc);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nplc_nplc;
            lv_slider_set_value(objects.nplc_nplc, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.pl_freq) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 29, 3, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.pl_freq);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.pl_freq;
                lv_dropdown_set_selected(objects.pl_freq, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 30, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj141);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj141;
            lv_label_set_text(objects.obj141, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 31, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj4, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj4;
            if (new_val) lv_obj_add_flag(objects.obj4, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj4, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_question_yn(getFlowState(flowState, 31), 44);
}

void create_screen_protections() {
    void *flowState = getFlowState(0, 7);
    lv_obj_t *obj = lv_obj_create(0);
    objects.protections = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_protections_protections, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj150 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 26);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj52 = obj;
            lv_obj_set_pos(obj, 230, 200);
            lv_obj_set_size(obj, 90, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj52, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj151 = obj;
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
            lv_obj_set_pos(obj, 0, 33);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Current (OCP):");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 67);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Voltage (OVP):");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 22, 101);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Power (OPP):");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 22, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Temp. (OTP): ");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj53 = obj;
            lv_obj_set_pos(obj, 160, 30);
            lv_obj_set_size(obj, 142, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj53, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj152 = obj;
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
            objects.obj54 = obj;
            lv_obj_set_pos(obj, 160, 64);
            lv_obj_set_size(obj, 142, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj54, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj153 = obj;
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
            objects.obj55 = obj;
            lv_obj_set_pos(obj, 160, 98);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj55, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj154 = obj;
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
            objects.obj56 = obj;
            lv_obj_set_pos(obj, 237, 98);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj56, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj155 = obj;
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
            objects.obj57 = obj;
            lv_obj_set_pos(obj, 28, 200);
            lv_obj_set_size(obj, 164, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj57, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffca0202), LV_PART_MAIN | LV_STATE_DEFAULT);
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
            objects.obj58 = obj;
            lv_obj_set_pos(obj, 160, 132);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj58, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj156 = obj;
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
            objects.obj59 = obj;
            lv_obj_set_pos(obj, 237, 132);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj59, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj157 = obj;
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
            objects.obj60 = obj;
            lv_obj_set_pos(obj, 203, 166);
            lv_obj_set_size(obj, 117, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj60, LV_EVENT_ALL, flowState);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj145 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 117, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj146 = obj;
            lv_obj_set_pos(obj, 0, 166);
            lv_obj_set_size(obj, 82, 30);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DISABLED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj147 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 82, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_keyboard(obj, getFlowState(flowState, 46), 51);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj148 = obj;
            lv_obj_set_pos(obj, 85, 166);
            lv_obj_set_size(obj, 115, 30);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
            add_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DISABLED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj149 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 115, 20);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_protections() {
    void *flowState = getFlowState(0, 7);
    {
        const char *new_val = evalTextProperty(flowState, 21, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj150);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj150;
            lv_label_set_text(objects.obj150, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 23, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj151);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj151;
            lv_label_set_text(objects.obj151, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 28, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj53, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj53;
            if (new_val) lv_obj_add_state(objects.obj53, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj53, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 29, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj152);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj152;
            lv_label_set_text(objects.obj152, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 30, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj54, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj54;
            if (new_val) lv_obj_add_state(objects.obj54, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj54, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 31, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj153);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj153;
            lv_label_set_text(objects.obj153, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 32, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj55, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj55;
            if (new_val) lv_obj_add_state(objects.obj55, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj55, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 33, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj154);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj154;
            lv_label_set_text(objects.obj154, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 34, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj56, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj56;
            if (new_val) lv_obj_add_state(objects.obj56, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj56, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 35, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj155);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj155;
            lv_label_set_text(objects.obj155, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 36, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj57, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj57;
            if (new_val) lv_obj_add_state(objects.obj57, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj57, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 36, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj57, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj57;
            if (new_val) lv_obj_add_flag(objects.obj57, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj57, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 38, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj58, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj58;
            if (new_val) lv_obj_add_state(objects.obj58, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj58, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 39, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj156);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj156;
            lv_label_set_text(objects.obj156, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 40, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj59, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj59;
            if (new_val) lv_obj_add_state(objects.obj59, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj59, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 41, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj157);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj157;
            lv_label_set_text(objects.obj157, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 42, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj60, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj60;
            if (new_val) lv_obj_add_state(objects.obj60, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj60, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 42, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj60, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj60;
            if (new_val) lv_obj_add_state(objects.obj60, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj60, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 43, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj145);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj145;
            lv_label_set_text(objects.obj145, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 44, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj146, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj146;
            if (new_val) lv_obj_add_flag(objects.obj146, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj146, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 45, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj147);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj147;
            lv_label_set_text(objects.obj147, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 46, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj5, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj5;
            if (new_val) lv_obj_add_flag(objects.obj5, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj5, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 46), 51);
    {
        bool new_val = evalBooleanProperty(flowState, 47, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj148, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj148;
            if (new_val) lv_obj_add_flag(objects.obj148, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj148, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 48, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj149);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj149;
            lv_label_set_text(objects.obj149, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_calibration() {
    void *flowState = getFlowState(0, 8);
    lv_obj_t *obj = lv_obj_create(0);
    objects.calibration = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_calibration_calibration, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj158 = obj;
            lv_obj_set_pos(obj, 0, 1);
            lv_obj_set_size(obj, 320, 27);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.obj61 = obj;
            lv_obj_set_pos(obj, 0, 28);
            lv_obj_set_size(obj, 320, LV_SIZE_CONTENT);
            lv_dropdown_set_options(obj, "Current Monitor High\nCurrent Monitor Low\nVoltage Monitor High\nVoltage Monitor Low\nCurrent Set High\nCurrent Set Low\nVoltage Set High\nVoltage Set Low\nVon Set High\nVon Set Low\nOCP set High\nOCP set Low\nOVP set High\nOVP set Low");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj61, LV_EVENT_ALL, flowState);
            add_style_selector_small(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 26, 102);
            lv_obj_set_size(obj, 82, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Set:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj62 = obj;
            lv_obj_set_pos(obj, 114, 98);
            lv_obj_set_size(obj, 190, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj62, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
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
                    objects.obj159 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 190, 32);
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
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj160 = obj;
            lv_obj_set_pos(obj, 0, 70);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj161 = obj;
            lv_obj_set_pos(obj, 160, 172);
            lv_obj_set_size(obj, 109, 25);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj63 = obj;
            lv_obj_set_pos(obj, 10, 206);
            lv_obj_set_size(obj, 90, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj63, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 90, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Init \nEEPROM");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj64 = obj;
            lv_obj_set_pos(obj, 198, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj64, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj65 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 45, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj65, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj66 = obj;
            lv_obj_set_pos(obj, 126, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj66, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj162 = obj;
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
            add_style_selectbutton(obj);
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
            objects.obj163 = obj;
            lv_obj_set_pos(obj, 151, 140);
            lv_obj_set_size(obj, 127, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 172);
            lv_obj_set_size(obj, 109, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Point:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj69 = obj;
            lv_obj_set_pos(obj, 136, 173);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj69, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            add_style_small_label_symbol(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj70 = obj;
            lv_obj_set_pos(obj, 268, 172);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj70, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            add_style_small_label_symbol(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj71 = obj;
            lv_obj_set_pos(obj, 278, 140);
            lv_obj_set_size(obj, 26, 26);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj71, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            add_style_small_label_symbol(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_pivot_x(obj, 13, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_pivot_y(obj, 13, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj72 = obj;
            lv_obj_set_pos(obj, 114, 140);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj72, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            add_style_small_label_symbol(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_keyboard(obj, getFlowState(flowState, 53), 58);
        }
    }
}

void tick_screen_calibration() {
    void *flowState = getFlowState(0, 8);
    {
        const char *new_val = evalTextProperty(flowState, 31, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj158);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj158;
            lv_label_set_text(objects.obj158, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 32, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj61, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj61;
            if (new_val) lv_obj_add_state(objects.obj61, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj61, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.obj61) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 32, 4, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj61);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj61;
                lv_dropdown_set_selected(objects.obj61, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 35, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj159);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj159;
            lv_label_set_text(objects.obj159, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 37, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj160);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj160;
            lv_label_set_text(objects.obj160, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 38, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj161);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj161;
            lv_label_set_text(objects.obj161, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 41, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj64, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj64;
            if (new_val) lv_obj_add_state(objects.obj64, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj64, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 42, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj65, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj65;
            if (new_val) lv_obj_add_state(objects.obj65, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj65, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 42, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj65);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj65;
            lv_label_set_text(objects.obj65, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 43, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj66, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj66;
            if (new_val) lv_obj_add_state(objects.obj66, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj66, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 44, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj162);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj162;
            lv_label_set_text(objects.obj162, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 45, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj67, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj67;
            if (new_val) lv_obj_add_state(objects.obj67, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj67, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 46, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj68, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj68;
            if (new_val) lv_obj_add_state(objects.obj68, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj68, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 46, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj68);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj68;
            lv_label_set_text(objects.obj68, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 47, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj163);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj163;
            lv_label_set_text(objects.obj163, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 49, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj69, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj69;
            if (new_val) lv_obj_add_state(objects.obj69, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj69, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 49, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj69);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj69;
            lv_label_set_text(objects.obj69, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 50, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj70, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj70;
            if (new_val) lv_obj_add_state(objects.obj70, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj70, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 50, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj70);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj70;
            lv_label_set_text(objects.obj70, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 51, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj71);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj71;
            lv_label_set_text(objects.obj71, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 52, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj72, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj72;
            if (new_val) lv_obj_add_flag(objects.obj72, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj72, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 52, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj72);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj72;
            lv_label_set_text(objects.obj72, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 53, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj6, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj6;
            if (new_val) lv_obj_add_flag(objects.obj6, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj6, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 53), 58);
    {
        float timeline_position = getTimelinePosition(flowState);
        
        static struct {
            float last_timeline_position;
            int32_t obj_obj71_rotate_init_value;
        } anim_state = { -1 };
        
        if (anim_state.last_timeline_position == -1) {
            anim_state.last_timeline_position = 0;
            anim_state.obj_obj71_rotate_init_value = lv_obj_get_style_prop(objects.obj71, LV_PART_MAIN, LV_STYLE_TRANSFORM_ROTATION).num;
        }
        
        if (timeline_position != anim_state.last_timeline_position) {
            anim_state.last_timeline_position = timeline_position;
            
            {
                lv_obj_t *obj = objects.obj71;
                
                float rotate_value = anim_state.obj_obj71_rotate_init_value;
                
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
                lv_obj_set_local_style_prop(obj, LV_STYLE_TRANSFORM_ROTATION, value, LV_PART_MAIN);
            }
        }
    }
}

void create_screen_fan() {
    void *flowState = getFlowState(0, 9);
    lv_obj_t *obj = lv_obj_create(0);
    objects.fan = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_fan_fan, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 6, 34);
            lv_obj_set_size(obj, 109, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Mode:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_1 = obj;
            lv_obj_set_pos(obj, 225, 190);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_fan_nlpc_home_1, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj169 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj164 = obj;
            lv_obj_set_pos(obj, 127, 159);
            lv_obj_set_size(obj, 193, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj165 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Fan Settings");
            add_style_small_header(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj166 = obj;
            lv_obj_set_pos(obj, 127, 73);
            lv_obj_set_size(obj, 98, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME_CANCEL_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_cancel_2 = obj;
            lv_obj_set_pos(obj, 115, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_fan_nlpc_home_cancel_2, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj170 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // NLPC_HOME_CANCEL_3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_cancel_3 = obj;
            lv_obj_set_pos(obj, 8, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_fan_nlpc_home_cancel_3, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj171 = obj;
                    lv_obj_set_pos(obj, 3, -1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.obj73 = obj;
            lv_obj_set_pos(obj, 127, 137);
            lv_obj_set_size(obj, 180, 10);
            lv_obj_add_event_cb(obj, event_handler_cb_fan_obj73, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            add_style_slider(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 73);
            lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Speed HS:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj172 = obj;
            lv_obj_set_pos(obj, 1, 130);
            lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Set speed:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 159);
            lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Temp:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.obj74 = obj;
            lv_obj_set_pos(obj, 160, 28);
            lv_obj_set_size(obj, 102, 36);
            lv_dropdown_set_options(obj, "Auto\nManual");
            lv_obj_add_event_cb(obj, event_handler_cb_fan_obj74, LV_EVENT_ALL, flowState);
            add_style_selector_small(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj167 = obj;
            lv_obj_set_pos(obj, 189, 130);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 102);
            lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Speed CS:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj168 = obj;
            lv_obj_set_pos(obj, 127, 102);
            lv_obj_set_size(obj, 98, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj7 = obj;
            lv_obj_set_pos(obj, 0, 2);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_question_yn(obj, getFlowState(flowState, 33), 65);
        }
    }
}

void tick_screen_fan() {
    void *flowState = getFlowState(0, 9);
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj169);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj169;
            lv_label_set_text(objects.obj169, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj164);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj164;
            lv_label_set_text(objects.obj164, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj166);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj166;
            lv_label_set_text(objects.obj166, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 21, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_2, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel_2;
            if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_2, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_home_cancel_2, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj170);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj170;
            lv_label_set_text(objects.obj170, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 23, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_3, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel_3;
            if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_3, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_home_cancel_3, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj171);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj171;
            lv_label_set_text(objects.obj171, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 25, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj73, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj73;
            if (new_val) lv_obj_add_flag(objects.obj73, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj73, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 25, 4, "Failed to evaluate Value in Slider widget");
        int32_t cur_val = lv_slider_get_value(objects.obj73);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj73;
            lv_slider_set_value(objects.obj73, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 27, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj172, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj172;
            if (new_val) lv_obj_add_flag(objects.obj172, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj172, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.obj74) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 29, 3, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj74);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj74;
                lv_dropdown_set_selected(objects.obj74, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 30, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj167, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj167;
            if (new_val) lv_obj_add_flag(objects.obj167, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj167, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 30, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj167);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj167;
            lv_label_set_text(objects.obj167, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 32, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj168);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj168;
            lv_label_set_text(objects.obj168, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 33, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj7, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj7;
            if (new_val) lv_obj_add_flag(objects.obj7, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj7, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_question_yn(getFlowState(flowState, 33), 65);
}

void create_screen_display() {
    void *flowState = getFlowState(0, 10);
    lv_obj_t *obj = lv_obj_create(0);
    objects.display = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_display_display, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 6, 34);
            lv_obj_set_size(obj, 109, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Mode:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_2 = obj;
            lv_obj_set_pos(obj, 225, 190);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_display_nlpc_home_2, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj175 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj173 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Display Settings");
            add_style_small_header(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME_CANCEL_4
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_cancel_4 = obj;
            lv_obj_set_pos(obj, 115, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_display_nlpc_home_cancel_4, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj176 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // NLPC_HOME_CANCEL_5
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_cancel_5 = obj;
            lv_obj_set_pos(obj, 8, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_display_nlpc_home_cancel_5, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj177 = obj;
                    lv_obj_set_pos(obj, 3, -1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.obj75 = obj;
            lv_obj_set_pos(obj, 131, 80);
            lv_obj_set_size(obj, 180, 10);
            lv_obj_add_event_cb(obj, event_handler_cb_display_obj75, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            add_style_slider(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj178 = obj;
            lv_obj_set_pos(obj, 1, 73);
            lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Timeout:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.obj76 = obj;
            lv_obj_set_pos(obj, 160, 28);
            lv_obj_set_size(obj, 102, 36);
            lv_dropdown_set_options(obj, "Auto\nManual");
            lv_obj_add_event_cb(obj, event_handler_cb_display_obj76, LV_EVENT_ALL, flowState);
            add_style_selector_small(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj174 = obj;
            lv_obj_set_pos(obj, 189, 73);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj77 = obj;
            lv_obj_set_pos(obj, 8, 144);
            lv_obj_set_size(obj, 197, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_display_obj77, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Display OFF");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj8 = obj;
            lv_obj_set_pos(obj, 0, 2);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_question_yn(obj, getFlowState(flowState, 33), 72);
        }
        {
            // display OFF
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.display_off = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_add_event_cb(obj, event_handler_cb_display_display_off, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_blackpanel(obj);
        }
    }
}

void tick_screen_display() {
    void *flowState = getFlowState(0, 10);
    {
        const char *new_val = evalTextProperty(flowState, 21, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj175);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj175;
            lv_label_set_text(objects.obj175, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 23, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_4, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel_4;
            if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_4, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_home_cancel_4, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj176);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj176;
            lv_label_set_text(objects.obj176, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 25, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_5, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel_5;
            if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_5, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_home_cancel_5, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 26, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj177);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj177;
            lv_label_set_text(objects.obj177, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 27, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj75, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj75;
            if (new_val) lv_obj_add_flag(objects.obj75, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj75, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 27, 4, "Failed to evaluate Value in Slider widget");
        int32_t cur_val = lv_slider_get_value(objects.obj75);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj75;
            lv_slider_set_value(objects.obj75, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 28, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj178, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj178;
            if (new_val) lv_obj_add_flag(objects.obj178, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj178, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.obj76) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 29, 3, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj76);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj76;
                lv_dropdown_set_selected(objects.obj76, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 30, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj174, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj174;
            if (new_val) lv_obj_add_flag(objects.obj174, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj174, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 30, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj174);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj174;
            lv_label_set_text(objects.obj174, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 33, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj8, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj8;
            if (new_val) lv_obj_add_flag(objects.obj8, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj8, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_question_yn(getFlowState(flowState, 33), 72);
    {
        bool new_val = evalBooleanProperty(flowState, 34, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.display_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.display_off;
            if (new_val) lv_obj_add_flag(objects.display_off, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.display_off, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_info() {
    void *flowState = getFlowState(0, 11);
    lv_obj_t *obj = lv_obj_create(0);
    objects.info = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_info_info, LV_EVENT_ALL, flowState);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj179 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Info");
            add_style_small_header(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME_4
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_4 = obj;
            lv_obj_set_pos(obj, 225, 190);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_info_nlpc_home_4, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj180 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj181 = obj;
            lv_obj_set_pos(obj, 56, 57);
            lv_obj_set_size(obj, 212, 18);
            lv_label_set_text(obj, "");
            add_style_extra_small_label(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj182 = obj;
            lv_obj_set_pos(obj, 34, 75);
            lv_obj_set_size(obj, 256, 18);
            lv_label_set_text(obj, "");
            add_style_extra_small_label(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj183 = obj;
            lv_obj_set_pos(obj, 0, 93);
            lv_obj_set_size(obj, 270, 18);
            lv_label_set_text(obj, "");
            add_style_extra_small_label(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj184 = obj;
            lv_obj_set_pos(obj, 22, 111);
            lv_obj_set_size(obj, 226, 18);
            lv_label_set_text(obj, "");
            add_style_extra_small_label(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 24);
            lv_obj_set_size(obj, 320, 42);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "DCL8010");
            add_style_bigfont_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj185 = obj;
            lv_obj_set_pos(obj, 22, 129);
            lv_obj_set_size(obj, 293, 18);
            lv_label_set_text(obj, "");
            add_style_extra_small_label(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj186 = obj;
            lv_obj_set_pos(obj, 63, 147);
            lv_obj_set_size(obj, 254, 18);
            lv_label_set_text(obj, "");
            add_style_extra_small_label(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj187 = obj;
            lv_obj_set_pos(obj, 10, 165);
            lv_obj_set_size(obj, 307, 18);
            lv_label_set_text(obj, "");
            add_style_extra_small_label(obj);
        }
    }
}

void tick_screen_info() {
    void *flowState = getFlowState(0, 11);
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj180);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj180;
            lv_label_set_text(objects.obj180, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj181);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj181;
            lv_label_set_text(objects.obj181, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj182);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj182;
            lv_label_set_text(objects.obj182, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 6, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj183);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj183;
            lv_label_set_text(objects.obj183, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj184);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj184;
            lv_label_set_text(objects.obj184, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 9, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj185);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj185;
            lv_label_set_text(objects.obj185, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj186);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj186;
            lv_label_set_text(objects.obj186, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj187);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj187;
            lv_label_set_text(objects.obj187, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_sound() {
    void *flowState = getFlowState(0, 12);
    lv_obj_t *obj = lv_obj_create(0);
    objects.sound = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_sound_sound, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // NLPC_HOME_3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_3 = obj;
            lv_obj_set_pos(obj, 225, 209);
            lv_obj_set_size(obj, 90, 28);
            lv_obj_add_event_cb(obj, event_handler_cb_sound_nlpc_home_3, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj190 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj188 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Sound");
            add_style_small_header(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME_CANCEL_6
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_cancel_6 = obj;
            lv_obj_set_pos(obj, 115, 209);
            lv_obj_set_size(obj, 90, 28);
            lv_obj_add_event_cb(obj, event_handler_cb_sound_nlpc_home_cancel_6, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj191 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // NLPC_HOME_CANCEL_7
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_cancel_7 = obj;
            lv_obj_set_pos(obj, 8, 210);
            lv_obj_set_size(obj, 90, 28);
            lv_obj_add_event_cb(obj, event_handler_cb_sound_nlpc_home_cancel_7, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj192 = obj;
                    lv_obj_set_pos(obj, 3, -1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // NPLC_NPLC_1
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.nplc_nplc_1 = obj;
            lv_obj_set_pos(obj, 61, 161);
            lv_obj_set_size(obj, 208, 10);
            lv_slider_set_range(obj, 1, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_sound_nplc_nplc_1, LV_EVENT_ALL, flowState);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            add_style_slider(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 8, 154);
            lv_obj_set_size(obj, 45, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "for:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.obj78 = obj;
            lv_obj_set_pos(obj, 8, 27);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "OCP/OVP/OPP/OTP");
            lv_obj_add_event_cb(obj, event_handler_cb_sound_obj78, LV_EVENT_ALL, flowState);
            add_style_checkbox_default(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj189 = obj;
            lv_obj_set_pos(obj, 137, 154);
            lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj9 = obj;
            lv_obj_set_pos(obj, 0, 2);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_question_yn(obj, getFlowState(flowState, 26), 79);
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.obj79 = obj;
            lv_obj_set_pos(obj, 8, 59);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "Capacity limit");
            lv_obj_add_event_cb(obj, event_handler_cb_sound_obj79, LV_EVENT_ALL, flowState);
            add_style_checkbox_default(obj);
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.obj80 = obj;
            lv_obj_set_pos(obj, 8, 91);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "Reverse polarity");
            lv_obj_add_event_cb(obj, event_handler_cb_sound_obj80, LV_EVENT_ALL, flowState);
            add_style_checkbox_default(obj);
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.obj81 = obj;
            lv_obj_set_pos(obj, 8, 180);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "Encoder movement click");
            lv_obj_add_event_cb(obj, event_handler_cb_sound_obj81, LV_EVENT_ALL, flowState);
            add_style_checkbox_default(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj82 = obj;
            lv_obj_set_pos(obj, 280, 152);
            lv_obj_set_size(obj, 32, 28);
            lv_obj_add_event_cb(obj, event_handler_cb_sound_obj82, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj193 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 28, 28);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            objects.obj83 = obj;
            lv_obj_set_pos(obj, 8, 124);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_checkbox_set_text(obj, "Sense error");
            lv_obj_add_event_cb(obj, event_handler_cb_sound_obj83, LV_EVENT_ALL, flowState);
            add_style_checkbox_default(obj);
        }
    }
}

void tick_screen_sound() {
    void *flowState = getFlowState(0, 12);
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj190);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj190;
            lv_label_set_text(objects.obj190, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 18, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_6, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel_6;
            if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_6, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_home_cancel_6, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj191);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj191;
            lv_label_set_text(objects.obj191, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_7, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel_7;
            if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_7, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_home_cancel_7, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 21, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj192);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj192;
            lv_label_set_text(objects.obj192, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 22, 3, "Failed to evaluate Value in Slider widget");
        int32_t cur_val = lv_slider_get_value(objects.nplc_nplc_1);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nplc_nplc_1;
            lv_slider_set_value(objects.nplc_nplc_1, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 24, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj78, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj78;
            if (new_val) lv_obj_add_state(objects.obj78, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj78, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 25, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj189);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj189;
            lv_label_set_text(objects.obj189, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 26, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj9, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj9;
            if (new_val) lv_obj_add_flag(objects.obj9, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj9, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_question_yn(getFlowState(flowState, 26), 79);
    {
        bool new_val = evalBooleanProperty(flowState, 27, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj79, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj79;
            if (new_val) lv_obj_add_state(objects.obj79, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj79, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 28, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj80, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj80;
            if (new_val) lv_obj_add_state(objects.obj80, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj80, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 29, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj81, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj81;
            if (new_val) lv_obj_add_state(objects.obj81, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj81, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 31, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj193);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj193;
            lv_label_set_text(objects.obj193, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 32, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj83, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj83;
            if (new_val) lv_obj_add_state(objects.obj83, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj83, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_stats() {
    void *flowState = getFlowState(0, 13);
    lv_obj_t *obj = lv_obj_create(0);
    objects.stats = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_stats_stats, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    add_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Stats_back
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.stats_back = obj;
            lv_obj_set_pos(obj, 193, 216);
            lv_obj_set_size(obj, 72, 24);
            lv_obj_add_event_cb(obj, event_handler_cb_stats_stats_back, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj195 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj194 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Statistics");
            add_style_small_header(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_8
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stat_min_8 = obj;
            lv_obj_set_pos(obj, 0, 69);
            lv_obj_set_size(obj, 45, 15);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Last:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_16, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_9
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stat_min_9 = obj;
            lv_obj_set_pos(obj, 0, 89);
            lv_obj_set_size(obj, 45, 15);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Min:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_16, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_10
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stat_min_10 = obj;
            lv_obj_set_pos(obj, 0, 108);
            lv_obj_set_size(obj, 45, 15);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Avg:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_16, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_11
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stat_min_11 = obj;
            lv_obj_set_pos(obj, 0, 129);
            lv_obj_set_size(obj, 45, 15);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Dev:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_16, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_12
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stat_min_12 = obj;
            lv_obj_set_pos(obj, 0, 168);
            lv_obj_set_size(obj, 45, 15);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Cnt:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_16, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_13
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stat_min_13 = obj;
            lv_obj_set_pos(obj, 0, 148);
            lv_obj_set_size(obj, 45, 15);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Max:");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_16, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj10 = obj;
            lv_obj_set_pos(obj, 47, 24);
            lv_obj_set_size(obj, 91, 191);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_stats_table(obj, getFlowState(flowState, 11), 86);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj11 = obj;
            lv_obj_set_pos(obj, 138, 24);
            lv_obj_set_size(obj, 91, 191);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_stats_table(obj, getFlowState(flowState, 12), 96);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj12 = obj;
            lv_obj_set_pos(obj, 229, 24);
            lv_obj_set_size(obj, 91, 191);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_stats_table(obj, getFlowState(flowState, 13), 106);
        }
    }
}

void tick_screen_stats() {
    void *flowState = getFlowState(0, 13);
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj195);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj195;
            lv_label_set_text(objects.obj195, new_val);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_stats_table(getFlowState(flowState, 11), 86);
    tick_user_widget_stats_table(getFlowState(flowState, 12), 96);
    tick_user_widget_stats_table(getFlowState(flowState, 13), 106);
}

void create_screen_popup() {
    void *flowState = getFlowState(0, 14);
    lv_obj_t *obj = lv_obj_create(0);
    objects.popup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_popup_popup, LV_EVENT_ALL, flowState);
    {
        lv_obj_t *parent_obj = obj;
        {
            // popup_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.popup_container = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // popupBox
                    lv_obj_t *obj = lv_msgbox_create(parent_obj);
                    objects.popup_box = obj;
                    lv_obj_set_pos(obj, 23, 100);
                    lv_obj_set_size(obj, 275, 40);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_GESTURE_BUBBLE);
                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // popupText
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.popup_text = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
                            lv_label_set_text(obj, "Reverse Polarity Detected");
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
            }
        }
    }
}

void tick_screen_popup() {
    void *flowState = getFlowState(0, 14);
    {
        bool new_val = evalBooleanProperty(flowState, 0, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.popup_container, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.popup_container;
            if (new_val) lv_obj_add_flag(objects.popup_container, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.popup_container, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
}

void create_user_widget_question_yn(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_transparant_overlay(obj);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 31, 28);
            lv_obj_set_size(obj, 260, 180);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_warning(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // sure_but_Yes
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                    lv_obj_set_pos(obj, 0, 115);
                    lv_obj_set_size(obj, 100, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_question_yn_sure_but_yes, LV_EVENT_ALL, flowState);
                    add_style_button(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // sure_label_Yes
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                            lv_obj_set_pos(obj, -4, -4);
                            lv_obj_set_size(obj, 100, 32);
                            lv_label_set_text(obj, "Yes");
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // sure_but_No
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 130, 115);
                    lv_obj_set_size(obj, 100, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_question_yn_sure_but_no, LV_EVENT_ALL, flowState);
                    add_style_button(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // sure_label_No
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
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
            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
            lv_obj_set_pos(obj, 90, 120);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Are you sure?");
            add_style_small_label(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
            lv_obj_set_pos(obj, 47, 43);
            lv_obj_set_size(obj, 230, 64);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_user_widget_question_yn(void *flowState, int startWidgetIndex) {
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 5]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 5];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 5], new_val);
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
            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 25);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_label_set_text(obj, "");
            add_style_small_header(obj);
            lv_obj_set_style_text_font(obj, &ui_font_ubuntu_mono_20, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // kbtext2
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 58, 26);
            lv_obj_set_size(obj, 204, 43);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_keyboard_kbtext2, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_WITH_ARROW);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffbbbbbb), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_LEFT, LV_PART_CURSOR | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 4, LV_PART_CURSOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 3, LV_PART_CURSOR | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_CURSOR | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_CURSOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 128, LV_PART_CURSOR | LV_STATE_DEFAULT);
            lv_obj_set_style_anim_duration(obj, 0, LV_PART_CURSOR | LV_STATE_FOCUSED);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_FOCUSED);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_CURSOR | LV_STATE_FOCUSED);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_LEFT, LV_PART_CURSOR | LV_STATE_FOCUSED);
            lv_obj_set_style_border_width(obj, 3, LV_PART_CURSOR | LV_STATE_FOCUSED);
            lv_obj_set_style_text_letter_space(obj, 4, LV_PART_CURSOR | LV_STATE_FOCUSED);
        }
        {
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
            lv_obj_set_pos(obj, 0, 70);
            lv_obj_set_size(obj, 320, 170);
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
            lv_obj_add_event_cb(obj, event_handler_cb_keyboard_obj2, LV_EVENT_ALL, flowState);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff222222), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 6, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff888888), LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // max-button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
            lv_obj_set_pos(obj, 263, 26);
            lv_obj_set_size(obj, 56, 43);
            lv_obj_add_event_cb(obj, event_handler_cb_keyboard_max_button, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 56, 28);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Max");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // min-button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
            lv_obj_set_pos(obj, 1, 26);
            lv_obj_set_size(obj, 56, 43);
            lv_obj_add_event_cb(obj, event_handler_cb_keyboard_min_button, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 56, 28);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Min");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
    lv_keyboard_set_textarea(((lv_obj_t **)&objects)[startWidgetIndex + 1], ((lv_obj_t **)&objects)[startWidgetIndex + 0]);
}

void tick_user_widget_keyboard(void *flowState, int startWidgetIndex) {
    {
        const char *new_val = evalTextProperty(flowState, 0, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 5]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 5];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 5], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 0]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 0];
            lv_textarea_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 0], new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_user_widget_stats_table(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // statMin_17
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 91, 20);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_checkbox_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 17, 20);
            lv_obj_set_size(obj, 58, 20);
            lv_checkbox_set_text(obj, "Run");
            lv_obj_add_event_cb(obj, event_handler_cb_stats_table_obj5, LV_EVENT_ALL, flowState);
            add_style_checkbox_small(obj);
        }
        {
            // statMin_last
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
            lv_obj_set_pos(obj, 0, 40);
            lv_obj_set_size(obj, 91, 20);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_min
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
            lv_obj_set_pos(obj, 0, 60);
            lv_obj_set_size(obj, 91, 20);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_avg
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
            lv_obj_set_pos(obj, 0, 80);
            lv_obj_set_size(obj, 91, 20);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_dev
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
            lv_obj_set_pos(obj, 0, 100);
            lv_obj_set_size(obj, 91, 20);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_max
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
            lv_obj_set_pos(obj, 0, 120);
            lv_obj_set_size(obj, 91, 20);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // statMin_count
            lv_obj_t *obj = lv_label_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
            lv_obj_set_pos(obj, 0, 140);
            lv_obj_set_size(obj, 91, 20);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            add_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
            lv_obj_set_pos(obj, 11, 165);
            lv_obj_set_size(obj, 70, 24);
            lv_obj_add_event_cb(obj, event_handler_cb_stats_table_obj6, LV_EVENT_ALL, flowState);
            add_style_selectbutton(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Clear");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_user_widget_stats_table(void *flowState, int startWidgetIndex) {
    {
        const char *new_val = evalTextProperty(flowState, 1, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 2]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 2];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 2], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 0, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(((lv_obj_t **)&objects)[startWidgetIndex + 0], LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 0];
            if (new_val) lv_obj_add_state(((lv_obj_t **)&objects)[startWidgetIndex + 0], LV_STATE_CHECKED);
            else lv_obj_clear_state(((lv_obj_t **)&objects)[startWidgetIndex + 0], LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 3]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 3];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 3], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 4]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 4];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 4], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 5]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 5];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 5], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 6]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 6];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 6], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 6, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 7]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 7];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 7], new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 8]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 8];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 8], new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_user_widget_event_filter_select(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_msgbox_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
            lv_obj_set_pos(obj, 14, 22);
            lv_obj_set_size(obj, 191, 177);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 189, 18);
                    lv_label_set_text(obj, "Select Filter:");
                    add_style_title_(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffc2c2c2), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                    lv_obj_set_pos(obj, 38, 26);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_checkbox_set_text(obj, "Debug");
                    lv_obj_add_event_cb(obj, event_handler_cb_event_filter_select_obj7, LV_EVENT_ALL, flowState);
                    add_style_checkbox_default(obj);
                    lv_obj_set_style_radius(obj, 14, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 38, 62);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_checkbox_set_text(obj, "Info");
                    lv_obj_add_event_cb(obj, event_handler_cb_event_filter_select_obj8, LV_EVENT_ALL, flowState);
                    add_style_checkbox_default(obj);
                    lv_obj_set_style_radius(obj, 14, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 38, 97);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_checkbox_set_text(obj, "Warning");
                    lv_obj_add_event_cb(obj, event_handler_cb_event_filter_select_obj9, LV_EVENT_ALL, flowState);
                    add_style_checkbox_default(obj);
                    lv_obj_set_style_radius(obj, 14, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_checkbox_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                    lv_obj_set_pos(obj, 38, 133);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_checkbox_set_text(obj, "Error");
                    lv_obj_add_event_cb(obj, event_handler_cb_event_filter_select_obj10, LV_EVENT_ALL, flowState);
                    add_style_checkbox_default(obj);
                    lv_obj_set_style_radius(obj, 14, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_user_widget_event_filter_select(void *flowState, int startWidgetIndex) {
    {
        bool new_val = evalBooleanProperty(flowState, 4, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(((lv_obj_t **)&objects)[startWidgetIndex + 0], LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 0];
            if (new_val) lv_obj_add_state(((lv_obj_t **)&objects)[startWidgetIndex + 0], LV_STATE_CHECKED);
            else lv_obj_clear_state(((lv_obj_t **)&objects)[startWidgetIndex + 0], LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 5, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(((lv_obj_t **)&objects)[startWidgetIndex + 1], LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 1];
            if (new_val) lv_obj_add_state(((lv_obj_t **)&objects)[startWidgetIndex + 1], LV_STATE_CHECKED);
            else lv_obj_clear_state(((lv_obj_t **)&objects)[startWidgetIndex + 1], LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 6, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(((lv_obj_t **)&objects)[startWidgetIndex + 2], LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 2];
            if (new_val) lv_obj_add_state(((lv_obj_t **)&objects)[startWidgetIndex + 2], LV_STATE_CHECKED);
            else lv_obj_clear_state(((lv_obj_t **)&objects)[startWidgetIndex + 2], LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 7, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(((lv_obj_t **)&objects)[startWidgetIndex + 3], LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 3];
            if (new_val) lv_obj_add_state(((lv_obj_t **)&objects)[startWidgetIndex + 3], LV_STATE_CHECKED);
            else lv_obj_clear_state(((lv_obj_t **)&objects)[startWidgetIndex + 3], LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
}


extern void add_style(lv_obj_t *obj, int32_t styleIndex);
extern void remove_style(lv_obj_t *obj, int32_t styleIndex);

void ui_create_groups() {
    if (!groups_created) {
        groups.encoder_group = lv_group_create();
        eez_flow_init_groups((lv_group_t **)&groups, sizeof(groups) / sizeof(lv_group_t *));
        groups_created = true;
    }
}

static const char *screen_names[] = { "Startup", "Main", "Capacity", "Settings", "events", "Ranges", "NPLC", "protections", "calibration", "Fan", "Display", "Info", "Sound", "Stats", "Popup" };
static const char *object_names[] = { "startup", "main", "capacity", "settings", "events", "ranges", "nplc", "protections", "calibration", "fan", "display", "info", "sound", "stats", "popup", "obj0", "obj0__kbtext2", "obj0__obj2", "obj0__max_button", "obj0__min_button", "obj0__obj3", "obj0__obj4", "obj1", "obj1__kbtext2", "obj1__obj2", "obj1__max_button", "obj1__min_button", "obj1__obj3", "obj1__obj4", "obj2", "obj2__obj7", "obj2__obj8", "obj2__obj9", "obj2__obj10", "obj2__obj11", "obj2__obj12", "obj3", "obj3__sure_but_yes", "obj3__sure_but_no", "obj3__sure_label_yes", "obj3__sure_label_no", "obj3__obj0", "obj3__obj1", "obj4", "obj4__sure_but_yes", "obj4__sure_but_no", "obj4__sure_label_yes", "obj4__sure_label_no", "obj4__obj0", "obj4__obj1", "obj5", "obj5__kbtext2", "obj5__obj2", "obj5__max_button", "obj5__min_button", "obj5__obj3", "obj5__obj4", "obj6", "obj6__kbtext2", "obj6__obj2", "obj6__max_button", "obj6__min_button", "obj6__obj3", "obj6__obj4", "obj7", "obj7__sure_but_yes", "obj7__sure_but_no", "obj7__sure_label_yes", "obj7__sure_label_no", "obj7__obj0", "obj7__obj1", "obj8", "obj8__sure_but_yes", "obj8__sure_but_no", "obj8__sure_label_yes", "obj8__sure_label_no", "obj8__obj0", "obj8__obj1", "obj9", "obj9__sure_but_yes", "obj9__sure_but_no", "obj9__sure_label_yes", "obj9__sure_label_no", "obj9__obj0", "obj9__obj1", "obj10", "obj10__obj5", "obj10__obj6", "obj10__stat_min_17", "obj10__stat_min_last", "obj10__stat_min_min", "obj10__stat_min_avg", "obj10__stat_min_dev", "obj10__stat_min_max", "obj10__stat_min_count", "obj11", "obj11__obj5", "obj11__obj6", "obj11__stat_min_17", "obj11__stat_min_last", "obj11__stat_min_min", "obj11__stat_min_avg", "obj11__stat_min_dev", "obj11__stat_min_max", "obj11__stat_min_count", "obj12", "obj12__obj5", "obj12__obj6", "obj12__stat_min_17", "obj12__stat_min_last", "obj12__stat_min_min", "obj12__stat_min_avg", "obj12__stat_min_dev", "obj12__stat_min_max", "obj12__stat_min_count", "startup_ok", "myspinbox", "mode_selector", "on_off_button", "range_current", "obj13", "obj14", "range_volt", "obj15", "obj16", "obj17", "obj18", "wh", "obj19", "obj20", "obj21", "obj22", "obj23", "obj24", "obj25", "range_volt_1", "obj26", "range_curr_1", "obj27", "obj28", "obj29", "obj30", "obj31", "obj32", "on_off_button_1", "obj33", "obj34", "obj35", "obj36", "obj37", "obj38", "obj39", "obj40", "obj41", "obj42", "obj43", "obj44", "obj45", "obj46", "obj47", "obj48", "events_table", "obj49", "obj50", "obj51", "current_range", "volt_range", "sense", "nlpc_back", "nlpc_ok", "nlpc_cancel", "nplc_nplc", "pl_freq", "nlpc_home", "nlpc_home_cancel", "nlpc_home_cancel_1", "obj52", "obj53", "obj54", "obj55", "obj56", "obj57", "obj58", "obj59", "obj60", "obj61", "obj62", "obj63", "obj64", "obj65", "obj66", "obj67", "obj68", "obj69", "obj70", "obj71", "obj72", "obj73", "obj74", "nlpc_home_1", "nlpc_home_cancel_2", "nlpc_home_cancel_3", "nlpc_home_2", "nlpc_home_cancel_4", "nlpc_home_cancel_5", "obj75", "obj76", "obj77", "display_off", "nlpc_home_4", "nplc_nplc_1", "nlpc_home_3", "nlpc_home_cancel_6", "nlpc_home_cancel_7", "obj78", "obj79", "obj80", "obj81", "obj82", "obj83", "stats_back", "startup_start_status", "startup_eeprom", "startup_calibration", "startup_fans", "obj84", "main_measure", "sense_indicator", "obj85", "flex_panel", "capacity_panel", "ah", "montime", "stats_panel", "stat_min", "montime_3", "ah_10", "stat_avg", "stat_max", "montime_4", "main_lower_panel", "set_value", "isetlabel_1", "von_panel", "vonlabel", "protection_and_temp", "wheel", "main_dvm", "obj86", "main_short", "obj87", "vonlabel_1", "obj88", "obj89", "obj90", "obj91", "obj92", "obj93", "obj94", "obj95", "obj96", "obj97", "obj98", "obj99", "obj100", "obj101", "obj102", "obj103", "obj104", "obj105", "obj106", "ah_2", "ah_3", "ah_4", "ah_5", "ah_6", "ah_7", "obj107", "obj108", "obj109", "obj110", "obj111", "obj112", "obj113", "obj114", "obj115", "obj116", "obj117", "obj118", "obj119", "obj120", "obj121", "obj122", "obj123", "obj124", "obj125", "obj126", "obj127", "obj128", "obj129", "obj130", "obj131", "obj132", "obj133", "obj134", "obj135", "obj136", "obj137", "obj138", "obj139", "obj140", "obj141", "obj142", "obj143", "obj144", "obj145", "obj146", "obj147", "obj148", "obj149", "obj150", "obj151", "obj152", "obj153", "obj154", "obj155", "obj156", "obj157", "obj158", "obj159", "obj160", "obj161", "obj162", "obj163", "obj164", "obj165", "obj166", "obj167", "obj168", "obj169", "obj170", "obj171", "obj172", "obj173", "obj174", "obj175", "obj176", "obj177", "obj178", "obj179", "obj180", "obj181", "obj182", "obj183", "obj184", "obj185", "obj186", "obj187", "obj188", "obj189", "obj190", "obj191", "obj192", "obj193", "obj194", "stat_min_8", "stat_min_9", "stat_min_10", "stat_min_11", "stat_min_12", "stat_min_13", "obj195", "popup_container", "popup_box", "popup_text" };
static const char *group_names[] = { "encoder_group" };
static const char *style_names[] = { "button", "selectbutton", "selectButtonRedGreen", "selectButton90deg", "blackpanel", "bigfont_label", "bigfont Normal", "warning", "Title ", "slider", "small label", "small label_symbol", "extra small label", "small header", "buttonText", "buttonText90deg", "checkbox_default", "checkbox_small", "screen_background", "transparant_overlay", "selector small", "selector_with_disable", "spinbox_default", "label_red" };

void create_screens() {
    ui_create_groups();
    
    eez_flow_init_styles(add_style, remove_style);
    
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    eez_flow_init_group_names(group_names, sizeof(group_names) / sizeof(const char *));
    eez_flow_init_style_names(style_names, sizeof(style_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_startup();
    create_screen_main();
    create_screen_capacity();
    create_screen_settings();
    create_screen_events();
    create_screen_ranges();
    create_screen_nplc();
    create_screen_protections();
    create_screen_calibration();
    create_screen_fan();
    create_screen_display();
    create_screen_info();
    create_screen_sound();
    create_screen_stats();
    create_screen_popup();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_startup,
    tick_screen_main,
    tick_screen_capacity,
    tick_screen_settings,
    tick_screen_events,
    tick_screen_ranges,
    tick_screen_nplc,
    tick_screen_protections,
    tick_screen_calibration,
    tick_screen_fan,
    tick_screen_display,
    tick_screen_info,
    tick_screen_sound,
    tick_screen_stats,
    tick_screen_popup,
    0,
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

