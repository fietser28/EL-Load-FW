#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_clear_power(lv_event_t * e);
extern void action_toggle_record(lv_event_t * e);
extern void action_cal_refresh_measured(lv_event_t * e);
extern void action_cal_reset_values(lv_event_t * e);
extern void action_cal_store_values(lv_event_t * e);
extern void action_cal_set_dac(lv_event_t * e);
extern void action_cal_store_defaults(lv_event_t * e);
extern void action_display_off(lv_event_t * e);
extern void action_display_on(lv_event_t * e);
extern void action_get_type_data(lv_event_t * e);
extern void action_clear_capacity_limits(lv_event_t * e);
extern void action_scpi_busy_incr(lv_event_t * e);
extern void action_scpi_busy_decr(lv_event_t * e);

enum {
    ACTION_BEEP_PROPERTY_DURATION,
};
extern void action_beep(lv_event_t * e);


enum {
    ACTION_CLEAR_STAT_PROPERTY_TYPE,
};
extern void action_clear_stat(lv_event_t * e);


enum {
    ACTION_FORMAT_STAT_PROPERTY_TYPE,
};
extern void action_format_stat(lv_event_t * e);

extern void action_events_table_setup(lv_event_t * e);
extern void action_events_table_load(lv_event_t * e);


#ifdef __cplusplus
}
#endif


#endif /*EEZ_LVGL_UI_EVENTS_H*/