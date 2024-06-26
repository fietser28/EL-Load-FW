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

// Global Debug settings
//#define FAKE_HARDWARE   1

/// Hardware definition
///////////////////////
#define PIN_UART_TX     0           // GPIO 0 - debug/scpi
#define PIN_UART_RX     1           // GPIO 1 - debug/scpi

#define SPI_ADC_SCK     2           // GPIO 2 - measure task
#define PIN_DAC1_SCK    2           // GPIO 2
#define PIN_DAC2_SCK    2           // GPIO 2

#define SPI_ADC_TX      3           // GPIO 3 - measure task 
#define PIN_DAC1_TX     3           // GPIO 3
#define PIN_DAC2_TX     3           // GPIO 3

#define SPI_ADC_RX      4           // GPIO 4 - measure task
#define PIN_DAC1_RX     4           // GPIO 4 - measure task
#define PIN_DAC2_RX     4           // GPIO 4 - measure task

#define PIN_DAC2_CS     5           // GPIO 5 - measure task
#define PIN_DAC1_CS     6           // GPIO 6 - measure task
#define PIN_ADC_RDY     7           // GPIO 7 - interrupt

#define PIN_LCD_DC      8           // GPIO 8 - display task
#define PIN_LCD_CS      9           // GPIO 9 - display task

#define PIN_LCD_SCK     10          // GPIO 10 - display task
#define PIN_TP_SCK      10          // GPIO 10 - display task
//#define PIN_KEYS_SCK    10          // GPIO 10 - display task

#define PIN_LCD_MOSI    11          // GPIO 11 - display task
#define PIN_TP_MOSI     11          // GPIO 11 - display task
//#define PIN_KEYS_MOSI   11          // GPIO 11 - display task

#define PIN_LCD_MISO    12          // GPIO 12 - display task
#define PIN_TP_MISO     12          // GPIO 12 - display task
//#define PIN_KEYS_MISO   12          // GPIO 12 - display task

#define PIN_LCD_BL      13          // GPIO 13 - display task

// GPIO14 - check if waveshare has no resistor on R11. 
//    => CS pin for MCP23S08 connected to SPI0 = Analog hardware
// => Interrupt pin MCP23008 hardware signals.
#define PIN_HWGPIO_INT    14          // GPIO 14 - interrupt pin for hadware MCP23008

#define PIN_LCD_RESET   15          // GPIO 15 - display task
#define PIN_TP_CS       16          // GPIO 16 - display task
#define PIN_TP_IRQ      17          // GPIO 17 - display task

//18 KEYS_SDA
//19 KeYS_SCL

#define SPI_ADC_CS      20          // GPIO 20 - measure task 

#define PIN_ADC_CLK      21          // GPIO 21 (unconnected SDIO_CLK) - HW clock pin

// GPIO 22 - connected to SD_CD with 47k 3V3 pullup. - TODO:CHECK.
// GPIO 23 = TP4 & controls DC convertor efficiency mode    
// GPIO 25 = LED & TP5 (GPIO 25 -> 470R -> TP5 -> LED -> GND)

//#define PIN_TEMP1_ADC     26         // GPIO 26 - ADC0 => I2C for keys & hw
#define PIN_KEYS_SDA      26
#define PIN_HWGPIO_SDA    26

//#define PIN_TEMP2_ADC     27         // GPIO 27 - ADC1 => I2C for keys & hw
#define PIN_KEYS_SCL      27
#define PIN_HWGPIO_SCL    27

//#define PIN_TEST          28  
#define PIN_KEYS_INT        28        // GPIO 28 - MCP23008 INT signal from keys.    
// GPIO 28 - change to interrupt pin for MCP2308 on I2C = UI hardware keys

#define SPI_ADC        SPI                // Wiring setup by ADC class
#define SPI_DAC1       SPI
#define SPI_DAC2       SPI
#define SPI_LCD        SPI1               // Wiring setup by display task
#define SPI_TP         SPI1
#define SPI_KEYS       SPI1
#define I2C_KEYS       Wire1              // Setup done in main (shared bus)
#define I2C_KEYS_SEM   Wire1Sem
#define I2C_HWGPIO     Wire1
#define I2C_HWGPIO_SEM Wire1Sem
#define I2C_EEPROM     Wire1
#define I2C_EEPROM_SEM Wire1Sem
#define I2C_TEMPADC     Wire1
#define I2C_TEMPADC_SEM Wire1Sem
#define I2C_FANCTRL     Wire1
#define I2C_FANCTRL_SEM Wire1Sem
#define SERIALDEBUG      Serial1

#define EEPROM_ADDR     0x50
#define FANCTRL_ADDRESS 0x51

// GPIO extender (MCP23x08) for keys
#define KEYS_CHIP_ADDRESS   0x20
#define KEYS_PIN_ENC0       4   // GP4
#define KEYS_PIN_ENC1       2   // GP2
#define KEYS_PIN_ENCBUT     3   // GP3
#define KEYS_PIN_BUT0       7   // GP7
#define KEYS_PIN_BUT1       6   // GP6
#define KEYS_PIN_BUT2       1   // GP1
#define KEYS_PIN_BUT3       0   // GP0
#define KEYS_PIN_LED0       5   // GP5 

// GPIO extender (MCP23008) for hardware signals
#define HWIO_CHIP_ADDRES      0x27
#define HWIO_PIN_VONLATCH     0   // GPA0 =output ///TODO: VON and VONLATCH are swapped in MCU PCB v4
#define HWIO_PIN_resetProt    1   // GPA1 =output
#define HWIO_PIN_HWProtEnable 2   // GPA2 =output
#define HWIO_PIN_SENSE_ERROR  3   // GPA3 =input
#define HWIO_CLAMPOFF         4   // GPA4 =input
#define HWIO_PIN_OVPTRIG      5   // GPA5 =input
#define HWIO_PIN_OCPTRIG      6   // GPA6 =input
#define HWIO_PIN_VON          7   // GPA7 =input   ///TODO: VON and VONLATCH are swapped in MCU PCB v4
#define HWIO_PIN_VOLTSENSECLR 12  // GPB4 =output  (12-8=4)
#define HWIO_PIN_CURRRANGELOW 13  // GPB5 =output
#define HWIO_PIN_VOLTRANGELOW 14  // GPB6 =output
#define HWIO_PIN_VOLTSENSESET 15  // GPB7 =output

#define TEMPADC_ADDRESS    0x48
#define NTC_T0              25+273.15
#define NTC_R0              10000
#define NTC_BETA            3435
#define TEMP1_CHANNEL       ADC_ADS1X1X_MUX_0_3
#define TEMP2_CHANNEL       ADC_ADS1X1X_MUX_1_3

#define NTC_R1              3300.0f
#define NTC_R2              6800.0f
#define NTC_VDD             3.3f

// TODO: Find new pins and rewire
#define PIN_OVPTRIGGERED 20         // GPIO 20  - pin 26
#define PIN_OCPTRIGGERED 20         // GPIO 19  - pin 25
#define PIN_VONLATCHSET  0
#define PIN_VON          0
#define PIN_RESETPROT    0
/////////////////////////////


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
#define ADC_OSR           4096
#endif

#ifdef __cplusplus
using namespace dcl;
#endif

// Global state manager

extern dcl::stateManager state;

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
    int32_t ImonRaw; // TODO: hardcoded to 2's complement because of ADS131M02 ADC
    int32_t UmonRaw; // TODO: same.
};

// Message stream from state change to Averaging task. This is to change window size and clear power measurements
struct changeAverageSettingsMsg {
    //uint16_t avgSamples;
    uint32_t avgSamples;
    bool clear;
    bool record;
    bool on;
    bool sendCalData;
    bool rangeCurrentLow;
    bool rangeVoltageLow;
    float OPPset;
    float OPPdelay;
    float CapVoltStop;
    float CapAhStop; //TODO: Remove?
    float CapWhStop; //TODO: Remove?
    float CapTimeStop; // TODO: Remove?
};

// Message from averaging task to state manager
struct newAvgMeasurementMsg
{
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

// Task priorities & affinities (if applicable)
#define TASK_PRIORITY_PROTHW    5
#define TASK_PRIORITY_MEASURE   6
#define TASK_PRIORITY_AVERAGE   5
#define TASK_PRIORITY_UI        3
#define TASK_PRIORITY_KEYS      4 
#define TASK_PRIORITY_WATCHDOG  7


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

//extern void taskMeasureAndOutputFunction();
extern TaskHandle_t taskOutput;            // Prio 4: output set values
extern TaskHandle_t taskProtSW;            // Prio 3: Software based OTP/OPP
extern TaskHandle_t taskUserInput;         // Prio 2@core0: Proces user buttons 
extern TaskHandle_t taskDisplay;           // Prio 1@core0: Update display

/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
// extern SemaphoreHandle_t xGuiSemaphore; // TODO: Unused?
extern QueueHandle_t changeScreen;

// functions in main.cpp
extern uint8_t readInputs();
extern void setOutputs(setStateStruct &newState);
extern void timerFakeADCInterruptFunction(TimerHandle_t taskFakeADCInterrupt);


// TODO: put this in a class somewhere

extern CalibrationValueConfiguration currentCal;
extern float currentMinVal;
extern float currentMaxVal;
extern CalibrationValueConfiguration voltCal;
extern float voltMinVal;
extern float voltMaxVal;
extern CalibrationValueConfiguration iSetCal;
extern float iSetMinVal;
extern float iSetMaxVal;
extern CalibrationValueConfiguration uSetCal;
extern float uSetMinVal;
extern float uSetMaxVal;
extern CalibrationValueConfiguration vonSetCal;
extern float vonSetMinVal;
extern float vonSetMaxVal;
extern CalibrationValueConfiguration OCPSetCal;
extern CalibrationValueConfiguration OVPSetCal;

