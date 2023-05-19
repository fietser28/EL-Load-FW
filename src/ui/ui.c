#include "ui.h"
#include "screens.h"
#include "images.h"
#include "flow_def.h"
#include "actions.h"

ActionExecFunc actions[] = {
    action_getdropdownindex,
    action_clear_power,
    action_toggle_record,
    action_text_area_disable_blink,
    action_grab_encoder,
    action_cal_refresh_measured,
    action_cal_reset_values,
    action_cal_store_values,
};


void ui_init() {
    eez_flow_init(assets, sizeof(assets), (lv_obj_t **)&objects, sizeof(objects), images, sizeof(images), actions);
}

void ui_tick() {
    eez_flow_tick();
    tick_screen(g_currentScreen);
}
