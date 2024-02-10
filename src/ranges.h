#pragma once
#include "scpi/scpi.h"

struct _range {
    const char* setName;
    const char* unitName;
    scpi_unit_t scpi_unit;
    float minValue;
    float maxValue;
    float defValue;
};

extern const _range ranges[];
