// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "main.h"
#include "cal.h"
#include "util.h"

using namespace dcl;

namespace dcl
{
    bool calLinear2P::setCalConfig(CalibrationValueConfiguration newconfig)
    {
        if (newconfig.numPoints != 2)
        {
            _gotConf = false;
            _configured = false;
            return false;
        }

        _conf = newconfig;
        _gotConf = true;

        return _configure();
    };

    CalibrationValueConfiguration calLinear2P::getCalConfig()
    {
        return _conf;
    };

    CalibrationValueConfiguration *calLinear2P::getCalConfigRef()
    {
        return &_conf;
    }

    bool calLinear2P::setADCConfig(int32_t min, int32_t max)
    {
        _minADC = min;
        _maxADC = max;
        _gotADC = true;

        return _configure();
    };

    bool calLinear2P::setDACConfig(int32_t min, int32_t max)
    {
        return setADCConfig(min,max);
    };

    bool calLinear2P::_configure()
    {
        if (_gotConf && _gotADC)
        {
            _multiply = (_conf.points[1].value - _conf.points[0].value) / (_conf.points[1].adc - _conf.points[0].adc);
            _offset = _conf.points[0].value - _conf.points[0].adc * _multiply;
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

    bool calLinear2P::configured() { return _configured; };

    float calLinear2P::remapADC(float input)
    {
        if (!_configured)
        {
            return 0;
        }
//        return ::remap((float)input, (float)_minADC, _minVal, (float)_maxADC, _maxVal);
        return ::remap((float)input, (float)_conf.points[0].adc, _conf.points[0].value, (float)_conf.points[1].adc, _conf.points[1].value);
    }

    float calLinear2P::remapDAC(float input)
    {
        if (!_configured)
        {
            return 0;
        }
//        return ::remap((float)input, (float)_minADC, _minVal, (float)_maxADC, _maxVal);
        return ::remap((float)input, (float)_conf.points[0].value, _conf.points[0].dac, (float)_conf.points[1].value, _conf.points[1].dac);
    }


    void calSetDefaults() 
    {
        // TODO: Hardcoded calibration values for now
        currentCal.numPoints = 2;
        currentCal.points[0].value = 0.1;  // 0.0; // 0.1V  => 1.0A
        currentCal.points[0].adc = 700572; // 4575;
        currentCal.points[1].value = 10.0; // 1.000V => 10A
        currentCal.points[1].adc = 6963036;

        state.cal.Imon = new calLinear2P();
        state.cal.Imon->setCalConfig(currentCal);
        state.cal.Imon->setADCConfig(currentADC.ADC_MIN, currentADC.ADC_MAX);

        currentCalLow.numPoints = 2;
        currentCalLow.points[0].value = 0.05; // 0.0; // 0.1V  => 1.0A
        currentCalLow.points[0].adc = 700000; // 4575;
        currentCalLow.points[1].value = 0.95; // 1.000V => 10A
        currentCalLow.points[1].adc = 6963036;

        state.cal.ImonLow = new calLinear2P();
        state.cal.ImonLow->setCalConfig(currentCalLow);
        state.cal.ImonLow->setADCConfig(currentADC.ADC_MIN, currentADC.ADC_MAX);

        //  CalibrationValueConfiguration voltCal;
        voltCal.numPoints = 2;
        voltCal.points[0].value = 0.0; // 50mV
        voltCal.points[0].adc = 2059;
        voltCal.points[1].value = 100.0; // 1.000V => 100V //1.100 * 34 * 2.1; // 1.100V => >80V
        voltCal.points[1].adc = 6970322;

        state.cal.Umon = new calLinear2P();
        state.cal.Umon->setCalConfig(voltCal);
        state.cal.Umon->setADCConfig(voltADC.ADC_MIN, voltADC.ADC_MAX);

        voltCalLow.numPoints = 2;
        voltCalLow.points[0].value = 0.0; // 50mV
        voltCalLow.points[0].adc = 2059;
        voltCalLow.points[1].value = 100.0; // 1.000V => 100V //1.100 * 34 * 2.1; // 1.100V => >80V
        voltCalLow.points[1].adc = 6970322;

        state.cal.UmonLow = new calLinear2P();
        state.cal.UmonLow->setCalConfig(voltCalLow);
        state.cal.UmonLow->setADCConfig(voltADC.ADC_MIN, voltADC.ADC_MAX);

        iSetCal.numPoints = 2;
        iSetCal.points[0].value = 0.00299; // @3.3Vinput (AMS1117)
        iSetCal.points[0].dac = 100;
        iSetCal.points[1].value = 3.2374; // @3.3Vinput (AMS1117)
        iSetCal.points[1].dac = 64000;

        state.cal.Iset = new calLinear2P();
        state.cal.Iset->setCalConfig(iSetCal);
        state.cal.Iset->setDACConfig(iSetDAC.DAC_MIN, iSetDAC.DAC_MAX);

        iSetCalLow.numPoints = 2;
        iSetCalLow.points[0].value = 0.00299; // @3.3Vinput (AMS1117)
        iSetCalLow.points[0].dac = 100;
        iSetCalLow.points[1].value = 3.2374; // @3.3Vinput (AMS1117)
        iSetCalLow.points[1].dac = 64000;

        state.cal.IsetLow = new calLinear2P();
        state.cal.IsetLow->setCalConfig(iSetCalLow);
        state.cal.IsetLow->setDACConfig(iSetDAC.DAC_MIN, iSetDAC.DAC_MAX);

        uSetCal.numPoints = 2;
        uSetCal.points[0].value = 1.00;
        uSetCal.points[0].dac = 100;
        uSetCal.points[1].value = 3.2;
        uSetCal.points[1].dac = 64000;

        state.cal.Uset = new calLinear2P();
        state.cal.Uset->setCalConfig(uSetCal);
        state.cal.Uset->setDACConfig(uSetDAC.DAC_MIN, uSetDAC.DAC_MAX);

        uSetCalLow.numPoints = 2;
        uSetCalLow.points[0].value = 1.00;
        uSetCalLow.points[0].dac = 100;
        uSetCalLow.points[1].value = 3.2;
        uSetCalLow.points[1].dac = 64000;

        state.cal.UsetLow = new calLinear2P();
        state.cal.UsetLow->setCalConfig(uSetCalLow);
        state.cal.UsetLow->setDACConfig(uSetDAC.DAC_MIN, uSetDAC.DAC_MAX);

        vonSetCal.numPoints = 2;
        vonSetCal.points[0].value = 0.50;
        vonSetCal.points[0].dac = 100;
        vonSetCal.points[1].value = 3.2;
        vonSetCal.points[1].dac = 64000;

        state.cal.Von = new calLinear2P();
        state.cal.Von->setCalConfig(vonSetCal);
        state.cal.Von->setDACConfig(vonSetDAC.DAC_MIN, vonSetDAC.DAC_MAX);

        vonSetCalLow.numPoints = 2;
        vonSetCalLow.points[0].value = 0.50;
        vonSetCalLow.points[0].dac = 100;
        vonSetCalLow.points[1].value = 3.2;
        vonSetCalLow.points[1].dac = 64000;

        state.cal.VonLow = new calLinear2P();
        state.cal.VonLow->setCalConfig(vonSetCalLow);
        state.cal.VonLow->setDACConfig(vonSetDAC.DAC_MIN, vonSetDAC.DAC_MAX);

        OCPSetCal.numPoints = 2;
        OCPSetCal.points[0].value = 0.50;
        OCPSetCal.points[0].dac = 100;
        OCPSetCal.points[1].value = 3.2;
        OCPSetCal.points[1].dac = 64000;

        state.cal.OCPset = new calLinear2P();
        state.cal.OCPset->setCalConfig(OCPSetCal);
        state.cal.OCPset->setDACConfig(OCPSetDAC.DAC_MIN, OCPSetDAC.DAC_MAX);

        OCPSetCalLow.numPoints = 2;
        OCPSetCalLow.points[0].value = 0.50;
        OCPSetCalLow.points[0].dac = 100;
        OCPSetCalLow.points[1].value = 3.2;
        OCPSetCalLow.points[1].dac = 64000;

        state.cal.OCPsetLow = new calLinear2P();
        state.cal.OCPsetLow->setCalConfig(OCPSetCalLow);
        state.cal.OCPsetLow->setDACConfig(OCPSetDAC.DAC_MIN, OCPSetDAC.DAC_MAX);

        OVPSetCal.numPoints = 2;
        OVPSetCal.points[0].value = 0.50;
        OVPSetCal.points[0].dac = 100;
        OVPSetCal.points[1].value = 3.2;
        OVPSetCal.points[1].dac = 64000;

        state.cal.OVPset = new calLinear2P();
        state.cal.OVPset->setCalConfig(OVPSetCal);
        state.cal.OVPset->setDACConfig(OVPSetDAC.DAC_MIN, OVPSetDAC.DAC_MAX);

        OVPSetCalLow.numPoints = 2;
        OVPSetCalLow.points[0].value = 0.50;
        OVPSetCalLow.points[0].dac = 100;
        OVPSetCalLow.points[1].value = 3.2;
        OVPSetCalLow.points[1].dac = 64000;

        state.cal.OVPsetLow = new calLinear2P();
        state.cal.OVPsetLow->setCalConfig(OVPSetCalLow);
        state.cal.OVPsetLow->setDACConfig(OVPSetDAC.DAC_MIN, OVPSetDAC.DAC_MAX);
    };
}