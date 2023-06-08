#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

extern void action_getdropdownindex(lv_event_t * e);
extern void action_clear_power(lv_event_t * e);
extern void action_toggle_record(lv_event_t * e);
extern void action_text_area_disable_blink(lv_event_t * e);
extern void action_grab_encoder(lv_event_t * e);
extern void action_cal_refresh_measured(lv_event_t * e);
extern void action_cal_reset_values(lv_event_t * e);
extern void action_cal_store_values(lv_event_t * e);
extern void action_cal_set_dac(lv_event_t * e);


#endif /*EEZ_LVGL_UI_EVENTS_H*/