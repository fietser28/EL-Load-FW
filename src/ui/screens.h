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
    lv_obj_t *ah;
    lv_obj_t *iset;
    lv_obj_t *isetkey;
    lv_obj_t *isetkey_value;
    lv_obj_t *isetkeyb;
    lv_obj_t *isetlabel;
    lv_obj_t *isetlkeyabel;
    lv_obj_t *mode_selector;
    lv_obj_t *montime;
    lv_obj_t *nlpc_home;
    lv_obj_t *nlpc_home_cancel;
    lv_obj_t *nlpc_home_cancel_1;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj2;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
    lv_obj_t *obj26;
    lv_obj_t *obj27;
    lv_obj_t *obj28;
    lv_obj_t *obj29;
    lv_obj_t *obj3;
    lv_obj_t *obj30;
    lv_obj_t *obj31;
    lv_obj_t *obj32;
    lv_obj_t *obj33;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *on_off_button;
    lv_obj_t *power_panel;
    lv_obj_t *set_value_area;
    lv_obj_t *von_panel;
    lv_obj_t *vonlabel;
    lv_obj_t *wh;
    lv_obj_t *wheel;
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