#ifndef UI_GLUE_H
#define UI_GLUE_H
#include "Arduino.h"
#include <stdint.h>
#include <stdbool.h>
#include <lvgl.h>
#include "state.h"

extern struct measuredStateStruct localstatecopy;
extern struct setStateStruct      localsetcopy;

extern lv_group_t *encoder_group;
extern lv_group_t *onoff_group;

extern void ui_init_encoder_group();

extern bool clearPower();
extern bool toggleRecord();
extern void setOnOff(bool value);

extern void printlogval(int val1, int val2, int val3, int val4);
extern char logtxt[256];

extern void set_nplc(int32_t value);

#endif