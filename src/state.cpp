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
    void clearMeasureStat(measureStat *s)
    {
        s->min = INFINITY;
        s->max = 0.0f;
        s->avg = 0.0f;
        s->count = 0;
    };


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
        _setState.sCount = 0;
        _measuredState.sCount = 0;
        _measuredState.sCountFromAverage = 0;
        _measuredState.sCountFromHWIO = 0;
    };

    bool stateManager::readCalibrationData()
    {
        return calActions.readAllValues();
    }

    uint64_t stateManager::setDefaults() 
    {
        uint64_t r = 0;
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
                _setState.ImonStat = false;
                _setState.UmonStat = false;
                _setState.PmonStat = false;
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
                _setState.CalibrationVonSet = false;
                _setState.OCPset = ranges[ranges_e_OCP_High].defValue;
                _setState.CalibrationOCPset = false;
                _setState.OVPset = ranges[ranges_e_OVP_High].defValue;
                _setState.CalibrationOVPset = false;
                //_setState.protection = false;
                _setState.VonLatched = VonType_e_Unlatched;
                _setState.CapVoltStop = ranges[ranges_e_VoltStop].defValue;
                _setState.CapAhStop = ranges[ranges_e_AHStop].defValue;
                _setState.CapWhStop = ranges[ranges_e_WHStop].defValue;
                _setState.CapTimeStop = ranges[ranges_e_TimeStop].defValue;
                _setState.capacityLimit = false;
                _setState.capacityLimitEnabled = false;
                _setState.FanManualSpeed = ranges[ranges_e_FanSpeed].defValue;
                _setState.FanAuto = true;
                _setState.rangeCurrentLow = false;
                _setState.rangeVoltageLow = false;
                _setState.senseVoltRemote = false;
                _setState.scpiWdogEnabled = false;
                _setState.scpiWdogDelay = 10;
                _setState.scpiWdogType = WDogType::ACTIVITY;
                _setState.beepOnProtect = true;
                _setState.beepOnCapacity = true;
                _setState.beepOnReverse = true;
                _setState.beepOnEncoder = true;
                _setState.beepOnSense   = true;
                _setState.beepDefaultDuration = ranges[ranges_e_beepDuration].defValue;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
                updateAverageTask(true);
                updateKeysTask(); // For led
                // Needed to get relay & sw in defined state.
                state.setVoltSense(true);
                state.setVoltSense(false);
                //state.setRangeCurrent(true);
                state.setRangeCurrent(false);
                //state.setRangeVoltage(true);
                r = state.setRangeVoltage(false);
                state.clearProtection();
                scpi_busy_dec();
                return r;
            }
        }
        scpi_busy_dec();
        return 0;
    }

    uint64_t stateManager::startupDone() 
    {
        uint64_t r = 0;
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
                //_setState.protection = false;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            }
        }
        state.clearProtection();
        updateLoadTasks();
        return r;
    }

    uint64_t stateManager::resetAllStates()
    {
        bool r;
        r = setDefaults();
        r = r && record(true);
        r = r && setOff();
        r = r && clearPower();
        r = r && clearProtection();
        r = r && clearImonStat();
        r = r && clearUmonStat();
        r = r && clearPmonStat();
        return r ? _setState.sCount : 0;
    };

    uint64_t stateManager::CalibrationMode(bool on) 
    {
        changeScreen_s msg;
        uint64_t r = 0;

        if (_setState.CalibrationMode == on) {
            return false; // Already in this mode.
        }

        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.CalibrationMode = on;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                if (on == true) {
                    msg.newScreen = SCREEN_ID_CALIBRATION;
                    msg.pop = false;
                } else {
                    r = resetAllStates();
                    msg.pop = true;
                }
                xQueueSend(changeScreen, &msg, 100); 
                return r;
            }
        }
        return 0;
    }

    bool stateManager::getCalibrationMode()
    {
        return _setState.CalibrationMode; // Atomic, no locking needed.
    }

    uint64_t stateManager::setOn() { 
        uint64_t r = 0;

        // Don't enable if there is a protection
        if (_measuredState.protection == true || ( _setState.capacityLimit == true && _setState.record == true)) {
            return 0;
        }
        // Don't enable in DVM mode.
        if (_setState.mode == ELmode::DVM) {
            return 0;
        }
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.on = true;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
                updateKeysTask();
                return true;
            }
        }
        return 0;
    }

    uint64_t stateManager::setOff() {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.on = false;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
                updateKeysTask();
                return r;
            }
        }
        return 0;
    }

    bool stateManager::getMeasuredStateCopy( measuredStateStruct *mystate, TickType_t waitTicks) {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, waitTicks) == pdTRUE)
            {
                //rp2040.memcpyDMA(mystate, &_measuredState, sizeof(_measuredState));
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
                //rp2040.memcpyDMA(mystate, &_setState, sizeof(_setState));
                memcpy(mystate, &_setState, sizeof(_setState));
                xSemaphoreGive(_setStateMutex);
                return true;
            }
        }
        return false;
    }

    uint64_t stateManager::getMeasuredSCount() { return _measuredState.sCount; };


    // Called from Avg Task, keep latency low.
    bool stateManager::setAvgMeasurements(float imon, float umon, double As,
                                          double Ws, double time, uint32_t avgCurrentRaw, uint32_t avgVoltRaw,
                                          measureStat Istat, measureStat Ustat, measureStat Pstat, uint64_t sCount)
    {
        if (_measuredStateMutex != NULL)
        {
            // Don't wait to long, it is nog a problem if this is skipped
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)2) == pdTRUE)
            {
                _measuredState.sCountFromAverage = max(_measuredState.sCountFromAverage,sCount);
                updateMeasureSCount();
                _measuredState.Imon = imon;
                _measuredState.Umon = umon;
                _measuredState.As = As;
                _measuredState.Ws = Ws;
                _measuredState.Ptime = time;
                _measuredState.avgCurrentRaw = avgCurrentRaw;
                _measuredState.avgVoltRaw = avgVoltRaw;
                _measuredState.ImonStats = Istat;
                _measuredState.UmonStats = Ustat;
                _measuredState.PmonStats = Pstat;
                
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

    // Called from HW Task.
    bool stateManager::setHWstate(bool ocptrig, bool ovptrig, bool von, bool sense_error, bool polarity_error, bool hwprotection, uint64_t sCount)
    {
    // Protection kicked in from HW signal
    if (!_setState.CalibrationMode && (ocptrig || ovptrig || sense_error || (polarity_error && _setState.on) || hwprotection)) 
    {
        state.setProtection();
        if (( (ocptrig || ovptrig) && getBeepProt()) ||
              (polarity_error      && getBeepReverse()) ||
              (sense_error         && getBeepSense()) ||
              (polarity_error       && getBeepReverse())
        ) { beep(0); }
    };

    // Polarity error when load is of only beeps, doesn't trigger protection.
    if (polarity_error && !_setState.on && getBeepReverse()) 
    {
        beep(0);
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

                // Only set and keep if load is on, otherwise set last measured value.
                _measuredState.PolarityError = (_setState.on? polarity_error : false) || _measuredState.PolarityError;

                _measuredState.PolarityErrorLast = polarity_error;

                _measuredState.sCountFromHWIO = max(_measuredState.sCountFromHWIO,sCount);
                updateMeasureSCount();
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
                if (getBeepProt() == true) { beep(0); }
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
                if (getBeepProt() == true) { beep(0); }
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

    bool stateManager::setFanRPMread(uint32_t rpm, uint8_t fan)
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                if (fan == 1) {
                    _measuredState.FanRPM2 = rpm;
                } else {
                    _measuredState.FanRPM = rpm;
                }
                xSemaphoreGive(_measuredStateMutex);
                return true;
            }
        }
        return false;
    };

    uint64_t stateManager::setFanAuto(bool fanauto)
    {
        uint64_t r = 0;
        uint8_t currentPWM = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.FanAuto = fanauto;
                currentPWM = _setState.FanManualSpeed; 
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
            }
        }
        if (fanauto) {
            // Auto
            fancontrol.setPWMDCRamp(fan_max31760::PWM_DC_RAMP_SLOW);
        } else {
            // Manual
            fancontrol.setPWMDCRamp(fan_max31760::PWM_DC_RAMP_FAST);    
        }
        fancontrol.clearFanFail();
        fancontrol.setDirectFanControl(!fanauto);
        if (!fanauto) {
            fancontrol.setPWM(currentPWM);
        }
        return r;
    };

    uint64_t stateManager::setFanPWM(uint8_t rpm)
    {
        uint64_t r = 0;
        bool fanAuto;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.FanManualSpeed = rpm;
                fanAuto = _setState.FanAuto;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                if (!fanAuto) { 
                    fancontrol.setDirectFanControl(true);
                    fancontrol.setPWM(rpm);
                    
                }
                updateLoadTasks();
            }
        }
        return r;
    };

    uint64_t stateManager::setVoltSense(bool senseOn)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.senseVoltRemote = senseOn;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
                // If remote sensing is turned off the error condition is meaningless and should be cleared.
                // This it not done here but in the processing of the message coming from HW task.
                return r;
            }
        }
        return r;
    };

    bool stateManager::getVoltSense()
    {
        // No locking needed.
        return _setState.senseVoltRemote;
    }

    uint64_t stateManager::setRangeCurrent(bool lowOn)
    {
        uint64_t r = 0;
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
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
                return r;
            }
        }
        return r;
    };

    bool stateManager::getRangeCurrentLow()
    {
        // No locking needed.
        return _setState.rangeCurrentLow;
    }

    uint64_t stateManager::setRangeVoltage(bool lowOn)
    {
        uint64_t r = 0;
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
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
                return r;
                }
            }
        return r;
    };

    bool stateManager::getRangeVoltageLow()
    {
        // No locking needed.
        return _setState.rangeVoltageLow;
    }

    // Send message to averaging task to clear the power measurements.
    // Note: this is asynchronous!
    uint64_t stateManager::clearPower()
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            }
        }
        updateLoadTasks();
        return updateAverageTask(true) ? r : 0;
    };

    uint64_t stateManager::clearProtection()
    {
        uint64_t r = 0;
       if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _measuredState.protection = false;
                r = ++_setState.sCount; // Keep this increment even if we move .protection to measured state!
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        SCPIWdogPet();
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
                _measuredState.PolarityErrorLast = false;
                _measuredState.scpiWdogTriggered = false;
                xSemaphoreGive(_measuredStateMutex);
            }
        }
        return updateLoadTasks();
    };

    bool stateManager::getProtection() {
        // No need for locking. This function is uses in measurement task, so needs to be fast and without locking.
        return _measuredState.protection;
    }

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
                _measuredState.protection = true;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateLoadTasks();
    };

    uint64_t stateManager::clearCapacityLimit()
    {
        uint64_t r = 0;
       if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.capacityLimit = false;
                r = ++_setState.sCount;
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
        return updateLoadTasks() ? r : 0;
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
        if (getBeepCap()) beep(0);
        return updateLoadTasks();
    };

    uint64_t stateManager::setCapacityLimitEnabled(bool enable)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.capacityLimitEnabled = enable;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            }
        }
        return updateLoadTasks() ? r : 0;
    };

    uint64_t stateManager::setMode(mode_e newMode)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // Don't enable if load is on.
                if (_setState.on == true)
                {
                    xSemaphoreGive(_setStateMutex);
                    return r;
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
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
                return r;
            }
        }
        return r;
    }

    uint64_t stateManager::setVonset(float newVonset, bool rawDACvalue)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                _setState.CalibrationVonSet = rawDACvalue;
                _setState.VonSet = newVonset;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                return updateLoadTasks() ? r : 0;
            }
        }
        return r;
    };

    uint64_t stateManager::setIset(float newIset, bool rawDACvalue)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                // Note: setRangeCurrent swith might also change iset.
                _setState.CalibrationIset = rawDACvalue; 
                _setState.Iset = newIset;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                return updateLoadTasks() ? r : 0;
            }
        }
        return r;
    };

    uint64_t stateManager::setUset(float newUset, bool rawDACvalue)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                // Note: setRangeVoltage swith might also change iset.
                _setState.CalibrationUset = rawDACvalue; 
                _setState.Uset = newUset;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                return updateLoadTasks() ? r : 0;
            }
        }
        return r;
    };

    uint64_t stateManager::setOCP(float newOCP, bool rawDACvalue)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                // Note: setRangeCurrent might also change OCPset.
                _setState.CalibrationOCPset = rawDACvalue; 
                _setState.OCPset = newOCP;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                // TODO: not clean: updateMeasureTask doesn't run when updateHWIOTask fails, a problem?
                return updateLoadTasks() ? r : 0;
            }
        }
        return r;
    };

    uint64_t stateManager::setOVP(float newOVP, bool rawDACvalue)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                // Note: setRangeVoltage might also change OVPset.
                _setState.CalibrationOVPset = rawDACvalue; 
                _setState.OVPset = newOVP;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                // TODO: not clean: updateMeasureTask doesn't run when updateHWIOTask fails, a problem?
                return updateLoadTasks() ? r : 0;
            }
        }
        return r;
    };

    uint64_t stateManager::setVonLatched(VonType_e value)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.VonLatched = value; 
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                // TODO: not clean: updateMeasureTask doesn't run when updateHWIOTask fails, a problem?
                return updateLoadTasks() ? r : 0;
            }
        }
        return 0;
    };

    uint64_t stateManager::setRset(float newRset)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                _setState.Rset = newRset;
                r = _setState.sCount;
                xSemaphoreGive(_setStateMutex);
                return updateLoadTasks() ? r : 0;
            }
        }
        return 0;
    };

    uint64_t stateManager::setPset(float newPset)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                // TODO: Check for limits.
                _setState.Pset = newPset;
                r = _setState.sCount;
                xSemaphoreGive(_setStateMutex);
                return updateLoadTasks() ? r : 0;
            }
        }
        return 0;
    };

   uint64_t stateManager::setOPPset(float OPPset)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.OPPset = OPPset;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateLoadTasks() ? r : 0;
    };

   uint64_t stateManager::setOPPdelay(float OPPdelay)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.OPPdelay = OPPdelay;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateLoadTasks() ? r : 0;
    };

   uint64_t stateManager::setOTPset(float OTPset)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.OTPset = OTPset;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateLoadTasks() ? r : 0;
    };

   uint64_t stateManager::setOTPdelay(float OTPdelay)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.OTPdelay = OTPdelay;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                // TODO: test & update clear hardware;
                //return true;
            }
        }
        return updateLoadTasks() ? r : 0;
    };

    uint64_t  stateManager::setCapVoltStop(float voltStop) 
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.CapVoltStop = voltStop;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            }
        }
        return updateLoadTasks() ? r : 0;
    };

    uint64_t stateManager::setCapAhStop(float AhStop) 
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.CapAhStop = AhStop;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            }
        }
        return updateLoadTasks() ? r : 0;
    };

    uint64_t stateManager::setCapWhStop(float WhStop) 
    {
        uint64_t r = 0;    
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.CapWhStop = WhStop;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            }
        }
        return updateLoadTasks() ? r : 0;
    };

    uint64_t stateManager::setCapTimeStop(float TimeStop) 
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, portMAX_DELAY) == pdTRUE)
            {
                _setState.CapTimeStop = TimeStop;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            }
        }
        return updateLoadTasks() ? r : 0;
    };

    uint64_t stateManager::setNPLC(uint32_t cycles)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.NLPC = cycles;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            };
        };
        return updateLoadTasks() ? r : 0;
    };

    uint64_t stateManager::setPLFreq(uint32_t freq)
    {
        uint64_t r = 0;
        if (freq != 50 && freq != 60) {
            return false;
        }
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.PLFreq = freq;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            };
        };
        return updateLoadTasks() ? r : 0;
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
    uint64_t stateManager::record(bool setrecord)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.record = setrecord;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
                return updateAverageTask(false) ? r : 0;
            }
        }
        return r;
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
/* Instantaniously enables SCPI watchdog, sCount increase not really needed?*/
    uint64_t stateManager::setSCPIWdog(bool enable) 
    {
        uint64_t r = 0;
        SCPIWdogPet(); // Clear timer
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.scpiWdogEnabled = enable;
                r = ++_setState.sCount; 
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
            }
        }
        return r;
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

/* Immediately clears the SCPIWdog state, instant command doesn't increase sCount. */
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
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)100) == pdTRUE)
            {
                _setState.scpiWdogDelay = delay;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
            }
        }
        return r;
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

    uint64_t stateManager::setSCPIWdogType(WDogType wdtype)
        {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)100) == pdTRUE)
            {
                _setState.scpiWdogType = wdtype;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
                updateLoadTasks();
            };
        };
        return r;
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
        if (wdogEnabled && !wdogTriggered && (lastPet+ wdogDelay*1000 < millis())) {
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

    // Beep states are not protected by semaphores, all are atomic read/writes and is not order critical.
    void stateManager::setBeepProt(bool on)      { _setState.beepOnProtect = on; };
    bool stateManager::getBeepProt()             { return _setState.beepOnProtect; };
    void stateManager::setBeepCap(bool on)       { _setState.beepOnCapacity = on; };
    bool stateManager::getBeepCap()              { return _setState.beepOnCapacity; };
    void stateManager::setBeepReverse(bool on)   { _setState.beepOnReverse = on; }
    bool stateManager::getBeepReverse()          { return _setState.beepOnReverse; };
    void stateManager::setBeepEncoder(bool on)   { _setState.beepOnEncoder = on; }
    bool stateManager::getBeepEncoder()          { return _setState.beepOnEncoder; };
    void stateManager::setBeepSense(bool on)     { _setState.beepOnSense = on; }
    bool stateManager::getBeepSense()            { return _setState.beepOnSense; };
    void stateManager::setBeepDefaultDuration(float duration) 
    {
        if ( duration > ranges[ranges_e_beepDuration].minValue && duration < ranges[ranges_e_beepDuration].maxValue)
        {
            _setState.beepDefaultDuration = duration;
        }
    };
    float stateManager::getBeepDefaultDuration() { return _setState.beepDefaultDuration; };

    bool stateManager::getImonStat()
    {
        bool on;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                on = _setState.ImonStat;
                xSemaphoreGive(_setStateMutex);
                return on;
            };
        };
        return 1;
    };

    uint64_t stateManager::setImonStat(bool on)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.ImonStat = on;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            };
        };
        return updateLoadTasks() ? r : 0;
    };

    uint64_t stateManager::clearImonStat()
    {
        uint64_t r = sCountIncr();
        updateLoadTasks();
        return updateAverageTask(false,true,false,false,false) ? r : 0;
    }

    bool stateManager::getUmonStat()
    {
        bool on;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                on = _setState.UmonStat;
                xSemaphoreGive(_setStateMutex);
                return on;
            };
        };
        return 1;
    };

    uint64_t stateManager::setUmonStat(bool on)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.UmonStat = on;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            };
        };
        return updateLoadTasks() ? r : 0;
    };

    uint64_t stateManager::clearUmonStat()
    {
        uint64_t r = sCountIncr();
        updateLoadTasks();
        return updateAverageTask(false,false,true,false,false) ? r : 0;
    }

    bool stateManager::getPmonStat()
    {
        bool on;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                on = _setState.ImonStat;
                xSemaphoreGive(_setStateMutex);
                return on;
            };
        };
        return 1;
    };

    uint64_t stateManager::setPmonStat(bool on)
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {
                _setState.PmonStat = on;
                r = ++_setState.sCount;
                xSemaphoreGive(_setStateMutex);
            };
        };
        updateLoadTasks();
        return updateAverageTask() ? r : 0;
    };

    uint64_t stateManager::clearPmonStat()
    {
        uint64_t r = sCountIncr();
        updateLoadTasks();
        return updateAverageTask(false,false,false,true, false) ? r : 0; 
    };

    uint64_t stateManager::startMeasurement()
    {
        uint64_t r = sCountIncr();
        updateHWIOTask();
        updateMeasureTask();
        return updateAverageTask(false,false,false,false, true) ? r : 0; 
    };

    void stateManager::updateMeasureSCount() {
        _measuredState.sCount = max(_measuredState.sCount, 
                                    min(_measuredState.sCountFromAverage,
                                        _measuredState.sCountFromHWIO)
                                );
    };

    bool stateManager::updateLoadTasks() {
        bool r = updateAverageTask();
        r = updateHWIOTask() && r;
        r = updateMeasureTask() && r;
        return r;
    }

    bool stateManager::updateAverageTask(bool clearPower, bool clearImonStat, bool clearUmonStat, bool clearPmonStat, bool doMeasurement)
    {
        changeAverageSettingsMsg msg;
        msg.clear = clearPower;  // Don't clear (default if parameter is not given)
        msg.ImonStatClear = clearImonStat;
        msg.UmonStatClear = clearUmonStat;
        msg.PmonStatClear = clearPmonStat;
        msg.doMeasurement = doMeasurement;
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
                msg.ImonStatRun = _setState.ImonStat;
                msg.UmonStatRun = _setState.UmonStat;
                msg.PmonStatRun = _setState.PmonStat;
                msg.sCount = _setState.sCount;    
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

    uint64_t stateManager::sCountIncr() 
    {
        uint64_t r = 0;
        if (_setStateMutex != NULL)
        {
            if (xSemaphoreTake(_setStateMutex, (TickType_t)10) == pdTRUE)
            {            
                 r= ++_setState.sCount;    
                xSemaphoreGive(_setStateMutex);
                return r;
            }
        }
        return 0;
    };

    void stateManager::updateSCountHW(uint64_t sCount)
    {
        if (_measuredStateMutex != NULL)
        {
            if (xSemaphoreTake(_measuredStateMutex, (TickType_t)100) == pdTRUE)
            {
                _measuredState.sCountFromHWIO = max(_measuredState.sCountFromHWIO, sCount);
                updateMeasureSCount();
                xSemaphoreGive(_measuredStateMutex);
            }
        }

    }

}