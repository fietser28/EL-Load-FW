// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "Arduino.h"
#include "util.h"

#ifdef __cplusplus
namespace dcl
{
#endif

#ifndef __cplusplus
//    typedef struct cal cal;
#else
    // Abstract calibration class
    class cal {
        public:
            virtual bool setCalConfig(CalibrationValueConfiguration newconfig) = 0;
            virtual CalibrationValueConfiguration getCalConfig();
            virtual CalibrationValueConfiguration *getCalConfigRef();

            virtual bool setADCConfig(int32_t min, int32_t max);
            virtual bool setDACConfig(int32_t min, int32_t max);

            virtual bool configured();

            virtual float remapADC(float input);
            virtual float remapDAC(float input);
    };

    // Simple 2 point linear calibration 
    class calLinear2P : public cal {
        public:
            bool setCalConfig(CalibrationValueConfiguration newconfig);
            CalibrationValueConfiguration getCalConfig();
            CalibrationValueConfiguration *getCalConfigRef();
            bool setADCConfig(int32_t min, int32_t max);
            bool setDACConfig(int32_t min, int32_t max);

            bool configured();

            float remapADC(float input);
            float remapDAC(float input);

        private:
            bool  _configure();
            bool  _configured;
            bool  _gotConf = false;
            bool  _gotADC  = false;
            CalibrationValueConfiguration _conf;
            float _minADC = 0;
            float _maxADC = 0;
            float _multiply, _offset; 
            float _minVal, _maxVal;
    };
#endif


#ifdef __cplusplus
} // end of namespace
#endif
