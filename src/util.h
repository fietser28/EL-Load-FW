// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#ifdef __cplusplus
namespace dcl
{
#endif

    float remap(float x, float x1, float y1, float x2, float y2);
    float clamp(float x, float min, float max);

    /// From BB3 bb3/index.h
    /// From https://github.com/eez-open/modular-psu-firmware
    /////////////////////////////////////////////////////////

    /// Calibration parameters for the single point.
    struct CalibrationValuePointConfiguration
    {
        /// Value set on DAC by the calibration module.
        float dac;
        /// Real value, in volts, set by the user who reads it on the instrument (voltmeter and ampermeter).
        float value;
        /// Value read from ADC.
        float adc;
    };

#ifndef __cplusplus
    typedef struct CalibrationValuePointConfiguration CalibrationValuePointConfiguration;
#endif

#define MAX_CALIBRATION_POINTS 2

    /// Calibration parameters for the voltage and current.
    /// There are three points defined: `min`, `mid` and `max`.
    /// Only `min` and `max` are used in actual calculations -
    /// `mid` is only used for the validity checking.
    /// Here is how `DAC` value is calculated from the `real_value` set by user:
    /// `DAC = min.dac + (real_value - min.val) * (max.dac - min.dac) / (max.val - min.val);`
    /// And here is how `real_value` is calculated from the `ADC` value:
    /// `real_value = min.val + (ADC - min.adc) * (max.val - min.val) / (max.adc - min.adc);`
    struct CalibrationValueConfiguration
    {
        unsigned int numPoints;
        CalibrationValuePointConfiguration points[MAX_CALIBRATION_POINTS];
        bool valid;
    };

#ifndef __cplusplus
    typedef struct CalibrationValueConfiguration CalibrationValueConfiguration;
#endif

extern float NTCResistanceToTemp(float res, float beta, float nominalTemp, float nominalRes);
            
#ifdef __cplusplus
} // end of namespace
#endif

#ifdef __cplusplus
extern "C" {
#endif
    extern void value2str(char* str, float value, int accuracy_exp, int total_digits, int after_point, 
                        bool show_prefix, const char* unit); 

#ifdef __cplusplus
}
#endif