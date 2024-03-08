// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Glue to EEZ flow vars

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "semphr.h"

#include "main.h"
#include "ui_glue.h"
#include "state.h"
//#include "display.h"
#include "scpi/scpi-def.h"
#include "vars.h"
#include "util.h"

using namespace dcl::scpi;

void set_var_startup_done(bool value) {};
bool get_var_startup_done() { return localsetcopy.startupDone; };

void set_var_alive(bool value) {};

float get_var_op_pset() { return localsetcopy.OPPset; };
void set_var_op_pset(float value) 
{
  state.setOPPset(value);
};

float get_var_op_pdelay() { return localsetcopy.OPPdelay; };
void set_var_op_pdelay(float value)
{
  state.setOPPdelay(value);
};

char imonstring[16];
float lastimon = 0;

void set_var_imon(const char *value) {  };
const char *get_var_imon() {
  // Only format if changed.
  if (localstatecopy.Imon != lastimon) {
    lastimon = localstatecopy.Imon;
    value2str(imonstring, lastimon, -3, 5, 3, true, "A");
  }
  return imonstring;
}

char umonstring[16];
float lastumon;

void set_var_umon(const char *value) {  };
const char *get_var_umon() {
  // Only format if changed.
  if (localstatecopy.Umon != lastumon) {
    lastumon = localstatecopy.Umon;
    //TODO: fix hardcoding of settings
    value2str(umonstring, lastumon, -3, 5, 3, true, "V");
  }
  return umonstring;
}

char pmonstring[16];
float lastpmoni, lastpmonu;

void set_var_pmon(const char *value){};
const char *get_var_pmon()
{
  if (localstatecopy.Imon != lastpmoni || localstatecopy.Umon != lastpmonu)
  {
    value2str(pmonstring, localstatecopy.Umon * localstatecopy.Imon, -3, 4, 3, true, "W");
    lastpmoni = localstatecopy.Imon;
    lastpmonu = localstatecopy.Umon;
  }
  return (char *)pmonstring;
};

char rmonstring[16];
float lastrmoni, lastrmonu;
void set_var_rmon(const char *value) {  };
//float get_var_rmon() { return localstatecopy.Imon != 0.0f ? localstatecopy.Umon/localstatecopy.Imon : INFINITY; };
const char *get_var_rmon() {
    if (localstatecopy.Imon != lastrmoni || localstatecopy.Umon != lastrmonu) 
    {
      lastrmoni = localstatecopy.Imon;
      lastrmonu = localstatecopy.Umon;
      float r = localstatecopy.Imon != 0.0f ? localstatecopy.Umon/localstatecopy.Imon : INFINITY;
      if ( r == INFINITY || r > 1000000 || r < 0) 
      {
        snprintf((char *)rmonstring, 10, "\u221e \u03a9");
      } 
      else 
      {
        //TODO: fix hardcoding of settings
        value2str(rmonstring, r, -2, 4, 3, true, "\u03a9");
      }
    }
    return (char *)rmonstring;
};


char ahstring[16];
float lastas = -1;

void set_var_ahmon(const char *value) {  };
const char *get_var_ahmon() {
    if (localstatecopy.As != lastas) {
    //snprintf((char *)ahstring, 10,"%.3f", (localstatecopy.As/3600.0f));
    value2str(ahstring, localstatecopy.As / 3600.0f, -3, 6, 3, true, "Ah");
    lastas = localstatecopy.As;
    }
    return (char *)ahstring;
};

char whstring[16];
float lastws = -1;
bool lastWhShowJoules = true;
bool whShowJoules = false;

bool get_var_show_joules() { return whShowJoules; };
void set_var_show_joules(bool value) {
  whShowJoules = value;
};

void set_var_whmon(const char *value) {  };
const char *get_var_whmon() {
    if (localstatecopy.Ws != lastws || whShowJoules != lastWhShowJoules) {
      if (whShowJoules) 
      {
        value2str(whstring, localstatecopy.Ws, -3, 6, 3, true, "J");
      } 
      else 
      {
        value2str(whstring, localstatecopy.Ws / 3600.0f, -3, 6, 3, true, "Wh");
      }
    lastws = localstatecopy.Ws;
    lastWhShowJoules = whShowJoules;
    }
    return (char *)whstring;
};

char montimestring[16];
uint32_t lastmontime = -1; // != 0 will trigger initialization to 0.

void set_var_montime(const char *value) {  };
const char *get_var_montime() {
    uint32_t montime = (uint32_t)localstatecopy.Ptime;
    if (montime != lastmontime) { // also roundoff to seconds...
    uint32_t h, m, s;
    h = montime / 3600;
    m = (montime % 3600) / 60;
    s = montime - h * 3600 - m * 60; 
    snprintf((char *)montimestring, 11,"%3d:%02d:%02d", h,m,s);
    lastmontime = montime;
    }
    return (char *)montimestring;
};

void set_var_precording(bool value) {};
bool get_var_precording() 
{
  return localsetcopy.record;
};


void set_var_on(bool value) 
{
  if (value) {
    state.setOn();
  } else {
    state.setOff();
  }
};
bool get_var_on()
{
  return localsetcopy.on;
};

mode_e get_var_mode() { 
  mode_e mode;
  // this maps the state modes to the UI modes.
  switch (localsetcopy.mode)
  {
        case ELmode::CC:
            mode = mode_e_CC;
            break;
        case ELmode::CV:
            mode = mode_e_CV;
            break;
        case ELmode::CR:
            mode = mode_e_CR;
            break;
        case ELmode::CP:
            mode = mode_e_CP;
            break;
        case ELmode::SHORT:
            mode = mode_e_SHORT;
        default:
            mode = mode_e_CC;
            break;
  }
  return mode;
  };

void set_var_mode(mode_e value) {
    state.setMode(value);
};

float get_var_von_set() { return localsetcopy.VonSet; };
void set_var_von_set(float value)
{
  state.setVonset(value, false);
};

float get_var_iset() { return localsetcopy.Iset; }; 
void set_var_iset(float value) 
{
      state.setIset(value, false);
};

float get_var_uset() { return localsetcopy.Uset; };
void set_var_uset(float value)
{
  state.setUset(value, false);
};

VonType_e get_var_von_latched() { return localsetcopy.VonLatched; };
void set_var_von_latched(VonType_e value)
{
  state.setVonLatched(value);
};

float get_var_rset() { return localsetcopy.Rset; }; 
void set_var_rset(float value) 
{
  state.setRset(value);
};

float get_var_pset() { return localsetcopy.Pset; }; 
void set_var_pset(float value) 
{
  state.setPset(value);
};

float get_var_oc_pset() { return localsetcopy.OCPset; };
void set_var_oc_pset(float value)
{
  state.setOCP(value, false);
};

float get_var_ov_pset() { return localsetcopy.OVPset; };
void set_var_ov_pset(float value) 
{
  state.setOVP(value, false);
};

float get_var_ot_pset() { return localsetcopy.OTPset; };
void set_var_ot_pset(float value)
{
  state.setOTPset(value);
};

float get_var_ot_pdelay() { return localsetcopy.OTPdelay; };
void set_var_ot_pdelay(float value)
{
  state.setOTPdelay(value);
};

bool get_var_protection_triggered() { 
  return localsetcopy.protection || localstatecopy.OCPstate || localstatecopy.OVPstate || localstatecopy.OPPstate || localstatecopy.OTPstate; 
};
// TODO: Change into action.
void set_var_protection_triggered(bool value) 
{ 
  state.clearProtection();
};

void set_var_logtxt(const char *value) {};
const char *get_var_logtxt() {
  return (char *)logtxt;
}

void set_var_nplc(int32_t value) 
{
  state.setNPLC((uint32_t)value);
}

int32_t get_var_nplc() 
{
  return localsetcopy.NLPC;
}


void set_var_pl_freq(int32_t value) {};
int32_t get_var_pl_freq() 
{
  return (int32_t)localsetcopy.PLFreq;
}

void set_var_sample_rate(float value) {};
float get_var_sample_rate() 
{
  return localsetcopy.sampleRate;
};

void set_var_adc_osr(int32_t value) {};
int32_t get_var_adc_osr()
{
  return ADC_OSR;

}

//// Calibration variables & some logic.

// Also used by SCPI command/query functions TODO: move to cal.h and make seperate function
calType_e cal_calType = calType_e::calType_e_Undefined; // Force init and copy!
int32_t cal_curpoint = 0; 
float cal_set = 0.0f;                       // This is the changed/temp value.
float cal_measured = 0.0f;                   // This is the changed/temp value.
CalibrationValueConfiguration cal_values;   // This is the changed/temp configuration.

// USED BY SCPI!
calType_e get_var_cal_cal_type() { return cal_calType; };
void set_var_cal_cal_type(calType_e value) { 
  // calType changes to different value, update everything.
  if (value != cal_calType){
    cal_calType = value; 
    copy_cal_values_from_state(&cal_values, cal_calType);
    set_var_cal_curpoint(0);
  }
};

// USED BY SCPI! TODO: move to cal.h/cpp and make seperate function
int32_t get_var_cal_curpoint() { return cal_curpoint; };
void set_var_cal_curpoint(int32_t value) { 
  if (value >= 0 && value < cal_values.numPoints)
  {
    cal_curpoint = value; 
    if (cal_calType == calType_e::calType_e_Imon_High || cal_calType == calType_e::calType_e_Imon_Low || 
        cal_calType == calType_e::calType_e_Umon_High || cal_calType == calType_e::calType_e_Umon_Low) 
    {
      // ADC
      cal_set = cal_values.points[value].value;
      cal_measured = cal_values.points[value].adc;
    } else {
      // DAC
      cal_set = cal_values.points[value].dac;
      cal_measured = cal_values.points[value].value;
    } 
  }
};

// Used by SCPI. TODO: move to cal.h/cpp and make seperate function
float get_var_cal_set() { return cal_set; };
void set_var_cal_set(float value) { 
  cal_set = value; 
  if (cal_calType == calType_e::calType_e_Imon_High || cal_calType == calType_e::calType_e_Imon_Low || 
      cal_calType == calType_e::calType_e_Umon_High || cal_calType == calType_e::calType_e_Umon_Low) 
  {
    cal_values.points[cal_curpoint].value = value;
  } else {
    cal_values.points[cal_curpoint].dac = (int32_t)value;
  }
};

float get_var_cal_measured() { return cal_measured; };
void set_var_cal_measured(float value) { 
  cal_measured = value;
  if (cal_calType == calType_e::calType_e_Imon_High || cal_calType == calType_e::calType_e_Imon_Low || 
      cal_calType == calType_e::calType_e_Umon_High || cal_calType == calType_e::calType_e_Umon_Low) 
  {
    // ADC
    cal_values.points[cal_curpoint].adc = (int32_t)value; 
  } else {
    // DAC
    cal_values.points[cal_curpoint].value = value; 
 }
};

// Used by SCPI TODO: move to cal.h/cpp and make seperate function
int32_t get_var_cal_numpoints() { return cal_values.numPoints; };
void set_var_cal_numpoints(int32_t value) {} ; // TODO: Needed?

const char *get_var_cal_unit() { return ranges[caldefaults[cal_calType].keyBoard].unitName; };
void set_var_cal_unit(const char *value) {}; // Read only.

ranges_e get_var_cal_keyboard() { return caldefaults[cal_calType].keyBoard; };
void set_var_cal_keyboard(ranges_e value) {}; // Read only.

// Used by SCPI TODO: move to cal.h/cpp and make seperate function
bool get_var_calibration_mode() { return localsetcopy.CalibrationMode; };
void set_var_calibration_mode(bool value) {
  state.CalibrationMode(value);
};

// Used by SCPI TODO: move to cal.h/cpp and make seperate function
bool cal_animate = false;
bool get_var_cal_animate() { return cal_animate; };
void set_var_cal_animate(bool value) {
  cal_animate = value;
};

bool cal_triggerMeasure = false;
bool get_var_cal_trigger_measure() { return cal_triggerMeasure; };
void set_var_cal_trigger_measure(bool value) {
  cal_triggerMeasure = value;
};

// Used by SCPI. TODO: move to cal.cpp/h
bool cal_valuesChanged = false;
bool get_var_cal_values_changed() { return cal_valuesChanged; };
void set_var_cal_values_changed(bool value) {
  cal_valuesChanged = value;
};

bool get_var_von_state() { return localstatecopy.VonState; };
void set_var_von_state(bool value) {}; // Read only.

float get_var_temperature() { return max(localstatecopy.Temp1, localstatecopy.Temp2); };
void set_var_temperature(float value) {}; // Read only.

bool get_var_oc_pstate() { return localstatecopy.OCPstate; };
void set_var_oc_pstate(bool value) {}; // Read only.

bool get_var_ov_pstate() { return localstatecopy.OVPstate; };
void set_var_ov_pstate(bool value) {}; // Read only.

bool get_var_ot_pstate() { return localstatecopy.OTPstate; };
void set_var_ot_pstate(bool value) {}; // Read only.

bool get_var_op_pstate() { return localstatecopy.OPPstate; };
void set_var_op_pstate(bool value) {}; // Read only.

bool get_var_fan_mode_manual() { return !localsetcopy.FanAuto; };
void set_var_fan_mode_manual(bool value) 
{
  state.setFanAuto(!value);
};


// Scaled: 1-100% => 20%-100% PWM 
int32_t get_var_fan_set_speed() 
{ 
  return (max(localsetcopy.FanManualSpeed/(2.55 - 0.50)-50,0)); 
};

void set_var_fan_set_speed(int32_t value)
{
  if (value >= 100.0) {
    state.setFanPWM(255);
  } else if (value <= 0.0) {
    state.setFanPWM(0);
  } else {
    state.setFanPWM(value*(2.05) + 50);
  }
};

int32_t get_var_fan_read_speed() { return localstatecopy.FanRPM; };
void set_var_fan_read_speed(int32_t value) {}; // Read only.

bool get_var_range_current_low() 
{
  return localsetcopy.rangeCurrentLow;
};

void set_var_range_current_low(bool value)
{
  state.setRangeCurrent(value);
};

bool get_var_range_voltage_low() 
{
  return localsetcopy.rangeVoltageLow;
};

void set_var_range_voltage_low(bool value)
{
  state.setRangeVoltage(value);
};

bool get_var_remote_sense_voltage()
{
  return localsetcopy.senseVoltRemote;
};
void set_var_remote_sense_voltage(bool value)
{
  state.setVoltSense(value);
};

//ranges_e get_var_range_select() { return range_select; };
//void set_var_range_select(ranges_e value) { range_select = value; };
float get_var_cap_volt_stop() {  return localsetcopy.CapVoltStop; };
void set_var_cap_volt_stop(float value) { state.setCapVoltStop(value); };

float get_var_cap_ah_stop() { return localsetcopy.CapAhStop; };
void set_var_cap_ah_stop(float value) { state.setCapAhStop(value); };

float get_var_cap_wh_stop() { return localsetcopy.CapWhStop; };
void set_var_cap_wh_stop(float value) { state.setCapWhStop(value); };

float get_var_cap_time_stop() { return localsetcopy.CapTimeStop; };
void set_var_cap_time_stop(float value) { state.setCapTimeStop(value); };

bool get_var_cap_volt_stop_triggered() { return localstatecopy.CapVoltStopTriggered; };
void set_var_cap_volt_stop_triggered(bool value) {}; //Read only. 
bool get_var_cap_ah_stop_triggered() { return localstatecopy.CapAhStopTriggered; };
void set_var_cap_ah_stop_triggered(bool value) {}; // Read only.
bool get_var_cap_time_stop_triggered() { return localstatecopy.CapTimeStopTriggered; };
void set_var_cap_time_stop_triggered(bool value) {}; // Read only.
bool get_var_cap_limit_triggered() { return localsetcopy.capacityLimit; };
void set_var_cap_limit_triggered(bool value) {}; // Read only. 
bool get_var_cap_wh_stop_triggered() { return localstatecopy.CapWhStopTriggered; };
void set_var_cap_wh_stop_triggered(bool value) {}; // Read only.
bool get_var_cap_limit_enabled() { return localsetcopy.capacityLimitEnabled; };
void set_var_cap_limit_enabled(bool value) {
    state.setCapacityLimitEnabled(value);
};

