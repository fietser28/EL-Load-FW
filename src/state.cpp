
#include "FreeRTOS.h"
#include "semphr.h"

#include "main.h"
#include "state.h"

namespace dcl
{

    void stateManager::begin()
    {

        _setStateMutex = xSemaphoreCreateMutex();
        if (_setStateMutex == NULL)
        { // TODO: reset, something is really wrong....
        }
        _measuredStateMutex = xSemaphoreCreateMutex();
        if (_measuredStateMutex == NULL)
        { // TODO: reset, something is really wrong....
        }

        _setState.startupDone = false;
    };

    bool stateManager::setDefaults() 
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // Is constant
                _setState.sampleRate = ((float)F_CPU)/((float)CLOCK_DIVIDER_ADC * 2.0f * (float)ADC_OSR);
                _setState.PLFreq = DEFAULT_PL_FREQ;
                _setState.on = false;
                _setState.NLPC = DEFAULT_AVG_SAMPLES_NPLC;
                _setState.OPPset = 80;
                _setState.OPPdelay = 5;
                _setState.Iset = 1.111f;
                _setState.CalibrationIset = false;
                _setState.Rset = 1000.0f;
                _setState.protection = false;
                xSemaphoreGive(_setStateMutex);
                //updateAverageTask();
                return true;
            }
        }
        return false;
    }

    void stateManager::startupDone() 
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.startupDone = true;
                _setState.mode = ELmode::CC;
                xSemaphoreGive(_setStateMutex);
                updateMeasureTask();
            }
        }
    }

    bool stateManager::setOn() {        
        // Don't enable if there is a protection
        if (_setState.protection == true) {
            return false;
        }
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.on = true;
                xSemaphoreGive(_setStateMutex);
                updateMeasureTask();
                updateAverageTask();
                return true;
            }
        }
        return false;
    }

    bool stateManager::setOff() {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.on = false;
                xSemaphoreGive(_setStateMutex);
                updateMeasureTask();
                updateAverageTask();
                return true;
            }
        }
        return false;
    }

    bool stateManager::getMeasuredStateCopy( measuredStateStruct *mystate, TickType_t waitTicks) {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, waitTicks) == pdTRUE)
            {
                memcpy(mystate, &_measuredState, sizeof(_measuredState));
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return false;
    }

    bool stateManager::getSetStateCopy( setStateStruct *mystate, TickType_t waitTicks) {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, waitTicks) == pdTRUE)
            {
                memcpy(mystate, &_setState, sizeof(_setState));
                xSemaphoreGive(_setStateMutex);
                return true;
            }
        }
        return false;
    }

    // Called from Avg Task, keep latency low.
    bool stateManager::setAvgMeasurements(float imon, float umon, double As,
                                          double Ws, double time, uint32_t avgCurrentRaw, uint32_t avgVoltRaw)
    {
        if (_measuredStateMutex != NULL)
        {
            // Don't wait to long, it is nog a problem if this is skipped
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)2) == pdTRUE)
            {
                _measuredState.Imon = imon;
                _measuredState.Umon = umon;
                _measuredState.As = As;
                _measuredState.Ws = Ws;
                _measuredState.Ptime = time;
                _measuredState.avgCurrentRaw = avgCurrentRaw;
                _measuredState.avgVoltRaw = avgVoltRaw;
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return false;
    }

    // Send message to averaging task to clear the power measurements.
    // Note: this is asynchronous!
    bool stateManager::clearPower()
    {
        return updateAverageTask(true);
    };

    bool stateManager::clearProtection()
    {
       if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.protection = false;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateAverageTask();
    };

    bool stateManager::setProtection()
    {
        setOff();
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.protection = true;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateAverageTask();
    };

    bool stateManager::setMode(mode_e newMode)
    {
    if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // Don't enable if load is on.
                if (_setState.on == true) {
                    xSemaphoreGive(_setStateMutex);
                    return false;
                }

                switch (newMode)
                {
                case mode_e_CC:
                    _setState.mode = ELmode::CC;
                    break;
                case mode_e_CV:
                    _setState.mode = ELmode::CV;
                    break;
                case mode_e_CP:
                    _setState.mode = ELmode::CP;
                    break;
                case mode_e_CR:
                    _setState.mode = ELmode::CR;
                    break;
                case mode_e_SHORT:
                    _setState.mode = ELmode::SHORT;
                    break;
                default:
                    _setState.mode = ELmode::CC;
                    _setState.Iset = 0.0f; // Something is wrong.                
                }
                xSemaphoreGive(_setStateMutex);
                updateMeasureTask();
                updateAverageTask();
                return true;
            }
        }
        return false;
    }

    bool stateManager::setIset(float newIset, bool rawDACvalue)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                _setState.CalibrationIset = rawDACvalue; 
                _setState.Iset = newIset;
                xSemaphoreGive(_setStateMutex);
                return updateMeasureTask();
            }
        }
        return false;
    };

    bool stateManager::setRset(float newRset)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                _setState.Rset = newRset;
                xSemaphoreGive(_setStateMutex);
                return updateMeasureTask();
            }
        }
        return false;
    };

    bool stateManager::setPset(float newPset)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                _setState.Pset = newPset;
                xSemaphoreGive(_setStateMutex);
                return updateMeasureTask();
            }
        }
        return false;
    };

   bool stateManager::setOPPset(float OPPset)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.OPPset = OPPset;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateAverageTask();
    };

   bool stateManager::setOPPdelay(float OPPdelay)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.OPPdelay = OPPdelay;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateAverageTask();
    };

    bool stateManager::setNPLC(uint32_t cycles)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.NLPC = cycles;
                xSemaphoreGive(_setStateMutex);
            };
        };
        return updateAverageTask();
    };

    uint32_t stateManager::getNPLC()
    {
        uint16_t cycles;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                cycles = _setState.NLPC;
                xSemaphoreGive(_setStateMutex);
                return cycles;
            };
        };
        return 1;
    };

    // Send message to averaging task to clear the power measurements.
    // Note: this is asynchronous!
    bool stateManager::record(bool setrecord)
    {

        changeAverageSettingsMsg msg;
        msg.avgSamples = 0; // Don't set new window sizes
        msg.clear = false; // Don't clear
        msg.record = setrecord;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.record = setrecord;
                msg.on     = _setState.on;
                xSemaphoreGive(_setStateMutex);
                xQueueSend(changeAverageSettings, &msg, 10);
                return true;
            }
        }
        return false;
    };

    bool stateManager::toggleRecord()
    {
        bool recordnow;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                recordnow = _setState.record;
                xSemaphoreGive(_setStateMutex);
                return record(!recordnow);
            }
        }
        return false;
    }

    bool stateManager::updateAverageTask(bool clearPower)
    {
        changeAverageSettingsMsg msg;
        //msg.avgSamplesCurrent = 0; // Don't set new window sizes
        //msg.avgSamplesVoltage = 0;
        msg.clear = clearPower;  // Don't clear (default if parameter is not given)
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                
                msg.record = _setState.record;
                msg.on     = _setState.on;
                msg.avgSamples = (_setState.NLPC * _setState.sampleRate) / _setState.PLFreq;
                msg.OPPset = _setState.OPPset;
                msg.OPPdelay = _setState.OPPdelay;
                xSemaphoreGive(_setStateMutex);
                xQueueSend(changeAverageSettings, &msg, 10);
                return true;
            }
        }
        return false;

    }

    bool stateManager::updateMeasureTask()
    {
        setStateStruct msg;
        if (getSetStateCopy(&msg, (TickType_t)10))
        {
            xQueueSend(changeMeasureTaskSettings, &msg, 10);
            return true;
        }
        return false;
    }

}