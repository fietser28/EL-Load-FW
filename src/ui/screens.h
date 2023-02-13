#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *startup;
    lv_obj_t *main;
    lv_obj_t *set_value;
    lv_obj_t *graph;
    lv_obj_t *settings;
    lv_obj_t *nlpc;
    lv_obj_t *mode_selector;
    lv_obj_t *on_off_button;
    lv_obj_t *power_panel;
    lv_obj_t *ah;
    lv_obj_t *wh;
    lv_obj_t *montime;
    lv_obj_t *iset;
    lv_obj_t *isetlabel;
    lv_obj_t *set_value_area;
    lv_obj_t *von_panel;
    lv_obj_t *vonlabel;
    lv_obj_t *wheel;
    lv_obj_t *isetkeyb;
    lv_obj_t *isetkey;
    lv_obj_t *isetlkeyabel;
    lv_obj_t *isetkey_value;
    lv_obj_t *nlpc_home;
    lv_obj_t *nlpc_home_cancel;
    lv_obj_t *nlpc_home_cancel_1;
    lv_obj_t *label_1;
    lv_obj_t *textarea_1;
    lv_obj_t *roller_1;
    lv_obj_t *textarea_2;
    lv_obj_t *label_2;
    lv_obj_t *label_3;
    lv_obj_t *label_4;
    lv_obj_t *label_5;
    lv_obj_t *label_6;
    lv_obj_t *label_7;
    lv_obj_t *label_8;
    lv_obj_t *label_9;
    lv_obj_t *label_10;
    lv_obj_t *label_11;
    lv_obj_t *label_12;
    lv_obj_t *label_13;
    lv_obj_t *label_14;
    lv_obj_t *label_15;
    lv_obj_t *label_16;
    lv_obj_t *label_17;
    lv_obj_t *label_18;
    lv_obj_t *label_19;
    lv_obj_t *label_20;
} objects_t;

extern objects_t objects;

void create_screen_startup();
void tick_screen_startup();

void create_screen_main();
void tick_screen_main();

void create_screen_set_value();
void tick_screen_set_value();

void create_screen_graph();
void tick_screen_graph();

void create_screen_settings();
void tick_screen_settings();

void create_screen_nlpc();
void tick_screen_nlpc();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/