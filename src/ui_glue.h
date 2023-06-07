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
extern bool clearProtection();
extern bool toggleRecord();
extern void setOnOff(bool value);
extern mode_e get_mode();
extern void set_mode(mode_e newMode);
extern void setIset(float value);
extern void setRset(float value);
extern void setOPPset(float value);
extern void setOPPdelay(float value);

extern void printlogval(int val1, int val2, int val3, int val4);
extern void printstr(const char* txt);
extern char logtxt[256];

extern void set_nplc(int32_t value);
extern int32_t get_adc_osr();

// Calibration page glue
extern void copy_cal_values_from_state(CalibrationValueConfiguration *cal_values, int32_t caltype);
extern void copy_cal_values_to_state(CalibrationValueConfiguration *cal_values, int32_t caltype);
extern void write_cal_to_eeprom(int32_t caltype);

#endif