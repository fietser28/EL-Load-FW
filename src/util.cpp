#include <stdio.h>
#include <string.h>
#include "util.h"
#include "math.h" 

namespace dcl {

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

// check: https://jkorpela.fi/c/eng.html
// for simpler/faster implementation

/*
ChatGTP version (has flaws):

#include <cstring>
#include <cmath>
#include <cstdio>

char* floatToEngineeringString(float value, int precision) {
  char result[100];
  char prefix[2] = "";
  if (value == 0.0) {
    sprintf(result, "0");
  } else {
    int exponent = static_cast<int>(floor(log10(fabs(value))));
    float mantissa = value / pow(10, exponent);
    mantissa = round(mantissa * pow(10, precision)) / pow(10, precision);

    static const char* prefixes[] = {"y", "z", "a", "f", "", "", "", "k", "M", "G", "T", "P", "E", "Z", "Y"};
    static const int prefix_exponents[] = {-24, -18, -12, -6, 0, 0, 0, 3, 6, 9, 12, 15, 18, 21, 24};

    for (int i = 0; i < 15; i++) {
      if (exponent >= prefix_exponents[i] && exponent <= prefix_exponents[i] + 3) {
        strcpy(prefix, prefixes[i]);
        exponent -= prefix_exponents[i];
        break;
      }
    }

    if (exponent >= -3 && exponent <= 2) {
      sprintf(result, "%.*f%s", precision, mantissa, prefix);
    } else {
      sprintf(result, "%.*fe%d", precision, mantissa, exponent);
    }
  }

  char* str = new char[strlen(result) + 1];
  strcpy(str, result);
  return str;
}

*/

static char SIScalePrefixes[] =        { 'p', 'n','u', 'm', ' ', 'k', 'M', 'G', 'T' };  
static const int   SIScalePrefixExponents[] = {-12,  -9, -6,  -3,   0,  3 ,  6,   9,  12  };
static const int   SIScalePrefixExponentsBase = 4; // Index of 0 exponent
static const int   SIScaleprefixExpLast = sizeof(SIScalePrefixExponents)/sizeof(SIScalePrefixExponents[0]);

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
    int exponentIndex = exponent / 3 + SIScalePrefixExponentsBase;
    char prefix = SIScalePrefixes[exponentIndex];
    float mantissa = abs(value) / pow(10, SIScalePrefixExponents[exponentIndex]);                                 // raw mantissa
    //mantissa = round(mantissa * pow(10, accuracy_exp)) / pow(10, accuracy_exp); // mantissa rounded to accuracy

    // Determine the number of digits after .
    int fraction_digits = std::min(after_point, total_digits - (exponentRaw - exponent));
    fraction_digits = std::min(fraction_digits, exponentRaw - accuracy_exp);

    // Format the string.
    sprintf(str, "%c%.*f %c%s", sign, fraction_digits, mantissa, SIScalePrefixes[exponentIndex], unit);

    /*
        int acc_base = floor(log10(accuracy));
        float absvalue = abs(value);
        int prefixdigits = 0; // 0 = no prefix
        if (show_prefix)
        {
            // prefixdigits =
            // max between ceiling of accuracy and actual value
            // max between mimimum prefix (-6 corresponds to nano) and log10 of value
            prefixdigits = std::max(floor(std::min(9.0f, std::max(-6.0f, log10(absvalue) / 3))), (float)ceil(acc_base / 3));
            }
            int int_base = pow(10, prefixdigits*3);
            float int_part = floor(absvalue / int_base);
            char int_base_str[10];
            sprintf(int_base_str, "%8.0", int_part);
            int int_digits = strlen(int_base_str);
            int frac_digits = std::min(std::min(after_point, total_digits - int_digits), prefixdigits*3-acc_base);
            float roundoff = pow(10, prefixdigits - frac_digits );
        }
        */
    } // value2str

} // namespace