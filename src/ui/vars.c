// Glue to EEZ flow vars

#include "Arduino.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "semphr.h"

#include "ui_glue.h"
#include "state.h"
//#include "display.h"
#include "vars.h"

void set_var_startup_done(bool value) {};
bool get_var_startup_done() { return localsetcopy.startupDone; };

void set_var_alive(bool value) {};

char imonstring[16];
float lastimon;

//void set_var_imon(const char *value) {  };
void set_var_imon(float value) {   };
float get_var_imon() { return localstatecopy.Imon; };
/*
 const char *get_var_imon() { 
    if (localstatecopy.Imon != lastimon) {
    if (localstatecopy.Imon < 1.0f) {
      snprintf((char *)imonstring, 10,"%3.0f m", localstatecopy.Imon*1000.0f);
    } else {
      snprintf((char *)imonstring, 10,"%.3f ", localstatecopy.Imon);
    }
    lastimon = localstatecopy.Imon;
    }
    return (char *)imonstring;
//  return localstatecopy.Imon;
};
*/ 
char umonstring[16];
float lastumon;

//void set_var_umon(const char *value) {  };
void set_var_umon(float value) { };
float get_var_umon() { return localstatecopy.Umon; };

/*
const char *get_var_umon() {
    if (localstatecopy.Umon != lastumon) {
    snprintf((char *)umonstring, 10,"%.3f", localstatecopy.Umon);
    lastumon = localstatecopy.Umon;
    }
    return (char *)umonstring;
};
*/

char pmonstring[16];
float lastpmoni, lastpmonu;

//void set_var_pmon(const char *value) {  };
void set_var_pmon(float value) {};
float get_var_pmon() { return localstatecopy.Umon*localstatecopy.Imon; };
/*
const char *get_var_pmon() {
    if (localstatecopy.Imon != lastpmoni || localstatecopy.Umon != lastpmonu) {
    snprintf((char *)pmonstring, 10,"%.3f", (localstatecopy.Umon*localstatecopy.Imon));
    lastpmoni = localstatecopy.Imon;
    lastpmonu = localstatecopy.Umon;
    }
    return (char *)pmonstring;
};
*/

char rmonstring[16];
float lastrmoni, lastrmonu;

//void set_var_rmon(const char *value) {  };
void set_var_rmon(float value) {  };
float get_var_rmon() { return localstatecopy.Imon != 0.0f ? localstatecopy.Umon/localstatecopy.Imon : INFINITY; };
//float get_var_rmon() { return (localstatecopy.Umon/localstatecopy.Imon); };
/*
const char *get_var_rmon() {
    if (localstatecopy.Imon != lastrmoni || localstatecopy.Umon != lastrmonu) {
    snprintf((char *)rmonstring, 10,"%.3f", (localstatecopy.Umon/localstatecopy.Imon));
    lastrmoni = localstatecopy.Imon;
    lastrmonu = localstatecopy.Umon;
    }
    return (char *)rmonstring;
};
*/

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

void set_var_imon_nplc(int32_t value) 
{
  set_imon_nplc(value);
}
int32_t get_var_imon_nplc() 
{
  return localsetcopy.ImonNLPC;
}

void set_var_umon_nplc(int32_t value) 
{
  set_umon_nplc(value);
}
int32_t get_var_umon_nplc() 
{
  return localsetcopy.UmonNLPC;
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


