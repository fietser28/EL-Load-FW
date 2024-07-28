// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "FreeRTOS.h"
#include "semphr.h"

#include "main.h"
#include "state.h"
#include "keys.h"
#include "ui/vars.h" // For the enum definitions
#include "ui/ui.h"
#include "ui/screens.h"
#include "scpi/scpi-def.h"

using namespace dcl::scpi;

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
        scpi_busy_inc();
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // Is constant
                _setState.sampleRate = ((float)F_CPU)/((float)CLOCK_DIVIDER_ADC * 2.0f * (float)ADC_OSR);
                _setState.PLFreq = DEFAULT_PL_FREQ;
                _setState.on = false;
                _setState.mode = ELmode::CC;
                _setState.CalibrationMode = false;
                _setState.NLPC = DEFAULT_AVG_SAMPLES_NPLC;
                _setState.OPPset = ranges[ranges_e_OPP_Delay].defValue;
                _setState.OPPdelay = ranges[ranges_e_OPP_Delay].defValue;
                _setState.OTPset = ranges[ranges_e_OTP_Temp].defValue;
                _setState.OTPdelay = ranges[ranges_e_OTP_Delay].defValue;
                _setState.Iset = ranges[ranges_e_Curr_High].defValue;
                _setState.CalibrationIset = false;
                _setState.Uset = ranges[ranges_e_Volt_High].defValue;
                _setState.CalibrationUset = false;
                _setState.Rset = ranges[ranges_e_Res].defValue;
                _setState.Pset = ranges[ranges_e_Power].defValue;
                _setState.VonSet = ranges[ranges_e_Von_High].defValue;
                _setState.OCPset = ranges[ranges_e_OCP_High].defValue;
                _setState.CalibrationOCPset = false;
                _setState.OVPset = ranges[ranges_e_OVP_High].defValue;
                _setState.CalibrationOVPset = false;
                _setState.protection = false;
                _setState.VonLatched = VonType_e_Unlatched;
                _setState.CapVoltStop = ranges[ranges_e_VoltStop].defValue;
                _setState.CapAhStop = ranges[ranges_e_AHStop].defValue;
                _setState.CapWhStop = ranges[ranges_e_WHStop].defValue;
                _setState.CapTimeStop = ranges[ranges_e_TimeStop].defValue;
                _setState.capacityLimit = false;
                _setState.FanManualSpeed = ranges[ranges_e_FanSpeed].defValue;
                _setState.FanAuto = true;
                _setState.rangeCurrentLow = false;
                _setState.rangeVoltageLow = false;
                _setState.senseVoltRemote = false;
                _setState.scpiWdogEnabled = false;
                _setState.scpiWdogDelay = 10;
                _setState.scpiWdogType = WDogType::ACTIVITY;
                xSemaphoreGive(_setStateMutex);
                updateMeasureTask();
                updateAverageTask(true);
                updateHWIOTask();
                updateKeysTask(); // For led
                // Needed to get relay & sw in defined state.
                state.setVoltSense(true);
                state.setVoltSense(false);
                //state.setRangeCurrent(true);
                state.setRangeCurrent(false);
                //state.setRangeVoltage(true);
                state.setRangeVoltage(false);
                scpi_busy_dec();
                return true;
            }
        }
        scpi_busy_dec();
        return false;
    }

    void stateManager::startupDone() 
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // Clear HW state memories
                _measuredState.OCPstate = false; 
                _measuredState.OVPstate = false;
                _measuredState.OTPstate = false;
                _measuredState.OPPstate = false;
                _measuredState.SenseError = false;
                _measuredState.PolarityError = false;
                xSemaphoreGive(_measuredStateMutex);
            }
        }
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.startupDone = true;
                _setState.mode = ELmode::CC;
                _setState.protection = false;
                xSemaphoreGive(_setStateMutex);
            }
        }
        updateMeasureTask();
    }

    bool stateManager::CalibrationMode(bool on) 
    {
        changeScreen_s msg;

        if (_setState.CalibrationMode == on) {
            return false; // Already in this mode.
        }

        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.CalibrationMode = on;
                xSemaphoreGive(_setStateMutex);
                if (on == true) {
                    msg.newScreen = SCREEN_ID_CALIBRATION;
                    msg.pop = false;
                } else {
                    msg.newScreen = SCREEN_ID_MAIN; // Just to be sure.
                    msg.pop = true;
                    state.setDefaults(); // Cleanup calibration mess.
                }
                xQueueSend(changeScreen, &msg, 100);
                return true;
            }
        }
        return false;
    }

    bool stateManager::getCalibrationMode()
    {
        return _setState.CalibrationMode; // Atomic, no locking needed.
    }

    bool stateManager::setOn() {        
        // Don't enable if there is a protection
        if (_setState.protection == true || ( _setState.capacityLimit == true && _setState.record == true)) {
            return false;
        }
        // Don't enable in DVM mode.
        if (_setState.mode == ELmode::DVM) {
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
                updateKeysTask();
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
                updateKeysTask();
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
                if (_setState.record && _setState.capacityLimitEnabled) { // TODO: Lazy on lock
                    _measuredState.CapVoltStopTriggered = _measuredState.CapVoltStopTriggered || ( _setState.CapVoltStop >= umon); // TODO?: Lazy on lock
                    _measuredState.CapAhStopTriggered   = _measuredState.CapAhStopTriggered   || ( _setState.CapAhStop   <= ((float)As / 3600.0f)); // TODO?: Lazy on lock
                    _measuredState.CapWhStopTriggered   = _measuredState.CapWhStopTriggered   || ( _setState.CapWhStop   <= ((float)Ws / 3600.0f)); // TODO?: Lazy on lock
                    _measuredState.CapTimeStopTriggered = _measuredState.CapTimeStopTriggered || ( _setState.CapTimeStop <= time); // TODO?: Lazy on lock
                }
                xSemaphoreGive(_measuredStateMutex);
                if (_setState.capacityLimitEnabled && !_setState.capacityLimit && 
                                                (_measuredState.CapVoltStopTriggered  || _measuredState.CapAhStopTriggered || 
                                                 _measuredState.CapTimeStopTriggered  || _measuredState.CapWhStopTriggered)) 
                {
                    state.setCapacityLimit();
                }
                if (_setState.capacityLimit && !_measuredState.CapVoltStopTriggered && !_measuredState.CapAhStopTriggered && 
                    !_measuredState.CapTimeStopTriggered && !_measuredState.CapWhStopTriggered) 
                {
                    state.clearCapacityLimit();
                }
                return true;
            }
        }
        return false;
    }

    // Called from Avg Task if triggered.
    bool stateManager::setCapacityTriggers(bool VoltStop, bool AhStop, bool WhStop, bool TimeStop)
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)200) == pdTRUE)
            {
                _measuredState.CapVoltStopTriggered = VoltStop;
                _measuredState.CapAhStopTriggered = AhStop;
                _measuredState.CapWhStopTriggered = WhStop;
                _measuredState.CapTimeStopTriggered = TimeStop;
                xSemaphoreGive(_measuredStateMutex);
            }
            if (_setState.capacityLimitEnabled && ( VoltStop || AhStop || TimeStop)) {
                state.setCapacityLimit();
            }
            if (!VoltStop && !AhStop && !TimeStop) {
                state.clearCapacityLimit();
            }
        }
        return false;
    }

    // Called from HW Task.
    bool stateManager::setHWstate(bool ocptrig, bool ovptrig, bool von, bool sense_error, bool polarity_error)
    {
    // Protection kicked in.
    if (!_setState.CalibrationMode && (ocptrig || ovptrig || sense_error || polarity_error)) 
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
                _measuredState.OVPstate = _setState.CalibrationOVPset ? ovptrig : _measuredState.OVPstate || ovptrig; 

                _measuredState.VonState = von;

                // Only set and keep if remote sensing is active otherwise clear.
                _measuredState.SenseError = _setState.senseVoltRemote?  sense_error || _measuredState.SenseError : false;
                _measuredState.PolarityError = polarity_error || _measuredState.PolarityError;
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

    bool stateManager::setFanAuto(bool fanauto)
    {
       uint8_t currentPWM = 0;
       if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.FanAuto = fanauto;
                currentPWM = _setState.FanManualSpeed; 
                xSemaphoreGive(_setStateMutex);
            }
        }
        if (fanauto) {
            // Auto
            fancontrol.setPWMDCRamp(fan_max31760::PWM_DC_RAMP_SLOW);
        } else {
            // Manual
            fancontrol.setPWMDCRamp(fan_max31760::PWM_DC_RAMP_FAST);    
        }
        fancontrol.setDirectFanControl(!fanauto);
        if (!fanauto) {
            fancontrol.setPWM(currentPWM);
        }
        return true;
    };

    bool stateManager::setFanPWM(uint8_t rpm)
    {
        bool fanAuto;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.FanManualSpeed = rpm;
                fanAuto = _setState.FanAuto;
                xSemaphoreGive(_setStateMutex);
                if (!fanAuto) { 
                    fancontrol.setDirectFanControl(true);
                    fancontrol.setPWM(rpm);
                    return true;
                }
            }
        }
        return false;
    };

    bool stateManager::setVoltSense(bool senseOn)
    {

        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.senseVoltRemote = senseOn;
                xSemaphoreGive(_setStateMutex);
                updateHWIOTask();
                // If remote sensing is turned off the error condition is meaningless and should be cleared.
                // This it not done here but in the processing of the message coming from HW task.
                return true;
            }
        }
        return false;
    };

    bool stateManager::getVoltSense()
    {
        // No locking needed.
        return _setState.senseVoltRemote;
    }

    bool stateManager::setRangeCurrent(bool lowOn)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.rangeCurrentLow = lowOn;
                // Limit current to max if switching to low range.
                if (lowOn && _setState.mode == ELmode::CC && _setState.Iset > ranges[ranges_e_Curr_Low].maxValue) {
                    _setState.Iset = ranges[ranges_e_Curr_Low].maxValue;
                }
                // Limit OCP to max if switching to low range.
                if (lowOn && _setState.OCPset > ranges[ranges_e_OCP_Low].maxValue) {
                    _setState.OCPset = ranges[ranges_e_OCP_Low].maxValue;
                }
                xSemaphoreGive(_setStateMutex);
                updateHWIOTask();
                updateMeasureTask();
                updateAverageTask();
                return true;
            }
        }
        return false;
    };

    bool stateManager::getRangeCurrentLow()
    {
        // No locking needed.
        return _setState.rangeCurrentLow;
    }

    bool stateManager::setRangeVoltage(bool lowOn)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.rangeVoltageLow = lowOn;
                // Limit voltage to max if switching to low range.
                if (lowOn && _setState.mode == ELmode::CV && _setState.Uset > ranges[ranges_e_Volt_Low].maxValue) {
                    _setState.Uset = ranges[ranges_e_Volt_Low].maxValue;
                }
                // Limit OVP voltage to max if switching to low range.
                if (lowOn && _setState.OVPset > ranges[ranges_e_OVP_Low].maxValue) {
                    _setState.OVPset = ranges[ranges_e_OVP_Low].maxValue;
                }
                xSemaphoreGive(_setStateMutex);
                updateHWIOTask();
                updateMeasureTask();
                updateAverageTask();
                return true;
                }
            }
        return false;
    };

    bool stateManager::getRangeVoltageLow()
    {
        // No locking needed.
        return _setState.rangeVoltageLow;
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
        if (!_setState.CalibrationMode && _measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                // Clear HW states
                _measuredState.OCPstate = false; 
                _measuredState.OVPstate = false;
                _measuredState.OTPstate = false;
                _measuredState.OPPstate = false;
                _measuredState.SenseError = false;
                _measuredState.PolarityError = false;
                xSemaphoreGive(_measuredStateMutex);
            }
        }
        updateHWIOTask();
        updateMeasureTask();
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

    bool stateManager::clearCapacityLimit()
    {
       if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.capacityLimit = false;
                xSemaphoreGive(_setStateMutex);
            }
        }
       if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _measuredState.CapVoltStopTriggered = false;
                _measuredState.CapAhStopTriggered = false;
                _measuredState.CapWhStopTriggered = false;
                _measuredState.CapTimeStopTriggered = false;
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return updateAverageTask();
    };

    bool stateManager::setCapacityLimit()
    {
        // Avoid hitting limits during calibration.
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
                _setState.capacityLimit = true;
                xSemaphoreGive(_setStateMutex);
            }
        }
        updateHWIOTask();
        return updateAverageTask();
    };

    bool stateManager::setCapacityLimitEnabled(bool enable)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.capacityLimitEnabled = enable;
                xSemaphoreGive(_setStateMutex);
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
                case mode_e_DVM:
                    _setState.mode = ELmode::DVM;
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
                // Note: setRangeCurrent swith might also change iset.
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
                // Note: setRangeVoltage swith might also change iset.
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
                // Note: setRangeCurrent might also change OCPset.
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
                // Note: setRangeVoltage might also change OVPset.
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

    bool stateManager::setCapVoltStop(float voltStop) {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.CapVoltStop = voltStop;
                xSemaphoreGive(_setStateMutex);
            }
        }
        return updateAverageTask();
    };

    bool stateManager::setCapAhStop(float AhStop) {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.CapAhStop = AhStop;
                xSemaphoreGive(_setStateMutex);
            }
        }
        return updateAverageTask();
    };

    bool stateManager::setCapWhStop(float WhStop) {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.CapWhStop = WhStop;
                xSemaphoreGive(_setStateMutex);
            }
        }
        return updateAverageTask();
    };

    bool stateManager::setCapTimeStop(float TimeStop) {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.CapTimeStop = TimeStop;
                xSemaphoreGive(_setStateMutex);
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

    bool stateManager::setPLFreq(uint32_t freq)
    {
        if (freq != 50 && freq != 60) {
            return false;
        }
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.PLFreq = freq;
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

    uint32_t stateManager::getPLFreq()
    {
        uint16_t freq;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                freq = _setState.PLFreq;
                xSemaphoreGive(_setStateMutex);
                return freq;
            };
        };
        return 1;
    };

    // Send message to averaging task to clear the power measurements.
    // Note: this is asynchronous!
    bool stateManager::record(bool setrecord)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.record = setrecord;
                xSemaphoreGive(_setStateMutex);
                return updateAverageTask(false);
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

    bool stateManager::setSCPIWdog(bool enable) 
    {
        SCPIWdogPet(); // Clear timer
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.scpiWdogEnabled = enable;
                xSemaphoreGive(_setStateMutex);
                return true;
            }
        }
        return false;
    };

    bool stateManager::getSCPIWdog() 
    {
        bool enabled;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)100) == pdTRUE)
            {
                enabled = _setState.scpiWdogEnabled;
                xSemaphoreGive(_setStateMutex);
                return enabled;
            };
        };
        return 0;
    };

    bool stateManager::SCPIWdogClear() 
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                _measuredState.scpiWdogLastPet = millis();
                _measuredState.scpiWdogTriggered = false;
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return false;
    };

    bool stateManager::setSCPIWdogDelay(uint32_t delay)
    {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)100) == pdTRUE)
            {
                _setState.scpiWdogDelay = delay;
                xSemaphoreGive(_setStateMutex);
                return true;
            }
        }
        return false;
    };

    uint32_t stateManager::getSCPIWdogDelay()
    {
        uint32_t delay;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)100) == pdTRUE)
            {
                delay = _setState.scpiWdogDelay;
                xSemaphoreGive(_setStateMutex);
                return delay;
            };
        };
        return 0;
    };

    bool stateManager::setSCPIWdogType(WDogType wdtype)
        {
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)100) == pdTRUE)
            {
                _setState.scpiWdogType = wdtype;
                xSemaphoreGive(_setStateMutex);
                return true;
            };
        };
        return false;
    };

    WDogType stateManager::getSCPIWdogType()
    {
        WDogType type;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                type = _setState.scpiWdogType;
                xSemaphoreGive(_setStateMutex);
                return type;
            };
        };
        return WDogType::ACTIVITY; // TODO: Fix to an error state.
    };

    bool stateManager::SCPIWdogPet()
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                _measuredState.scpiWdogLastPet = millis();
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return false;
    };

    bool stateManager::SCPIWdogCheck()
    {
        uint32_t lastPet = 0;
        bool wdogTriggered = false;
        bool wdogEnabled = false;
        uint32_t wdogDelay;
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                lastPet = _measuredState.scpiWdogLastPet;
                wdogTriggered = _measuredState.scpiWdogTriggered;
                xSemaphoreGive(_measuredStateMutex);
            }
        }
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)100) == pdTRUE)
            {
                wdogEnabled = _setState.scpiWdogEnabled;
                wdogDelay   = _setState.scpiWdogDelay;
                xSemaphoreGive(_setStateMutex);
            };
        };
        if (wdogEnabled && wdogTriggered && (lastPet+ wdogDelay*1000 < millis())) {
            // Trigger watchdog
            setProtection();
            if (_measuredStateMutex != NULL)
            {
                if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
                {
                    _measuredState.scpiWdogTriggered = true;
                    xSemaphoreGive(_measuredStateMutex);
                }
            }
            return false;      
        }
        return true;
    };

    bool stateManager::getSCPIWdogTripped()
    {
        bool tripped = false;
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                tripped = _measuredState.scpiWdogTriggered;
                xSemaphoreGive(_measuredStateMutex);
            }
        }
        return tripped;
    };

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
                msg.rangeCurrentLow = _setState.rangeCurrentLow;
                msg.rangeVoltageLow = _setState.rangeVoltageLow;
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

    bool stateManager::updateKeysTask()
    {
        keys_update();
        return true;
    }

}