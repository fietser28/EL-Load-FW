// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STATE_H
#define STATE_H

#include "Arduino.h"
#include "FreeRTOS.h"
#include "cal.h"
#include "ui/vars.h"

#ifdef __cplusplus

using namespace dcl::cal;
namespace dcl
{
#endif

    struct measureStat
    {
        float min;
        float max;
        float avg;
        uint32_t count;
    };

    extern void clearMeasureStat(measureStat *s);
   
    // all (calculated) measurements
    struct measuredStateStruct
    {
        float Imon;
        measureStat ImonStats;
        float Umon;
        measureStat UmonStats;
        measureStat PmonStats;
        double Ws;
        double As;
        double Ptime;
        int32_t avgCurrentRaw; // TODO: 2's complement because of ADS131M02
        int32_t avgVoltRaw;    // TODO: 2's complement because of ADS131M02
        bool Precording;
        bool VonState;
        bool OCPstate;
        bool OVPstate;
        bool SenseError;
        bool PolarityError;
        bool OPPstate;
        bool OTPstate;
        bool CapVoltStopTriggered;
        bool CapAhStopTriggered;
        bool CapWhStopTriggered;
        bool CapTimeStopTriggered;
        bool scpiWdogTriggered;
        uint32_t scpiWdogLastPet;
        float Temp1;
        float Temp2;
        uint32_t FanRPM;
        uint32_t FanRPM2;
    };

    enum ELmode
    {
        START,
        SHORT,
        CC,
        CV,
        CR,
        CP,
        DVM
    };

    enum WDogType
    {
        ACTIVITY,
        PET
    };
    struct calibrationRawData
    {
        int32_t    avgCurrentRaw; // TODO: 2's complement because of ADS131M02
        int32_t    avgVoltRaw;    // TODO: same here.
    };
    struct setStateStruct
    {
        bool on;
        bool protection;
        bool record;
        bool ImonStat;
        bool UmonStat;
        bool PmonStat;
        bool CalibrationMode;
        bool startupDone;
        uint32_t PLFreq;
        float sampleRate;
        uint32_t NLPC;
//        uint16_t windowSize; // Sampling window size in SW (HW ADC also has OSR!)
        enum ELmode mode;
        bool CalibrationIset; // True means Iset float = DAC value not real value.
        float Iset; // float = 32 bits
        bool CalibrationUset; // True means Iset float = DAC value not real value.
        float Uset;
        float Rset;
        float Pset;
        float VonSet;
        bool CalibrationVonSet; // True means VonSet float = DAC value not real value;
        VonType_e VonLatched;
        bool CalibrationOCPset; // True means OCPset float = DAC value not real value.
        float OCPset;
        bool CalibrationOVPset; // True means OVPset float = DAC value not real value.
        float OVPset;
        float OTPset;
        float OTPdelay;
        float OPPset;
        float OPPdelay;
        float CapVoltStop;
        float CapAhStop;
        float CapWhStop;
        float CapTimeStop;
        bool capacityLimit;
        bool capacityLimitEnabled;
        bool FanAuto;
        uint8_t FanManualSpeed;
        bool rangeCurrentLow;
        bool rangeVoltageLow;
        bool senseVoltRemote;
        bool scpiWdogEnabled;
        uint32_t scpiWdogDelay;
        WDogType scpiWdogType;
        bool beepOnProtect;
        bool beepOnCapacity;
        bool beepOnReverse;
        bool beepOnEncoder;
        bool beepOnSense;
        float beepDefaultDuration;
    };

#ifdef __cplusplus
    struct calibration
    {
        calData *Imon;
        calData *ImonLow;
        calData *Umon;
        calData *UmonLow;
        calData *Iset;
        calData *IsetLow;
        calData *Uset;
        calData *UsetLow;
        calData *Von;
        calData *VonLow;
        calData *OCPset;
        calData *OCPsetLow;
        calData *OVPset;
        calData *OVPsetLow;
    };
#endif 

#ifndef __cplusplus
//    typedef struct stateManager stateManager;
#else
class stateManager
{
public:
    void begin();
    bool setDefaults();
    void startupDone();
    bool CalibrationMode(bool on);
    bool getCalibrationMode();

    bool setOn();
    bool setOff();
    bool getOn();

    bool setMode(ELmode newMode);
    ELmode getMode();

    bool getMeasuredStateCopy(measuredStateStruct *mystate, TickType_t waitTicks);
    bool getSetStateCopy(setStateStruct *mystate, TickType_t waitTicks);

    bool setAvgMeasurements(float imon, float umon, double As,
                            double Ws, double time, uint32_t avgCurrentRaw, uint32_t avgVoltRaw,
                            measureStat ImonStat, measureStat UmonStat, measureStat PmonStat);

    bool setCapacityTriggers(bool VoltStop, bool AhStop, bool WhStop, bool TimeStop);

    bool setHWstate(bool ocptrig, bool ovptrig, bool von, bool sense_error, bool polarity_error);
    bool OTPtriggered();
    bool OPPtriggered();
    bool setTemp1(float temp);
    bool setTemp2(float temp);
    bool setFanRPMread(uint32_t rpm, uint8_t fan = 0);
    bool setFanAuto(bool fanauto);
    bool setFanPWM(uint8_t rpm);
    bool setVoltSense(bool senseOn);
    bool getVoltSense();
    bool setRangeCurrent(bool lowOn);
    bool getRangeCurrentLow();
    bool setRangeVoltage(bool lowOn);
    bool getRangeVoltageLow();
    bool clearPower();
    bool clearProtection();
    bool setProtection();
    bool clearCapacityLimit();
    bool setCapacityLimit();
    bool setCapacityLimitEnabled(bool enable);
    bool setMode(mode_e newMode);
    bool setVonset(float newVonset, bool rawDACvalue = false);
    bool setIset(float newIset, bool rawDACvalue = false);
    bool setUset(float newUset, bool rawDACvalue = false);
    bool setOCP(float newOCP, bool rawDACvalue = false);
    bool setOVP(float newOVP, bool rawDACvalue = false);
    bool setVonLatched(VonType_e value);
    bool setRset(float newRset);
    bool setPset(float newPset);
    bool setOPPset(float OPPset);
    bool setOPPdelay(float OPPdelay);
    bool setOTPset(float OTPset);
    bool setOTPdelay(float OTPdelay);
    bool setCapVoltStop(float voltStop);
    bool setCapAhStop(float AhStop);
    bool setCapWhStop(float WhStop);
    bool setCapTimeStop(float TimeStop);
    bool setNPLC(uint32_t cycles);
    uint32_t getNPLC();
    bool setPLFreq(uint32_t freq);
    uint32_t getPLFreq();
    bool record(bool setrecord);
    bool toggleRecord();
    bool setSCPIWdog(bool enable);
    bool getSCPIWdog();
    bool SCPIWdogClear();
    bool setSCPIWdogDelay(uint32_t delay);
    uint32_t getSCPIWdogDelay();
    bool setSCPIWdogType(WDogType wdtype);
    WDogType getSCPIWdogType();
    bool SCPIWdogPet();
    bool SCPIWdogCheck();
    bool getSCPIWdogTripped();

    void setBeepProt(bool on);
    bool getBeepProt();
    void setBeepCap(bool on);
    bool getBeepCap();
    void setBeepReverse(bool on);
    bool getBeepReverse();
    void setBeepEncoder(bool on);
    bool getBeepEncoder();
    void setBeepSense(bool on);
    bool getBeepSense();
    void setBeepDefaultDuration(float duration);
    float getBeepDefaultDuration();

    bool getImonStat();
    bool setImonStat(bool on);
    bool clearImonStat();
    bool getUmonStat();
    bool setUmonStat(bool on);
    bool clearUmonStat();
    bool getPmonStat();
    bool setPmonStat(bool on);
    bool clearPmonStat();

// TODO: Move to private?
    bool updateHWIOTask();
    bool updateMeasureTask();
    bool updateAverageTask(bool clearPower = false, bool clearImonStat = false, 
                           bool clearUmonStat = false, bool clearPmonStat = false);
    bool updateKeysTask();
    bool pushState();
    calibration cal;

private:
    bool sendWindowSizes();

    SemaphoreHandle_t _setStateMutex;
    setStateStruct _setState;
    setStateStruct _setStatePush;

    SemaphoreHandle_t _measuredStateMutex;
    measuredStateStruct _measuredState;

};
#endif

#ifdef __cplusplus
} // end of namespace
#endif

#endif