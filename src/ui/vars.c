// Glue to EEZ flow vars

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "semphr.h"

#include "ui_glue.h"
#include "state.h"
//#include "display.h"
#include "vars.h"
#include "util.h"

void set_var_startup_done(bool value) {};
bool get_var_startup_done() { return localsetcopy.startupDone; };

void set_var_alive(bool value) {};

float get_var_oppset() { return localsetcopy.OPPset; };
void set_var_oppset(float value) 
{
  setOPPset(value);
};
float get_var_oppdelay() { return localsetcopy.OPPdelay; };
void set_var_oppdelay(float value)
{
  setOPPdelay(value);
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
      if ( r != INFINITY) 
      {
        //TODO: fix hardcoding of settings
        value2str(rmonstring, r, -2, 4, 3, true, "\u03a9");
      } 
      else 
      {
        snprintf((char *)rmonstring, 10, "INF \u03a9");
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

void set_var_whmon(const char *value) {  };
const char *get_var_whmon() {
    if (localstatecopy.Ws != lastws) {
    //snprintf((char *)whstring, 10,"%.3f", (localstatecopy.Ws/3600.0f));
    value2str(whstring, localstatecopy.Ws / 3600.0f, -3, 6, 3, true, "Wh");
    lastws = localstatecopy.Ws;
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
  setOnOff(value);
};
bool get_var_on()
{
  return localsetcopy.on;
};

mode_e get_var_mode() { return get_mode(); };
void set_var_mode(mode_e value) {
  return set_mode(value);
};


float get_var_iset() { return localsetcopy.Iset; }; 
void set_var_iset(float value) 
{
  setIset(value, false);
};

float get_var_rset() { return localsetcopy.Rset; }; 
void set_var_rset(float value) 
{
  setRset(value);
};

float get_var_pset() { return localsetcopy.Pset; }; 
void set_var_pset(float value) 
{
  setPset(value);
};


bool get_var_protection_triggered() { return localsetcopy.protection; };
void set_var_protection_triggered(bool value) 
{ 
  clearProtection();
};

void set_var_logtxt(const char *value) {};
const char *get_var_logtxt() {
  return (char *)logtxt;
}

void set_var_nplc(int32_t value) 
{
  set_nplc(value);
}
int32_t get_var_nplc() 
{
  return localsetcopy.NLPC;
}


void set_var_plfreq(int32_t value) {};
int32_t get_var_plfreq() 
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
  return get_adc_osr();
}

//// Calibration variables & some logic.

int32_t cal_calType = -1; // Force init and copy!
int32_t cal_curpoint = 0; 
float cal_set = 0.0f;                       // This is the changed/temp value.
float cal_measured = 0.0f;                   // This is the changed/temp value.
CalibrationValueConfiguration cal_values;   // This is the changed/temp configuration.

int32_t get_var_cal_cal_type() { return cal_calType; };
void set_var_cal_cal_type(int32_t value) { 
  // calType changes to different value, update everything.
  if (value != cal_calType){
    cal_calType = value; 
    copy_cal_values_from_state(&cal_values, cal_calType);
    set_var_cal_curpoint(0);
  }
};

int32_t get_var_cal_curpoint() { return cal_curpoint; };
void set_var_cal_curpoint(int32_t value) { 
  if (value >= 0 && value < cal_values.numPoints)
  {
    cal_curpoint = value; 
    if (cal_calType <= 1) {
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

float get_var_cal_set() { return cal_set; };
void set_var_cal_set(float value) { 
  cal_set = value; 
  if (cal_calType <= 1) {
    cal_values.points[cal_curpoint].value = value;
  } else {
    cal_values.points[cal_curpoint].dac = (int32_t)value;
  }
};

float get_var_cal_measured() { return cal_measured; };
void set_var_cal_measured(float value) { 
  cal_measured = value;
  if (cal_calType <= 1) 
  {
    // ADC
    cal_values.points[cal_curpoint].adc = (int32_t)value; 
  } else {
    // DAC
    cal_values.points[cal_curpoint].value = value; 
 }
};

int32_t get_var_cal_numpoints() { return cal_values.numPoints; };
void set_var_cal_numpoints(int32_t value) {} ; // TODO: Needed?

