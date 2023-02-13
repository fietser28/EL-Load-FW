#pragma once

#ifdef __cplusplus
namespace dcl
{
#endif

    float remap(float x, float x1, float y1, float x2, float y2);
    float clamp(float x, float min, float max);

    /// From BB3 bb3/index.h
    ////////////////////////

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

#define MAX_CALIBRATION_POINTS 20

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
    };

#ifdef __cplusplus
} // end of namespace
#endif
