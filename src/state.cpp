// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "FreeRTOS.h"
#include "semphr.h"

#include "main.h"
#include "state.h"
#include "ui/vars.h" // For the enum definitions

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
                _setState.OPPset = 80.0f;
                _setState.OPPdelay = 5;
                _setState.OTPset = 80.0f;
                _setState.OTPdelay = 10;
                _setState.Iset = 0.111f;
                _setState.CalibrationIset = false;
                _setState.Uset = 1000.0f;
                _setState.CalibrationUset = false;
                _setState.Rset = 1000.0f;
                _setState.Pset = 12.5f;
                _setState.VonSet = 1.1f;
                _setState.OCPset = 10.0f;
                _setState.CalibrationOCPset = false;
                _setState.OVPset = 20.0f;
                _setState.CalibrationOVPset = false;
                _setState.protection = false;
                _setState.VonLatched = VonType_e_Unlatched;
                _setState.FanManualSpeed = 128;
                _setState.FanAuto = true;
                xSemaphoreGive(_setStateMutex);
                //updateAverageTask();
                updateHWIOTask();
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
                updateHWIOTask();
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
                updateHWIOTask();
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

    // Called from HW Task.
    bool stateManager::setHWstate(bool ocptrig, bool ovptrig, bool von)
    {
    // Protection kicked in.
    if (ocptrig || ovptrig) 
    {
        state.setProtection();
    };

    // Von kicks in when on and inhibit mode => Turn load of.
    // TODO: Fix mutexed around this test?
    if (_setState.VonLatched == VonType_e_Inhibit && !von && _setState.on)
    {
        state.setOff();
    }

    if (_measuredStateMutex != NULL)
    {
        if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
        {
                // Do not clear, only set. Cleared in clearProtection. DO clear when calibrating OCP
                _measuredState.OCPstate = _setState.CalibrationOCPset ? ocptrig : _measuredState.OCPstate || ocptrig; 

                // Do not clear, only set. Cleared in clearProtection. No need for calibration special: OVP is calibrated in OFF state.
                _measuredState.OVPstate = _measuredState.OVPstate || ovptrig; 

                _measuredState.VonState = von;
                xSemaphoreGive(_measuredStateMutex);

                return true;
        }
    }
    return false;
    };

    bool stateManager::OTPtriggered() 
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                _measuredState.OTPstate = true;
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return false;
    };

    bool stateManager::OPPtriggered() 
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                _measuredState.OPPstate = true;
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return false;
    };

    bool stateManager::setTemp1(float temp)
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                _measuredState.Temp1 = temp;
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return false;
    };

    bool stateManager::setTemp2(float temp)
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                _measuredState.Temp2 = temp;
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return false;
    };

    bool stateManager::setFanRPMread(uint32_t rpm)
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                _measuredState.FanRPM = rpm;
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return false;
    };

    bool stateManager::setFanAuto(bool value)
    {
       uint8_t currentPWM = 0;
       if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.FanAuto = value;
                currentPWM = _setState.FanManualSpeed; 
                xSemaphoreGive(_setStateMutex);
            }
        }
        if (value) {
            // Auto
            fancontrol.setPWMDCRamp(fan_max31760::PWM_DC_RAMP_SLOW);
        } else {
            // Manual
            fancontrol.setPWMDCRamp(fan_max31760::PWM_DC_RAMP_FAST);    
        }
        fancontrol.setDirectFanControl(!value);
        if (value) {
            fancontrol.setPWM(currentPWM);
        }
        return true;
    };

    bool stateManager::setFanPWM(uint8_t rpm)
    {
       if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.FanManualSpeed = rpm;
                xSemaphoreGive(_setStateMutex);
            }
        }
        fancontrol.setPWM(rpm);
        return true;
    };

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
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                // Clear HW states
                _measuredState.OCPstate = false; 
                _measuredState.OVPstate = false;
                _measuredState.OTPstate = false;
                _measuredState.OPPstate = false;
                xSemaphoreGive(_measuredStateMutex);
            }
        }
        updateHWIOTask();
        return updateAverageTask();
    };

    bool stateManager::setProtection()
    {
        // Avoid protection during calibration.
        // TODO: mutex?
        if (_setState.CalibrationIset == true || _setState.CalibrationOCPset == true || _setState.CalibrationOVPset == true ||
            _setState.CalibrationUset == true || _setState.CalibrationVonSet == true) 
        {
            return false;
        }

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
        updateHWIOTask();
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

    bool stateManager::setVonset(float newVonset, bool rawDACvalue)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                _setState.CalibrationVonSet = rawDACvalue;
                _setState.VonSet = newVonset;
                xSemaphoreGive(_setStateMutex);
                return updateMeasureTask();
            }
        }
        return false;
    };

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

    bool stateManager::setUset(float newUset, bool rawDACvalue)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                _setState.CalibrationUset = rawDACvalue; 
                _setState.Uset = newUset;
                xSemaphoreGive(_setStateMutex);
                return updateMeasureTask();
            }
        }
        return false;
    };

    bool stateManager::setOCP(float newOCP, bool rawDACvalue)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                _setState.CalibrationOCPset = rawDACvalue; 
                _setState.OCPset = newOCP;
                xSemaphoreGive(_setStateMutex);
                // TODO: not clean: updateMeasureTask doesn't run when updateHWIOTask fails, a problem?
                updateHWIOTask();
                return updateMeasureTask();
            }
        }
        return false;
    };

    bool stateManager::setOVP(float newOVP, bool rawDACvalue)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                _setState.CalibrationOVPset = rawDACvalue; 
                _setState.OVPset = newOVP;
                xSemaphoreGive(_setStateMutex);
                // TODO: not clean: updateMeasureTask doesn't run when updateHWIOTask fails, a problem?
                updateHWIOTask();
                return updateMeasureTask();
            }
        }
        return false;
    };


    bool stateManager::setVonLatched(VonType_e value)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.VonLatched = value; 
                xSemaphoreGive(_setStateMutex);
                // TODO: not clean: updateMeasureTask doesn't run when updateHWIOTask fails, a problem?
                updateHWIOTask();
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

   bool stateManager::setOTPset(float OTPset)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.OTPset = OTPset;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateHWIOTask();
    };

   bool stateManager::setOTPdelay(float OTPdelay)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.OTPdelay = OTPdelay;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateHWIOTask();
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

        // TODO: use updateAverageTask function instead.
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.record = setrecord;
                msg.on     = _setState.on;
                msg.OPPset = _setState.OPPset;
                msg.OPPdelay = _setState.OPPdelay;
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

    bool stateManager::updateHWIOTask()
    {
        setStateStruct msg;
        if (getSetStateCopy(&msg, (TickType_t)10))
        {
            xQueueSend(changeHWIOSettings, &msg, 10);
            return true;
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