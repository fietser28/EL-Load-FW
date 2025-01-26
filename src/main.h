// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "FreeRTOS.h"
#include "message_buffer.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"

#include "state.h"
#include "cal.h"
#include "ranges.h"
#include "ui/screens.h"

#include "dac.h"
#include "adc.h"
#include "eeprom.h"
#include "adc_ads1x1x.h"
#include "fan_max31760.h"

#include "hardware.h"

#define UNKOWN_ERROR_TASK_TIMEOUT   100  // = 100ms. Ususally we reset in this case to force a save mode.
//#define AVG_SAMPLES_MAX     1000    // Eq. 1 sec at 1kHz sample rate
//#define AVG_SAMPLES_MIN     1   
//#define AVG_SAMPLES_DEFAULT 50       // 100 = 2 cycles in 50Hz
#define DEFAULT_AVG_SAMPLES_NPLC      25
#define DEFAULT_PL_FREQ               50

#define FAKE_HARDWARE_TIMER_TICKS 1   // Real = 1 = 1kHz
#ifdef FAKE_HARDWARE
#define CLOCK_DIVIDER_ADC 30
#define ADC_OSR           2050
#else
#define CLOCK_DIVIDER_ADC 15         // ~1kHz = 15
#define ADC_OSR           2048
#endif

#ifdef __cplusplus
using namespace dcl;
#endif

// Global state manager
extern dcl::stateManager state;

// Global calibration actions
extern dcl::cal::calAction calActions;

extern adc_ADS131M02 currentADC;
extern adc_ADS131M02 voltADC; // volt = secondary channel

extern dac_dac8555 iSetDAC;
extern dac_dac8555 vonSetDAC;
extern dac_dac8555 OCPSetDAC;
extern dac_dac8555 OVPSetDAC;
extern dac_dac8555 uSetDAC;

extern dcl::eeprom::eeprom myeeprom;
extern fan_max31760 fancontrol;

extern SemaphoreHandle_t WireSem;       // Manage sharing between tasks 
extern SemaphoreHandle_t Wire1Sem;      // Manage sharing between tasks

extern SemaphoreHandle_t setStateMutex;
extern setStateStruct setState;

// Message stream from Measure to Averaging task.
struct newMeasurementMsg {
    int64_t sCount;
    int32_t ImonRaw; // TODO: hardcoded to 2's complement because of ADS131M02 ADC
    int32_t UmonRaw; // TODO: same.
};

// Message stream from state change to Averaging task. This is to change window size and clear power measurements
struct changeAverageSettingsMsg {
    uint64_t sCount;
    //uint16_t avgSamples;
    uint32_t avgSamples;
    bool clear;
    bool doMeasurement;
    bool record;
    bool on;
    bool sendCalData;
    bool rangeCurrentLow;
    bool rangeVoltageLow;
    float OPPset;
    float OPPdelay;
    float CapVoltStop;
    bool ImonStatRun;
    bool ImonStatClear;
    bool UmonStatRun;
    bool UmonStatClear;
    bool PmonStatRun;
    bool PmonStatClear;
    //float CapAhStop; //TODO: Remove?
    //float CapWhStop; //TODO: Remove?
    //float CapTimeStop; // TODO: Remove?
};

// Message from averaging task to state manager
struct newAvgMeasurementMsg
{
    uint64_t sCount;
    float Imon;
    float Umon;
    double Ah;
    double Wh;
    double Ptime;
};

struct changeScreen_s 
{
    ScreensEnum newScreen;
    bool    pop;
};

/// Task setup
//////////////

// Queue & Buffer sizes
#define QUEUE_SIZE_NEWMEASURE    10
#define QUEUE_SIZE_CHANGEMEASURE 10
#define QUEUE_SIZE_CHANGEAVG     10
#define QUEUE_SIZE_CHANGEHWIO    20
#define QUEUE_SIZE_CHANGESCREEN  10
#define QUEUE_SIZE_BEEP          10


// Task priorities & affinities (if applicable)
#define TASK_PRIORITY_PROTHW    5
#define TASK_PRIORITY_MEASURE   6
#define TASK_PRIORITY_AVERAGE   5
#define TASK_PRIORITY_UI        3
#define TASK_PRIORITY_UI_TIMER  4
#define TASK_PRIORITY_KEYS      5 
#define TASK_PRIORITY_WATCHDOG  7
#define TASK_PRIORITY_BEEP      4
#define TASK_PRIORITY_EEPROM    4
#define TASK_PRIORITY_UART      4

#define TASK_AFFINITY_MEASURE   1 << 1    // Core1
#define TASK_AFFINITY_AVERAGE   1 << 1    // Core1
#define TASK_AFFINITY_UI        1 << 0    // Core0
//#define TASK_AFFINITY_UI_TICK   1 << 0    // Core0

// Highest prio HW IO task, triggered by intererupt and runs frequently (every 0.1s)
extern TaskHandle_t taskProtHW; // Prio 6: Hardware triggered OCP/OVP
extern void taskProtHWFunction(void * pvParameters);
extern QueueHandle_t changeHWIOSettings;      // Queue/stream from state class to HWIO task.
extern volatile uint8_t watchdogProtHW;

// Main ADC read and CP/CR calculation and DAC writing, fast and high priority. TODO: pin to RAM.
// Gets triggered by ADC interrupt@ 1kHz
extern TaskHandle_t taskMeasureAndOutput;  // Prio 5@core1: Fast ADC measure, calc and output set values
extern SemaphoreHandle_t adcReady;       // Task notification via ISR didn't work. TODO: Why? 
extern QueueHandle_t changeMeasureTaskSettings;      // Queue/stream from state class to measure task.
extern void taskMeasureAndOutputFunction(void * pvParameters);
extern volatile uint8_t watchdogMeasureAndOutput;

// Task receiving ADC readouts and putting it into moving averaging values for other outputs. This task writes to measuredStateStruct
extern QueueHandle_t changeAverageSettings; // Queue/stream from functions to change/clear the averaging settings (many-to-1)
extern MessageBufferHandle_t newMeasurements;      // Queue/stream from measurementandoutput to Averaging task (1-on-1)
extern TaskHandle_t taskAveraging;         // Prio 4: moving average of raw measurement values in NPLC cycles AND Wh/Ah keeping.
extern void taskAveragingFunction(void * pvParameters);
extern volatile uint8_t watchdogAveraging;

// Task sending/receiving UART messages (mainly SCPI)
extern TaskHandle_t taskUART;
extern MessageBufferHandle_t SCPImessages;
extern MessageBufferHandle_t SCPIreturns;
extern volatile uint8_t watchdogUART;

//extern void taskMeasureAndOutputFunction();
//extern TaskHandle_t taskOutput;            // Prio 4: output set values
extern TaskHandle_t taskProtSW;            // Prio 3: Software based OTP/OPP
extern TaskHandle_t taskUserInput;         // Prio 2@core0: Proces user buttons 
extern TaskHandle_t taskDisplay;           // Prio 1@core0: Update display
extern TaskHandle_t taskWatchdog;

extern TaskHandle_t taskBeep;
extern TaskHandle_t taskLoop;              // Default setup/loop handle.

/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
// extern SemaphoreHandle_t xGuiSemaphore; // TODO: Unused?
extern QueueHandle_t changeScreen;

// functions in main.cpp
extern uint8_t readInputs();
extern void setOutputs(setStateStruct &newState);
extern void timerFakeADCInterruptFunction(TimerHandle_t taskFakeADCInterrupt);
extern bool beep(float length);

// Debug information
extern volatile uint32_t watchdogAveragingMax;
extern volatile uint32_t watchdogEncTaskMax;
extern volatile uint32_t watchdogGuiTaskMax;
extern volatile uint32_t watchdogGuiTimerFunctionMax;
extern volatile uint32_t watchdogLoopMax;
extern volatile uint32_t watchdogProtHWMax;
extern volatile uint32_t watchdogMeasureAndOutputMax;
extern volatile uint32_t watchdogUARTMax;

// Min free space in queues and buffers.
extern volatile uint32_t debugMemoryNewMeasurementsBuffMinSpace;
extern volatile uint32_t debugMemoryChangeHWIOSettingsQMinSpace;
extern volatile uint32_t debugMemoryChangeMeasureTaskSettingsQMinSpace;
extern volatile uint32_t debugMemoryChangeAverageSettingsQMinSpace;
extern volatile uint32_t debugMemoryChangeScreenQMinSpace;
extern volatile uint32_t debugMemoryBeeperQMinSpace;
extern volatile uint32_t debugMemorySCPIMessagesMinSpace;
extern volatile uint32_t debugMemorySCPIReturnsMinSpace;

// Overflows in queues and buffers.
extern volatile uint32_t debugMemoryNewMeasurementsBuffOverflows;
extern volatile uint32_t debugMemoryChangeHWIOSettingsQOverflows;
extern volatile uint32_t debugMemoryChangeMeasureTaskSettingsQOverflows;
extern volatile uint32_t debugMemoryChangeAverageSettingsQOverflows;
extern volatile uint32_t debugMemoryChangeScreenQOverflows;
extern volatile uint32_t debugMemoryBeeperQOverflows;
extern volatile uint32_t debugMemorySCPIMessagesOverflows;
extern volatile uint32_t debugMemorySCPIReturnsOverflows;

// Debugging incomming IO from hardware board
extern uint16_t gpiopinstate;
