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

            virtual bool setADCConfig(int32_t min, int32_t max);
            virtual bool configured();

            virtual float remap(float input);
    };

    // Simple 2 point linear calibration 
    class calLinear2P : public cal {
        public:
            bool setCalConfig(CalibrationValueConfiguration newconfig);
            CalibrationValueConfiguration getCalConfig();
            bool setADCConfig(int32_t min, int32_t max);
            bool configured();

            float remap(float input);

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
