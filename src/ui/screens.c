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
        flowPropagateValue(flowState, 49, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 49, 4, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
}

static void event_handler_cb_main_on_off_button(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 51, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 51, 4, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_range_current(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 53, 0);
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
        flowPropagateValue(flowState, 56, 0);
    }
}

static void event_handler_cb_main_obj9(lv_event_t *e) {
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
        flowPropagateValue(flowState, 67, 0);
    }
}

static void event_handler_cb_main_obj11(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 69, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 69, 3, value, "Failed to assign Checked state");
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
        flowPropagateValue(flowState, 74, 1);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            if (tick_value_change_obj != ta) {
                assignStringProperty(flowState, 74, 3, value, "Failed to assign Text in Textarea widget");
            }
        }
    }
}

static void event_handler_cb_main_obj13(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 75, 0);
    }
}

static void event_handler_cb_main_obj15(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 79, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 79, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_obj17(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 81, 0);
    }
}

static void event_handler_cb_main_obj19(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 84, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 84, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_obj22(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 88, 0);
    }
}

static void event_handler_cb_main_range_volt_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 91, 0);
    }
}

static void event_handler_cb_main_obj27(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 95, 0);
    }
}

static void event_handler_cb_capacity_obj33(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 17, 0);
    }
}

static void event_handler_cb_capacity_obj35(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 20, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 20, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_obj37(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 22, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 22, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_obj39(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 24, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 24, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_obj41(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 26, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 26, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_on_off_button_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 35, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 35, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_obj44(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        action_toggle_record(e);
    }
}

static void event_handler_cb_capacity_obj46(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 39, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 39, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_capacity_obj48(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        action_clear_power(e);
    }
}

static void event_handler_cb_capacity_obj50(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        action_clear_capacity_limits(e);
    }
}

static void event_handler_cb_capacity_obj51(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 45, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_settings_obj54(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 9, 0);
    }
}

static void event_handler_cb_settings_obj56(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 11, 0);
    }
}

static void event_handler_cb_settings_obj58(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 13, 0);
    }
}

static void event_handler_cb_settings_obj60(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 15, 0);
    }
}

static void event_handler_cb_settings_obj62(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 17, 0);
    }
}

static void event_handler_cb_settings_obj64(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 19, 0);
    }
}

static void event_handler_cb_settings_obj66(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 21, 0);
    }
}

static void event_handler_cb_settings_obj68(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 23, 0);
    }
}

static void event_handler_cb_settings_obj70(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 25, 0);
    }
}

static void event_handler_cb_events_obj73(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 3, 0);
    }
}

static void event_handler_cb_events_obj75(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            const char *value = lv_textarea_get_text(ta);
            if (tick_value_change_obj != ta) {
                assignStringProperty(flowState, 5, 3, value, "Failed to assign Text in Textarea widget");
            }
        }
    }
}

static void event_handler_cb_ranges_ranges(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_SCREEN_LOAD_START) {
        flowPropagateValue(flowState, 9, 0);
    }
}

static void event_handler_cb_ranges_nlpc_home_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 11, 0);
    }
}

static void event_handler_cb_ranges_nlpc_home_cancel_6(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 14, 0);
    }
}

static void event_handler_cb_ranges_nlpc_home_cancel_7(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 16, 0);
    }
}

static void event_handler_cb_ranges_obj79(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 19, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 19, 4, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
}

static void event_handler_cb_ranges_obj80(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 20, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 20, 4, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
}

static void event_handler_cb_ranges_obj81(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 22, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 22, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_nplc_nlpc_home(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 16, 0);
    }
}

static void event_handler_cb_nplc_nlpc_home_cancel(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 21, 0);
    }
}

static void event_handler_cb_nplc_nlpc_home_cancel_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 23, 0);
    }
}

static void event_handler_cb_nplc_obj91(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 25, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 25, 3, value, "Failed to assign Value in Slider widget");
            }
        }
    }
}

static void event_handler_cb_nplc_obj92(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 29, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 29, 3, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
}

static void event_handler_cb_protections_obj96(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 22, 0);
    }
}

static void event_handler_cb_protections_obj98(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 28, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 28, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj100(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 30, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 30, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj102(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 32, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 32, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj104(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 34, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 34, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj106(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 36, 0);
    }
}

static void event_handler_cb_protections_obj107(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 38, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 38, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj109(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 40, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 40, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_protections_obj111(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 42, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_calibration_obj117(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
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

static void event_handler_cb_calibration_obj118(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 34, 0);
    }
}

static void event_handler_cb_calibration_obj122(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 39, 0);
    }
}

static void event_handler_cb_calibration_obj123(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 41, 0);
    }
}

static void event_handler_cb_calibration_obj124(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
}

static void event_handler_cb_calibration_obj125(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 43, 0);
    }
}

static void event_handler_cb_calibration_obj127(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 45, 0);
    }
}

static void event_handler_cb_calibration_obj128(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
}

static void event_handler_cb_calibration_obj130(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 49, 0);
    }
}

static void event_handler_cb_calibration_obj131(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 50, 0);
    }
}

static void event_handler_cb_calibration_obj132(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 51, 0);
    }
}

static void event_handler_cb_calibration_obj133(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 52, 0);
    }
}

static void event_handler_cb_fan_nlpc_home_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 16, 0);
    }
}

static void event_handler_cb_fan_nlpc_home_cancel_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 21, 0);
    }
}

static void event_handler_cb_fan_nlpc_home_cancel_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 23, 0);
    }
}

static void event_handler_cb_fan_obj140(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 25, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 25, 4, value, "Failed to assign Value in Slider widget");
            }
        }
    }
}

static void event_handler_cb_fan_obj142(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 29, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 29, 3, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
}

static void event_handler_cb_display_nlpc_home_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 20, 0);
    }
}

static void event_handler_cb_display_nlpc_home_cancel_4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 23, 0);
    }
}

static void event_handler_cb_display_nlpc_home_cancel_5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 25, 0);
    }
}

static void event_handler_cb_display_obj148(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 27, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 27, 4, value, "Failed to assign Value in Slider widget");
            }
        }
    }
}

static void event_handler_cb_display_obj150(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        flowPropagateValue(flowState, 29, 0);
    }
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_dropdown_get_selected(ta);
            if (tick_value_change_obj != ta) {
                assignIntegerProperty(flowState, 29, 3, value, "Failed to assign Selected in Dropdown widget");
            }
        }
    }
}

static void event_handler_cb_display_obj152(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_RELEASED) {
        flowPropagateValue(flowState, 31, 0);
    }
}

static void event_handler_cb_display_display_off(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 34, 0);
    }
}

static void event_handler_cb_question_yn_obj83(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 2, 0);
    }
}

static void event_handler_cb_question_yn_obj84(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 4, 0);
    }
}

static void event_handler_cb_keyboard_kbtext2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
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

static void event_handler_cb_keyboard_obj31(lv_event_t *e) {
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

void create_screen_startup() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.startup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    apply_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
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
        const char *new_val = evalTextProperty(flowState, 9, 3, "Failed to evaluate Text in Label widget");
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
    apply_style_screen_background(obj);
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
            apply_style_selector_with_disable(obj);
        }
        {
            // ON-OFF button
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.on_off_button = obj;
            lv_obj_set_pos(obj, -2, 2);
            lv_obj_set_size(obj, 109, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_main_on_off_button, LV_EVENT_ALL, flowState);
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
                    lv_obj_set_size(obj, 126, 32);
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
                    lv_obj_set_pos(obj, 163, 18);
                    lv_obj_set_size(obj, 120, 4);
                    apply_style_blackpanel(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DISABLED);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DISABLED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj5 = obj;
                    lv_obj_set_pos(obj, 23, -2);
                    lv_obj_set_size(obj, 64, 64);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Sense");
                    apply_style_button_text90deg(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_y(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_x(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj6 = obj;
                    lv_obj_set_pos(obj, 147, -10);
                    lv_obj_set_size(obj, 136, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj7 = obj;
                    lv_obj_set_pos(obj, -13, 24);
                    lv_obj_set_size(obj, 150, 36);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj8 = obj;
                    lv_obj_set_pos(obj, 147, 24);
                    lv_obj_set_size(obj, 136, 36);
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
                    objects.obj9 = obj;
                    lv_obj_set_pos(obj, -11, 1);
                    lv_obj_set_size(obj, 32, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj9, LV_EVENT_ALL, flowState);
                    apply_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
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
                    objects.obj11 = obj;
                    lv_obj_set_pos(obj, 11, 1);
                    lv_obj_set_size(obj, 38, 32);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj11, LV_EVENT_ALL, flowState);
                    apply_style_select_button_red_green(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_RIGHT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj12 = obj;
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
                            objects.obj13 = obj;
                            lv_obj_set_pos(obj, 109, 14);
                            lv_obj_set_size(obj, 38, 36);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            lv_obj_add_event_cb(obj, event_handler_cb_main_obj13, LV_EVENT_ALL, flowState);
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
                            objects.obj14 = obj;
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
                                    objects.obj15 = obj;
                                    lv_obj_set_pos(obj, -12, 12);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj15, LV_EVENT_ALL, flowState);
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
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff00), LV_PART_MAIN | LV_STATE_CHECKED);
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
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.obj17 = obj;
                                    lv_obj_set_pos(obj, -12, 36);
                                    lv_obj_set_size(obj, 78, 21);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj17, LV_EVENT_ALL, flowState);
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
                                            objects.obj18 = obj;
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
                                    objects.obj19 = obj;
                                    lv_obj_set_pos(obj, -2, -9);
                                    lv_obj_set_size(obj, 55, 34);
                                    lv_obj_add_event_cb(obj, event_handler_cb_main_obj19, LV_EVENT_ALL, flowState);
                                    apply_style_select_button_red_green(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.obj20 = obj;
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
                                    objects.obj21 = obj;
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
            objects.obj22 = obj;
            lv_obj_set_pos(obj, 11, 2);
            lv_obj_set_size(obj, 58, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj22, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj23 = obj;
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
            apply_style_blackpanel(obj);
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
                    apply_style_select_button90deg(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj24 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 58, 28);
                            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                            lv_label_set_text(obj, "");
                            apply_style_button_text(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj25 = obj;
                    lv_obj_set_pos(obj, 40, 40);
                    lv_obj_set_size(obj, 93, 25);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "Sense");
                    apply_style_button_text90deg(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_decor(obj, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_y(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_pivot_x(obj, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_transform_angle(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj26 = obj;
                    lv_obj_set_pos(obj, 8, -12);
                    lv_obj_set_size(obj, 263, 61);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    apply_style_bigfont_label(obj);
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
                    apply_style_selectbutton(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj28 = obj;
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
            objects.obj29 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_keyboard(obj, getFlowState(flowState, 97), 131);
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
        bool new_val = evalBooleanProperty(flowState, 51, 4, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.on_off_button, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button;
            if (new_val) lv_obj_add_state(objects.on_off_button, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.on_off_button, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 51, 5, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.on_off_button, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button;
            if (new_val) lv_obj_add_state(objects.on_off_button, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.on_off_button, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 51, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.on_off_button, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.on_off_button;
            if (new_val) lv_obj_add_flag(objects.on_off_button, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.on_off_button, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 50, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj1;
            lv_label_set_text(objects.obj1, new_val);
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
        bool cur_val = lv_obj_has_state(objects.obj2, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj2;
            if (new_val) lv_obj_add_state(objects.obj2, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj2, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 54, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj2;
            lv_label_set_text(objects.obj2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 55, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj3);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj3;
            lv_label_set_text(objects.obj3, new_val);
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
        const char *cur_val = lv_label_get_text(objects.obj4);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj4;
            lv_label_set_text(objects.obj4, new_val);
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
        bool cur_val = lv_obj_has_flag(objects.obj5, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj5;
            if (new_val) lv_obj_add_flag(objects.obj5, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj5, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 60, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj6);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj6;
            lv_label_set_text(objects.obj6, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 61, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj7);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj7;
            lv_label_set_text(objects.obj7, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 62, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj8);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj8;
            lv_label_set_text(objects.obj8, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 63, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.power_panel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.power_panel;
            if (new_val) lv_obj_add_flag(objects.power_panel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.power_panel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 65, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj10);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj10;
            lv_label_set_text(objects.obj10, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 66, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ah);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ah;
            lv_label_set_text(objects.ah, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 67, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wh);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wh;
            lv_label_set_text(objects.wh, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 68, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.montime);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.montime;
            lv_label_set_text(objects.montime, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 69, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj11, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj11;
            if (new_val) lv_obj_add_state(objects.obj11, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj11, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 70, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj12);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj12;
            lv_label_set_text(objects.obj12, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 72, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.iset, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.iset;
            if (new_val) lv_obj_add_flag(objects.iset, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.iset, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 73, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.isetlabel);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.isetlabel;
            lv_label_set_text(objects.isetlabel, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 74, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.set_value_area);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.set_value_area;
            lv_textarea_set_text(objects.set_value_area, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 75, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj13);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj13;
            lv_label_set_text(objects.obj13, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 77, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj14, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj14;
            if (new_val) lv_obj_add_flag(objects.obj14, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj14, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 79, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj15, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj15;
            if (new_val) lv_obj_add_state(objects.obj15, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj15, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 80, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj16);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj16;
            lv_label_set_text(objects.obj16, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 82, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj18);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj18;
            lv_label_set_text(objects.obj18, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 84, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj19, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj19;
            if (new_val) lv_obj_add_state(objects.obj19, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj19, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 85, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj20);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj20;
            lv_label_set_text(objects.obj20, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 86, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj21);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj21;
            lv_label_set_text(objects.obj21, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 87, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.wheel;
            if (new_val) lv_obj_add_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.wheel, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 89, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj23);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj23;
            lv_label_set_text(objects.obj23, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 90, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.main_dvm, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.main_dvm;
            if (new_val) lv_obj_add_flag(objects.main_dvm, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.main_dvm, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 91, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.range_volt_1, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.range_volt_1;
            if (new_val) lv_obj_add_state(objects.range_volt_1, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.range_volt_1, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 92, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj24);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj24;
            lv_label_set_text(objects.obj24, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 93, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj25, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj25;
            if (new_val) lv_obj_add_flag(objects.obj25, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj25, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 94, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj26);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj26;
            lv_label_set_text(objects.obj26, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 96, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj28);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj28;
            lv_label_set_text(objects.obj28, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 97, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj29, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj29;
            if (new_val) lv_obj_add_flag(objects.obj29, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj29, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 97), 131);
}

void create_screen_capacity() {
    void *flowState = getFlowState(0, 2);
    lv_obj_t *obj = lv_obj_create(0);
    objects.capacity = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    apply_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj32 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 25);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj33 = obj;
            lv_obj_set_pos(obj, -2, -2);
            lv_obj_set_size(obj, 55, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj33, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj34 = obj;
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
            objects.obj35 = obj;
            lv_obj_set_pos(obj, 204, 174);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj35, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj36 = obj;
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
            objects.obj37 = obj;
            lv_obj_set_pos(obj, 204, 149);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj37, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj38 = obj;
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
            objects.obj39 = obj;
            lv_obj_set_pos(obj, 204, 124);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj39, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj40 = obj;
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
            objects.obj41 = obj;
            lv_obj_set_pos(obj, 204, 100);
            lv_obj_set_size(obj, 114, 22);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj41, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj42 = obj;
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
            objects.on_off_button_1 = obj;
            lv_obj_set_pos(obj, 2, -2);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_on_off_button_1, LV_EVENT_ALL, flowState);
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
                    objects.obj43 = obj;
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
            objects.obj44 = obj;
            lv_obj_set_pos(obj, 2, -77);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj44, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj45 = obj;
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
            objects.obj46 = obj;
            lv_obj_set_pos(obj, -32, -2);
            lv_obj_set_size(obj, 55, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj46, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj47 = obj;
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
            objects.obj48 = obj;
            lv_obj_set_pos(obj, -142, -148);
            lv_obj_set_size(obj, 32, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj48, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj49 = obj;
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
            objects.obj50 = obj;
            lv_obj_set_pos(obj, 51, -2);
            lv_obj_set_size(obj, 88, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj50, LV_EVENT_ALL, flowState);
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
            objects.obj51 = obj;
            lv_obj_set_pos(obj, 2, 97);
            lv_obj_set_size(obj, 187, 28);
            lv_checkbox_set_text(obj, "    Volt stop:");
            lv_obj_add_event_cb(obj, event_handler_cb_capacity_obj51, LV_EVENT_ALL, flowState);
            apply_style_checkbox_default(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj52 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_keyboard(obj, getFlowState(flowState, 46), 160);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 94);
            lv_obj_set_size(obj, 320, 2);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff828282), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_capacity() {
    void *flowState = getFlowState(0, 2);
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj32);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj32;
            lv_label_set_text(objects.obj32, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj34);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj34;
            lv_label_set_text(objects.obj34, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj35, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj35;
            if (new_val) lv_obj_add_state(objects.obj35, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj35, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj35, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj35;
            if (new_val) lv_obj_add_state(objects.obj35, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj35, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 21, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj36);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj36;
            lv_label_set_text(objects.obj36, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 22, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj37, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj37;
            if (new_val) lv_obj_add_state(objects.obj37, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj37, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 22, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj37, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj37;
            if (new_val) lv_obj_add_state(objects.obj37, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj37, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 23, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj38);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj38;
            lv_label_set_text(objects.obj38, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 24, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj39, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj39;
            if (new_val) lv_obj_add_state(objects.obj39, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj39, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 24, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj39, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj39;
            if (new_val) lv_obj_add_state(objects.obj39, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj39, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 25, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj40);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj40;
            lv_label_set_text(objects.obj40, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 26, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj41, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj41;
            if (new_val) lv_obj_add_state(objects.obj41, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj41, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 26, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj41, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj41;
            if (new_val) lv_obj_add_state(objects.obj41, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj41, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 27, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj42);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj42;
            lv_label_set_text(objects.obj42, new_val);
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
        const char *cur_val = lv_label_get_text(objects.obj43);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj43;
            lv_label_set_text(objects.obj43, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 38, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj45);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj45;
            lv_label_set_text(objects.obj45, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 39, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj46, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj46;
            if (new_val) lv_obj_add_state(objects.obj46, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj46, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 40, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj47);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj47;
            lv_label_set_text(objects.obj47, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 42, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj49);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj49;
            lv_label_set_text(objects.obj49, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 45, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj51, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj51;
            if (new_val) lv_obj_add_state(objects.obj51, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj51, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 46, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj52, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj52;
            if (new_val) lv_obj_add_flag(objects.obj52, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj52, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 46), 160);
}

void create_screen_settings() {
    void *flowState = getFlowState(0, 3);
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    apply_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj53 = obj;
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
            objects.obj54 = obj;
            lv_obj_set_pos(obj, 206, 206);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj54, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj55 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj56 = obj;
            lv_obj_set_pos(obj, 9, 206);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj56, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj57 = obj;
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
            objects.obj58 = obj;
            lv_obj_set_pos(obj, 9, 134);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj58, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj59 = obj;
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
            objects.obj60 = obj;
            lv_obj_set_pos(obj, 9, 170);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj60, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj61 = obj;
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
            objects.obj62 = obj;
            lv_obj_set_pos(obj, 9, 98);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj62, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj63 = obj;
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
            objects.obj64 = obj;
            lv_obj_set_pos(obj, 206, 170);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj64, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj65 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj66 = obj;
            lv_obj_set_pos(obj, 206, 134);
            lv_obj_set_size(obj, 105, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj66, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj67 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj68 = obj;
            lv_obj_set_pos(obj, 9, 62);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj68, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj69 = obj;
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
            objects.obj70 = obj;
            lv_obj_set_pos(obj, 9, 27);
            lv_obj_set_size(obj, 188, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj70, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj71 = obj;
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
        const char *new_val = evalTextProperty(flowState, 8, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj53);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj53;
            lv_label_set_text(objects.obj53, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj55);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj55;
            lv_label_set_text(objects.obj55, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj57);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj57;
            lv_label_set_text(objects.obj57, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 14, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj59);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj59;
            lv_label_set_text(objects.obj59, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj61);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj61;
            lv_label_set_text(objects.obj61, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj63);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj63;
            lv_label_set_text(objects.obj63, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj65);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj65;
            lv_label_set_text(objects.obj65, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj67);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj67;
            lv_label_set_text(objects.obj67, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj69);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj69;
            lv_label_set_text(objects.obj69, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 26, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj71);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj71;
            lv_label_set_text(objects.obj71, new_val);
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
    apply_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj72 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 25);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj73 = obj;
            lv_obj_set_pos(obj, 225, 200);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_events_obj73, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj74 = obj;
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
            objects.obj75 = obj;
            lv_obj_set_pos(obj, 3, 26);
            lv_obj_set_size(obj, 314, 161);
            lv_textarea_set_max_length(obj, 500);
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, event_handler_cb_events_obj75, LV_EVENT_ALL, flowState);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff444444), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_events() {
    void *flowState = getFlowState(0, 4);
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj72);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj72;
            lv_label_set_text(objects.obj72, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj74);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj74;
            lv_label_set_text(objects.obj74, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 3, "Failed to evaluate Text in Textarea widget");
        const char *cur_val = lv_textarea_get_text(objects.obj75);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj75;
            lv_textarea_set_text(objects.obj75, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_ranges() {
    void *flowState = getFlowState(0, 5);
    lv_obj_t *obj = lv_obj_create(0);
    objects.ranges = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_event_cb(obj, event_handler_cb_ranges_ranges, LV_EVENT_ALL, flowState);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    apply_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 6, 34);
            lv_obj_set_size(obj, 155, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Current range:");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME_3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_3 = obj;
            lv_obj_set_pos(obj, 225, 190);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_nlpc_home_3, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj76 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Ranges & Sense");
            apply_style_small_header(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // NLPC_HOME_CANCEL_6
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nlpc_home_cancel_6 = obj;
            lv_obj_set_pos(obj, 115, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_nlpc_home_cancel_6, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj77 = obj;
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
            lv_obj_set_pos(obj, 8, 191);
            lv_obj_set_size(obj, 90, 38);
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_nlpc_home_cancel_7, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj78 = obj;
                    lv_obj_set_pos(obj, 3, -1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 91);
            lv_obj_set_size(obj, 160, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Volt range:");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.obj79 = obj;
            lv_obj_set_pos(obj, 180, 29);
            lv_obj_set_size(obj, 102, 36);
            lv_dropdown_set_options(obj, "10A\n1A");
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_obj79, LV_EVENT_ALL, flowState);
            apply_style_selector_small(obj);
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.obj80 = obj;
            lv_obj_set_pos(obj, 180, 85);
            lv_obj_set_size(obj, 102, 36);
            lv_dropdown_set_options(obj, "80V\n10V");
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_obj80, LV_EVENT_ALL, flowState);
            apply_style_selector_small(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 1, 148);
            lv_obj_set_size(obj, 160, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "Remote sense:");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj81 = obj;
            lv_obj_set_pos(obj, 206, 148);
            lv_obj_set_size(obj, 50, 25);
            lv_obj_add_event_cb(obj, event_handler_cb_ranges_obj81, LV_EVENT_ALL, flowState);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj82 = obj;
            lv_obj_set_pos(obj, 0, 2);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_question_yn(obj, getFlowState(flowState, 23), 198);
        }
    }
}

void tick_screen_ranges() {
    void *flowState = getFlowState(0, 5);
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj76);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj76;
            lv_label_set_text(objects.obj76, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 14, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_6, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel_6;
            if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_6, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_home_cancel_6, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 15, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj77);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj77;
            lv_label_set_text(objects.obj77, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 16, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.nlpc_home_cancel_7, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel_7;
            if (new_val) lv_obj_add_state(objects.nlpc_home_cancel_7, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.nlpc_home_cancel_7, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 16, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.nlpc_home_cancel_7, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.nlpc_home_cancel_7;
            if (new_val) lv_obj_add_flag(objects.nlpc_home_cancel_7, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.nlpc_home_cancel_7, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj78);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj78;
            lv_label_set_text(objects.obj78, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 19, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj79, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj79;
            if (new_val) lv_obj_add_state(objects.obj79, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj79, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.obj79) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 19, 4, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj79);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj79;
                lv_dropdown_set_selected(objects.obj79, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj80, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj80;
            if (new_val) lv_obj_add_state(objects.obj80, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj80, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.obj80) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 20, 4, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj80);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj80;
                lv_dropdown_set_selected(objects.obj80, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 22, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj81, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj81;
            if (new_val) lv_obj_add_state(objects.obj81, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj81, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 23, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj82, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj82;
            if (new_val) lv_obj_add_flag(objects.obj82, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj82, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_question_yn(getFlowState(flowState, 23), 198);
}

void create_screen_nplc() {
    void *flowState = getFlowState(0, 6);
    lv_obj_t *obj = lv_obj_create(0);
    objects.nplc = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    apply_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
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
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj86 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj87 = obj;
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
            objects.obj88 = obj;
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
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj89 = obj;
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
            apply_style_selectbutton(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj90 = obj;
                    lv_obj_set_pos(obj, 3, -1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.obj91 = obj;
            lv_obj_set_pos(obj, 141, 117);
            lv_obj_set_size(obj, 166, 10);
            lv_slider_set_range(obj, 1, 100);
            lv_obj_add_event_cb(obj, event_handler_cb_nplc_obj91, LV_EVENT_ALL, flowState);
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
            objects.obj92 = obj;
            lv_obj_set_pos(obj, 101, 28);
            lv_obj_set_size(obj, 80, 36);
            lv_dropdown_set_options(obj, "50 Hz\n60 Hz");
            lv_obj_add_event_cb(obj, event_handler_cb_nplc_obj92, LV_EVENT_ALL, flowState);
            apply_style_selector_small(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj93 = obj;
            lv_obj_set_pos(obj, 101, 110);
            lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj94 = obj;
            lv_obj_set_pos(obj, 0, 2);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_question_yn(obj, getFlowState(flowState, 31), 211);
        }
    }
}

void tick_screen_nplc() {
    void *flowState = getFlowState(0, 6);
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj86);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj86;
            lv_label_set_text(objects.obj86, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj87);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj87;
            lv_label_set_text(objects.obj87, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj88);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj88;
            lv_label_set_text(objects.obj88, new_val);
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
        const char *cur_val = lv_label_get_text(objects.obj89);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj89;
            lv_label_set_text(objects.obj89, new_val);
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
        const char *cur_val = lv_label_get_text(objects.obj90);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj90;
            lv_label_set_text(objects.obj90, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 25, 3, "Failed to evaluate Value in Slider widget");
        int32_t cur_val = lv_slider_get_value(objects.obj91);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj91;
            lv_slider_set_value(objects.obj91, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.obj92) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 29, 3, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj92);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj92;
                lv_dropdown_set_selected(objects.obj92, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 30, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj93);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj93;
            lv_label_set_text(objects.obj93, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 31, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj94, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj94;
            if (new_val) lv_obj_add_flag(objects.obj94, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj94, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_question_yn(getFlowState(flowState, 31), 211);
}

void create_screen_protections() {
    void *flowState = getFlowState(0, 7);
    lv_obj_t *obj = lv_obj_create(0);
    objects.protections = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    apply_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj95 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 26);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj96 = obj;
            lv_obj_set_pos(obj, 212, 200);
            lv_obj_set_size(obj, 90, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj96, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj97 = obj;
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
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 67);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Voltage (OVP):");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 22, 101);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Power (OPP):");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 22, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Temp. (OTP): ");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj98 = obj;
            lv_obj_set_pos(obj, 160, 30);
            lv_obj_set_size(obj, 142, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj98, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj99 = obj;
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
            objects.obj100 = obj;
            lv_obj_set_pos(obj, 160, 64);
            lv_obj_set_size(obj, 142, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj100, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj101 = obj;
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
            objects.obj102 = obj;
            lv_obj_set_pos(obj, 160, 98);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj102, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj103 = obj;
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
            objects.obj104 = obj;
            lv_obj_set_pos(obj, 237, 98);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj104, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj105 = obj;
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
            objects.obj106 = obj;
            lv_obj_set_pos(obj, 28, 200);
            lv_obj_set_size(obj, 164, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj106, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
            apply_style_selectbutton(obj);
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
            objects.obj107 = obj;
            lv_obj_set_pos(obj, 160, 132);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj107, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj108 = obj;
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
            objects.obj109 = obj;
            lv_obj_set_pos(obj, 237, 132);
            lv_obj_set_size(obj, 65, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj109, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj110 = obj;
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
            objects.obj111 = obj;
            lv_obj_set_pos(obj, 160, 166);
            lv_obj_set_size(obj, 142, 30);
            lv_obj_add_event_cb(obj, event_handler_cb_protections_obj111, LV_EVENT_ALL, flowState);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj112 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 142, 20);
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
            objects.obj113 = obj;
            lv_obj_set_pos(obj, 28, 166);
            lv_obj_set_size(obj, 120, 30);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
            apply_style_select_button_red_green(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DISABLED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj114 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 120, 20);
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
            objects.obj115 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_keyboard(obj, getFlowState(flowState, 46), 58);
        }
    }
}

void tick_screen_protections() {
    void *flowState = getFlowState(0, 7);
    {
        const char *new_val = evalTextProperty(flowState, 21, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj95);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj95;
            lv_label_set_text(objects.obj95, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 23, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj97);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj97;
            lv_label_set_text(objects.obj97, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 28, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj98, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj98;
            if (new_val) lv_obj_add_state(objects.obj98, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj98, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 29, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj99);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj99;
            lv_label_set_text(objects.obj99, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 30, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj100, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj100;
            if (new_val) lv_obj_add_state(objects.obj100, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj100, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 31, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj101);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj101;
            lv_label_set_text(objects.obj101, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 32, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj102, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj102;
            if (new_val) lv_obj_add_state(objects.obj102, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj102, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 33, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj103);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj103;
            lv_label_set_text(objects.obj103, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 34, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj104, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj104;
            if (new_val) lv_obj_add_state(objects.obj104, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj104, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 35, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj105);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj105;
            lv_label_set_text(objects.obj105, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 36, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj106, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj106;
            if (new_val) lv_obj_add_state(objects.obj106, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj106, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 38, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj107, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj107;
            if (new_val) lv_obj_add_state(objects.obj107, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj107, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 39, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj108);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj108;
            lv_label_set_text(objects.obj108, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 40, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj109, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj109;
            if (new_val) lv_obj_add_state(objects.obj109, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj109, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 41, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj110);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj110;
            lv_label_set_text(objects.obj110, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 42, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj111, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj111;
            if (new_val) lv_obj_add_state(objects.obj111, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj111, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 42, 4, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj111, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj111;
            if (new_val) lv_obj_add_state(objects.obj111, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj111, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 43, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj112);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj112;
            lv_label_set_text(objects.obj112, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 44, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj113, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj113;
            if (new_val) lv_obj_add_flag(objects.obj113, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj113, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 45, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj114);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj114;
            lv_label_set_text(objects.obj114, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 46, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj115, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj115;
            if (new_val) lv_obj_add_flag(objects.obj115, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj115, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 46), 58);
}

void create_screen_calibration() {
    void *flowState = getFlowState(0, 8);
    lv_obj_t *obj = lv_obj_create(0);
    objects.calibration = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    apply_style_screen_background(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj116 = obj;
            lv_obj_set_pos(obj, 0, 1);
            lv_obj_set_size(obj, 320, 27);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_header(obj);
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.obj117 = obj;
            lv_obj_set_pos(obj, 0, 28);
            lv_obj_set_size(obj, 320, LV_SIZE_CONTENT);
            lv_dropdown_set_options(obj, "Current Monitor High\nCurrent Monitor Low\nVoltage Monitor High\nVoltage Monitor Low\nCurrent Set High\nCurrent Set Low\nVoltage Set High\nVoltage Set Low\nVon Set High\nVon Set Low\nOCP set High\nOCP set Low\nOVP set High\nOVP set Low");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj117, LV_EVENT_ALL, flowState);
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
            objects.obj118 = obj;
            lv_obj_set_pos(obj, 114, 98);
            lv_obj_set_size(obj, 190, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj118, LV_EVENT_ALL, flowState);
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
                    objects.obj119 = obj;
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
            objects.obj120 = obj;
            lv_obj_set_pos(obj, 0, 70);
            lv_obj_set_size(obj, 320, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL);
            lv_label_set_text(obj, "");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj121 = obj;
            lv_obj_set_pos(obj, 160, 172);
            lv_obj_set_size(obj, 109, 25);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            apply_style_small_label(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj122 = obj;
            lv_obj_set_pos(obj, 10, 206);
            lv_obj_set_size(obj, 90, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj122, LV_EVENT_ALL, flowState);
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
            objects.obj123 = obj;
            lv_obj_set_pos(obj, 198, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj123, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj124 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 45, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj124, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj125 = obj;
            lv_obj_set_pos(obj, 126, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj125, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj126 = obj;
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
            objects.obj127 = obj;
            lv_obj_set_pos(obj, 269, 206);
            lv_obj_set_size(obj, 45, 32);
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj127, LV_EVENT_ALL, flowState);
            apply_style_selectbutton(obj);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj128 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 45, 32);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj128, LV_EVENT_ALL, flowState);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj129 = obj;
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
            objects.obj130 = obj;
            lv_obj_set_pos(obj, 136, 173);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj130, LV_EVENT_ALL, flowState);
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
            objects.obj131 = obj;
            lv_obj_set_pos(obj, 268, 172);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj131, LV_EVENT_ALL, flowState);
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
            objects.obj132 = obj;
            lv_obj_set_pos(obj, 278, 140);
            lv_obj_set_size(obj, 26, 26);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj132, LV_EVENT_ALL, flowState);
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
            objects.obj133 = obj;
            lv_obj_set_pos(obj, 114, 140);
            lv_obj_set_size(obj, 24, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_calibration_obj133, LV_EVENT_ALL, flowState);
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
            objects.obj134 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_keyboard(obj, getFlowState(flowState, 53), 84);
        }
    }
}

void tick_screen_calibration() {
    void *flowState = getFlowState(0, 8);
    {
        const char *new_val = evalTextProperty(flowState, 31, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj116);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj116;
            lv_label_set_text(objects.obj116, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 32, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj117, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj117;
            if (new_val) lv_obj_add_state(objects.obj117, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj117, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.obj117) & LV_STATE_EDITED)) {
            int32_t new_val = evalIntegerProperty(flowState, 32, 4, "Failed to evaluate Selected in Dropdown widget");
            int32_t cur_val = lv_dropdown_get_selected(objects.obj117);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj117;
                lv_dropdown_set_selected(objects.obj117, new_val);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 35, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj119);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj119;
            lv_label_set_text(objects.obj119, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 37, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj120);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj120;
            lv_label_set_text(objects.obj120, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 38, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj121);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj121;
            lv_label_set_text(objects.obj121, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 41, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj123, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj123;
            if (new_val) lv_obj_add_state(objects.obj123, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj123, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 42, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj124, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj124;
            if (new_val) lv_obj_add_state(objects.obj124, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj124, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 42, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj124);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj124;
            lv_label_set_text(objects.obj124, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 43, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj125, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj125;
            if (new_val) lv_obj_add_state(objects.obj125, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj125, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 44, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj126);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj126;
            lv_label_set_text(objects.obj126, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 45, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj127, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj127;
            if (new_val) lv_obj_add_state(objects.obj127, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj127, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 46, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj128, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj128;
            if (new_val) lv_obj_add_state(objects.obj128, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj128, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 46, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj128);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj128;
            lv_label_set_text(objects.obj128, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 47, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj129);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj129;
            lv_label_set_text(objects.obj129, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 49, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj130, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj130;
            if (new_val) lv_obj_add_state(objects.obj130, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj130, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 49, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj130);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj130;
            lv_label_set_text(objects.obj130, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 50, 3, "Failed to evaluate Disabled state");
        bool cur_val = lv_obj_has_state(objects.obj131, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj131;
            if (new_val) lv_obj_add_state(objects.obj131, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.obj131, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 50, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj131);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj131;
            lv_label_set_text(objects.obj131, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 51, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj132);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj132;
            lv_label_set_text(objects.obj132, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 52, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj133, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj133;
            if (new_val) lv_obj_add_flag(objects.obj133, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj133, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 52, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj133);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj133;
            lv_label_set_text(objects.obj133, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 53, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.obj134, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj134;
            if (new_val) lv_obj_add_flag(objects.obj134, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.obj134, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    tick_user_widget_keyboard(getFlowState(flowState, 53), 84);
    {
        float timeline_position = getTimelinePosition(flowState);
        
        static struct {
            float last_timeline_position;
            int32_t obj_obj132_rotate_init_value;
        } anim_state = { -1 };
        
        if (anim_state.last_timeline_position == -1) {
            anim_state.last_timeline_position = 0;
            anim_state.obj_obj132_rotate_init_value = lv_obj_get_style_prop(objects.obj132, LV_PART_MAIN, LV_STYLE_TRANSFORM_ANGLE).num;
        }
        
        if (timeline_position != anim_state.last_timeline_position) {
            anim_state.last_timeline_position = timeline_position;
            
            {
                lv_obj_t *obj = objects.obj132;
                
                float rotate_value = anim_state.obj_obj132_rotate_init_value;
                
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
    
    void create_screen_fan() {
        void *flowState = getFlowState(0, 9);
        lv_obj_t *obj = lv_obj_create(0);
        objects.fan = obj;
        lv_obj_set_pos(obj, 0, 0);
        lv_obj_set_size(obj, 320, 240);
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        apply_style_screen_background(obj);
        {
            lv_obj_t *parent_obj = obj;
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
                apply_style_selectbutton(obj);
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
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj136 = obj;
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
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 24);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Fan Settings");
                apply_style_small_header(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xffdddddd), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj137 = obj;
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
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj138 = obj;
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
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj139 = obj;
                        lv_obj_set_pos(obj, 3, -1);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_slider_create(parent_obj);
                objects.obj140 = obj;
                lv_obj_set_pos(obj, 127, 117);
                lv_obj_set_size(obj, 180, 10);
                lv_obj_add_event_cb(obj, event_handler_cb_fan_obj140, LV_EVENT_ALL, flowState);
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
                objects.obj141 = obj;
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
                objects.obj142 = obj;
                lv_obj_set_pos(obj, 160, 28);
                lv_obj_set_size(obj, 102, 36);
                lv_dropdown_set_options(obj, "Auto\nManual");
                lv_obj_add_event_cb(obj, event_handler_cb_fan_obj142, LV_EVENT_ALL, flowState);
                apply_style_selector_small(obj);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj143 = obj;
                lv_obj_set_pos(obj, 189, 110);
                lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "");
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_obj_create(parent_obj);
                objects.obj144 = obj;
                lv_obj_set_pos(obj, 0, 2);
                lv_obj_set_size(obj, 320, 240);
                lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                create_user_widget_question_yn(obj, getFlowState(flowState, 31), 100);
            }
        }
    }
    
    void tick_screen_fan() {
        void *flowState = getFlowState(0, 9);
        {
            const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj135);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj135;
                lv_label_set_text(objects.obj135, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj136);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj136;
                lv_label_set_text(objects.obj136, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj137);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj137;
                lv_label_set_text(objects.obj137, new_val);
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
            const char *cur_val = lv_label_get_text(objects.obj138);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj138;
                lv_label_set_text(objects.obj138, new_val);
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
            const char *cur_val = lv_label_get_text(objects.obj139);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj139;
                lv_label_set_text(objects.obj139, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 25, 3, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj140, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj140;
                if (new_val) lv_obj_add_flag(objects.obj140, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj140, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            int32_t new_val = evalIntegerProperty(flowState, 25, 4, "Failed to evaluate Value in Slider widget");
            int32_t cur_val = lv_slider_get_value(objects.obj140);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj140;
                lv_slider_set_value(objects.obj140, new_val, LV_ANIM_OFF);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 27, 3, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj141, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj141;
                if (new_val) lv_obj_add_flag(objects.obj141, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj141, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            if (!(lv_obj_get_state(objects.obj142) & LV_STATE_EDITED)) {
                int32_t new_val = evalIntegerProperty(flowState, 29, 3, "Failed to evaluate Selected in Dropdown widget");
                int32_t cur_val = lv_dropdown_get_selected(objects.obj142);
                if (new_val != cur_val) {
                    tick_value_change_obj = objects.obj142;
                    lv_dropdown_set_selected(objects.obj142, new_val);
                    tick_value_change_obj = NULL;
                }
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 30, 3, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj143, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj143;
                if (new_val) lv_obj_add_flag(objects.obj143, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj143, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 30, 4, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj143);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj143;
                lv_label_set_text(objects.obj143, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 31, 3, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj144, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj144;
                if (new_val) lv_obj_add_flag(objects.obj144, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj144, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        tick_user_widget_question_yn(getFlowState(flowState, 31), 100);
    }
    
    void create_screen_display() {
        void *flowState = getFlowState(0, 10);
        lv_obj_t *obj = lv_obj_create(0);
        objects.display = obj;
        lv_obj_set_pos(obj, 0, 0);
        lv_obj_set_size(obj, 320, 240);
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
        apply_style_screen_background(obj);
        {
            lv_obj_t *parent_obj = obj;
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
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj145 = obj;
                        lv_obj_set_pos(obj, 0, 0);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 24);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Display Settings");
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
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj146 = obj;
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
                apply_style_selectbutton(obj);
                {
                    lv_obj_t *parent_obj = obj;
                    {
                        lv_obj_t *obj = lv_label_create(parent_obj);
                        objects.obj147 = obj;
                        lv_obj_set_pos(obj, 3, -1);
                        lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                        lv_label_set_text(obj, "");
                        lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    }
                }
            }
            {
                lv_obj_t *obj = lv_slider_create(parent_obj);
                objects.obj148 = obj;
                lv_obj_set_pos(obj, 131, 80);
                lv_obj_set_size(obj, 180, 10);
                lv_obj_add_event_cb(obj, event_handler_cb_display_obj148, LV_EVENT_ALL, flowState);
                apply_style_slider(obj);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj149 = obj;
                lv_obj_set_pos(obj, 1, 73);
                lv_obj_set_size(obj, 114, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "Timeout:");
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_dropdown_create(parent_obj);
                objects.obj150 = obj;
                lv_obj_set_pos(obj, 160, 28);
                lv_obj_set_size(obj, 102, 36);
                lv_dropdown_set_options(obj, "Auto\nManual");
                lv_obj_add_event_cb(obj, event_handler_cb_display_obj150, LV_EVENT_ALL, flowState);
                apply_style_selector_small(obj);
            }
            {
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.obj151 = obj;
                lv_obj_set_pos(obj, 189, 73);
                lv_obj_set_size(obj, 32, LV_SIZE_CONTENT);
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
                lv_label_set_text(obj, "");
                lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
                apply_style_small_label(obj);
                lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xff00ffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            {
                lv_obj_t *obj = lv_btn_create(parent_obj);
                objects.obj152 = obj;
                lv_obj_set_pos(obj, 8, 144);
                lv_obj_set_size(obj, 197, 38);
                lv_obj_add_event_cb(obj, event_handler_cb_display_obj152, LV_EVENT_ALL, flowState);
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
                objects.obj153 = obj;
                lv_obj_set_pos(obj, 0, 2);
                lv_obj_set_size(obj, 320, 240);
                lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                create_user_widget_question_yn(obj, getFlowState(flowState, 33), 113);
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
        void *flowState = getFlowState(0, 10);
        {
            const char *new_val = evalTextProperty(flowState, 21, 3, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj145);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj145;
                lv_label_set_text(objects.obj145, new_val);
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
            const char *cur_val = lv_label_get_text(objects.obj146);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj146;
                lv_label_set_text(objects.obj146, new_val);
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
            const char *cur_val = lv_label_get_text(objects.obj147);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj147;
                lv_label_set_text(objects.obj147, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 27, 3, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj148, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj148;
                if (new_val) lv_obj_add_flag(objects.obj148, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj148, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            int32_t new_val = evalIntegerProperty(flowState, 27, 4, "Failed to evaluate Value in Slider widget");
            int32_t cur_val = lv_slider_get_value(objects.obj148);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj148;
                lv_slider_set_value(objects.obj148, new_val, LV_ANIM_OFF);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 28, 3, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj149, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj149;
                if (new_val) lv_obj_add_flag(objects.obj149, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj149, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            if (!(lv_obj_get_state(objects.obj150) & LV_STATE_EDITED)) {
                int32_t new_val = evalIntegerProperty(flowState, 29, 3, "Failed to evaluate Selected in Dropdown widget");
                int32_t cur_val = lv_dropdown_get_selected(objects.obj150);
                if (new_val != cur_val) {
                    tick_value_change_obj = objects.obj150;
                    lv_dropdown_set_selected(objects.obj150, new_val);
                    tick_value_change_obj = NULL;
                }
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 30, 3, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj151, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj151;
                if (new_val) lv_obj_add_flag(objects.obj151, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj151, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        {
            const char *new_val = evalTextProperty(flowState, 30, 4, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(objects.obj151);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = objects.obj151;
                lv_label_set_text(objects.obj151, new_val);
                tick_value_change_obj = NULL;
            }
        }
        {
            bool new_val = evalBooleanProperty(flowState, 33, 3, "Failed to evaluate Hidden flag");
            bool cur_val = lv_obj_has_flag(objects.obj153, LV_OBJ_FLAG_HIDDEN);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.obj153;
                if (new_val) lv_obj_add_flag(objects.obj153, LV_OBJ_FLAG_HIDDEN);
                else lv_obj_clear_flag(objects.obj153, LV_OBJ_FLAG_HIDDEN);
                tick_value_change_obj = NULL;
            }
        }
        tick_user_widget_question_yn(getFlowState(flowState, 33), 113);
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
    
    void create_user_widget_question_yn(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
        lv_obj_t *obj = parent_obj;
        {
            lv_obj_t *parent_obj = obj;
            {
                lv_obj_t *obj = lv_obj_create(parent_obj);
                lv_obj_set_pos(obj, 0, 0);
                lv_obj_set_size(obj, 320, 240);
                lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                apply_style_transparant_overlay(obj);
                lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
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
                        lv_obj_add_event_cb(obj, event_handler_cb_question_yn_obj83, LV_EVENT_ALL, flowState);
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
                        lv_obj_add_event_cb(obj, event_handler_cb_question_yn_obj84, LV_EVENT_ALL, flowState);
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
            const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
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
                lv_obj_add_event_cb(obj, event_handler_cb_keyboard_obj31, LV_EVENT_ALL, flowState);
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
            const char *new_val = evalTextProperty(flowState, 0, 3, "Failed to evaluate Text in Label widget");
            const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 3]);
            if (strcmp(new_val, cur_val) != 0) {
                tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 3];
                lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 3], new_val);
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
    

void create_screens() {
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

