// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef STATE_H
#define STATE_H

#include "Arduino.h"
#include "FreeRTOS.h"
#include "ui/vars.h"
#include "cal.h"

#ifdef __cplusplus

using namespace dcl;
using namespace dcl::cal;
namespace dcl
{
#endif

    typedef struct 
    {
        float min;
        float max;
        float avg;
        float M2;  // For variance calculation.
        uint32_t count;
    } measureStat;

    extern void clearMeasureStat(measureStat *s);
   
    // all (calculated) measurements
    typedef struct 
    {
        uint64_t sCount;
        uint64_t sCountFromAverage;
        uint64_t sCountFromHWIO;
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
        bool protection;
        bool Precording;
        bool VonState;
        bool OCPstate;
        bool OVPstate;
        bool SenseError;
        bool PolarityError;
        bool PolarityErrorLast;
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
    } measuredStateStruct;

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

    typedef enum 
    {
        ACTIVITY,
        PET
    } WDogType;

    struct calibrationRawData
    {
        int32_t    avgCurrentRaw; // TODO: 2's complement because of ADS131M02
        int32_t    avgVoltRaw;    // TODO: same here.
    };
    typedef struct 
    {
        uint64_t sCount;
        bool on;
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
        bool capacityLimit;     // TODO: move to measured state, this is a measured value
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
    } setStateStruct;

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

#ifdef __cplusplus
    struct hardwareState
    {
        RP2040::resetReason_t resetReason;
        bool eepromMagicDetected;
        bool calibrationCRCOK;
        bool calibrationValid;
    };
#endif

#ifndef __cplusplus
//    typedef struct stateManager stateManager;
#else
class stateManager
{
public:
    void begin();
    bool readCalibrationData();
    uint64_t setDefaults();
    uint64_t startupDone();

    uint64_t resetAllStates();

    uint64_t CalibrationMode(bool on);
    bool getCalibrationMode();

    uint64_t setOn();
    uint64_t setOff();
    bool getOn();

    bool setMode(ELmode newMode);
    ELmode getMode();

    bool getMeasuredStateCopy(measuredStateStruct *mystate, TickType_t waitTicks);
    bool getSetStateCopy(setStateStruct *mystate, TickType_t waitTicks);
    uint64_t getMeasuredSCount();

    /* Called from HW threads 
       These functions set the measure state
    */
    bool setAvgMeasurements(float imon, float umon, double As,
                            double Ws, double time, uint32_t avgCurrentRaw, uint32_t avgVoltRaw,
                            measureStat ImonStat, measureStat UmonStat, measureStat PmonStat, uint64_t sCount);

    bool setHWstate(bool ocptrig, bool ovptrig, bool von, bool sense_error, bool polarity_error, bool hwprotection, uint64_t sCount);
    bool OTPtriggered();
    bool OPPtriggered();
    bool setTemp1(float temp);
    bool setTemp2(float temp);
    bool setFanRPMread(uint32_t rpm, uint8_t fan = 0);
    bool setProtection();
    /* ***********************/

    uint64_t setFanAuto(bool fanauto);
    uint64_t setFanPWM(uint8_t rpm);
    uint64_t setVoltSense(bool senseOn);
    bool getVoltSense();
    uint64_t setRangeCurrent(bool lowOn);
    bool getRangeCurrentLow();
    uint64_t setRangeVoltage(bool lowOn);
    bool getRangeVoltageLow();
    uint64_t clearPower();
    uint64_t clearProtection();
    bool getProtection();
    bool getReversePolarityNow();
    bool getReversePolarityTriggered();
    uint64_t clearCapacityLimit();
    bool setCapacityLimit();
    uint64_t setCapacityLimitEnabled(bool enable);
    uint64_t setMode(mode_e newMode);
    uint64_t setVonset(float newVonset, bool rawDACvalue = false);
    uint64_t setIset(float newIset, bool rawDACvalue = false);
    uint64_t setUset(float newUset, bool rawDACvalue = false);
    uint64_t setOCP(float newOCP, bool rawDACvalue = false);
    uint64_t setOVP(float newOVP, bool rawDACvalue = false);
    uint64_t setVonLatched(VonType_e value);
    uint64_t setRset(float newRset);
    uint64_t setPset(float newPset);
    uint64_t setOPPset(float OPPset);
    uint64_t setOPPdelay(float OPPdelay);
    uint64_t setOTPset(float OTPset);
    uint64_t setOTPdelay(float OTPdelay);
    uint64_t setCapVoltStop(float voltStop);
    uint64_t setCapAhStop(float AhStop);
    uint64_t setCapWhStop(float WhStop);
    uint64_t setCapTimeStop(float TimeStop);
    uint64_t setNPLC(uint32_t cycles);
    uint32_t getNPLC();
    uint64_t setPLFreq(uint32_t freq);
    uint32_t getPLFreq();
    uint64_t record(bool setrecord);
    bool toggleRecord();

    uint64_t setSCPIWdog(bool enable);
    bool getSCPIWdog();
    bool SCPIWdogClear();
    bool setSCPIWdogDelay(uint32_t delay);
    uint32_t getSCPIWdogDelay();
    uint64_t setSCPIWdogType(WDogType wdtype);
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
    uint64_t setImonStat(bool on);
    uint64_t clearImonStat();
    bool getUmonStat();
    uint64_t setUmonStat(bool on);
    uint64_t clearUmonStat();
    bool getPmonStat();
    uint64_t setPmonStat(bool on);
    uint64_t clearPmonStat();

    uint64_t startMeasurement();

    calibration cal;
    hardwareState hw;

private:
    bool updateLoadTasks();
    bool updateHWIOTask();
    bool updateMeasureTask();
    bool updateAverageTask(bool clearPower = false, bool clearImonStat = false, 
                           bool clearUmonStat = false, bool clearPmonStat = false,
                           bool doMeasurement = false);
    bool updateKeysTask();
    void updateSCountHW(uint64_t sCount);
    bool sendWindowSizes();
    void updateMeasureSCount(); // Only call withing semaphore lock on _measuredState!
    uint64_t sCountIncr();

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

#endif // STATE_H