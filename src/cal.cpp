// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "main.h"
#include "events.h"
#include "cal.h"
#include "ranges.h"
#include "util.h"

using namespace dcl;
using namespace dcl::events;
namespace dcl::cal
{

/*
    CalibrationValueConfiguration currentCal;
    CalibrationValueConfiguration currentCalLow;
    CalibrationValueConfiguration voltCal;
    CalibrationValueConfiguration voltCalLow;
    CalibrationValueConfiguration iSetCal;
    CalibrationValueConfiguration iSetCalLow;
    CalibrationValueConfiguration uSetCal;
    CalibrationValueConfiguration uSetCalLow;
    CalibrationValueConfiguration vonSetCal;
    CalibrationValueConfiguration vonSetCalLow;
    CalibrationValueConfiguration OCPSetCal;
    CalibrationValueConfiguration OCPSetCalLow;
    CalibrationValueConfiguration OVPSetCal;
    CalibrationValueConfiguration OVPSetCalLow;
*/

    bool calDataLinear2P::setCalConfigRef(CalibrationValueConfiguration* newconfig)
    {
        if (newconfig->numPoints != 2)
        {
            _gotConf = false;
            _configured = false;
            return false;
        }

        _conf = newconfig;
        _gotConf = true;

        return _configure();
    };

    CalibrationValueConfiguration *calDataLinear2P::getCalConfigRef()
    {
        return _conf;
    }

    bool calDataLinear2P::setADCConfig(int32_t min, int32_t max)
    {
        _minADC = min;
        _maxADC = max;
        _gotADC = true;

        return _configure();
    };

    bool calDataLinear2P::setDACConfig(int32_t min, int32_t max)
    {
        return setADCConfig(min,max);
    };

    bool calDataLinear2P::_configure()
    {
        if (_gotConf && _gotADC)
        {
            _multiply = (_conf->points[1].value - _conf->points[0].value) / (_conf->points[1].adc - _conf->points[0].adc);
            _offset = _conf->points[0].value - _conf->points[0].adc * _multiply;
            _minVal = _offset; // TODO: support negative values?
            _maxVal = _maxADC * _multiply;
            _configured = true;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool calDataLinear2P::configured() { return _configured; };

    float calDataLinear2P::remapADC(float input)
    {
        if (!_configured)
        {
            return 0;
        }
//        return ::remap((float)input, (float)_minADC, _minVal, (float)_maxADC, _maxVal);
        return ::remap((float)input, (float)_conf->points[0].adc, _conf->points[0].value, (float)_conf->points[1].adc, _conf->points[1].value);
    }

    float calDataLinear2P::remapDAC(float input)
    {
        if (!_configured)
        {
            return 0;
        }
//        return ::remap((float)input, (float)_minADC, _minVal, (float)_maxADC, _maxVal);
        return ::remap((float)input, (float)_conf->points[0].value, _conf->points[0].dac, (float)_conf->points[1].value, _conf->points[1].dac);
    }

    void calSetDefaults() 
    {
        /*
        // TODO: Hardcoded calibration values for now
        currentCal.numPoints = 2;
        currentCal.points[0].value = 0.1;  // 0.0; // 0.1V  => 1.0A
        currentCal.points[0].adc = 700572; // 4575;
        currentCal.points[1].value = 10.0; // 1.000V => 10A
        currentCal.points[1].adc = 6963036;

        state.cal.Imon = new calDataLinear2P();
        //state.cal.Imon->setCalConfigRef(&currentCal);
        //state.cal.Imon->setADCConfig(currentADC.ADC_MIN, currentADC.ADC_MAX);

        currentCalLow.numPoints = 2;
        currentCalLow.points[0].value = 0.05; // 0.0; // 0.1V  => 1.0A
        currentCalLow.points[0].adc = 700000; // 4575;
        currentCalLow.points[1].value = 0.95; // 1.000V => 10A
        currentCalLow.points[1].adc = 6963036;

        state.cal.ImonLow = new calDataLinear2P();
        //state.cal.ImonLow->setCalConfigRef(&currentCalLow);
        //state.cal.ImonLow->setADCConfig(currentADC.ADC_MIN, currentADC.ADC_MAX);

        //CalibrationValueConfiguration voltCal;
        voltCal.numPoints = 2;
        voltCal.points[0].value = 0.0; // 50mV
        voltCal.points[0].adc = 2059;
        voltCal.points[1].value = 100.0; // 1.000V => 100V //1.100 * 34 * 2.1; // 1.100V => >80V
        voltCal.points[1].adc = 6970322;

        //state.cal.Umon = new calDataLinear2P();
        //state.cal.Umon->setCalConfigRef(&voltCal);
        //state.cal.Umon->setADCConfig(voltADC.ADC_MIN, voltADC.ADC_MAX);

        voltCalLow.numPoints = 2;
        voltCalLow.points[0].value = 0.0; // 50mV
        voltCalLow.points[0].adc = 2059;
        voltCalLow.points[1].value = 100.0; // 1.000V => 100V //1.100 * 34 * 2.1; // 1.100V => >80V
        voltCalLow.points[1].adc = 6970322;

        state.cal.UmonLow = new calDataLinear2P();
        //state.cal.UmonLow->setCalConfigRef(&voltCalLow);
        //state.cal.UmonLow->setADCConfig(voltADC.ADC_MIN, voltADC.ADC_MAX);

        iSetCal.numPoints = 2;
        iSetCal.points[0].value = 0.00299; // @3.3Vinput (AMS1117)
        iSetCal.points[0].dac = 100;
        iSetCal.points[1].value = 3.2374; // @3.3Vinput (AMS1117)
        iSetCal.points[1].dac = 64000;

        state.cal.Iset = new calDataLinear2P();
        state.cal.Iset->setCalConfigRef(&iSetCal);
        state.cal.Iset->setDACConfig(iSetDAC.DAC_MIN, iSetDAC.DAC_MAX);

        iSetCalLow.numPoints = 2;
        iSetCalLow.points[0].value = 0.00299; // @3.3Vinput (AMS1117)
        iSetCalLow.points[0].dac = 100;
        iSetCalLow.points[1].value = 3.2374; // @3.3Vinput (AMS1117)
        iSetCalLow.points[1].dac = 64000;

        state.cal.IsetLow = new calDataLinear2P();
        state.cal.IsetLow->setCalConfigRef(&iSetCalLow);
        state.cal.IsetLow->setDACConfig(iSetDAC.DAC_MIN, iSetDAC.DAC_MAX);

        uSetCal.numPoints = 2;
        uSetCal.points[0].value = 1.00;
        uSetCal.points[0].dac = 100;
        uSetCal.points[1].value = 3.2;
        uSetCal.points[1].dac = 64000;

        state.cal.Uset = new calDataLinear2P();
        state.cal.Uset->setCalConfigRef(&uSetCal);
        state.cal.Uset->setDACConfig(uSetDAC.DAC_MIN, uSetDAC.DAC_MAX);

        uSetCalLow.numPoints = 2;
        uSetCalLow.points[0].value = 1.00;
        uSetCalLow.points[0].dac = 100;
        uSetCalLow.points[1].value = 3.2;
        uSetCalLow.points[1].dac = 64000;

        state.cal.UsetLow = new calDataLinear2P();
        state.cal.UsetLow->setCalConfigRef(&uSetCalLow);
        state.cal.UsetLow->setDACConfig(uSetDAC.DAC_MIN, uSetDAC.DAC_MAX);

        vonSetCal.numPoints = 2;
        vonSetCal.points[0].value = 0.50;
        vonSetCal.points[0].dac = 100;
        vonSetCal.points[1].value = 3.2;
        vonSetCal.points[1].dac = 64000;

        state.cal.Von = new calDataLinear2P();
        state.cal.Von->setCalConfigRef(&vonSetCal);
        state.cal.Von->setDACConfig(vonSetDAC.DAC_MIN, vonSetDAC.DAC_MAX);

        vonSetCalLow.numPoints = 2;
        vonSetCalLow.points[0].value = 0.50;
        vonSetCalLow.points[0].dac = 100;
        vonSetCalLow.points[1].value = 3.2;
        vonSetCalLow.points[1].dac = 64000;

        state.cal.VonLow = new calDataLinear2P();
        state.cal.VonLow->setCalConfigRef(&vonSetCalLow);
        state.cal.VonLow->setDACConfig(vonSetDAC.DAC_MIN, vonSetDAC.DAC_MAX);

        OCPSetCal.numPoints = 2;
        OCPSetCal.points[0].value = 0.50;
        OCPSetCal.points[0].dac = 100;
        OCPSetCal.points[1].value = 3.2;
        OCPSetCal.points[1].dac = 64000;

        state.cal.OCPset = new calDataLinear2P();
        state.cal.OCPset->setCalConfigRef(&OCPSetCal);
        state.cal.OCPset->setDACConfig(OCPSetDAC.DAC_MIN, OCPSetDAC.DAC_MAX);

        OCPSetCalLow.numPoints = 2;
        OCPSetCalLow.points[0].value = 0.50;
        OCPSetCalLow.points[0].dac = 100;
        OCPSetCalLow.points[1].value = 3.2;
        OCPSetCalLow.points[1].dac = 64000;

        state.cal.OCPsetLow = new calDataLinear2P();
        state.cal.OCPsetLow->setCalConfigRef(&OCPSetCalLow);
        state.cal.OCPsetLow->setDACConfig(OCPSetDAC.DAC_MIN, OCPSetDAC.DAC_MAX);

        OVPSetCal.numPoints = 2;
        OVPSetCal.points[0].value = 0.50;
        OVPSetCal.points[0].dac = 100;
        OVPSetCal.points[1].value = 3.2;
        OVPSetCal.points[1].dac = 64000;

        state.cal.OVPset = new calDataLinear2P();
        state.cal.OVPset->setCalConfigRef(&OVPSetCal);
        state.cal.OVPset->setDACConfig(OVPSetDAC.DAC_MIN, OVPSetDAC.DAC_MAX);

        OVPSetCalLow.numPoints = 2;
        OVPSetCalLow.points[0].value = 0.50;
        OVPSetCalLow.points[0].dac = 100;
        OVPSetCalLow.points[1].value = 3.2;
        OVPSetCalLow.points[1].dac = 64000;

        state.cal.OVPsetLow = new calDataLinear2P();
        state.cal.OVPsetLow->setCalConfigRef(&OVPSetCalLow);
        state.cal.OVPsetLow->setDACConfig(OVPSetDAC.DAC_MIN, OVPSetDAC.DAC_MAX);
        */

        for (int i = 0; i< caldefaultsLength; i++)
        {
            calData *c =  new calDataLinear2P();      
            *caldefaults[i].stateRef = c;

            CalibrationValueConfiguration *p = c->getCalConfigRef(); 
            p->numPoints = 2;
            p->valid = false;
            p->points[0].value = caldefaults[i].value0;
            p->points[1].value = caldefaults[i].value1;
            if (caldefaults[i].type == calCalType_e::calCalType_e_ADC) {
                p->points[0].adc   = caldefaults[i].adc0;
                p->points[1].adc   = caldefaults[i].adc1;
                c->setADCConfig(caldefaults[i].adcMin, caldefaults[i].adcMax);
            }
            if (caldefaults[i].type == calCalType_e::calCalType_e_DAC || caldefaults[i].type == calCalType_e::calCalType_e_LEVEL ) {
                p->points[0].dac   = caldefaults[i].adc0;
                p->points[1].dac   = caldefaults[i].adc1;
                c->setDACConfig(caldefaults[i].adcMin, caldefaults[i].adcMax);
            }
            c->setCalConfigRef(p);    
        } 
    };

    calType_e calAction::getCalType() { return _calType; };
    void      calAction::setCalType(calType_e value) 
    {
        if (value != _calType) 
        {
            _calType = value; 
            copy_cal_values_from_state(&_values, _calType);
            setCurPoint(0);
    }

    };

    int32_t calAction::getCurPoint() { return _curpoint; };
    void    calAction::setCurPoint(int32_t point) 
    {
        if (point >= 0 && point < _values.numPoints)
        {
            _curpoint = point;
            if (_calType == calType_e::calType_e_Imon_High || _calType == calType_e::calType_e_Imon_Low ||
                _calType == calType_e::calType_e_Umon_High || _calType == calType_e::calType_e_Umon_Low)
            {
                // ADC
                _set = _values.points[point].value;
                _measured = _values.points[point].adc;
            } 
            else
            {
                // DAC
                _set = _values.points[point].dac;
                _measured = _values.points[point].value;
            }
        }
    };

    float calAction::getSet() {return _set;};
    void  calAction::setSet(float set)
    {
        _set = set; 
        if (_calType == calType_e::calType_e_Imon_High || _calType == calType_e::calType_e_Imon_Low || 
            _calType == calType_e::calType_e_Umon_High || _calType == calType_e::calType_e_Umon_Low) 
        {
            _values.points[_curpoint].value = set;
        } else {
            _values.points[_curpoint].dac = (int32_t)set;
        }
    };


    float calAction::getMeasured() { return _measured; };
    void  calAction::setMeasured(float measured)
    {
        _measured = measured;
        if (_calType == calType_e::calType_e_Imon_High || _calType == calType_e::calType_e_Imon_Low || 
            _calType == calType_e::calType_e_Umon_High || _calType == calType_e::calType_e_Umon_Low) 
        {
            // ADC
            _values.points[_curpoint].adc = (int32_t)measured; 
        } else {
            // DAC
            _values.points[_curpoint].value = measured; 
        }
    };

    int32_t calAction::getNumPoints() { return _values.numPoints; };

    bool calAction::getRunning() { return _running; };
    void calAction::setRunning(bool running) { _running = running; };  // Flow is doing actual calibration routine
    bool calAction::getTriggeredCalibration() { return _triggerMeasure; };
    void calAction::setTriggeredCalibration(bool trigger) { _triggerMeasure = trigger; }; // Bool to trigger calibration start in Flow
    bool calAction::getValuesChanged() { return _valuesChanged; };
    void calAction::setValuesChanged(bool changed) { _valuesChanged = changed; };

    void calAction::setDAC()
    {
        if (_calType == calType_e_Iset_High || _calType == calType_e_Iset_Low)
        { // Iset
            state.setIset(_set, true);
        }

        if (_calType == calType_e_Von_High || _calType == calType_e_Von_Low)
        { // VonSet
            state.setVonset(_set, true);
        }

        if (_calType == calType_e_Uset_High || _calType == calType_e_Uset_Low)
        { // Uset
            state.setUset(_set, true);
        }

        if (_calType == calType_e_OCPset_High || _calType == calType_e_OCPset_Low)
        {
            state.setOCP(_set, true);
        }

        if (_calType == calType_e_OVPset_High || _calType == calType_e_OVPset_Low)
        {
            state.setOVP(_set, true);
        }
    };

    void calAction::fetchMeasured()
    {
        dcl::measuredStateStruct _measuredStateCopy;

        state.getMeasuredStateCopy(&_measuredStateCopy, 1000);

        if (_calType == calType_e::calType_e_Imon_High || _calType == calType_e::calType_e_Imon_Low)
        {
            _measured = _measuredStateCopy.avgCurrentRaw;
            _values.points[_curpoint].adc = (int32_t)_measured;
        }
        if (_calType == calType_e::calType_e_Umon_High || _calType == calType_e::calType_e_Umon_Low)
        {
            _measured = _measuredStateCopy.avgVoltRaw;
            _values.points[_curpoint].adc = (int32_t)_measured;
        }
        if (_calType == calType_e::calType_e_Iset_High || _calType == calType_e::calType_e_Iset_Low)
        { // Iset
            _measured = _measuredStateCopy.Imon;
            _values.points[_curpoint].value = _measured;
        }
        if (_calType == calType_e::calType_e_Von_High || _calType == calType_e::calType_e_Von_Low)
        { // VonSet, after do_search action.
            _measured = _measuredStateCopy.Umon;
            _values.points[_curpoint].value = _measured;
            _values.points[_curpoint].dac = (int32_t)_set;
        }
        if (_calType == calType_e::calType_e_Uset_High || _calType == calType_e::calType_e_Uset_Low)
        { // Uset
            _measured = _measuredStateCopy.Umon;
            _values.points[_curpoint].value = _measured;
        }
        if (_calType == calType_e::calType_e_OCPset_High || _calType == calType_e::calType_e_OCPset_Low)
        { // OCPSet, after do_search action.
            _measured = _measuredStateCopy.Imon;
            _values.points[_curpoint].value = _measured;
            _values.points[_curpoint].dac = (int32_t)_set;
        }
        if (_calType == calType_e::calType_e_OVPset_High || _calType == calType_e::calType_e_OVPset_Low)
        { // OVPset, after do_search action.
            _measured = _measuredStateCopy.Umon;
            _values.points[_curpoint].value = _measured;
            _values.points[_curpoint].dac = (int32_t)_set;
        }
        _values.valid = true; // TODO: Add more sanity checks?
    }

    void calAction::storeValues() 
    {
        copy_cal_values_to_state(&_values, _calType);
        write_cal_to_eeprom(_calType);
        _valuesChanged = false;
    }

    void calAction::resetValues()
    {
        copy_cal_values_from_state(&_values, _calType);
        if (_curpoint > _values.numPoints -1) {
            setCurPoint(0);
        } else {
            setCurPoint(_curpoint);
        }
    }

    void calAction::copy_cal_values_from_state(CalibrationValueConfiguration *cal_values, calType_e caltype)
    {
        CalibrationValueConfiguration *calconfig = state.cal.Imon->getCalConfigRef();
        switch (caltype)
        {
        case calType_e::calType_e_Imon_High:
            calconfig = state.cal.Imon->getCalConfigRef();
            break;
        case calType_e::calType_e_Imon_Low:
            calconfig = state.cal.ImonLow->getCalConfigRef();
            break;
        case calType_e::calType_e_Umon_High:
            calconfig = state.cal.Umon->getCalConfigRef();
            break;
        case calType_e::calType_e_Umon_Low:
            calconfig = state.cal.UmonLow->getCalConfigRef();
            break;
        case calType_e::calType_e_Iset_High:
            calconfig = state.cal.Iset->getCalConfigRef();
            break;
        case calType_e::calType_e_Iset_Low:
            calconfig = state.cal.IsetLow->getCalConfigRef();
            break;
        case calType_e::calType_e_Von_High:
            calconfig = state.cal.Von->getCalConfigRef();
            break;
        case calType_e::calType_e_Von_Low:
            calconfig = state.cal.VonLow->getCalConfigRef();
            break;
        case calType_e::calType_e_Uset_High:
            calconfig = state.cal.Uset->getCalConfigRef();
            break;
        case calType_e::calType_e_Uset_Low:
            calconfig = state.cal.Uset->getCalConfigRef();
            break;
        case calType_e::calType_e_OCPset_High:
            calconfig = state.cal.OCPset->getCalConfigRef();
            break;
        case calType_e::calType_e_OCPset_Low:
            calconfig = state.cal.OCPsetLow->getCalConfigRef();
            break;
        case calType_e::calType_e_OVPset_High:
            calconfig = state.cal.OVPset->getCalConfigRef();
            break;
        case calType_e::calType_e_OVPset_Low:
            calconfig = state.cal.OVPsetLow->getCalConfigRef();
            break;
        default:
            // Should not happen. Avoid uncontrolled memcpy
            // TODO: Add some kind of assert.
            return;
        }
        memcpy(cal_values, calconfig, sizeof(CalibrationValueConfiguration));
    };

    void calAction::copy_cal_values_to_state(CalibrationValueConfiguration *cal_values, calType_e caltype)
    {
        CalibrationValueConfiguration *calconfig = state.cal.Imon->getCalConfigRef();
        switch (caltype)
        {
        case calType_e::calType_e_Imon_High:
            calconfig = state.cal.Imon->getCalConfigRef();
            break;
        case calType_e::calType_e_Imon_Low:
            calconfig = state.cal.ImonLow->getCalConfigRef();
            break;
        case calType_e::calType_e_Umon_High:
            calconfig = state.cal.Umon->getCalConfigRef();
            break;
        case calType_e::calType_e_Umon_Low:
            calconfig = state.cal.UmonLow->getCalConfigRef();
            break;
        case calType_e::calType_e_Iset_High:
            calconfig = state.cal.Iset->getCalConfigRef();
            break;
        case calType_e::calType_e_Iset_Low:
            calconfig = state.cal.IsetLow->getCalConfigRef();
            break;
        case calType_e::calType_e_Von_High:
            calconfig = state.cal.Von->getCalConfigRef();
            break;
        case calType_e::calType_e_Von_Low:
            calconfig = state.cal.VonLow->getCalConfigRef();
            break;
        case calType_e::calType_e_Uset_High:
            calconfig = state.cal.Uset->getCalConfigRef();
            break;
        case calType_e::calType_e_Uset_Low:
            calconfig = state.cal.UsetLow->getCalConfigRef();
            break;
        case calType_e::calType_e_OCPset_High:
            calconfig = state.cal.OCPset->getCalConfigRef();
            break;
        case calType_e::calType_e_OCPset_Low:
            calconfig = state.cal.OCPsetLow->getCalConfigRef();
            break;
        case calType_e::calType_e_OVPset_High:
            calconfig = state.cal.OVPset->getCalConfigRef();
            break;
        case calType_e::calType_e_OVPset_Low:
            calconfig = state.cal.OVPsetLow->getCalConfigRef();
            break;
        default:
            // Should not happen. Avoid uncontrolled memcpy
            // TODO: Add some kind of assert.
            return;
        }
        memcpy(calconfig, cal_values, sizeof(CalibrationValueConfiguration));
    };

    void calAction::write_cal_to_eeprom(calType_e caltype)
    {
        CalibrationValueConfiguration *calconfig; // = state.cal.Imon->getCalConfigRef();
        uint32_t startaddress;
        switch (caltype)
        {
        case calType_e::calType_e_Imon_High:
            calconfig = state.cal.Imon->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_IMON_H;
            break;
        case calType_e::calType_e_Imon_Low:
            calconfig = state.cal.ImonLow->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_IMON_L;
            break;
        case calType_e::calType_e_Umon_High:
            calconfig = state.cal.Umon->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_UMON_H;
            break;
        case calType_e::calType_e_Umon_Low:
            calconfig = state.cal.UmonLow->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_UMON_L;
            break;
        case calType_e::calType_e_Iset_High:
            calconfig = state.cal.Iset->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_ISET_H;
            break;
        case calType_e::calType_e_Iset_Low:
            calconfig = state.cal.IsetLow->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_ISET_L;
            break;
        case calType_e::calType_e_Von_High:
            calconfig = state.cal.Von->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_VON_H;
            break;
        case calType_e::calType_e_Von_Low:
            calconfig = state.cal.VonLow->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_VON_L;
            break;
        case calType_e::calType_e_Uset_High:
            calconfig = state.cal.Uset->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_USET_H;
            break;
        case calType_e::calType_e_Uset_Low:
            calconfig = state.cal.UsetLow->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_USET_L;
            break;
        case calType_e::calType_e_OCPset_High:
            calconfig = state.cal.OCPset->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_OCP_H;
            break;
        case calType_e::calType_e_OCPset_Low:
            calconfig = state.cal.OCPsetLow->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_OCP_L;
            break;
        case calType_e::calType_e_OVPset_High:
            calconfig = state.cal.OVPset->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_OVP_H;
            break;
        case calType_e::calType_e_OVPset_Low:
            calconfig = state.cal.OVPsetLow->getCalConfigRef();
            startaddress = EEPROM_ADDR_CAL_OVP_L;
            break;
        default:
            startaddress = 0xF00; // Dummy
            // TODO: Add assert of some kind.
            return;
            break;
        }
        myeeprom.calibrationValuesWrite(calconfig, startaddress);
    };

    bool calAction::storeDefaults()
    {
        calSetDefaults();
        return storeAllValues();
    }

    bool calAction::storeAllValues()
    {
        if (myeeprom.magicWrite()) //Also tests if writing works.
        {
            //printlogstr("INFO: EEPROM magic written.");
            write_cal_to_eeprom(calType_e::calType_e_Imon_High);
            write_cal_to_eeprom(calType_e::calType_e_Imon_Low);
            write_cal_to_eeprom(calType_e::calType_e_Umon_High);
            write_cal_to_eeprom(calType_e::calType_e_Umon_Low);
            write_cal_to_eeprom(calType_e::calType_e_Iset_High);
            write_cal_to_eeprom(calType_e::calType_e_Iset_Low);
            write_cal_to_eeprom(calType_e::calType_e_Uset_High);
            write_cal_to_eeprom(calType_e::calType_e_Uset_Low);
            write_cal_to_eeprom(calType_e::calType_e_Von_High);
            write_cal_to_eeprom(calType_e::calType_e_Von_Low);
            write_cal_to_eeprom(calType_e::calType_e_OCPset_High);
            write_cal_to_eeprom(calType_e::calType_e_OCPset_Low);
            write_cal_to_eeprom(calType_e::calType_e_OVPset_High);
            write_cal_to_eeprom(calType_e::calType_e_OVPset_Low);
            return true;
            //printlogstr("INFO: Default cal values stored.");
        }
        else
        {
            //printlogstr("ERROR: Unable to write EEPROM magic.");
            return false;
        }
    }

    bool calAction::readAllValues()
    {
        state.hw.calibrationCRCOK = false;
        if (state.hw.eepromMagicDetected)
        {
            bool r,v;
            r = myeeprom.calibrationValuesRead(state.cal.Imon->getCalConfigRef(), EEPROM_ADDR_CAL_IMON_H);
            v = state.cal.Imon->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.ImonLow->getCalConfigRef(), EEPROM_ADDR_CAL_IMON_L);
            v = v && state.cal.ImonLow->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.Umon->getCalConfigRef(), EEPROM_ADDR_CAL_UMON_H);
            v = v && state.cal.Umon->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.UmonLow->getCalConfigRef(), EEPROM_ADDR_CAL_UMON_L);
            v = v && state.cal.UmonLow->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.Iset->getCalConfigRef(), EEPROM_ADDR_CAL_ISET_H);
            v = v && state.cal.Iset->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.IsetLow->getCalConfigRef(), EEPROM_ADDR_CAL_ISET_L);
            v = v && state.cal.IsetLow->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.Von->getCalConfigRef(), EEPROM_ADDR_CAL_VON_H);
            v = v && state.cal.Von->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.VonLow->getCalConfigRef(), EEPROM_ADDR_CAL_VON_L);
            v = v && state.cal.VonLow->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.OCPset->getCalConfigRef(), EEPROM_ADDR_CAL_OCP_H);
            v = v && state.cal.OCPset->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.OCPsetLow->getCalConfigRef(), EEPROM_ADDR_CAL_OCP_L);
            v = v && state.cal.OCPsetLow->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.OVPset->getCalConfigRef(), EEPROM_ADDR_CAL_OVP_H);
            v = v && state.cal.OVPset->getCalConfigRef()->valid;
            r = r && myeeprom.calibrationValuesRead(state.cal.OVPsetLow->getCalConfigRef(), EEPROM_ADDR_CAL_OVP_L);
            v = v && state.cal.OVPsetLow->getCalConfigRef()->valid;
            state.hw.calibrationCRCOK = r;
            state.hw.calibrationValid = v;
            if (r == true)
            {
                addEvent(EVENT_DEBUG_CAL_CRC_OK);
                //SERIALDEBUG.println("INFO: Calibration data CRC OK.");
            }
            else
            {
                addEvent(EVENT_ERROR_CAL_CRC);
                //SERIALDEBUG.println("ERROR: Calibartion data CRC NOT OK.");
            };
            return r;
        } else {
            return false;
        }
    }

}