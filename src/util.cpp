// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdio.h>
#include <string.h>
#include "util.h"
#include "math.h" 

namespace dcl {

// From https://github.com/eez-open/modular-psu-firmware
float remap(float x, float x1, float y1, float x2, float y2) {
    return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}

float clamp(float x, float min, float max) {
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}

// TODO check: https://jkorpela.fi/c/eng.html
// for simpler/faster implementation


float NTCResistanceToTemp(float res, float beta, float nominalTemp, float nominalRes)
{
  float inverseTemp = (1.0f / nominalTemp + log (res  / nominalRes) / beta);
  return 1.0f/inverseTemp - 273.15f;
}

} // namespace

extern "C" {

static const char* SIScalePrefixes[] =        { "p", "n","\u03bc", "m", " ", "k", "M", "G", "T" };  
static const int   SIScalePrefixExponents[] = {-12,  -9,    -6,    -3,   0,   3 ,  6,   9,  12  };
static const int   SIScalePrefixExponentsBase = 4; // Index of 0 exponent
static const int   SIScaleprefixExpLast = sizeof(SIScalePrefixExponents)/sizeof(SIScalePrefixExponents[0]) - 1;

void value2str(char* str, float value, int accuracy_exp, int total_digits, int after_point, 
                bool show_prefix, const char* unit) 
    {
    // 0 is special case
    if (value == 0.0f)
    {
        sprintf(str, " 0  %s", unit);
        return;
    }

    // Determine sign
    char sign = value < 0.0f ? '-' : ' ';
  
    // Find exponent
    int exponentRaw = floor(log10(abs(value)));
    int exponent = std::max(exponentRaw, SIScalePrefixExponents[0]); // Lower limit of exponent
    exponent = std::min(exponent, SIScalePrefixExponents[SIScaleprefixExpLast]); // Upper limit of exponent
    exponent = std::max(exponent, accuracy_exp); // Don't go below accuracy

    // Find prefix, exponent and mantissa to nearest enginering scale.
    int exponentIndex = floor((float)exponent * 3.0f)/9 + SIScalePrefixExponentsBase;
    exponentIndex = std::max(exponentIndex, (int)ceil(accuracy_exp / 3) + SIScalePrefixExponentsBase);
    const char* prefix = SIScalePrefixes[exponentIndex];

    float mantissa = abs(value) / pow(10, SIScalePrefixExponents[exponentIndex]); // raw mantissa
    //mantissa = round(mantissa * pow(10, accuracy_exp)) / pow(10, accuracy_exp); // mantissa rounded to accuracy

    // Determine the number of digits after .
    int fraction_digits = std::min(after_point, total_digits - (exponentRaw + 1 - SIScalePrefixExponents[exponentIndex] ));
    fraction_digits = std::min(fraction_digits, SIScalePrefixExponents[exponentIndex] - accuracy_exp);
    
    // Format the string.
    sprintf(str, "%c%.*f%s%s", sign, fraction_digits, mantissa, SIScalePrefixes[exponentIndex], unit);

    } // value2str
}

