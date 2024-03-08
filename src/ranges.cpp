
// SPDX-FileCopyrightText: 2024 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "main.h"
#include "ui/vars.h"
#include "ranges.h"

using namespace dcl;

const _range ranges[] = {
    { "Current",        "A",      SCPI_UNIT_AMPER,  0.0, 10.0,     0.111 }, // Curr_High = 0
    { "Current",        "A",      SCPI_UNIT_AMPER,  0.0,  1.0,     0.111 }, // Curr_Low  = 1
    { "Voltage",        "V",      SCPI_UNIT_VOLT,   0.0, 80.0,     10.0  }, // Volt_High = 2
    { "Voltage",        "V",      SCPI_UNIT_VOLT,   0.0,  9.0,     3.3  },  // Volt_Low  = 3
    { "Power",          "W",      SCPI_UNIT_WATT,   0.0, 125.0,    10.0  }, // Power     = 4
    { "Resistance",     "\u03a9", SCPI_UNIT_OHM,    0.1, 100000.0, 1000.0}, // Res       = 5
    { "Von",            "V",      SCPI_UNIT_VOLT,   0.1, 10.0,      1.0},   // Von_High  = 6
    { "Von",            "V",      SCPI_UNIT_VOLT,   0.1, 9.0,      1.0},    // Von_Low   = 7
    { "OCP",            "A",      SCPI_UNIT_AMPER,  0.0, 10.0,     10.0},   // OCP_High  = 8
    { "OCP",            "A",      SCPI_UNIT_AMPER,  0.0, 1.0,       1.0},   // OCP_Low   = 9
    { "OVP",            "V",      SCPI_UNIT_VOLT,   1.0, 80.0,     40.0},   // OVP_High  = 10
    { "OVP",            "V",      SCPI_UNIT_VOLT,   1.0, 9.0,     40.0},    // OVP_Low   = 11
    { "OPP",            "W",      SCPI_UNIT_WATT,   1.0, 125.0,    80.0},   // OPP_Power = 12
    { "OPP delay",      "s",      SCPI_UNIT_SECOND, 1.0, 600.0,    20.0},   // OPP_Delay = 13
    { "OTP",            "C",      SCPI_UNIT_CELSIUS,10.0,110.0,    80.0},   // OTP_Temp  = 14
    { "OTP delay",      "s",      SCPI_UNIT_SECOND, 1.0, 600.0,    20.0},   // OTP_Delay = 15
    { "Current Cal Set","A",      SCPI_UNIT_AMPER, -1.0, 11.0,      0.1},   // Curr_Cal  = 16
    { "Voltage Cal Set","V",      SCPI_UNIT_VOLT,  -1.0, 100.0,     0.1},   // Volt_Cal  = 17
    { "16bit DAC",      "",       SCPI_UNIT_NONE,     0, 65535,       0},   // DAC16b    = 18
    { "Cap Ah Stop",    "Ah",     SCPI_UNIT_JOULE,0.001, 3600,       10},   // AHStop    = 19
    { "Cap Time Stop",  "s",      SCPI_UNIT_SECOND,   1, 864000,  86400},   // TimeStop  = 20
    { "Cap Volt Stop",  "V",      SCPI_UNIT_VOLT,    0.5, 80,       3.0},   // VoltStop  = 21
    { "Cap Wh Stop",    "Wh",     SCPI_UNIT_JOULE,0.001, 3600,       10},   // WHStop    = 22
    { "Fan Speed (%)",    "%",    SCPI_UNIT_NONE ,    0,  100,       50},   // FanSpeed  = 23
};


// Calibration defaults, ranges, pointers and eeprom adresses

_caldef caldefaults[] = {
    //  val0      adc0      val1           adc1          adcMin                adcMax            keyboard             type                                     callback         eepromAddress
    {   0.1,    700572,     10.0,       6963036,    currentADC.ADC_MIN,     currentADC.ADC_MAX,  ranges_e_Curr_Cal,   calCalType_e::calCalType_e_ADC,        state.cal.Imon,      0x100 }, // Imon_High = 0
    {   0.1,     70000,     0.95,       6900000,    currentADC.ADC_MIN ,    currentADC.ADC_MAX,  ranges_e_Curr_Cal,   calCalType_e::calCalType_e_ADC,        state.cal.ImonLow,   0x200 }, // Imon_Low  = 1
    {   0.0,      2059,    35.0,        6970322,    voltADC.ADC_MIN,        voltADC.ADC_MAX,     ranges_e_Volt_Cal,   calCalType_e::calCalType_e_ADC,        state.cal.Umon,      0x300 }, // Umon_High = 2
    {   0.0,      2000,     8.5,        6900000,    voltADC.ADC_MIN,        voltADC.ADC_MAX,     ranges_e_Volt_Cal,   calCalType_e::calCalType_e_ADC,        state.cal.UmonLow,   0x400 }, // Umon_Low  = 3
    { 0.00299,    255,      9.5,        640000,      iSetDAC.DAC_MIN,        iSetDAC.DAC_MAX,     ranges_e_DAC16b,   calCalType_e::calCalType_e_DAC,        state.cal.Iset,      0x500 }, // Iset_High = 4
    { 0.00299,    100,      0.95,       640000,      iSetDAC.DAC_MIN,        iSetDAC.DAC_MAX,     ranges_e_DAC16b,   calCalType_e::calCalType_e_DAC,        state.cal.IsetLow,   0x600 }, // Iset_Low  = 5
    {   0.5,      100,      75,        640000,      uSetDAC.DAC_MIN,        uSetDAC.DAC_MAX,     ranges_e_Volt_Cal,   calCalType_e::calCalType_e_DAC,        state.cal.Uset,      0x700 }, // Uset_High = 6
    {   0.2,      100,      8.5,        640000,      uSetDAC.DAC_MIN,        uSetDAC.DAC_MAX,     ranges_e_Volt_Cal,   calCalType_e::calCalType_e_DAC,        state.cal.UsetLow,   0x800 }, // Uset_Low  = 7
    {   0.5,      100,      75,        640000,    vonSetDAC.DAC_MIN,      vonSetDAC.DAC_MAX,     ranges_e_Volt_Cal,   calCalType_e::calCalType_e_DAC,        state.cal.Von,       0x900 }, // Von_High = 8
    {   0.2,      100,      8.5,        640000,    vonSetDAC.DAC_MIN,      vonSetDAC.DAC_MAX,     ranges_e_Volt_Cal,   calCalType_e::calCalType_e_DAC,        state.cal.VonLow,    0xA00 }, // Von_Low  = 9
    {   0.5,      100,      9.5,        640000,    OCPSetDAC.DAC_MIN,      OCPSetDAC.DAC_MAX,     ranges_e_Curr_Cal,   calCalType_e::calCalType_e_LEVEL,      state.cal.OCPset,    0xB00 }, // OCPset_High = 10
    {   0.5,      100,      0.95,        640000,    OCPSetDAC.DAC_MIN,      OCPSetDAC.DAC_MAX,     ranges_e_Curr_Cal,   calCalType_e::calCalType_e_LEVEL,      state.cal.OCPsetLow, 0xC00 }, // OCPset_Low = 11
    {   0.5,      100,      80,        640000,    OVPSetDAC.DAC_MIN,      OVPSetDAC.DAC_MAX,     ranges_e_Volt_Cal,   calCalType_e::calCalType_e_LEVEL,      state.cal.OVPset,    0xD00 }, // OVPset_High = 12
    {   0.5,      100,      8.5,        640000,    OVPSetDAC.DAC_MIN,      OVPSetDAC.DAC_MAX,     ranges_e_Volt_Cal,   calCalType_e::calCalType_e_LEVEL,      state.cal.OVPsetLow, 0xE00 }, // OVPset_Low = 13
};
