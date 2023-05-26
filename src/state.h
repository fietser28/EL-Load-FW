#ifndef STATE_H
#define STATE_H

#include "Arduino.h"
#include "FreeRTOS.h"
#include "cal.h"

#ifdef __cplusplus
namespace dcl
{
#endif

    // all (calculated) measurements
    struct measuredStateStruct
    {
        float Imon;
        float Umon;
        double Ws;
        double As;
        double Ptime;
        int32_t avgCurrentRaw; // TODO: 2's complement because of ADS131M02
        int32_t avgVoltRaw;    // TODO: 2's complement because of ADS131M02
        bool Precording;
        bool VonState;
        bool OCPstate;
        bool OVPstate;
        uint16_t Temp1;
        uint16_t Temp2;
    };

    enum ELmode
    {
        START,
        SHORT,
        CC,
        CV,
        CR,
        CP
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
        bool startupDone;
        uint32_t PLFreq;
        float sampleRate;
        uint32_t NLPC;
//        uint16_t windowSize; // Sampling window size in SW (HW ADC also has OSR!)
        enum ELmode mode;
        float Iset; // float = 32 bits
        float Uset;
        float Rset;
        float Pset;
        float VonSet;
        bool VonLatched;
        float OCPset;
        float OVPset;
        float OTPset;
        float OTPdelay;
        float OPPset;
        float OPPdelay;
    };

#ifdef __cplusplus
    struct calibration
    {
        cal *Imon;
        cal *Umon;
        cal *Iset;
        cal *Uset;
        cal *Von;
        cal *OCPset;
        cal *OVPset;
//        cal *OTPset;
//        cal *Temp1;
//        cal *Temp2;
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

    bool setOn();
    bool setOff();
    bool getOn();

    bool setMode(ELmode newMode);
    ELmode getMode();

    bool getMeasuredStateCopy(measuredStateStruct *mystate, TickType_t waitTicks);
    bool getSetStateCopy(setStateStruct *mystate, TickType_t waitTicks);

    bool setAvgMeasurements(float imon, float umon, double As,
                            double Ws, double time, uint32_t avgCurrentRaw, uint32_t avgVoltRaw);

    bool clearPower();
    bool clearProtection();
    bool setProtection();
    bool setOPPset(float OPPset);
    bool setOPPdelay(float OPPdelay);
    bool setNPLC(uint32_t cycles);
    uint32_t getNPLC();
    bool record(bool setrecord);
    bool toggleRecord();
    bool updateAverageTask();
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