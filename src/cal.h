// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "Arduino.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "util.h"
#include "ui/vars.h"

#ifdef __cplusplus
using namespace dcl;
namespace dcl::cal
{
#endif

#ifndef __cplusplus
//    typedef struct cal cal;
#else
    // Abstract calibration data class
    class calData {
        public:
            calData() {};
            virtual bool setCalConfigRef(CalibrationValueConfiguration* newconfig) ;

            virtual CalibrationValueConfiguration *getCalConfigRef();

            virtual bool setADCConfig(int32_t min, int32_t max) ;
            virtual bool setDACConfig(int32_t min, int32_t max) ;

            virtual bool configured();

            virtual float remapADC(float input);
            virtual float remapDAC(float input);
    };

    // Simple 2 point linear calibration data
    class calDataLinear2P : public calData {
        public:
            calDataLinear2P() : calData() { _conf = new CalibrationValueConfiguration; };
            bool setCalConfigRef(CalibrationValueConfiguration* newconfig);

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
            CalibrationValueConfiguration *_conf;
            float _minADC = 0;
            float _maxADC = 0;
            float _multiply, _offset; 
            float _minVal, _maxVal;
    };
#endif

extern void calSetDefaults();

class calAction {
    public:
        calType_e   getCalType();
        void        setCalType(calType_e value);
        int32_t     getCurPoint();
        void        setCurPoint(int32_t point);
        float       getSet();
        void        setSet(float set);
        float       getMeasured();
        void        setMeasured(float measured);
        int32_t     getNumPoints();
        const char* getUnit();
        ranges_e    getKeyboard();
        bool        getRunning();
        void        setRunning(bool running);  // Flow is doing actual calibration routine
        bool        getTriggeredCalibration();
        void        setTriggeredCalibration(bool trigger); // Bool to trigger calibration start in Flow
        bool        getValuesChanged();
        void        setValuesChanged(bool changed);
        void        setDAC();
        void        fetchMeasured();
        void        storeValues();
        void        resetValues();
        bool        storeDefaults(); // load Default values and store in eeprom
        bool        storeAllValues(); // store all current values to eeprom

    private:
        SemaphoreHandle_t _sem;

        void      copy_cal_values_from_state(CalibrationValueConfiguration *cal_values, calType_e caltype);
        void      copy_cal_values_to_state(CalibrationValueConfiguration *cal_values, calType_e caltype);
        void      write_cal_to_eeprom(calType_e caltype);

        calType_e _calType = calType_e::calType_e_Undefined; // Force init and copy!
        int32_t   _curpoint = 0; 
        float     _set = 0.0f;                       // This is the changed/temp value.
        float     _measured = 0.0f;                   // This is the changed/temp value.
        CalibrationValueConfiguration _values;   // This is the changed/temp configuration.
        bool      _running = false;
        bool      _triggerMeasure = false;
        bool      _valuesChanged = false;
};

#ifdef __cplusplus
} // end of namespace
#endif
