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
#include <TFT_eSPI.h>

#include "pico.h"
#include "hardware/address_mapped.h"
#include "hardware/regs/tbman.h"
#include "hardware/regs/sysinfo.h"

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
    if (localsetcopy.rangeCurrentLow == true) {
      //TODO: fix hardcoding of settings
      value2str(imonstring, lastimon, -4, 5, 3, true, "A");
    } else {
      value2str(imonstring, lastimon, -3, 5, 3, true, "A");
    }
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
    if (localsetcopy.rangeVoltageLow == true) {
      //TODO: fix hardcoding of settings
      value2str(umonstring, lastumon, -4, 5, 4, true, "V");
    } else {
      //TODO: fix hardcoding of settings
      value2str(umonstring, lastumon, -3, 5, 3, true, "V");
    }
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
            break;
        case ELmode::DVM:
            mode = mode_e_DVM;
            break;
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
  return localstatecopy.protection || localstatecopy.OCPstate || localstatecopy.OVPstate || localstatecopy.OPPstate || localstatecopy.OTPstate; 
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

//// Calibration variables
calType_e get_var_cal_cal_type() { return calActions.getCalType(); };
void set_var_cal_cal_type(calType_e value) { calActions.setCalType(value); };

int32_t get_var_cal_curpoint() { return calActions.getCurPoint(); };
void set_var_cal_curpoint(int32_t value) { calActions.setCurPoint(value); };

float get_var_cal_set() { return calActions.getSet(); };
void set_var_cal_set(float value) { calActions.setSet(value); };

float get_var_cal_measured() { return calActions.getMeasured(); };
void set_var_cal_measured(float value) { calActions.setMeasured(value); };

int32_t get_var_cal_numpoints() { return calActions.getNumPoints(); };
void set_var_cal_numpoints(int32_t value) {}; // Read only.

const char *get_var_cal_unit() { return ranges[caldefaults[calActions.getCalType()].keyBoard].unitName; };
void set_var_cal_unit(const char *value) {}; // Read only.

ranges_e get_var_cal_keyboard() { return caldefaults[calActions.getCalType()].keyBoard; };
void set_var_cal_keyboard(ranges_e value) {}; // Read only.

bool get_var_calibration_mode() { return localsetcopy.CalibrationMode; };
void set_var_calibration_mode(bool value) {
  state.CalibrationMode(value);
};

bool get_var_cal_animate() { return calActions.getRunning(); };
void set_var_cal_animate(bool value) {
  calActions.setRunning(value);
};

bool get_var_cal_trigger_measure() { return calActions.getTriggeredCalibration(); };
void set_var_cal_trigger_measure(bool value) {
  calActions.setTriggeredCalibration(value);
};

bool get_var_cal_values_changed() { return calActions.getValuesChanged(); };
void set_var_cal_values_changed(bool value) {
  calActions.setValuesChanged(value);
};

// End of calibration variables


bool get_var_von_state() { return localstatecopy.VonState; };
void set_var_von_state(bool value) {}; // Read only.

float get_var_temperature() { return localstatecopy.Temp1; };
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

int32_t get_var_fan_read_speed2() { return localstatecopy.FanRPM2; };
void set_var_fan_read_speed2(int32_t value) {}; // Read only.

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
void set_var_cap_limit_enabled(bool value) { state.setCapacityLimitEnabled(value); };
bool get_var_sense_error() { return localstatecopy.SenseError; };
void set_var_sense_error(bool value) {}; // Read only.
bool get_var_polarity_error() { return localstatecopy.PolarityError; };
void set_var_polarity_error(bool value) {}; // Read only.

// (static) Version variables
char version_lvgl[20] = "";
const char *get_var_version_lvgl() {
  snprintf(version_lvgl, 20, "%d.%d.%d%s", LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH, LVGL_VERSION_INFO); 
  return version_lvgl; };
void set_var_version_lvgl(const char *value) {}; // Read only.

const char *version_arduino_pico = ARDUINO_PICO_VERSION_STR;
const char *get_var_version_arduino_pico() { return version_arduino_pico; };
void set_var_version_arduino_pico(const char *value) {};  // Read only.

const char *version_tft_espi = TFT_ESPI_VERSION;
const char *get_var_version_tft_espi() { return version_tft_espi; };
void set_var_version_tft_espi(const char *value) {};  // Read only.

const char *version_freertos = tskKERNEL_VERSION_NUMBER;
const char *get_var_version_freertos() { return version_freertos; };
void set_var_version_freertos(const char *value) {};  // Read only.

const char *version_dcl = __DATE__ " " __TIME__;
const char *get_var_version_dcl() { return version_dcl; };
void set_var_version_dcl(const char *value) {};  // Read only.

int32_t get_var_version_cpu_freq() { return rp2040.f_cpu(); };
void set_var_version_cpu_freq(int32_t value) {};  // Read only.

#define RP2040_ID 0x02
#define RP2350_ID 0x04

char cpu_type[20] = "";
const char *get_var_version_cpu_type() {
    // First register of sysinfo is chip id
    uint32_t chip_id = *((io_ro_32*)(SYSINFO_BASE + SYSINFO_CHIP_ID_OFFSET));
    //uint32_t __unused manufacturer = chip_id & SYSINFO_CHIP_ID_MANUFACTURER_BITS;
    uint32_t part = (chip_id & SYSINFO_CHIP_ID_PART_BITS) >> SYSINFO_CHIP_ID_PART_LSB;
    if (part == RP2040_ID) {
      snprintf(cpu_type, 20, "RP2040");
    } else if (part == RP2350_ID) {
      snprintf(cpu_type, 20, "RP2350");
    } else {
      snprintf(cpu_type, 20, "Unkown CPU");
    }
    return cpu_type;
}
void set_var_version_cpu_type(const char* value) {}; // Read-only.

int32_t get_var_version_hw_version() { return HARDWARE_VERSION; }
void set_var_version_hw_version(int32_t value) {}; // Read only.

bool get_var_beep_on_protect() { return localsetcopy.beepOnProtect; };
void set_var_beep_on_protect(bool value) { state.setBeepProt(value); };
bool get_var_beep_on_capacity() { return localsetcopy.beepOnCapacity; };
void set_var_beep_on_capacity(bool value) { state.setBeepCap(value); };
bool get_var_beep_on_reverse() { return localsetcopy.beepOnReverse; };
void set_var_beep_on_reverse(bool value) { state.setBeepReverse(value); };
bool get_var_beep_on_encoder() { return localsetcopy.beepOnEncoder; };
void set_var_beep_on_encoder(bool value) { state.setBeepEncoder(value); };
float get_var_beep_default_duration() { return localsetcopy.beepDefaultDuration; };
void set_var_beep_default_duration(float value) { state.setBeepDefaultDuration(value); };
bool get_var_beep_on_sense() { return localsetcopy.beepOnSense; };
void set_var_beep_on_sense(bool value) { state.setBeepSense(value); };

statsType_e statsTypeCurrent;
measureStat *statsCurrent;

statsType_e get_var_stat_type() { return statsTypeCurrent; };
void set_var_stat_type(statsType_e value) 
{
  statsTypeCurrent = value;
  switch(statsTypeCurrent) 
  {
    case statsType_e::statsType_e_I:
      statsCurrent = &localstatecopy.ImonStats;
      break;
    case statsType_e::statsType_e_U:
      statsCurrent = &localstatecopy.UmonStats;
      break;
    case statsType_e::statsType_e_P:
      statsCurrent = &localstatecopy.PmonStats;
      break;
    default:
      statsCurrent = &localstatecopy.ImonStats;   
  }
};

void formatStatValue(char* str, statsType_e type, float value)
{
  if(statsCurrent->count == 0)
  {
    sprintf(str,"-");
    return;
  }
  if(type == statsType_e_I) 
  {
    if (localsetcopy.rangeCurrentLow == true) {
      //TODO: fix hardcoding of settings
      value2str(str, value, -4, 5, 3, true, "A");
    } else {
      value2str(str, value, -3, 5, 3, true, "A");
    }
  }
  if(type == statsType_e_U) 
  {
    if (localsetcopy.rangeVoltageLow == true) {
      //TODO: fix hardcoding of settings
      value2str(str, value, -4, 5, 4, true, "V");
    } else {
      //TODO: fix hardcoding of settings
      value2str(str, value, -3, 5, 3, true, "V");
    }
  }
  if(type == statsType_e_P) 
  {
    value2str(str, value, -3, 4, 3, true, "W");
  }
}

char statminstring[16];
float laststatmin = -1;
statsType_e laststatmintype = statsType_e_I;

void set_var_stat_min(const char *value) {}; // Read only
const char *get_var_stat_min()
{
  if (statsTypeCurrent != laststatmintype || statsCurrent->min != laststatmin) {
    laststatmin = statsCurrent->min;
    laststatmintype = statsTypeCurrent;
    formatStatValue(statminstring, statsTypeCurrent, statsCurrent->min);
  }
  return statminstring;
}

char statavgstring[16];
float laststatavg = -1;
statsType_e laststatavgtype = statsType_e_I;

void set_var_stat_avg(const char *value) {}; // Read only
const char *get_var_stat_avg()
{
  if (statsTypeCurrent != laststatavgtype || statsCurrent->avg != laststatavg) {
    laststatavg = statsCurrent->avg;
    laststatavgtype = statsTypeCurrent;
    formatStatValue(statavgstring, statsTypeCurrent, statsCurrent->avg);
  }
  return statavgstring;
}

char statmaxstring[16];
float laststatmax = -1;
statsType_e laststatmaxtype = statsType_e_I;

void set_var_stat_max(const char *value) {}; // Read only
const char *get_var_stat_max()
{
  if (statsTypeCurrent != laststatmaxtype || statsCurrent->max != laststatmax) {
    laststatmax = statsCurrent->max;
    laststatmaxtype = statsTypeCurrent;
    formatStatValue(statmaxstring, statsTypeCurrent, statsCurrent->max);
  }
  return statmaxstring;
}

char statcntstring[16];
float laststatcnt = -1;

void set_var_stat_counts(const char *value) {}; // Read only
const char *get_var_stat_counts()
{
  if (statsCurrent->count != laststatcnt) {
    laststatcnt = statsCurrent->count;
    //formatStatValue(statmaxstring, statsTypeCurrent, statsCurrent->max);
    value2str(statcntstring, statsCurrent->count, 0, 6, 6, true, "");
  }
  return statcntstring;
}

bool get_var_stat_irun() { return localsetcopy.ImonStat; };
void set_var_stat_irun(bool value) { state.setImonStat(value); };
bool get_var_stat_urun() { return localsetcopy.UmonStat; };
void set_var_stat_urun(bool value) { state.setUmonStat(value); };
bool get_var_stat_prun() { return localsetcopy.PmonStat; };
void set_var_stat_prun(bool value)  { state.setPmonStat(value); };

int32_t get_var_stat_icount() { return localstatecopy.ImonStats.count; };
void set_var_stat_icount(int32_t value) {}; // Read only
int32_t get_var_stat_ucount() { return localstatecopy.UmonStats.count; };
void set_var_stat_ucount(int32_t value) {}; // Read only
int32_t get_var_stat_pcount() { return localstatecopy.PmonStats.count; };
void set_var_stat_pcount(int32_t value) {}; // Read only

bool get_var_scpi_wdog_tripped() { return state.getSCPIWdogTripped(); };
void set_var_scpi_wdog_tripped(bool value) {}; //Read only

int32_t get_var_start_r() { return state.hw.resetReason; };
void set_var_start_r(int32_t value) {}; // Read only

bool get_var_start_eeprom() { return state.hw.eepromMagicDetected; };
void set_var_start_eeprom(bool value) {}; //Read only

bool get_var_start_cal_ok() { return state.hw.calibrationCRCOK && state.hw.calibrationValid; };
void set_var_start_cal_ok(bool value) {}; // Read only
