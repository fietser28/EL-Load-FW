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
    snprintf((char *)ahstring, 10,"%.3f", (localstatecopy.As/3600.0f));
    lastas = localstatecopy.As;
    }
    return (char *)ahstring;
};

char whstring[16];
float lastws = -1;

void set_var_whmon(const char *value) {  };
const char *get_var_whmon() {
    if (localstatecopy.Ws != lastws) {
    snprintf((char *)whstring, 10,"%.3f", (localstatecopy.Ws/3600.0f));
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


