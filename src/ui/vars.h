#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>
#include "util.h"

#ifdef __cplusplus
using namespace dcl;
#endif

// For calibration actions
extern int32_t cal_calType;
extern int32_t cal_curpoint;
extern float   cal_measured;
extern float   cal_set;
extern CalibrationValueConfiguration cal_values;


typedef enum {
    mode_e_CC = 0,
    mode_e_CV = 1,
    mode_e_CP = 2,
    mode_e_CR = 3,
    mode_e_SHORT = 4
} mode_e;

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_VON_SET = 0,
    FLOW_GLOBAL_VARIABLE_DROPDOWNMODEINDEX = 1,
    FLOW_GLOBAL_VARIABLE_SET_VALUE = 2,
    FLOW_GLOBAL_VARIABLE_SET_VALUE_STRING = 3,
    FLOW_GLOBAL_VARIABLE_SET_TYPES = 4,
    FLOW_GLOBAL_VARIABLE_SET_TYPE = 5,
    FLOW_GLOBAL_VARIABLE_USET = 6,
    FLOW_GLOBAL_VARIABLE_VON_LATCHED = 7,
    FLOW_GLOBAL_VARIABLE_OCPSET = 8,
    FLOW_GLOBAL_VARIABLE_OVPSET = 9,
    FLOW_GLOBAL_VARIABLE_OTPSET = 10,
    FLOW_GLOBAL_VARIABLE_OTPDELAY = 11,
    FLOW_GLOBAL_VARIABLE_PREFIXES = 12,
    FLOW_GLOBAL_VARIABLE_CAL_DATA = 13
};

// Native global variables

#ifdef __cplusplus
extern "C" {
#endif

extern bool get_var_startup_done();
extern void set_var_startup_done(bool value);
extern const char *get_var_imon();
extern void set_var_imon(const char *value);
extern const char *get_var_umon();
extern void set_var_umon(const char *value);
extern const char *get_var_pmon();
extern void set_var_pmon(const char *value);
extern const char *get_var_rmon();
extern void set_var_rmon(const char *value);
extern const char *get_var_ahmon();
extern void set_var_ahmon(const char *value);
extern const char *get_var_whmon();
extern void set_var_whmon(const char *value);
extern const char *get_var_montime();
extern void set_var_montime(const char *value);
extern bool get_var_on();
extern void set_var_on(bool value);
extern bool get_var_alive();
extern void set_var_alive(bool value);
extern mode_e get_var_mode();
extern void set_var_mode(mode_e value);
extern float get_var_iset();
extern void set_var_iset(float value);
extern float get_var_rset();
extern void set_var_rset(float value);
extern float get_var_pset();
extern void set_var_pset(float value);
extern float get_var_oppset();
extern void set_var_oppset(float value);
extern float get_var_oppdelay();
extern void set_var_oppdelay(float value);
extern bool get_var_precording();
extern void set_var_precording(bool value);
extern const char *get_var_logtxt();
extern void set_var_logtxt(const char *value);
extern int32_t get_var_nplc();
extern void set_var_nplc(int32_t value);
extern int32_t get_var_plfreq();
extern void set_var_plfreq(int32_t value);
extern float get_var_sample_rate();
extern void set_var_sample_rate(float value);
extern int32_t get_var_adc_osr();
extern void set_var_adc_osr(int32_t value);
extern int32_t get_var_cal_cal_type();
extern void set_var_cal_cal_type(int32_t value);
extern int32_t get_var_cal_curpoint();
extern void set_var_cal_curpoint(int32_t value);
extern float get_var_cal_set();
extern void set_var_cal_set(float value);
extern float get_var_cal_measured();
extern void set_var_cal_measured(float value);
extern int32_t get_var_cal_numpoints();
extern void set_var_cal_numpoints(int32_t value);
extern bool get_var_protection_triggered();
extern void set_var_protection_triggered(bool value);


#ifdef __cplusplus
}
#endif


#endif /*EEZ_LVGL_UI_VARS_H*/