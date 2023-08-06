#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#include "util.h"

#ifdef __cplusplus
using namespace dcl;
#endif

typedef enum {
    mode_e_CC = 0,
    mode_e_CV = 1,
    mode_e_CP = 2,
    mode_e_CR = 3,
    mode_e_SHORT = 4
} mode_e;

typedef enum {
    calType_e_Imon = 0,
    calType_e_Umon = 1,
    calType_e_Iset = 2,
    calType_e_Von = 3,
    calType_e_Uset = 4,
    calType_e_OCPset = 5,
    calType_e_OVPset = 6,
    calType_e_Undefined = -1
} calType_e;

typedef enum {
    VonType_e_Unlatched = 0,
    VonType_e_Latched = 1,
    VonType_e_Inhibit = 2
} VonType_e;

typedef enum {
    setTypes_e_current = 0,
    setTypes_e_voltage = 1,
    setTypes_e_power = 2,
    setTypes_e_resistance = 3,
    setTypes_e_von = 4
} setTypes_e;

// For calibration actions
extern calType_e cal_calType;
extern int32_t cal_curpoint;
extern float   cal_measured;
extern float   cal_set;
extern CalibrationValueConfiguration cal_values;

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_DROPDOWNMODEINDEX = 0,
    FLOW_GLOBAL_VARIABLE_SET_VALUE = 1,
    FLOW_GLOBAL_VARIABLE_SET_VALUE_STRING = 2,
    FLOW_GLOBAL_VARIABLE_SET_TYPES = 3,
    FLOW_GLOBAL_VARIABLE_SET_TYPE = 4,
    FLOW_GLOBAL_VARIABLE_PREFIXES = 5,
    FLOW_GLOBAL_VARIABLE_CAL_DATA = 6,
    FLOW_GLOBAL_VARIABLE_VON_LATCHED_TEXT = 7
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
extern bool get_var_show_joules();
extern void set_var_show_joules(bool value);
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
extern float get_var_von_set();
extern void set_var_von_set(float value);
extern float get_var_iset();
extern void set_var_iset(float value);
extern float get_var_uset();
extern void set_var_uset(float value);
extern VonType_e get_var_von_latched();
extern void set_var_von_latched(VonType_e value);
extern float get_var_rset();
extern void set_var_rset(float value);
extern float get_var_pset();
extern void set_var_pset(float value);
extern float get_var_oc_pset();
extern void set_var_oc_pset(float value);
extern float get_var_ov_pset();
extern void set_var_ov_pset(float value);
extern float get_var_op_pset();
extern void set_var_op_pset(float value);
extern float get_var_op_pdelay();
extern void set_var_op_pdelay(float value);
extern float get_var_ot_pset();
extern void set_var_ot_pset(float value);
extern float get_var_ot_pdelay();
extern void set_var_ot_pdelay(float value);
extern bool get_var_precording();
extern void set_var_precording(bool value);
extern const char *get_var_logtxt();
extern void set_var_logtxt(const char *value);
extern int32_t get_var_nplc();
extern void set_var_nplc(int32_t value);
extern int32_t get_var_pl_freq();
extern void set_var_pl_freq(int32_t value);
extern float get_var_sample_rate();
extern void set_var_sample_rate(float value);
extern int32_t get_var_ad_c_osr();
extern void set_var_ad_c_osr(int32_t value);
extern calType_e get_var_cal_cal_type();
extern void set_var_cal_cal_type(calType_e value);
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
extern bool get_var_von_state();
extern void set_var_von_state(bool value);
extern float get_var_temperature();
extern void set_var_temperature(float value);
extern bool get_var_oc_pstate();
extern void set_var_oc_pstate(bool value);
extern bool get_var_ov_pstate();
extern void set_var_ov_pstate(bool value);
extern bool get_var_ot_pstate();
extern void set_var_ot_pstate(bool value);
extern bool get_var_op_pstate();
extern void set_var_op_pstate(bool value);
extern bool get_var_fan_mode_manual();
extern void set_var_fan_mode_manual(bool value);
extern int32_t get_var_fan_set_speed();
extern void set_var_fan_set_speed(int32_t value);
extern int32_t get_var_fan_read_speed();
extern void set_var_fan_read_speed(int32_t value);


#ifdef __cplusplus
}
#endif


#endif /*EEZ_LVGL_UI_VARS_H*/