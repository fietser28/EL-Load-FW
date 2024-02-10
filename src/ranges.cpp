
// SPDX-FileCopyrightText: 2024 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "main.h"
#include "ui/vars.h"
#include "ranges.h"

const _range ranges[] = {
    { "Current",        "A",      SCPI_UNIT_AMPER,  0.0, 10.0,     0.111 }, // Curr_High = 0
    { "Current",        "A",      SCPI_UNIT_AMPER,  0.0,  1.0,     0.111 }, // Curr_Low  = 1
    { "Voltage",        "V",      SCPI_UNIT_VOLT,   0.0, 80.0,     10.0  }, // Volt_High = 2
    { "Voltage",        "V",      SCPI_UNIT_VOLT,   0.0,  9.0,     3.3  },  // Volt_Low  = 3
    { "Power",          "W",      SCPI_UNIT_WATT,   0.0, 100.0,    10.0  }, // Power     = 4
    { "Resistance",     "\u03a9", SCPI_UNIT_OHM,    0.1, 100000.0, 1000.0}, // Res       = 5
    { "Von",            "V",      SCPI_UNIT_VOLT,   0.1, 10.0,      1.0},   // Von_High  = 6
    { "Von",            "V",      SCPI_UNIT_VOLT,   0.1, 9.0,      1.0},    // Von_Low   = 7
    { "OCP",            "A",      SCPI_UNIT_AMPER,  0.0, 10.0,     10.0},   // OCP_High  = 8
    { "OCP",            "A",      SCPI_UNIT_AMPER,  0.0, 1.0,       1.0},   // OCP_Low   = 9
    { "OVP",            "V",      SCPI_UNIT_VOLT,   1.0, 80.0,     40.0},   // OVP_High  = 10
    { "OVP",            "V",      SCPI_UNIT_VOLT,   1.0, 9.0,     40.0},    // OVP_Low   = 11
    { "OPP",            "W",      SCPI_UNIT_WATT,   1.0, 125.0,    80.0},   // OPP_Power = 12
    { "OPP delay",      "s",      SCPI_UNIT_SECOND, 1.0, 600.0,    20.0},   // OPP_Delay = 13
    { "OTP",            "C",      SCPI_UNIT_CELSIUS,10.0,100.0,    80.0},   // OTP_Temp  = 14
    { "OTP delay",      "s",      SCPI_UNIT_SECOND, 1.0, 600.0,    20.0},   // OTP_Delay = 15
    { "Current Cal Set","A",      SCPI_UNIT_AMPER, -1.0, 11.0,      0.1},   // Curr_Cal  = 16
    { "Voltage Cal Set","V",      SCPI_UNIT_VOLT,  -1.0, 100.0,     0.1},   // Volt_Cal  = 17
    { "16bit DAC",      "",       SCPI_UNIT_NONE,     0, 65535,       0},   // 16bDAC    = 18
};