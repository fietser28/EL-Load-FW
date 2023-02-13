#include "main.h"
#include "cal.h"
#include "util.h"

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

    bool calLinear2P::setADCConfig(uint32_t min, uint32_t max)
    {
        _minADC = min;
        _maxADC = max;
        _gotADC = true;

        return _configure();
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

    float calLinear2P::remap(float input)
    {
        if (!_configured)
        {
            return 0;
        }
        return ::remap((float)input, (float)_minADC, _minVal, (float)_maxADC, _maxVal);
    }

}