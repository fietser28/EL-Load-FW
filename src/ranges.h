#pragma once

#include "scpi/scpi.h"

#include "main.h"
#include "cal.h"
#include "ui/vars.h"

struct _range {
    const char* setName;
    const char* unitName;
    scpi_unit_t scpi_unit;
    float minValue;
    float maxValue;
    float defValue;
};

extern const _range ranges[];

struct _caldef {
    float value0;
    float adc0;
    float value1;
    float adc1;
    uint32_t adcMin;
    uint32_t adcMax;
    ranges_e keyBoard;
    calCalType_e type;
    calData **stateRef;
    uint16_t eepromAddress;
};

extern _caldef caldefaults[];
extern uint_fast32_t caldefaultsLength;
