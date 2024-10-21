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
    mode_e_SHORT = 4,
    mode_e_DVM = 5
} mode_e;

typedef enum {
    calType_e_Imon_High = 0,
    calType_e_Imon_Low = 1,
    calType_e_Umon_High = 2,
    calType_e_Umon_Low = 3,
    calType_e_Iset_High = 4,
    calType_e_Iset_Low = 5,
    calType_e_Uset_High = 6,
    calType_e_Uset_Low = 7,
    calType_e_Von_High = 8,
    calType_e_Von_Low = 9,
    calType_e_OCPset_High = 10,
    calType_e_OCPset_Low = 11,
    calType_e_OVPset_High = 12,
    calType_e_OVPset_Low = 13,
    calType_e_Undefined = -1
} calType_e;

typedef enum {
    calCalType_e_ADC = 0,
    calCalType_e_DAC = 1,
    calCalType_e_LEVEL = 2
} calCalType_e;

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

typedef enum {
    ranges_e_Curr_High = 0,
    ranges_e_Curr_Low = 1,
    ranges_e_Volt_High = 2,
    ranges_e_Volt_Low = 3,
    ranges_e_Power = 4,
    ranges_e_Res = 5,
    ranges_e_Von_High = 6,
    ranges_e_Von_Low = 7,
    ranges_e_OCP_High = 8,
    ranges_e_OCP_Low = 9,
    ranges_e_OVP_High = 10,
    ranges_e_OVP_Low = 11,
    ranges_e_OPP_Power = 12,
    ranges_e_OPP_Delay = 13,
    ranges_e_OTP_Temp = 14,
    ranges_e_OTP_Delay = 15,
    ranges_e_Curr_Cal = 16,
    ranges_e_Volt_Cal = 17,
    ranges_e_DAC16b = 18,
    ranges_e_AHStop = 19,
    ranges_e_TimeStop = 20,
    ranges_e_VoltStop = 21,
    ranges_e_WHStop = 22,
    ranges_e_FanSpeed = 23,
    ranges_e_WatchdogDelay = 24,
    ranges_e_beepDuration = 25
} ranges_e;

// For calibration actions
extern calType_e cal_calType;
extern int32_t cal_curpoint;
extern float   cal_measured;
extern float   cal_set;
extern CalibrationValueConfiguration cal_values;

extern bool cal_valuesChanged;

// For encoder 
//extern float setValue;
//extern float setValueNew;


// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_DROPDOWNMODEINDEX = 0,
    FLOW_GLOBAL_VARIABLE_SET_VALUE = 1,
    FLOW_GLOBAL_VARIABLE_SET_VALUE_STRING = 2,
    FLOW_GLOBAL_VARIABLE_SET_TYPES = 3,
    FLOW_GLOBAL_VARIABLE_SET_TYPE = 4,
    FLOW_GLOBAL_VARIABLE_PREFIXES = 5,
    FLOW_GLOBAL_VARIABLE_CAL_DATA = 6,
    FLOW_GLOBAL_VARIABLE_VON_LATCHED_TEXT = 7,
    FLOW_GLOBAL_VARIABLE_DISPLAY_BACKLIGHT = 8,
    FLOW_GLOBAL_VARIABLE_RANGE_PROPERTIES = 9,
    FLOW_GLOBAL_VARIABLE_RANGE_TYPE = 10,
    FLOW_GLOBAL_VARIABLE_SET_VALUE_STR_FORMATTED = 11,
    FLOW_GLOBAL_VARIABLE_SET_VALUE_NEW = 12,
    FLOW_GLOBAL_VARIABLE_SET_VALUE_POINT_POS = 13,
    FLOW_GLOBAL_VARIABLE_SET_VALUE_STR_FORMATTED_LENGTH = 14,
    FLOW_GLOBAL_VARIABLE_SET_VALUE_INT = 15,
    FLOW_GLOBAL_VARIABLE_SET_VALUE_INT_IN = 16,
    FLOW_GLOBAL_VARIABLE_SET_VALUE_INT_DIR = 17
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
extern int32_t get_var_adc_osr();
extern void set_var_adc_osr(int32_t value);
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
extern bool get_var_range_current_low();
extern void set_var_range_current_low(bool value);
extern bool get_var_range_voltage_low();
extern void set_var_range_voltage_low(bool value);
extern bool get_var_remote_sense_voltage();
extern void set_var_remote_sense_voltage(bool value);
extern float get_var_cap_volt_stop();
extern void set_var_cap_volt_stop(float value);
extern float get_var_cap_ah_stop();
extern void set_var_cap_ah_stop(float value);
extern float get_var_cap_time_stop();
extern void set_var_cap_time_stop(float value);
extern bool get_var_cap_volt_stop_triggered();
extern void set_var_cap_volt_stop_triggered(bool value);
extern bool get_var_cap_ah_stop_triggered();
extern void set_var_cap_ah_stop_triggered(bool value);
extern bool get_var_cap_time_stop_triggered();
extern void set_var_cap_time_stop_triggered(bool value);
extern bool get_var_cap_limit_triggered();
extern void set_var_cap_limit_triggered(bool value);
extern float get_var_cap_wh_stop();
extern void set_var_cap_wh_stop(float value);
extern bool get_var_cap_wh_stop_triggered();
extern void set_var_cap_wh_stop_triggered(bool value);
extern const char *get_var_cal_unit();
extern void set_var_cal_unit(const char *value);
extern ranges_e get_var_cal_keyboard();
extern void set_var_cal_keyboard(ranges_e value);
extern bool get_var_calibration_mode();
extern void set_var_calibration_mode(bool value);
extern bool get_var_cal_animate();
extern void set_var_cal_animate(bool value);
extern bool get_var_cal_trigger_measure();
extern void set_var_cal_trigger_measure(bool value);
extern bool get_var_cal_values_changed();
extern void set_var_cal_values_changed(bool value);
extern bool get_var_cap_limit_enabled();
extern void set_var_cap_limit_enabled(bool value);
extern bool get_var_sense_error();
extern void set_var_sense_error(bool value);
extern bool get_var_polarity_error();
extern void set_var_polarity_error(bool value);
extern const char *get_var_version_lvgl();
extern void set_var_version_lvgl(const char *value);
extern const char *get_var_version_arduino_pico();
extern void set_var_version_arduino_pico(const char *value);
extern const char *get_var_version_tft_espi();
extern void set_var_version_tft_espi(const char *value);
extern const char *get_var_version_freertos();
extern void set_var_version_freertos(const char *value);
extern const char *get_var_version_dcl();
extern void set_var_version_dcl(const char *value);
extern int32_t get_var_version_cpu_freq();
extern void set_var_version_cpu_freq(int32_t value);
extern const char *get_var_version_cpu_type();
extern void set_var_version_cpu_type(const char *value);
extern int32_t get_var_version_hw_version();
extern void set_var_version_hw_version(int32_t value);
extern int32_t get_var_fan_read_speed2();
extern void set_var_fan_read_speed2(int32_t value);
extern bool get_var_beep_on_protect();
extern void set_var_beep_on_protect(bool value);
extern bool get_var_beep_on_capacity();
extern void set_var_beep_on_capacity(bool value);
extern bool get_var_beep_on_reverse();
extern void set_var_beep_on_reverse(bool value);
extern bool get_var_beep_on_encoder();
extern void set_var_beep_on_encoder(bool value);
extern float get_var_beep_default_duration();
extern void set_var_beep_default_duration(float value);


#ifdef __cplusplus
}
#endif


#endif /*EEZ_LVGL_UI_VARS_H*/