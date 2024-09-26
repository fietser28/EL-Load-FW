#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _groups_t {
    lv_group_t *encoder_group;
} groups_t;

extern groups_t groups;

typedef struct _objects_t {
    lv_obj_t *startup;
    lv_obj_t *main;
    lv_obj_t *capacity;
    lv_obj_t *settings;
    lv_obj_t *events;
    lv_obj_t *ranges;
    lv_obj_t *nplc;
    lv_obj_t *protections;
    lv_obj_t *calibration;
    lv_obj_t *fan;
    lv_obj_t *display;
    lv_obj_t *info;
    lv_obj_t *ah;
    lv_obj_t *ah_2;
    lv_obj_t *ah_3;
    lv_obj_t *ah_4;
    lv_obj_t *ah_5;
    lv_obj_t *ah_6;
    lv_obj_t *ah_7;
    lv_obj_t *current_range;
    lv_obj_t *display_off;
    lv_obj_t *isetlabel_1;
    lv_obj_t *main_dvm;
    lv_obj_t *main_lower_panel;
    lv_obj_t *main_measure;
    lv_obj_t *mode_selector;
    lv_obj_t *montime;
    lv_obj_t *myspinbox;
    lv_obj_t *nlpc_back;
    lv_obj_t *nlpc_cancel;
    lv_obj_t *nlpc_home;
    lv_obj_t *nlpc_home_1;
    lv_obj_t *nlpc_home_2;
    lv_obj_t *nlpc_home_4;
    lv_obj_t *nlpc_home_cancel;
    lv_obj_t *nlpc_home_cancel_1;
    lv_obj_t *nlpc_home_cancel_2;
    lv_obj_t *nlpc_home_cancel_3;
    lv_obj_t *nlpc_home_cancel_4;
    lv_obj_t *nlpc_home_cancel_5;
    lv_obj_t *nlpc_ok;
    lv_obj_t *nplc_nplc;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj10;
    lv_obj_t *obj100;
    lv_obj_t *obj101;
    lv_obj_t *obj102;
    lv_obj_t *obj103;
    lv_obj_t *obj104;
    lv_obj_t *obj105;
    lv_obj_t *obj106;
    lv_obj_t *obj107;
    lv_obj_t *obj108;
    lv_obj_t *obj109;
    lv_obj_t *obj11;
    lv_obj_t *obj110;
    lv_obj_t *obj110__kbtext2;
    lv_obj_t *obj110__max_button;
    lv_obj_t *obj110__min_button;
    lv_obj_t *obj110__obj30;
    lv_obj_t *obj110__obj31;
    lv_obj_t *obj111;
    lv_obj_t *obj112;
    lv_obj_t *obj113;
    lv_obj_t *obj114;
    lv_obj_t *obj115;
    lv_obj_t *obj116;
    lv_obj_t *obj117;
    lv_obj_t *obj118;
    lv_obj_t *obj119;
    lv_obj_t *obj12;
    lv_obj_t *obj120;
    lv_obj_t *obj121;
    lv_obj_t *obj122;
    lv_obj_t *obj123;
    lv_obj_t *obj124;
    lv_obj_t *obj125;
    lv_obj_t *obj126;
    lv_obj_t *obj127;
    lv_obj_t *obj128;
    lv_obj_t *obj129;
    lv_obj_t *obj129__kbtext2;
    lv_obj_t *obj129__max_button;
    lv_obj_t *obj129__min_button;
    lv_obj_t *obj129__obj30;
    lv_obj_t *obj129__obj31;
    lv_obj_t *obj13;
    lv_obj_t *obj130;
    lv_obj_t *obj131;
    lv_obj_t *obj132;
    lv_obj_t *obj133;
    lv_obj_t *obj134;
    lv_obj_t *obj135;
    lv_obj_t *obj136;
    lv_obj_t *obj137;
    lv_obj_t *obj138;
    lv_obj_t *obj139;
    lv_obj_t *obj139__obj82;
    lv_obj_t *obj139__sure_but_no;
    lv_obj_t *obj139__sure_but_yes;
    lv_obj_t *obj139__sure_label_no;
    lv_obj_t *obj139__sure_label_yes;
    lv_obj_t *obj14;
    lv_obj_t *obj140;
    lv_obj_t *obj141;
    lv_obj_t *obj142;
    lv_obj_t *obj143;
    lv_obj_t *obj144;
    lv_obj_t *obj145;
    lv_obj_t *obj146;
    lv_obj_t *obj147;
    lv_obj_t *obj148;
    lv_obj_t *obj148__obj82;
    lv_obj_t *obj148__sure_but_no;
    lv_obj_t *obj148__sure_but_yes;
    lv_obj_t *obj148__sure_label_no;
    lv_obj_t *obj148__sure_label_yes;
    lv_obj_t *obj149;
    lv_obj_t *obj15;
    lv_obj_t *obj150;
    lv_obj_t *obj151;
    lv_obj_t *obj152;
    lv_obj_t *obj153;
    lv_obj_t *obj154;
    lv_obj_t *obj155;
    lv_obj_t *obj156;
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
    lv_obj_t *obj29__kbtext2;
    lv_obj_t *obj29__max_button;
    lv_obj_t *obj29__min_button;
    lv_obj_t *obj29__obj30;
    lv_obj_t *obj29__obj31;
    lv_obj_t *obj3;
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
    lv_obj_t *obj52__kbtext2;
    lv_obj_t *obj52__max_button;
    lv_obj_t *obj52__min_button;
    lv_obj_t *obj52__obj30;
    lv_obj_t *obj52__obj31;
    lv_obj_t *obj53;
    lv_obj_t *obj54;
    lv_obj_t *obj55;
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
    lv_obj_t *obj75;
    lv_obj_t *obj76;
    lv_obj_t *obj77;
    lv_obj_t *obj78;
    lv_obj_t *obj79;
    lv_obj_t *obj8;
    lv_obj_t *obj80;
    lv_obj_t *obj81;
    lv_obj_t *obj81__obj82;
    lv_obj_t *obj81__sure_but_no;
    lv_obj_t *obj81__sure_but_yes;
    lv_obj_t *obj81__sure_label_no;
    lv_obj_t *obj81__sure_label_yes;
    lv_obj_t *obj83;
    lv_obj_t *obj84;
    lv_obj_t *obj85;
    lv_obj_t *obj86;
    lv_obj_t *obj87;
    lv_obj_t *obj88;
    lv_obj_t *obj89;
    lv_obj_t *obj89__obj82;
    lv_obj_t *obj89__sure_but_no;
    lv_obj_t *obj89__sure_but_yes;
    lv_obj_t *obj89__sure_label_no;
    lv_obj_t *obj89__sure_label_yes;
    lv_obj_t *obj9;
    lv_obj_t *obj90;
    lv_obj_t *obj91;
    lv_obj_t *obj92;
    lv_obj_t *obj93;
    lv_obj_t *obj94;
    lv_obj_t *obj95;
    lv_obj_t *obj96;
    lv_obj_t *obj97;
    lv_obj_t *obj98;
    lv_obj_t *obj99;
    lv_obj_t *on_off_button;
    lv_obj_t *on_off_button_1;
    lv_obj_t *pl_freq;
    lv_obj_t *power_panel;
    lv_obj_t *protection_and_temp;
    lv_obj_t *range_current;
    lv_obj_t *range_volt;
    lv_obj_t *range_volt_1;
    lv_obj_t *sense;
    lv_obj_t *sense_indicator;
    lv_obj_t *set_value;
    lv_obj_t *volt_range;
    lv_obj_t *von_panel;
    lv_obj_t *vonlabel;
    lv_obj_t *wh;
    lv_obj_t *wheel;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_STARTUP = 1,
    SCREEN_ID_MAIN = 2,
    SCREEN_ID_CAPACITY = 3,
    SCREEN_ID_SETTINGS = 4,
    SCREEN_ID_EVENTS = 5,
    SCREEN_ID_RANGES = 6,
    SCREEN_ID_NPLC = 7,
    SCREEN_ID_PROTECTIONS = 8,
    SCREEN_ID_CALIBRATION = 9,
    SCREEN_ID_FAN = 10,
    SCREEN_ID_DISPLAY = 11,
    SCREEN_ID_INFO = 12,
    SCREEN_ID_QUESTION_YN = 13,
    SCREEN_ID_KEYBOARD = 14,
};

void create_screen_startup();
void tick_screen_startup();

void create_screen_main();
void tick_screen_main();

void create_screen_capacity();
void tick_screen_capacity();

void create_screen_settings();
void tick_screen_settings();

void create_screen_events();
void tick_screen_events();

void create_screen_ranges();
void tick_screen_ranges();

void create_screen_nplc();
void tick_screen_nplc();

void create_screen_protections();
void tick_screen_protections();

void create_screen_calibration();
void tick_screen_calibration();

void create_screen_fan();
void tick_screen_fan();

void create_screen_display();
void tick_screen_display();

void create_screen_info();
void tick_screen_info();

void create_user_widget_question_yn(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_question_yn(void *flowState, int startWidgetIndex);

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