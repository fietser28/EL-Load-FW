#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *startup;
    lv_obj_t *main;
    lv_obj_t *settings;
    lv_obj_t *events;
    lv_obj_t *protections;
    lv_obj_t *calibration;
    lv_obj_t *nlpc;
    lv_obj_t *ah;
    lv_obj_t *iset;
    lv_obj_t *isetlabel;
    lv_obj_t *main_lower_panel;
    lv_obj_t *mode_selector;
    lv_obj_t *montime;
    lv_obj_t *nlp_c_hom_e_cance_l_1;
    lv_obj_t *nlp_c_hom_e_cancel;
    lv_obj_t *nlp_c_home;
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
    lv_obj_t *obj21__kbtext2;
    lv_obj_t *obj21__obj22;
    lv_obj_t *obj21__obj23;
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
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *obj36;
    lv_obj_t *obj37;
    lv_obj_t *obj38;
    lv_obj_t *obj39;
    lv_obj_t *obj4;
    lv_obj_t *obj40;
    lv_obj_t *obj41;
    lv_obj_t *obj42;
    lv_obj_t *obj43;
    lv_obj_t *obj44;
    lv_obj_t *obj45;
    lv_obj_t *obj46;
    lv_obj_t *obj47;
    lv_obj_t *obj48;
    lv_obj_t *obj49;
    lv_obj_t *obj5;
    lv_obj_t *obj50;
    lv_obj_t *obj51;
    lv_obj_t *obj52;
    lv_obj_t *obj53;
    lv_obj_t *obj54;
    lv_obj_t *obj55;
    lv_obj_t *obj55__kbtext2;
    lv_obj_t *obj55__obj22;
    lv_obj_t *obj55__obj23;
    lv_obj_t *obj56;
    lv_obj_t *obj57;
    lv_obj_t *obj58;
    lv_obj_t *obj59;
    lv_obj_t *obj6;
    lv_obj_t *obj60;
    lv_obj_t *obj61;
    lv_obj_t *obj62;
    lv_obj_t *obj63;
    lv_obj_t *obj64;
    lv_obj_t *obj65;
    lv_obj_t *obj66;
    lv_obj_t *obj67;
    lv_obj_t *obj68;
    lv_obj_t *obj69;
    lv_obj_t *obj7;
    lv_obj_t *obj70;
    lv_obj_t *obj71;
    lv_obj_t *obj72;
    lv_obj_t *obj73;
    lv_obj_t *obj74;
    lv_obj_t *obj74__kbtext2;
    lv_obj_t *obj74__obj22;
    lv_obj_t *obj74__obj23;
    lv_obj_t *obj75;
    lv_obj_t *obj76;
    lv_obj_t *obj77;
    lv_obj_t *obj78;
    lv_obj_t *obj79;
    lv_obj_t *obj8;
    lv_obj_t *obj80;
    lv_obj_t *obj81;
    lv_obj_t *obj82;
    lv_obj_t *obj83;
    lv_obj_t *obj83__obj84;
    lv_obj_t *obj83__obj85;
    lv_obj_t *obj83__obj86;
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

void create_screen_settings();
void tick_screen_settings();

void create_screen_events();
void tick_screen_events();

void create_screen_protections();
void tick_screen_protections();

void create_screen_calibration();
void tick_screen_calibration();

void create_screen_nlpc();
void tick_screen_nlpc();

void create_user_widget_question_yn(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_question_yn(void *flowState, int startWidgetIndex);

void create_user_widget_keyboard_old(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_keyboard_old(void *flowState, int startWidgetIndex);

void create_user_widget_keyboard(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_keyboard(void *flowState, int startWidgetIndex);

void create_screens();
void tick_screen(int screen_index);


extern size_t get_num_screens();
extern lv_obj_t *get_screen_obj(size_t screen_index);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/