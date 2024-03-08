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

static void event_handler_cb_main_on_of_f_button(lv_event_t *e) {
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

static void event_handler_cb_main_range_current(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 4, 0);
    }
}

static void event_handler_cb_main_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
}

static void event_handler_cb_main_range_volt(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 7, 0);
    }
}

static void event_handler_cb_main_obj8(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        action_toggle_record(e);
    }
}

static void event_handler_cb_main_wh(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 18, 0);
    }
}

static void event_handler_cb_main_obj10(lv_event_t *e) {
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

static void event_handler_cb_main_set_value_area(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_FOCUSED) {
        action_text_area_disable_blink(e);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 25, 1);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        const char *value = lv_textarea_get_text(ta);
        if (tick_value_change_obj != ta) {
            assignStringProperty(flowState, 25, 2, value, "Failed to assign Text in Textarea widget");
        }
    }
}

static void event_handler_cb_main_obj12(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 26, 0);
    }
}

static void event_handler_cb_main_obj13(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 30, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 30, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_obj15(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 32, 0);
    }
}

static void event_handler_cb_main_obj17(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 35, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 35, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_obj20(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 47, 0);
    }
}

static void event_handler_cb_capacity_obj26(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 0, 0);
    }
}

static void event_handler_cb_capacity_obj28(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 5, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 5, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_obj30(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 7, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 7, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_obj32(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 9, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 9, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_obj34(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 11, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 11, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_on_of_f_button_1(lv_event_t *e) {
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

static void event_handler_cb_capacity_obj37(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        action_toggle_record(e);
    }
}

static void event_handler_cb_capacity_obj39(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 25, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 25, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_obj41(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        action_clear_power(e);
    }
}

static void event_handler_cb_capacity_obj43(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        action_clear_capacity_limits(e);
    }
}

static void event_handler_cb_capacity_obj44(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
        if (tick_value_change_obj != ta) {
            assignBooleanProperty(flowState, 42, 2, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_settings_obj47(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 0, 0);
    }
}

static void event_handler_cb_settings_obj49(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 4, 0);
    }
}

static void event_handler_cb_settings_obj51(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 6, 0);
    }
}

static void event_handler_cb_settings_obj53(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 9, 0);
    }
}

static void event_handler_cb_settings_obj55(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 11, 0);
    }
}

static void event_handler_cb_settings_obj57(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 15, 0);
    }
}

static void event_handler_cb_settings_obj59(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 18, 0);
    }
}

static void event_handler_cb_settings_obj61(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 21, 0);
    }
}

static void event_handler_cb_settings_obj63(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 23, 0);
    }
}

static void event_handler_cb_events_obj66(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 0, 0);
    }
}

static void event_handler_cb_events_obj68(lv_event_t *e) {
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

static void event_handler_cb_protections_obj70(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 0, 0);
    }
}

static void event_handler_cb_protections_obj72(lv_event_t *e) {
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

static void event_handler_cb_protections_obj74(lv_event_t *e) {
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

static void event_handler_cb_protections_obj76(lv_event_t *e) {
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

static void event_handler_cb_protections_obj78(lv_event_t *e) {
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

static void event_handler_cb_protections_obj80(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 22, 0);
    }
}

static void event_handler_cb_protections_obj81(lv_event_t *e) {
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

static void event_handler_cb_protections_obj83(lv_event_t *e) {
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

static void event_handler_cb_calibration_obj87(lv_event_t *e) {
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

static void event_handler_cb_calibration_obj88(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 3, 0);
    }
}

static void event_handler_cb_calibration_obj92(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 8, 0);
    }
}

static void event_handler_cb_calibration_obj93(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 10, 0);
    }
}

static void event_handler_cb_calibration_obj94(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
}

static void event_handler_cb_calibration_obj95(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 12, 0);
    }
}

static void event_handler_cb_calibration_obj97(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 14, 0);
    }
}

static void event_handler_cb_calibration_obj98(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
}

static void event_handler_cb_calibration_obj100(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 18, 0);
    }
}

static void event_handler_cb_calibration_obj101(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 19, 0);
    }
}

static void event_handler_cb_calibration_obj102(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 27, 0);
    }
}

static void event_handler_cb_calibration_obj103(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 28, 0);
    }
}

static void event_handler_cb_nplc_nlpc_home(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 5, 0);
    }
}

static void event_handler_cb_nplc_nlpc_home_cancel(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 11, 0);
    }
}

static void event_handler_cb_nplc_nlpc_home_cancel_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 13, 0);
    }
}

static void event_handler_cb_nplc_obj110(lv_event_t *e) {
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

static void event_handler_cb_nplc_obj111(lv_event_t *e) {
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

static void event_handler_cb_fan_nlpc_home_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 5, 0);
    }
}

static void event_handler_cb_fan_obj119(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_SCREEN_LOADED) {
        flowPropagateValue(flowState, 9, 0);
    }
}

static void event_handler_cb_fan_nlpc_home_cancel_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 11, 0);
    }
}

static void event_handler_cb_fan_nlpc_home_cancel_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 13, 0);
    }
}

static void event_handler_cb_fan_obj123(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 15, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        int32_t value = lv_slider_get_value(ta);
        if (tick_value_change_obj != ta) {
            assignIntegerProperty(flowState, 15, 3, value, "Failed to assign Value in Slider widget");
        }
    }
}

static void event_handler_cb_fan_obj125(lv_event_t *e) {
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

static void event_handler_cb_display_nlpc_home_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 5, 0);
    }
}

static void event_handler_cb_display_obj129(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_SCREEN_LOADED) {
        flowPropagateValue(flowState, 8, 0);
    }
}

static void event_handler_cb_display_nlpc_home_cancel_4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 9, 0);
    }
}

static void event_handler_cb_display_nlpc_home_cancel_5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 11, 0);
    }
}

static void event_handler_cb_display_obj132(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 13, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        int32_t value = lv_slider_get_value(ta);
        if (tick_value_change_obj != ta) {
            assignIntegerProperty(flowState, 13, 3, value, "Failed to assign Value in Slider widget");
        }
    }
}

static void event_handler_cb_display_obj134(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 15, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        int32_t value = lv_dropdown_get_selected(ta);
        if (tick_value_change_obj != ta) {
            assignIntegerProperty(flowState, 15, 2, value, "Failed to assign Selected in Dropdown widget");
        }
    }
}

static void event_handler_cb_display_obj136(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 21, 0);
    }
}

static void event_handler_cb_display_display_off(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 30, 0);
    }
}

static void event_handler_cb_question_yn_obj114(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 0, 0);
    }
}

static void event_handler_cb_question_yn_obj115(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 3, 0);
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

static void event_handler_cb_keyboard_obj24(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_READY) {
        flowPropagateValue(flowState, 3, 0);
    }
    if (event == LV_EVENT_CANCEL) {
        flowPropagateValue(flowState, 3, 1);
    }
}

static void event_handler_cb_keyboard_max_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 16, 0);
    }
}

static void event_handler_cb_keyboard_min_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 18, 0);
    }
}

static void event_handler_cb_keyboard_old2_kbtext2_1(lv_event_t *e) {
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

static void event_handler_cb_keyboard_old2_obj139(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_READY) {
        flowPropagateValue(flowState, 3, 0);
    }
    if (event == LV_EVENT_CANCEL) {
        flowPropagateValue(flowState, 3, 1);
    }
}

static void event_handler_cb_keyboard_old2_max_button_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 16, 0);
    }
}

static void event_handler_cb_keyboard_old2_min_button_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 18, 0);
    }
}

void create_screen_startup() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.startup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffaaaaaa), LV_PART_MAIN | LV_STATE_DEFAULT);
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
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 3, 42);
            lv_obj_set_size(obj, 314, 194);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            lv_obj_set_pos(obj, 2, 2);
            lv_obj_set_size(obj, 130, 38);
            lv_dropdown_set_options(obj, "Mode CC\nMode CV\nMode CP\nMode CR\nSHORT");
            lv_obj_add_event_cb(obj, event_handler_cb_main_mode_selector, LV_EVENT_ALL, flowState);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff818181), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff111111), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffcccccc), LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff404040), LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
        }
        {
            // ON-OFF button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.on_of_f_button = obj;
            lv_obj_set_pos(obj, -2, 2);
            lv_obj_set_size(obj, 109, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_main_on_of_f_button, LV_EVENT_ALL, flowState);
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
            lv_obj_set_pos(obj, 0, 43);
            lv_obj_set_size(obj, 320, 75);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_blackpanel(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // RangeCurrent
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.range_current = obj;
                    lv_obj_set_pos(obj, -13, -13);
                    lv_obj_set_size(obj, 24, 37);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_range_current, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_select_button90deg(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj2 = obj;
                            lv_obj_set_pos(obj, 2, 1);
                            lv_obj_set_size(obj, 21, 37);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj2, LV_EVENT_ALL, flowState);
                            apply_style_button_text90deg(obj);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj3 = obj;
                    lv_obj_set_pos(obj, 11, -10);
                    lv_obj_set_size(obj, 136, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
                }
                {
                    // RangeVolt
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.range_volt = obj;
                    lv_obj_set_pos(obj, 283, -13);
                    lv_obj_set_size(obj, 24, 37);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_range_volt, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_select_button90deg(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj4 = obj;
                            lv_obj_set_pos(obj, 2, 1);
                            lv_obj_set_size(obj, 21, 37);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            apply_style_button_text90deg(obj);
                        }
                    }
                }
                {
                    // SenseIndicator
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.sense_indicator = obj;
                    lv_obj_set_pos(obj, 171, 18);
                    lv_obj_set_size(obj, 105, 4);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_blackpanel(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DISABLED);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj5 = obj;
                    lv_obj_set_pos(obj, 147, -10);
                    lv_obj_set_size(obj, 136, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj6 = obj;
                    lv_obj_set_pos(obj, -13, 24);
                    lv_obj_set_size(obj, 160, 36);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj7 = obj;
                    lv_obj_set_pos(obj, 147, 24);
                    lv_obj_set_size(obj, 160, 36);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
                }
            }
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
                    objects.obj8 = obj;
                    lv_obj_set_pos(obj, -11, 1);
                    lv_obj_set_size(obj, 32, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj8, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj9 = obj;
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
                    lv_obj_set_pos(obj, 21, -12);
                    lv_obj_set_size(obj, 140, 21);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    apply_style_small_label(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // Wh
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wh = obj;
                    lv_obj_set_pos(obj, 21, 9);
                    lv_obj_set_size(obj, 140, 21);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_main_wh, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_small_label(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // montime
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.montime = obj;
                    lv_obj_set_pos(obj, 164, 0);
                    lv_obj_set_size(obj, 92, 21);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    apply_style_small_label(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj10 = obj;
                    lv_obj_set_pos(obj, 11, 1);
                    lv_obj_set_size(obj, 38, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj10, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    apply_style_select_button_red_green(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_RIGHT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj11 = obj;
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
                            objects.obj12 = obj;
                            lv_obj_set_pos(obj, 109, 14);
                            lv_obj_set_size(obj, 38, 36);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj12, LV_EVENT_ALL, flowState);
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
                                    objects.obj13 = obj;
                                    lv_obj_set_pos(obj, -12, 12);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj13, LV_EVENT_ALL, flowState);
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
                                            objects.obj14 = obj;
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
                                    objects.obj15 = obj;
                                    lv_obj_set_pos(obj, -12, 36);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj15, LV_EVENT_ALL, flowState);
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
                                            objects.obj16 = obj;
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
                            apply_style_blackpanel(obj);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.obj17 = obj;
                                    lv_obj_set_pos(obj, -2, -9);
                                    lv_obj_set_size(obj, 55, 34);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj17, LV_EVENT_ALL, flowState);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    apply_style_select_button_red_green(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj18 = obj;
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
                                    objects.obj19 = obj;
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
            lv_obj_set_pos(obj, 133, 27);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj20 = obj;
            lv_obj_set_pos(obj, 11, 2);
            lv_obj_set_size(obj, 58, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj20, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj21 = obj;
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
            objects.obj22 = obj;
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
            create_user_widget_keyboard(obj, getFlowState(flowState, 56), 98);
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
        bool cur_val = lv_obj_has_state(objects.on_of_f_button, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_of_f_button;
            if (new_val) lv_obj_add_state(objects.on_of_f_button, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.on_of_f_button, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 0, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.on_of_f_button, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_of_f_button;
            if (new_val) lv_obj_add_state(objects.on_of_f_button, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.on_of_f_button, LV_STATE_DISABLED);
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
        bool new_val = evalBooleanProperty(flowState, 4, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.range_current, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.range_current;
            if (new_val) lv_obj_add_state(objects.range_current, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.range_current, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 5, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj2, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj2;
            if (new_val) lv_obj_add_state(objects.obj2, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj2, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj2;
            lv_label_set_text(objects.obj2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 6, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj3);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj3;
            lv_label_set_text(objects.obj3, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 7, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.range_volt, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.range_volt;
            if (new_val) lv_obj_add_state(objects.range_volt, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.range_volt, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 8, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj4);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj4;
            lv_label_set_text(objects.obj4, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 9, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sense_indicator, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sense_indicator;
            if (new_val) lv_obj_add_flag(objects.sense_indicator, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.sense_indicator, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj5);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj5;
            lv_label_set_text(objects.obj5, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj6);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj6;
            lv_label_set_text(objects.obj6, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj7);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj7;
            lv_label_set_text(objects.obj7, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj9);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj9;
            lv_label_set_text(objects.obj9, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah;
            lv_label_set_text(objects.ah, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wh);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wh;
            lv_label_set_text(objects.wh, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.montime);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.montime;
            lv_label_set_text(objects.montime, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj10, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj10;
            if (new_val) lv_obj_add_state(objects.obj10, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj10, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 21, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj11);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj11;
            lv_label_set_text(objects.obj11, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 23, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.iset, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.iset;
            if (new_val) lv_obj_add_flag(objects.iset, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.iset, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.isetlabel);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.isetlabel;
            lv_label_set_text(objects.isetlabel, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 25, 2, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.set_value_area);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.set_value_area;
            lv_textarea_set_text(objects.set_value_area, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 26, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj12);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj12;
            lv_label_set_text(objects.obj12, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 30, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj13, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj13;
            if (new_val) lv_obj_add_state(objects.obj13, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj13, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 31, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj14);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj14;
            lv_label_set_text(objects.obj14, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 33, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj16);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj16;
            lv_label_set_text(objects.obj16, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 35, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj17, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj17;
            if (new_val) lv_obj_add_state(objects.obj17, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj17, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 36, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj18);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj18;
            lv_label_set_text(objects.obj18, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 37, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj19);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj19;
            lv_label_set_text(objects.obj19, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 39, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.wheel;
            if (new_val) lv_obj_add_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 48, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj21);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj21;
            lv_label_set_text(objects.obj21, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 56, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj22, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj22;
            if (new_val) lv_obj_add_flag(objects.obj22, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj22, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 56), 98);
}

void create_screen_capacity() {
    void *flowState = getFlowState(0, 2);
    lv_obj_t *obj = lv_obj_create(0);
    objects.capacity = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj25 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 25);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj26 = obj;
            lv_obj_set_pos(obj, -2, -2);
            lv_obj_set_size(obj, 55, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj26, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj27 = obj;
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
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj28 = obj;
            lv_obj_set_pos(obj, 204, 174);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj28, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj29 = obj;
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
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj31 = obj;
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
            lv_obj_set_pos(obj, 204, 124);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj32, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj33 = obj;
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
            objects.obj34 = obj;
            lv_obj_set_pos(obj, 204, 100);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj34, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj35 = obj;
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
            apply_style_small_label(obj);
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
            apply_style_small_label(obj);
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
            apply_style_small_label(obj);
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
            apply_style_small_label(obj);
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
            apply_style_small_label(obj);
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
            apply_style_small_label(obj);
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
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // ON-OFF button_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.on_of_f_button_1 = obj;
            lv_obj_set_pos(obj, 2, -2);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_on_of_f_button_1, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_button(obj);
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
                    objects.obj36 = obj;
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
            objects.obj37 = obj;
            lv_obj_set_pos(obj, 2, -77);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj37, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj38 = obj;
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
            objects.obj39 = obj;
            lv_obj_set_pos(obj, -32, -2);
            lv_obj_set_size(obj, 55, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj39, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj40 = obj;
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
            objects.obj41 = obj;
            lv_obj_set_pos(obj, -142, -148);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj41, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj42 = obj;
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
            objects.obj43 = obj;
            lv_obj_set_pos(obj, 51, -2);
            lv_obj_set_size(obj, 88, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj43, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
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
            objects.obj44 = obj;
            lv_obj_set_pos(obj, 2, 97);
            lv_obj_set_size(obj, 187, 28);
            lv_checkbox_set_text(obj, "    Volt stop:");
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj44, LV_EVENT_ALL, flowState);
            apply_style_checkbox_default(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj45 = obj;
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
            create_user_widget_keyboard(obj, getFlowState(flowState, 43), 126);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 94);
            lv_obj_set_size(obj, 320, 2);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff828282), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_capacity() {
    void *flowState = getFlowState(0, 2);
    {
        const char *new_val = evalTextProperty(flowState, 1, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj25);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj25;
            lv_label_set_text(objects.obj25, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj27);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj27;
            lv_label_set_text(objects.obj27, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 5, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj28, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj28;
            if (new_val) lv_obj_add_state(objects.obj28, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj28, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 5, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj28, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj28;
            if (new_val) lv_obj_add_state(objects.obj28, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj28, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 6, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj29);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj29;
            lv_label_set_text(objects.obj29, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 7, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj30, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj30;
            if (new_val) lv_obj_add_state(objects.obj30, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj30, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 7, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj30, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj30;
            if (new_val) lv_obj_add_state(objects.obj30, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj30, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 8, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj31);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj31;
            lv_label_set_text(objects.obj31, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 9, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj32, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj32;
            if (new_val) lv_obj_add_state(objects.obj32, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj32, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 9, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj32, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj32;
            if (new_val) lv_obj_add_state(objects.obj32, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj32, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj33);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj33;
            lv_label_set_text(objects.obj33, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 11, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj34, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj34;
            if (new_val) lv_obj_add_state(objects.obj34, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj34, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 11, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj34, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj34;
            if (new_val) lv_obj_add_state(objects.obj34, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj34, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj35);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj35;
            lv_label_set_text(objects.obj35, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 14, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_2;
            lv_label_set_text(objects.ah_2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 15, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_3);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_3;
            lv_label_set_text(objects.ah_3, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_4);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_4;
            lv_label_set_text(objects.ah_4, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_5);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_5;
            lv_label_set_text(objects.ah_5, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_6);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_6;
            lv_label_set_text(objects.ah_6, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah_7);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah_7;
            lv_label_set_text(objects.ah_7, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.on_of_f_button_1, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_of_f_button_1;
            if (new_val) lv_obj_add_state(objects.on_of_f_button_1, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.on_of_f_button_1, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.on_of_f_button_1, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_of_f_button_1;
            if (new_val) lv_obj_add_state(objects.on_of_f_button_1, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.on_of_f_button_1, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 21, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj36);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj36;
            lv_label_set_text(objects.obj36, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj38);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj38;
            lv_label_set_text(objects.obj38, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 25, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj39, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj39;
            if (new_val) lv_obj_add_state(objects.obj39, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj39, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 26, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj40);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj40;
            lv_label_set_text(objects.obj40, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 39, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj42);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj42;
            lv_label_set_text(objects.obj42, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 42, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj44, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj44;
            if (new_val) lv_obj_add_state(objects.obj44, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj44, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 43, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj45, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj45;
            if (new_val) lv_obj_add_flag(objects.obj45, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj45, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 43), 126);
}

void create_screen_settings() {
    void *flowState = getFlowState(0, 3);
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj46 = obj;
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
            objects.obj47 = obj;
            lv_obj_set_pos(obj, 206, 206);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj47, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj48 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj49 = obj;
            lv_obj_set_pos(obj, 9, 206);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj49, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj50 = obj;
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
            objects.obj51 = obj;
            lv_obj_set_pos(obj, 9, 134);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj51, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj52 = obj;
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
            objects.obj53 = obj;
            lv_obj_set_pos(obj, 9, 170);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj53, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj54 = obj;
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
            objects.obj55 = obj;
            lv_obj_set_pos(obj, 9, 98);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj55, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj56 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    apply_style_button_text(obj);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj57 = obj;
            lv_obj_set_pos(obj, 206, 170);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj57, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj58 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj59 = obj;
            lv_obj_set_pos(obj, 206, 134);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj59, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj60 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj61 = obj;
            lv_obj_set_pos(obj, 9, 62);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj61, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj62 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    apply_style_button_text(obj);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj63 = obj;
            lv_obj_set_pos(obj, 9, 27);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj63, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj64 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    apply_style_button_text(obj);
                }
            }
        }
    }
}

void tick_screen_settings() {
    void *flowState = getFlowState(0, 3);
    {
        const char *new_val = evalTextProperty(flowState, 1, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj46);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj46;
            lv_label_set_text(objects.obj46, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj48);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj48;
            lv_label_set_text(objects.obj48, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj50);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj50;
            lv_label_set_text(objects.obj50, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj52);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj52;
            lv_label_set_text(objects.obj52, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj54);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj54;
            lv_label_set_text(objects.obj54, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj56);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj56;
            lv_label_set_text(objects.obj56, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj58);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj58;
            lv_label_set_text(objects.obj58, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj60);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj60;
            lv_label_set_text(objects.obj60, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj62);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj62;
            lv_label_set_text(objects.obj62, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj64);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj64;
            lv_label_set_text(objects.obj64, new_val);
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
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj65 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 25);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj66 = obj;
            lv_obj_set_pos(obj, 225, 200);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_events_obj66, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj67 = obj;
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
            objects.obj68 = obj;
            lv_obj_set_pos(obj, 3, 26);
            lv_obj_set_size(obj, 314, 161);
            lv_textarea_set_max_length(obj, 500);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_events_obj68, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_events() {
    void *flowState = getFlowState(0, 4);
    {
        const char *new_val = evalTextProperty(flowState, 1, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj65);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj65;
            lv_label_set_text(objects.obj65, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj67);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj67;
            lv_label_set_text(objects.obj67, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 2, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.obj68);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj68;
            lv_textarea_set_text(objects.obj68, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_protections() {
    void *flowState = getFlowState(0, 5);
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
            objects.obj69 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 26);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj70 = obj;
            lv_obj_set_pos(obj, 212, 200);
            lv_obj_set_size(obj, 90, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj70, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj71 = obj;
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
            objects.obj72 = obj;
            lv_obj_set_pos(obj, 160, 32);
            lv_obj_set_size(obj, 142, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj72, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj73 = obj;
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
            objects.obj74 = obj;
            lv_obj_set_pos(obj, 160, 73);
            lv_obj_set_size(obj, 142, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj74, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj75 = obj;
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
            objects.obj76 = obj;
            lv_obj_set_pos(obj, 160, 117);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj76, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj77 = obj;
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
            objects.obj78 = obj;
            lv_obj_set_pos(obj, 237, 117);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj78, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj79 = obj;
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
            objects.obj80 = obj;
            lv_obj_set_pos(obj, 22, 200);
            lv_obj_set_size(obj, 164, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj80, LV_EVENT_ALL, flowState);
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
            objects.obj81 = obj;
            lv_obj_set_pos(obj, 160, 156);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj81, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj82 = obj;
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
            objects.obj83 = obj;
            lv_obj_set_pos(obj, 237, 156);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj83, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj84 = obj;
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
            objects.obj85 = obj;
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
            create_user_widget_keyboard(obj, getFlowState(flowState, 28), 175);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
    }
}

void tick_screen_protections() {
    void *flowState = getFlowState(0, 5);
    {
        const char *new_val = evalTextProperty(flowState, 1, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj69);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj69;
            lv_label_set_text(objects.obj69, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj71);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj71;
            lv_label_set_text(objects.obj71, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 8, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj72, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj72;
            if (new_val) lv_obj_add_state(objects.obj72, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj72, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 9, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj73);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj73;
            lv_label_set_text(objects.obj73, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 10, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj74, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj74;
            if (new_val) lv_obj_add_state(objects.obj74, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj74, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj75);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj75;
            lv_label_set_text(objects.obj75, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 18, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj76, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj76;
            if (new_val) lv_obj_add_state(objects.obj76, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj76, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj77);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj77;
            lv_label_set_text(objects.obj77, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj78, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj78;
            if (new_val) lv_obj_add_state(objects.obj78, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj78, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 21, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj79);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj79;
            lv_label_set_text(objects.obj79, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 22, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj80, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj80;
            if (new_val) lv_obj_add_state(objects.obj80, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj80, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 24, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj81, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj81;
            if (new_val) lv_obj_add_state(objects.obj81, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj81, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 25, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj82);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj82;
            lv_label_set_text(objects.obj82, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 26, 2, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj83, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj83;
            if (new_val) lv_obj_add_state(objects.obj83, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj83, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 27, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj84);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj84;
            lv_label_set_text(objects.obj84, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 28, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj85, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj85;
            if (new_val) lv_obj_add_flag(objects.obj85, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj85, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 28), 175);
}

void create_screen_calibration() {
    void *flowState = getFlowState(0, 6);
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
            objects.obj86 = obj;
            lv_obj_set_pos(obj, 0, 1);
            lv_obj_set_size(obj, 320, 27);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.obj87 = obj;
            lv_obj_set_pos(obj, 0, 28);
            lv_obj_set_size(obj, 320, LV_SIZE_CONTENT);
            lv_dropdown_set_options(obj, "Current Monitor High\nCurrent Monitor Low\nVoltage Monitor High\nVoltage Monitor Low\nCurrent Set High\nCurrent Set Low\nVoltage Set High\nVoltage Set Low\nVon Set High\nVon Set Low\nOCP set High\nOCP set Low\nOVP set High\nOVP set Low");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj87, LV_EVENT_ALL, flowState);
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
            objects.obj88 = obj;
            lv_obj_set_pos(obj, 166, 98);
            lv_obj_set_size(obj, 97, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj88, LV_EVENT_ALL, flowState);
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
                    objects.obj89 = obj;
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
            objects.obj90 = obj;
            lv_obj_set_pos(obj, 0, 70);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_label_set_text(obj, "");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj91 = obj;
            lv_obj_set_pos(obj, 160, 172);
            lv_obj_set_size(obj, 109, 25);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj92 = obj;
            lv_obj_set_pos(obj, 10, 206);
            lv_obj_set_size(obj, 90, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj92, LV_EVENT_ALL, flowState);
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
                    lv_label_set_text(obj, "Init \nEEPROM");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj93 = obj;
            lv_obj_set_pos(obj, 198, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj93, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj94 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 45, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj94, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj95 = obj;
            lv_obj_set_pos(obj, 126, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj95, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj96 = obj;
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
            objects.obj97 = obj;
            lv_obj_set_pos(obj, 269, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj97, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj98 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 45, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj98, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj99 = obj;
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
            objects.obj100 = obj;
            lv_obj_set_pos(obj, 136, 173);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj100, LV_EVENT_ALL, flowState);
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
            objects.obj101 = obj;
            lv_obj_set_pos(obj, 268, 172);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj101, LV_EVENT_ALL, flowState);
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
            objects.obj102 = obj;
            lv_obj_set_pos(obj, 278, 140);
            lv_obj_set_size(obj, 26, 26);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj102, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            apply_style_small_label_symbol(obj);
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
            objects.obj103 = obj;
            lv_obj_set_pos(obj, 114, 140);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj103, LV_EVENT_ALL, flowState);
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
            objects.obj104 = obj;
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
            create_user_widget_keyboard(obj, getFlowState(flowState, 29), 41);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        }
    }
}

void tick_screen_calibration() {
    void *flowState = getFlowState(0, 6);
    {
        const char *new_val = evalTextProperty(flowState, 1, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj86);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj86;
            lv_label_set_text(objects.obj86, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 0, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj87, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj87;
            if (new_val) lv_obj_add_state(objects.obj87, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj87, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 0, 3, "Failed to evaluate Selected in Dropdown widget");
        int32_t cur_val = lv_dropdown_get_selected(objects.obj87);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj87;
            lv_dropdown_set_selected(objects.obj87, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj89);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj89;
            lv_label_set_text(objects.obj89, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 6, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj90);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj90;
            lv_label_set_text(objects.obj90, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj91);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj91;
            lv_label_set_text(objects.obj91, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 10, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj93, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj93;
            if (new_val) lv_obj_add_state(objects.obj93, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj93, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 11, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj94, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj94;
            if (new_val) lv_obj_add_state(objects.obj94, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj94, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj94);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj94;
            lv_label_set_text(objects.obj94, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 12, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj95, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj95;
            if (new_val) lv_obj_add_state(objects.obj95, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj95, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 13, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj96);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj96;
            lv_label_set_text(objects.obj96, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 14, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj97, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj97;
            if (new_val) lv_obj_add_state(objects.obj97, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj97, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 15, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj98, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj98;
            if (new_val) lv_obj_add_state(objects.obj98, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj98, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 15, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj98);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj98;
            lv_label_set_text(objects.obj98, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj99);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj99;
            lv_label_set_text(objects.obj99, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 18, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj100, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj100;
            if (new_val) lv_obj_add_state(objects.obj100, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj100, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj100);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj100;
            lv_label_set_text(objects.obj100, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 19, 2, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj101, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj101;
            if (new_val) lv_obj_add_state(objects.obj101, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj101, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj101);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj101;
            lv_label_set_text(objects.obj101, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 27, 2, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj102);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj102;
            lv_label_set_text(objects.obj102, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 28, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj103, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj103;
            if (new_val) lv_obj_add_flag(objects.obj103, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj103, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 28, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj103);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj103;
            lv_label_set_text(objects.obj103, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 29, 2, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj104, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj104;
            if (new_val) lv_obj_add_flag(objects.obj104, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj104, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 29), 41);
    {
        float timeline_position = getTimelinePosition(flowState);
        
        static struct {
            float last_timeline_position;
            int32_t obj_obj102_rotate_init_value;
        } anim_state = { -1 };
        
        if (anim_state.last_timeline_position == -1) {
            anim_state.last_timeline_position = 0;
            anim_state.obj_obj102_rotate_init_value = lv_obj_get_style_prop(objects.obj102, LV_PART_MAIN, LV_STYLE_TRANSFORM_ANGLE).num;
        }
        
        if (timeline_position != anim_state.last_timeline_position) {
            anim_state.last_timeline_position = timeline_position;
            
            {
                lv_obj_t *obj = objects.obj102;
                
                float rotate_value = anim_state.obj_obj102_rotate_init_value;
                
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
    
    void create_screen_nplc() {
        void *flowState = getFlowState(0, 7);
        lv_obj_t *obj = lv_obj_create(0);
        objects.nplc = obj;
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
                objects.nlpc_home = obj;
                lv_obj_set_pos(obj, 225, 190);
                lv_obj_set_size(obj, 90, 38);
                lv_obj_add_event_cb(obj, event_handler_cb_nplc_nlpc_home, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj105 = obj;
                        lv_obj_set_pos(obj, 0, 0);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj106 = obj;
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
                objects.obj107 = obj;
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
                objects.nlpc_home_cancel = obj;
                lv_obj_set_pos(obj, 115, 191);
                lv_obj_set_size(obj, 90, 38);
                lv_obj_add_event_cb(obj, event_handler_cb_nplc_nlpc_home_cancel, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj108 = obj;
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
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj109 = obj;
                        lv_obj_set_pos(obj, 3, -1);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_slider_create(parent_obj);
                objects.obj110 = obj;
                lv_obj_set_pos(obj, 141, 117);
                lv_obj_set_size(obj, 166, 10);
                lv_slider_set_range(obj, 1, 100);
                lv_obj_add_event_cb(obj, event_handler_cb_nplc_obj110, LV_EVENT_ALL, flowState);
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
                objects.obj111 = obj;
                lv_obj_set_pos(obj, 101, 28);
                lv_obj_set_size(obj, 80, 36);
                lv_dropdown_set_options(obj, "50 Hz\n60 Hz");
                lv_obj_add_event_cb(obj, event_handler_cb_nplc_obj111, LV_EVENT_ALL, flowState);
                apply_style_selector_small(obj);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj112 = obj;
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
                objects.obj113 = obj;
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
                create_user_widget_question_yn(obj, getFlowState(flowState, 25), 56);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            }
        }
    }
    
    void tick_screen_nplc() {
        void *flowState = getFlowState(0, 7);
        {
            const char *new_val = evalTextProperty(flowState, 6, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj105);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj105;
                lv_label_set_text(objects.obj105, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 8, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj106);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj106;
                lv_label_set_text(objects.obj106, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 10, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj107);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj107;
                lv_label_set_text(objects.obj107, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 11, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.nlpc_home_cancel;
                if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.nlpc_home_cancel, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 12, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj108);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj108;
                lv_label_set_text(objects.obj108, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 13, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_1, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.nlpc_home_cancel_1;
                if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_1, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.nlpc_home_cancel_1, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 14, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj109);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj109;
                lv_label_set_text(objects.obj109, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            int32_t new_val = evalIntegerProperty(flowState, 15, 2, "Failed to evaluate Value in Slider widget");
            int32_t cur_val = lv_slider_get_value(objects.obj110);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj110;
                lv_slider_set_value(objects.obj110, new_val, LV_ANIM_OFF);
                tick_value_change_obj = NULL;
            }
        }
        {
            int32_t new_val = evalIntegerProperty(flowState, 19, 2, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj111);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj111;
                lv_dropdown_set_selected(objects.obj111, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 20, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj112);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj112;
                lv_label_set_text(objects.obj112, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 25, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj113, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj113;
                if (new_val) lv_obj_add_flag(objects.obj113, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj113, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        tick_user_widget_question_yn(getFlowState(flowState, 25), 56);
    }
    
    void create_screen_fan() {
        void *flowState = getFlowState(0, 8);
        lv_obj_t *obj = lv_obj_create(0);
        objects.fan = obj;
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
                lv_obj_set_pos(obj, 6, 34);
                lv_obj_set_size(obj, 109, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Mode:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                // NLPC_HOME_1
                lv_obj_t *obj = lv_btn_create(parent_obj);
                objects.nlpc_home_1 = obj;
                lv_obj_set_pos(obj, 225, 190);
                lv_obj_set_size(obj, 90, 38);
                lv_obj_add_event_cb(obj, event_handler_cb_fan_nlpc_home_1, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj117 = obj;
                        lv_obj_set_pos(obj, 0, 0);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj118 = obj;
                lv_obj_set_pos(obj, 127, 144);
                lv_obj_set_size(obj, 204, 24);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DISABLED);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DISABLED);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj119 = obj;
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 24);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Fan Settings");
                lv_obj_add_event_cb(obj, event_handler_cb_fan_obj119, LV_EVENT_ALL, flowState);
                apply_style_small_header(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj120 = obj;
                lv_obj_set_pos(obj, 127, 73);
                lv_obj_set_size(obj, 193, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                // NLPC_HOME_CANCEL_2
                lv_obj_t *obj = lv_btn_create(parent_obj);
                objects.nlpc_home_cancel_2 = obj;
                lv_obj_set_pos(obj, 115, 191);
                lv_obj_set_size(obj, 90, 38);
                lv_obj_add_event_cb(obj, event_handler_cb_fan_nlpc_home_cancel_2, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj121 = obj;
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
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj122 = obj;
                        lv_obj_set_pos(obj, 3, -1);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_slider_create(parent_obj);
                objects.obj123 = obj;
                lv_obj_set_pos(obj, 127, 117);
                lv_obj_set_size(obj, 180, 10);
                lv_obj_add_event_cb(obj, event_handler_cb_fan_obj123, LV_EVENT_ALL, flowState);
                apply_style_slider(obj);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                lv_obj_set_pos(obj, 1, 73);
                lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Speed:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj124 = obj;
                lv_obj_set_pos(obj, 1, 110);
                lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Set speed:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                lv_obj_set_pos(obj, 1, 144);
                lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Temp:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_dropdown_create(parent_obj);
                objects.obj125 = obj;
                lv_obj_set_pos(obj, 160, 28);
                lv_obj_set_size(obj, 102, 36);
                lv_dropdown_set_options(obj, "Auto\nManual");
                lv_obj_add_event_cb(obj, event_handler_cb_fan_obj125, LV_EVENT_ALL, flowState);
                apply_style_selector_small(obj);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj126 = obj;
                lv_obj_set_pos(obj, 189, 110);
                lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "");
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE);
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_obj_create(parent_obj);
                objects.obj127 = obj;
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
                create_user_widget_question_yn(obj, getFlowState(flowState, 25), 71);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            }
        }
    }
    
    void tick_screen_fan() {
        void *flowState = getFlowState(0, 8);
        {
            const char *new_val = evalTextProperty(flowState, 6, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj117);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj117;
                lv_label_set_text(objects.obj117, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 8, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj118);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj118;
                lv_label_set_text(objects.obj118, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 10, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj120);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj120;
                lv_label_set_text(objects.obj120, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 11, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_2, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.nlpc_home_cancel_2;
                if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_2, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.nlpc_home_cancel_2, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 12, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj121);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj121;
                lv_label_set_text(objects.obj121, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 13, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_3, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.nlpc_home_cancel_3;
                if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_3, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.nlpc_home_cancel_3, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 14, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj122);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj122;
                lv_label_set_text(objects.obj122, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 15, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj123, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj123;
                if (new_val) lv_obj_add_flag(objects.obj123, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj123, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            int32_t new_val = evalIntegerProperty(flowState, 15, 3, "Failed to evaluate Value in Slider widget");
            int32_t cur_val = lv_slider_get_value(objects.obj123);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj123;
                lv_slider_set_value(objects.obj123, new_val, LV_ANIM_OFF);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 17, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj124, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj124;
                if (new_val) lv_obj_add_flag(objects.obj124, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj124, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            int32_t new_val = evalIntegerProperty(flowState, 19, 2, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj125);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj125;
                lv_dropdown_set_selected(objects.obj125, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 20, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj126, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj126;
                if (new_val) lv_obj_add_flag(objects.obj126, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj126, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj126);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj126;
                lv_label_set_text(objects.obj126, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 25, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj127, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj127;
                if (new_val) lv_obj_add_flag(objects.obj127, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj127, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        tick_user_widget_question_yn(getFlowState(flowState, 25), 71);
    }
    
    void create_screen_display() {
        void *flowState = getFlowState(0, 9);
        lv_obj_t *obj = lv_obj_create(0);
        objects.display = obj;
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
                lv_obj_set_pos(obj, 6, 34);
                lv_obj_set_size(obj, 109, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Mode:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                // NLPC_HOME_2
                lv_obj_t *obj = lv_btn_create(parent_obj);
                objects.nlpc_home_2 = obj;
                lv_obj_set_pos(obj, 225, 190);
                lv_obj_set_size(obj, 90, 38);
                lv_obj_add_event_cb(obj, event_handler_cb_display_nlpc_home_2, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj128 = obj;
                        lv_obj_set_pos(obj, 0, 0);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj129 = obj;
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 24);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Display Settings");
                lv_obj_add_event_cb(obj, event_handler_cb_display_obj129, LV_EVENT_ALL, flowState);
                apply_style_small_header(obj);
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
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj130 = obj;
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
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj131 = obj;
                        lv_obj_set_pos(obj, 3, -1);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_slider_create(parent_obj);
                objects.obj132 = obj;
                lv_obj_set_pos(obj, 131, 80);
                lv_obj_set_size(obj, 180, 10);
                lv_obj_add_event_cb(obj, event_handler_cb_display_obj132, LV_EVENT_ALL, flowState);
                apply_style_slider(obj);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj133 = obj;
                lv_obj_set_pos(obj, 1, 73);
                lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Timeout:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_dropdown_create(parent_obj);
                objects.obj134 = obj;
                lv_obj_set_pos(obj, 160, 28);
                lv_obj_set_size(obj, 102, 36);
                lv_dropdown_set_options(obj, "Auto\nManual");
                lv_obj_add_event_cb(obj, event_handler_cb_display_obj134, LV_EVENT_ALL, flowState);
                apply_style_selector_small(obj);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj135 = obj;
                lv_obj_set_pos(obj, 189, 73);
                lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "");
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE);
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_btn_create(parent_obj);
                objects.obj136 = obj;
                lv_obj_set_pos(obj, 8, 144);
                lv_obj_set_size(obj, 197, 38);
                lv_obj_add_event_cb(obj, event_handler_cb_display_obj136, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
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
                objects.obj137 = obj;
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
                create_user_widget_question_yn(obj, getFlowState(flowState, 23), 85);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            }
            {
                // display OFF
                lv_obj_t *obj = lv_obj_create(parent_obj);
                objects.display_off = obj;
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 240);
                lv_obj_add_event_cb(obj, event_handler_cb_display_display_off, LV_EVENT_ALL, flowState);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_blackpanel(obj);
            }
        }
    }
    
    void tick_screen_display() {
        void *flowState = getFlowState(0, 9);
        {
            const char *new_val = evalTextProperty(flowState, 6, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj128);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj128;
                lv_label_set_text(objects.obj128, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 9, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_4, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.nlpc_home_cancel_4;
                if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_4, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.nlpc_home_cancel_4, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 10, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj130);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj130;
                lv_label_set_text(objects.obj130, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 11, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_5, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.nlpc_home_cancel_5;
                if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_5, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.nlpc_home_cancel_5, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 12, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj131);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj131;
                lv_label_set_text(objects.obj131, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 13, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj132, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj132;
                if (new_val) lv_obj_add_flag(objects.obj132, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj132, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            int32_t new_val = evalIntegerProperty(flowState, 13, 3, "Failed to evaluate Value in Slider widget");
            int32_t cur_val = lv_slider_get_value(objects.obj132);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj132;
                lv_slider_set_value(objects.obj132, new_val, LV_ANIM_OFF);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 14, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj133, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj133;
                if (new_val) lv_obj_add_flag(objects.obj133, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj133, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            int32_t new_val = evalIntegerProperty(flowState, 15, 2, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj134);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj134;
                lv_dropdown_set_selected(objects.obj134, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 16, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj135, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj135;
                if (new_val) lv_obj_add_flag(objects.obj135, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj135, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj135);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj135;
                lv_label_set_text(objects.obj135, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 23, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj137, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj137;
                if (new_val) lv_obj_add_flag(objects.obj137, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj137, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        tick_user_widget_question_yn(getFlowState(flowState, 23), 85);
        {
            bool new_val = evalBooleanProperty(flowState, 30, 2, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.display_off, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.display_off;
                if (new_val) lv_obj_add_flag(objects.display_off, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.display_off, LV_OBJ_FLAG_HIDDEN);
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
                        lv_obj_add_event_cb(obj, event_handler_cb_question_yn_obj114, LV_EVENT_ALL, flowState);
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
                        lv_obj_add_event_cb(obj, event_handler_cb_question_yn_obj115, LV_EVENT_ALL, flowState);
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
                ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 25);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
                lv_label_set_text(obj, "");
                apply_style_small_header(obj);
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
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_DEFAULT);
                lv_obj_set_style_border_opa(obj, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_keyboard_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                lv_obj_set_pos(obj, 0, 70);
                lv_obj_set_size(obj, 320, 170);
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_obj24, LV_EVENT_ALL, flowState);
                lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                // max-button
                lv_obj_t *obj = lv_btn_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                lv_obj_set_pos(obj, 263, 26);
                lv_obj_set_size(obj, 56, 43);
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_max_button, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
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
                ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                lv_obj_set_pos(obj, 1, 26);
                lv_obj_set_size(obj, 56, 43);
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_min_button, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
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
        lv_keyboard_set_textarea(((lv_obj_t **)&objects)[startWidgetIndex + 4], ((lv_obj_t **)&objects)[startWidgetIndex + 0]);
    }
    
    void tick_user_widget_keyboard(void *flowState, int startWidgetIndex) {
        {
            const char *new_val = evalTextProperty(flowState, 0, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 3]);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 3];
                lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 3], new_val);
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
    
    void create_user_widget_keyboard_old2(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
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
                ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 25);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
                lv_label_set_text(obj, "");
                apply_style_small_header(obj);
            }
            {
                // kbtext2_1
                lv_obj_t *obj = lv_textarea_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                lv_obj_set_pos(obj, 58, 26);
                lv_obj_set_size(obj, 204, 43);
                lv_textarea_set_max_length(obj, 128);
                lv_textarea_set_one_line(obj, true);
                lv_textarea_set_password_mode(obj, false);
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_old2_kbtext2_1, LV_EVENT_ALL, flowState);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_DEFAULT);
                lv_obj_set_style_border_opa(obj, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff00), LV_PART_CURSOR | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_keyboard_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                lv_obj_set_pos(obj, 0, 70);
                lv_obj_set_size(obj, 320, 170);
                lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_old2_obj139, LV_EVENT_ALL, flowState);
                lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                // max-button_1
                lv_obj_t *obj = lv_btn_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                lv_obj_set_pos(obj, 263, 26);
                lv_obj_set_size(obj, 56, 43);
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_old2_max_button_1, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
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
                // min-button_1
                lv_obj_t *obj = lv_btn_create(parent_obj);
                ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                lv_obj_set_pos(obj, 1, 26);
                lv_obj_set_size(obj, 56, 43);
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_old2_min_button_1, LV_EVENT_ALL, flowState);
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_selectbutton(obj);
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
        lv_keyboard_set_textarea(((lv_obj_t **)&objects)[startWidgetIndex + 4], ((lv_obj_t **)&objects)[startWidgetIndex + 0]);
    }
    
    void tick_user_widget_keyboard_old2(void *flowState, int startWidgetIndex) {
        {
            const char *new_val = evalTextProperty(flowState, 0, 2, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 3]);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 3];
                lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 3], new_val);
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
    create_screen_capacity();
    create_screen_settings();
    create_screen_events();
    create_screen_protections();
    create_screen_calibration();
    create_screen_nplc();
    create_screen_fan();
    create_screen_display();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_startup,
    tick_screen_main,
    tick_screen_capacity,
    tick_screen_settings,
    tick_screen_events,
    tick_screen_protections,
    tick_screen_calibration,
    tick_screen_nplc,
    tick_screen_fan,
    tick_screen_display,
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

