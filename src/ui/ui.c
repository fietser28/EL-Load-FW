#include "ui.h"
#include "screens.h"
#include "images.h"
#include "flow_def.h"
#include "actions.h"

ActionExecFunc actions[] = {
    action_clear_power,
    action_getdropdownindex,
    action_toggle_record,
    action_text_area_disable_blink,
    action_cal_refresh_measured,
    action_cal_reset_values,
    action_cal_store_values,
    action_cal_set_dac,
    action_cal_store_defaults,
    action_display_off,
    action_display_on,
    action_get_type_data,
    action_clear_capacity_limits,
    action_scpi_busy_incr,
    action_scpi_busy_decr,
};


void ui_init() {
    eez_flow_init(assets, sizeof(assets), (lv_obj_t **)&objects, sizeof(objects), images, sizeof(images), actions);
}

void ui_tick() {
    eez_flow_tick();
    tick_screen(g_currentScreen);
}
