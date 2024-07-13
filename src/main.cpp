// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <limits.h>

#include <Arduino.h>
#include <Wire.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "message_buffer.h"
#include "SPI.h"

#include <eez/flow/queue.h>

#include "main.h"
#include "state.h"
#include "util.h"
#include "ranges.h"
#include "cal.h"
#include "ui/screens.h"
#include "adc.h"
#include "dac.h"
#include "display.h"
#include "keys.h"
#include "ui_glue.h"
#include "eeprom.h"
#include "gpio_mcp23008.h"
#include "gpio_mcp23017.h"
#include "adc_ads1x1x.h"   // For temp sensors
#include "fan_max31760.h"
#include "scpi/scpi-def.h"

// Fixes lvgl include. TODO: remove?
#include "LittleFS.h"

using namespace dcl;
using namespace dcl::eeprom;
using namespace dcl::scpi;

#ifdef FAKE_HARDWARE
TimerHandle_t timerFakeADCInterrupt;
#endif

// I2C bus semaphores
SemaphoreHandle_t WireSem;       // Manage sharing between tasks 
SemaphoreHandle_t Wire1Sem;      // Manage sharing between tasks

// Tasks and buffer allocations
// HW protection task
TaskHandle_t taskProtHW;
QueueHandle_t changeHWIOSettings;
volatile uint8_t watchdogProtHW;
volatile bool taskProtHWReady = false;

// Measurement and Ouput Task
TaskHandle_t taskMeasureAndOutput;
SemaphoreHandle_t adcReady;
QueueHandle_t changeMeasureTaskSettings;
volatile uint8_t watchdogMeasureAndOutput;
volatile bool taskMeasureAndOutputReady = false;

// Averaging and power calculation task 
TaskHandle_t taskAveraging;
MessageBufferHandle_t newMeasurements;
QueueHandle_t changeAverageSettings;
volatile uint8_t watchdogAveraging;
volatile bool taskAveragingReady = false;

// Loop task
volatile uint8_t watchdogLoop;

// Blink task
TaskHandle_t taskWatchdog; 

// UI task
// Task definition is in display.cpp
QueueHandle_t changeScreen;

// adc_MCP3202 currentADC = adc_MCP3202(SPI_ADC, PIN_SPI0_SS, 0);
// adc_MCP3202 voltADC = adc_MCP3202(SPI_ADC, PIN_SPI0_SS, 1);
// adc_MCP3462 currentADC = adc_MCP3462(SPI_ADC, SPI_ADC_CS, 0);
// adc_MCP3462 voltADC = adc_MCP3462(&currentADC, 1);
adc_ADS131M02 currentADC = adc_ADS131M02(SPI_ADC, SPI_ADC_CS, PIN_ADC_CLK, PIN_ADC_RDY);
adc_ADS131M02 voltADC = adc_ADS131M02(&currentADC, 1); // volt = secondary channel

// TODO: Properly define the channels in main.h 
dac_dac8555 iSetDAC = dac_dac8555(SPI_DAC1, PIN_DAC1_CS, 0);
dac_dac8555 vonSetDAC = dac_dac8555(SPI_DAC1, PIN_DAC1_CS, 1);
dac_dac8555 OCPSetDAC = dac_dac8555(SPI_DAC1, PIN_DAC1_CS, 2);
dac_dac8555 OVPSetDAC = dac_dac8555(SPI_DAC1, PIN_DAC1_CS, 3);
dac_dac8555 uSetDAC = dac_dac8555(SPI_DAC2, PIN_DAC2_CS, 0);

dcl::eeprom::eeprom myeeprom = dcl::eeprom::eeprom();

fan_max31760 fancontrol = fan_max31760();

// Global state manager
stateManager state;

// TODO: put this in a class somewhere

CalibrationValueConfiguration currentCal;
CalibrationValueConfiguration currentCalLow;
CalibrationValueConfiguration voltCal;
CalibrationValueConfiguration voltCalLow;
CalibrationValueConfiguration iSetCal;
CalibrationValueConfiguration iSetCalLow;
CalibrationValueConfiguration uSetCal;
CalibrationValueConfiguration uSetCalLow;
CalibrationValueConfiguration vonSetCal;
CalibrationValueConfiguration vonSetCalLow;
CalibrationValueConfiguration OCPSetCal;
CalibrationValueConfiguration OCPSetCalLow;
CalibrationValueConfiguration OVPSetCal;
CalibrationValueConfiguration OVPSetCalLow;

// TODO for debug/test
volatile uint32_t i = -10;

bool ledstate;

void watchdog(void *pvParameters)
{
  // Start watchdog timer
  rp2040.wdt_begin(3000); // ms
  for (;;)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    ledstate = true;
    watchdogAveraging++;
    watchdogEncTask++;
    watchdogGuiTask++;
    watchdogGuiTimerFunction++;
    watchdogLoop++;
    watchdogProtHW++;
    watchdogMeasureAndOutput++;
    vTaskDelay(500);

    digitalWrite(LED_BUILTIN, LOW);
    ledstate = false;
    if (watchdogAveraging < 3 &&        // Normal: 1kHz
        watchdogEncTask < 3 &&          // Normal: 10Hz
        watchdogGuiTask < 3 &&          // Normal: 10Hz
        watchdogGuiTimerFunction < 3 && // Normal: 50Hz
        watchdogLoop < 3 &&             // Normal: busy, SCPI can take long?
        watchdogProtHW < 3  &&          // Normal: 10Hz
        watchdogMeasureAndOutput <3)    // Normal: 1kHz
      {
        // Reset watchdog if all tasks reset there watchdog to zero in last 2 seconds
        rp2040.wdt_reset();
      } 
    vTaskDelay(500);
  }
}

/*
void corerunningtest(void *pvParameters)
{
  for (;;)
  {
    if (get_core_num() == 1)
    {
      xQueueSend(bootbugtestQueue, (uint8_t *)1, 10);
      vTaskSuspend(taskBootBug);
    }
    vTaskDelay(10);
  }
}
*/

int heaptotal, heapused, heapfree; 


void setup()
{
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, LOW);

  pinMode(LED_BUILTIN, OUTPUT);
  SERIALDEBUG.setPollingMode(true);
  SERIALDEBUG.begin(115200);

  sleep_ms(2000); // Wait for serial to connect
  // Flush serial
  while (SERIALDEBUG.available())
  {
    SERIALDEBUG.read();
  }

  I2C_KEYS.setSCL(PIN_KEYS_SCL);
  I2C_KEYS.setSDA(PIN_KEYS_SDA);
  //I2C_KEYS.setClock(400000);
  I2C_KEYS.begin();

  state.begin(); // Setup memory, mutexes and queues.
  printlogstr("INFO: Startup.");

  // TODO: Hardcoded calibration values for now
  currentCal.numPoints = 2;
  currentCal.points[0].value = 0.1; //0.0; // 0.1V  => 1.0A
  currentCal.points[0].adc = 700572; //4575;
  currentCal.points[1].value = 10.0 ; // 1.000V => 10A
  currentCal.points[1].adc = 6963036;

  state.cal.Imon = new calLinear2P();
  state.cal.Imon->setCalConfig(currentCal);
  state.cal.Imon->setADCConfig(currentADC.ADC_MIN, currentADC.ADC_MAX);

  currentCalLow.numPoints = 2;
  currentCalLow.points[0].value = 0.05; //0.0; // 0.1V  => 1.0A
  currentCalLow.points[0].adc = 700000; //4575;
  currentCalLow.points[1].value = 0.95 ; // 1.000V => 10A
  currentCalLow.points[1].adc = 6963036;

  state.cal.ImonLow = new calLinear2P();
  state.cal.ImonLow->setCalConfig(currentCalLow);
  state.cal.ImonLow->setADCConfig(currentADC.ADC_MIN, currentADC.ADC_MAX);

//  CalibrationValueConfiguration voltCal;
  voltCal.numPoints = 2;
  voltCal.points[0].value = 0.0; // 50mV
  voltCal.points[0].adc = 2059;
  voltCal.points[1].value = 100.0; // 1.000V => 100V //1.100 * 34 * 2.1; // 1.100V => >80V
  voltCal.points[1].adc = 6970322;

  state.cal.Umon = new calLinear2P();
  state.cal.Umon->setCalConfig(voltCal);
  state.cal.Umon->setADCConfig(voltADC.ADC_MIN, voltADC.ADC_MAX);

  voltCalLow.numPoints = 2;
  voltCalLow.points[0].value = 0.0; // 50mV
  voltCalLow.points[0].adc = 2059;
  voltCalLow.points[1].value = 100.0; // 1.000V => 100V //1.100 * 34 * 2.1; // 1.100V => >80V
  voltCalLow.points[1].adc = 6970322;

  state.cal.UmonLow = new calLinear2P();
  state.cal.UmonLow->setCalConfig(voltCalLow);
  state.cal.UmonLow->setADCConfig(voltADC.ADC_MIN, voltADC.ADC_MAX);

  iSetCal.numPoints = 2;
  iSetCal.points[0].value = 0.00299; // @3.3Vinput (AMS1117)
  iSetCal.points[0].dac = 100;
  iSetCal.points[1].value = 3.2374; // @3.3Vinput (AMS1117)
  iSetCal.points[1].dac = 64000;

  state.cal.Iset = new calLinear2P();
  state.cal.Iset->setCalConfig(iSetCal);
  state.cal.Iset->setDACConfig(iSetDAC.DAC_MIN, iSetDAC.DAC_MAX);

  iSetCalLow.numPoints = 2;
  iSetCalLow.points[0].value = 0.00299; // @3.3Vinput (AMS1117)
  iSetCalLow.points[0].dac = 100;
  iSetCalLow.points[1].value = 3.2374; // @3.3Vinput (AMS1117)
  iSetCalLow.points[1].dac = 64000;

  state.cal.IsetLow = new calLinear2P();
  state.cal.IsetLow->setCalConfig(iSetCalLow);
  state.cal.IsetLow->setDACConfig(iSetDAC.DAC_MIN, iSetDAC.DAC_MAX);

  uSetCal.numPoints = 2;
  uSetCal.points[0].value = 1.00;
  uSetCal.points[0].dac = 100;
  uSetCal.points[1].value = 3.2; 
  uSetCal.points[1].dac = 64000;

  state.cal.Uset = new calLinear2P();
  state.cal.Uset->setCalConfig(uSetCal);
  state.cal.Uset->setDACConfig(uSetDAC.DAC_MIN, uSetDAC.DAC_MAX);

  uSetCalLow.numPoints = 2;
  uSetCalLow.points[0].value = 1.00;
  uSetCalLow.points[0].dac = 100;
  uSetCalLow.points[1].value = 3.2; 
  uSetCalLow.points[1].dac = 64000;

  state.cal.UsetLow = new calLinear2P();
  state.cal.UsetLow->setCalConfig(uSetCalLow);
  state.cal.UsetLow->setDACConfig(uSetDAC.DAC_MIN, uSetDAC.DAC_MAX);

  vonSetCal.numPoints = 2;
  vonSetCal.points[0].value = 0.50;
  vonSetCal.points[0].dac = 100;
  vonSetCal.points[1].value = 3.2; 
  vonSetCal.points[1].dac = 64000;

  state.cal.Von = new calLinear2P();
  state.cal.Von->setCalConfig(vonSetCal);
  state.cal.Von->setDACConfig(vonSetDAC.DAC_MIN, vonSetDAC.DAC_MAX);

  vonSetCalLow.numPoints = 2;
  vonSetCalLow.points[0].value = 0.50;
  vonSetCalLow.points[0].dac = 100;
  vonSetCalLow.points[1].value = 3.2; 
  vonSetCalLow.points[1].dac = 64000;

  state.cal.VonLow = new calLinear2P();
  state.cal.VonLow->setCalConfig(vonSetCalLow);
  state.cal.VonLow->setDACConfig(vonSetDAC.DAC_MIN, vonSetDAC.DAC_MAX);

  OCPSetCal.numPoints = 2;
  OCPSetCal.points[0].value = 0.50;
  OCPSetCal.points[0].dac = 100;
  OCPSetCal.points[1].value = 3.2; 
  OCPSetCal.points[1].dac = 64000;

  state.cal.OCPset = new calLinear2P();
  state.cal.OCPset->setCalConfig(OCPSetCal);
  state.cal.OCPset->setDACConfig(OCPSetDAC.DAC_MIN, OCPSetDAC.DAC_MAX);

  OCPSetCalLow.numPoints = 2;
  OCPSetCalLow.points[0].value = 0.50;
  OCPSetCalLow.points[0].dac = 100;
  OCPSetCalLow.points[1].value = 3.2; 
  OCPSetCalLow.points[1].dac = 64000;

  state.cal.OCPsetLow = new calLinear2P();
  state.cal.OCPsetLow->setCalConfig(OCPSetCalLow);
  state.cal.OCPsetLow->setDACConfig(OCPSetDAC.DAC_MIN, OCPSetDAC.DAC_MAX);

  OVPSetCal.numPoints = 2;
  OVPSetCal.points[0].value = 0.50;
  OVPSetCal.points[0].dac = 100;
  OVPSetCal.points[1].value = 3.2; 
  OVPSetCal.points[1].dac = 64000;

  state.cal.OVPset = new calLinear2P();
  state.cal.OVPset->setCalConfig(OVPSetCal);
  state.cal.OVPset->setDACConfig(OVPSetDAC.DAC_MIN, OVPSetDAC.DAC_MAX);

  OVPSetCalLow.numPoints = 2;
  OVPSetCalLow.points[0].value = 0.50;
  OVPSetCalLow.points[0].dac = 100;
  OVPSetCalLow.points[1].value = 3.2; 
  OVPSetCalLow.points[1].dac = 64000;

  state.cal.OVPsetLow = new calLinear2P();
  state.cal.OVPsetLow->setCalConfig(OVPSetCalLow);
  state.cal.OVPsetLow->setDACConfig(OVPSetDAC.DAC_MIN, OVPSetDAC.DAC_MAX);

  //// FreeRTOS setup.
  //////////////////////////

  WireSem = xSemaphoreCreateMutex();
  Wire1Sem = xSemaphoreCreateMutex();

  // Message stream from state functions to HWIO task.
  const size_t changeHWIOMsgBuffer = 6 * (4 + sizeof(setStateStruct)); // => Buffer fits 6 messages.
  changeHWIOSettings = xQueueCreate(6, sizeof(setStateStruct));
  if (changeHWIOSettings == NULL)
  { // TODO: reset, something is really wrong....
  }

  // ADC ready semasphore between ISR and measure task
  adcReady = xSemaphoreCreateBinary();

  // Message straam from Measure to Averaging task
  const size_t newMeasurementsMsgBuffer = 60; // 1 msg = 4bytes + 2x4bytes = 12 bytes => 5 messages.
  newMeasurements = xMessageBufferCreate(newMeasurementsMsgBuffer);
  if (newMeasurements == NULL)
  { // TODO: reset, something is really wrong....
  }

  // Message stream from state functions to averaging task.
  const size_t changeAverageSettingsBuffer = 6 * (4 + sizeof(changeAverageSettings)); // => Buffer fits 6 messages.
  changeAverageSettings = xQueueCreate(6, sizeof(changeAverageSettingsMsg));
  if (changeAverageSettings == NULL)
  { // TODO: reset, something is really wrong....
  };

  // Message stream from state functions to measure task.
  const size_t changeMeasureTaskSettingsBuffer = 6 * (4 + sizeof(setStateStruct)); // => Buffer fits 6 messages.
  changeMeasureTaskSettings = xQueueCreate(6, sizeof(setStateStruct));
  if (changeMeasureTaskSettings == NULL)
  { // TODO: reset, something is really wrong....
  }

  // Message stream from state functions to display task.
  const size_t changeScreenBuffer = 6 * ( 4 + sizeof(changeScreen_s));
  changeScreen = xQueueCreate(6, sizeof(changeScreen_s));
  if (changeScreen == NULL) 
  { // TODO: reset, something is really wrong....
  }

  myeeprom.begin(&I2C_EEPROM, I2C_EEPROM_SEM, EEPROM_ADDR, 64, 32);

  // Wait for serial....
  //vTaskDelay(2000);

  // Detect and read/write eeprom config data
  bool eepromMagicFound = myeeprom.magicDetect();

  SERIALDEBUG.printf("EEPROM detect magic: %d\n", eepromMagicFound);
  if (eepromMagicFound) {
    printlogstr("OK: EEPROM magic found.");
  } else {
    printlogstr("ERROR: No EEPROM with magic found.");
  }

/*
  // Write magic if not found. E.g. initialize eeprom and write default values.
  if (!eepromMagicFound) {
    myeeprom.magicWrite();
    printlogstr("INFO: EEPROM magic written?");
    write_cal_to_eeprom(calType_e::calType_e_Imon);
    write_cal_to_eeprom(calType_e::calType_e_Umon);
    write_cal_to_eeprom(calType_e::calType_e_Iset);
    write_cal_to_eeprom(calType_e::calType_e_Uset);
    write_cal_to_eeprom(calType_e::calType_e_Von);
    write_cal_to_eeprom(calType_e::calType_e_OCPset);
    write_cal_to_eeprom(calType_e::calType_e_OVPset);
    printlogstr("INFO: Default cal values stored.");
  }
*/

  if (eepromMagicFound) {
    myeeprom.calibrationValuesRead(state.cal.Imon->getCalConfigRef(), EEPROM_ADDR_CAL_IMON_H);
    myeeprom.calibrationValuesRead(state.cal.ImonLow->getCalConfigRef(), EEPROM_ADDR_CAL_IMON_L);
    myeeprom.calibrationValuesRead(state.cal.Umon->getCalConfigRef(), EEPROM_ADDR_CAL_UMON_H);
    myeeprom.calibrationValuesRead(state.cal.UmonLow->getCalConfigRef(), EEPROM_ADDR_CAL_UMON_L);
    myeeprom.calibrationValuesRead(state.cal.Iset->getCalConfigRef(), EEPROM_ADDR_CAL_ISET_H);
    myeeprom.calibrationValuesRead(state.cal.IsetLow->getCalConfigRef(), EEPROM_ADDR_CAL_ISET_L);
    myeeprom.calibrationValuesRead(state.cal.Von->getCalConfigRef(),  EEPROM_ADDR_CAL_VON_H);
    myeeprom.calibrationValuesRead(state.cal.VonLow->getCalConfigRef(),  EEPROM_ADDR_CAL_VON_L);
    myeeprom.calibrationValuesRead(state.cal.OCPset->getCalConfigRef(), EEPROM_ADDR_CAL_OCP_H);
    myeeprom.calibrationValuesRead(state.cal.OCPsetLow->getCalConfigRef(), EEPROM_ADDR_CAL_OCP_L);
    myeeprom.calibrationValuesRead(state.cal.OVPset->getCalConfigRef(), EEPROM_ADDR_CAL_OVP_H);
    myeeprom.calibrationValuesRead(state.cal.OVPsetLow->getCalConfigRef(), EEPROM_ADDR_CAL_OVP_L);
  }
  
  //vTaskDelay(50);
  //  myeeprom.write(EEPROM_ADDR_VERSION, eeprom_version);  
  //  myeeprom.write(EEPROM_ADDR_VERSION, eeprom_version);  
  //vTaskDelay(50);


  uint8_t eepromVersionRead = myeeprom.read(EEPROM_ADDR_VERSION);

  SERIALDEBUG.printf("EEPROM Version read: %x\n", eepromVersionRead);

  SERIALDEBUG.printf("Single calibration size: %d\n", sizeof(CalibrationValueConfiguration));

  gui_task_init(); // Takes lot of memory?

  //state.setDefaults();
  //state.record(true);
  //state.setOff();
  //state.clearPower();

  //vTaskDelay(400);

  keys_task_init();

  //vTaskDelay(2000);

  //gui_task_init();

  //vTaskDelay(400);

  // Next create the protection tasks.
  BaseType_t xTaskRet;
  xTaskRet = xTaskCreate(taskProtHWFunction, "HWProt", 1024, (void *) 1, TASK_PRIORITY_PROTHW, &taskProtHW);
  if (xTaskRet != pdPASS) { // TODO: reset, something is really wrong;
     SERIALDEBUG.println("ERROR: Error starting ProtHW task.");
  }
  // vTaskCoreAffinitySet(taskProtHW, 0x03); // Can run on both cores.
  //vTaskDelay(3000);

  xTaskRet = xTaskCreate(taskAveragingFunction, "", 1024, (void *)1, TASK_PRIORITY_MEASURE, &taskAveraging);
  if (xTaskRet != pdPASS)
  { // TODO: reset, something is really wrong;
    SERIALDEBUG.println("ERROR: Error starting Averaging task.");
  }
  //vTaskCoreAffinitySet(taskMeasureAndOutput, 1 << 1); // Runs on core1


  xTaskRet = xTaskCreate(taskMeasureAndOutputFunction, "", 1024, (void *)1, TASK_PRIORITY_MEASURE, &taskMeasureAndOutput);
  if (xTaskRet != pdPASS)
  { // TODO: reset, something is really wrong;
    SERIALDEBUG.println("ERROR: Error starting MeasureAndOutput task.");
  }
  //vTaskCoreAffinitySet(taskMeasureAndOutput, TASK_AFFINITY_MEASURE); 

#ifdef FAKE_HARDWARE
  vTaskDelay(500); // Wait for tasks to start 
  SERIALDEBUG.println("INFO: Using FAKE HARDWARE ");
  printlogstr("INFO:  Using FAKE ADC/DAC HARDWARE");
  timerFakeADCInterrupt = xTimerCreate("", FAKE_HARDWARE_TIMER_TICKS, pdTRUE, ( void * ) 0, timerFakeADCInterruptFunction);
  if (timerFakeADCInterrupt == NULL ) {
    SERIALDEBUG.println("ERROR: Unable to create FakeADCTimer.");
  } else {
    xTimerStart(timerFakeADCInterrupt, 0);
  }
#endif

  // Wait for all tasks to have started into their normal run loops.
  while(guiTaskReady == false || taskProtHWReady == false || 
        taskAveragingReady == false || taskMeasureAndOutputReady == false)
  {
    vTaskDelay(5);
  }

  state.setDefaults();
  state.record(true);
  state.setOff();
  state.clearPower();
  state.clearProtection(); // Reset power-on OCP/OVP latches.

  heaptotal = rp2040.getTotalHeap();
  heapused = rp2040.getUsedHeap();
  heapfree = rp2040.getFreeHeap();
  SERIALDEBUG.printf("Heap total beofre SCPI init: %d, used: %d, free:  %d\n", heaptotal, heapused, heapfree);
  
  SCPI_Init(&scpi_context,
            scpi_commands,
            &scpi_interface,
            scpi_units_def,
            SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
            scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
            scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);

  xTaskRet = xTaskCreate(watchdog, "", 200, (void *)1, TASK_PRIORITY_WATCHDOG, &taskWatchdog);
  if (xTaskRet != pdPASS)
  { // TODO: reset, something is really wrong;
    SERIALDEBUG.println("ERROR: Error starting watchdog task.");
  }

  heaptotal = rp2040.getTotalHeap();
  heapused = rp2040.getUsedHeap();
  heapfree = rp2040.getFreeHeap();
  SERIALDEBUG.printf("Heap total: %d, used: %d, free:  %d\n", heaptotal, heapused, heapfree);

    //vTaskDelay(250 / portTICK_PERIOD_MS); // Wait for actual HW to clear.
  state.startupDone();
  //vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait for actual HW to clear.
  //state.clearProtection(); // Reset power-on OCP/OVP latches.
  SERIALDEBUG.println("INFO: Setup done.");  
}

const TickType_t ondelay = 1000;
measuredStateStruct loopmystate;
setStateStruct loopmysetstate;

int cyclecount = 0;

// TODO remove, just for testing.
uint8_t fanstatus = 0;

lv_mem_monitor_t lv_mem_stats;

void loop()
{
  // TODO: Replace with SCPI reading class/task?
  if (SERIALDEBUG.available())
  {
    //SERIALDEBUG.write(SERIALDEBUG.read());
    char ch = SERIALDEBUG.read();
    if (ch == '\n') {
      /*
        heaptotal = rp2040.getTotalHeap();
        heapused = rp2040.getUsedHeap();
        heapfree = rp2040.getFreeHeap();
        SERIALDEBUG.printf("\nHeap total: %d, used: %d, free:  %d\n", heaptotal, heapused, heapfree);
        //SERIALDEBUG.printf("%d, %d, %d, %d, %d, %d, %d\n",watchdogAveraging, watchdogEncTask, watchdogGuiTask, watchdogGuiTimerFunction, watchdogLoop, watchdogProtHW, watchdogMeasureAndOutput);
        lv_mem_monitor(&lv_mem_stats);
        SERIALDEBUG.printf("LV mem: total: %d, used: %d, free:%d, free biggest: %d, used %%: %d%%, max used: %d, count used/free: %d/%d \n", 
                             lv_mem_stats.total_size, lv_mem_stats.total_size-lv_mem_stats.free_size, lv_mem_stats.free_size, lv_mem_stats.free_biggest_size, 
                             lv_mem_stats.used_pct, lv_mem_stats.max_used, lv_mem_stats.used_cnt, lv_mem_stats.free_cnt);
        SERIALDEBUG.printf("Flow Queue: current: %d, max used: %d\n", eez::flow::getQueueSize(), eez::flow::getMaxQueueSize() );
      */
    } else {
    //    SERIALDEBUG.write(ch); // TODO: Keep echo back or make it an option?
    }
    SCPI_Input(&scpi_context, &ch, 1);
  }
  
  //bool getok = state.getMeasuredStateCopy(&loopmystate, 20);
  //getok = getok && state.getSetStateCopy(&loopmysetstate, 20);

  //SERIALDEBUG.printf("%.4f (%.5f/%.5f) %d %d\n", loopmystate.Imon, loopmystate.As/3600.0f, loopmystate.Ptime, getok, loopmysetstate.startupDone);
  //heaptotal = rp2040.getTotalHeap();
  //heapused = rp2040.getUsedHeap();
  //heapfree = rp2040.getFreeHeap();
//  cyclecount = rp2040.getCycleCount64()/rp2040.f_cpu();
  //cyclecount++;
  //SERIALDEBUG.printf("Heap total: %d, used: %d, free:  %d, uptime: %d, ADC0: %i, ADC1: %i, %d\n", heaptotal, heapused, heapfree, cyclecount, loopmystate.avgCurrentRaw, loopmystate.avgVoltRaw, loopmystate.avgCurrentRaw < 0 ? 1 : 0);
  //SERIALDEBUG.printf("Temp1: %f, Temp2: %f, uptime: %d, Mode: %d, VonSet: %f, RPM: %d, status: %d\n", loopmystate.Temp1, loopmystate.Temp2, cyclecount, loopmysetstate.mode, loopmysetstate.VonSet, loopmystate.FanRPM, fanstatus);
  //snprintf(logtxt, 120, "Heap total: %d\nHeap used: %d\nHeap free:  %d\nADC0: %d\n", heaptotal, heapused, heapfree, loopmystate.avgCurrentRaw);
  //printlogstr(logtxt, 120, "Heap total: %d\nHeap used: %d\nHeap free:  %d\nADC0: %d\n", heaptotal, heapused, heapfree, loopmystate.avgCurrentRaw);
  //if (fanstatus == 1) {fancontrol.clearFanFail(); };
  //vTaskDelay(ondelay);
  watchdogLoop = 0;
}

// HW Protection interrupt & task
/////////////////////////////////
static void __not_in_flash_func(ISR_ProtHW())
{
  BaseType_t taskWoken = pdFALSE;
  vTaskNotifyGiveFromISR(taskProtHW, &taskWoken);
  if (taskWoken != pdFALSE) {
    portYIELD_FROM_ISR(taskWoken);
  }
};

enum tempReadState {
  chan1reading = 0,
  chan1ready = 1,
  chan2reading = 2,
  chan2ready = 3
};


void taskProtHWFunction(void *pvParameters)
{
  uint32_t ulNotifiedValue;
  //gpio_mcp23008 gpiokeys = gpio_mcp23008();
  gpio_mcp23017 hwio = gpio_mcp23017(); 
  //adc_ads1x1x  tempadc = adc_ads1x1x();

  uint8_t  gpiopinstate, gpiointerruptflagged;
  bool ocptrig, ocptrig_prev = false;
  bool ovptrig, ovptrig_prev = false;
  bool sense_error, sense_error_prev = false;
  bool polarity_error, polarity_error_prev = false;
  bool protection, protection_prev = false, protection_prev2 = false;
  bool HWprotenable_prev = false;
  bool von, von_prev = false;
  bool senseVoltage = false;
  bool rangeCurrentLow = false;
  bool rangeVoltageLow = false;

  tempReadState tempReadState = tempReadState::chan2ready; 
  int16_t temp1Raw, temp2Raw;
  float Rntc1, Rntc2;
  float temp1, temp2;
  bool OTPStarted = false;
  double OTPTriggerStart;

  bool fanAutoStopped = false;
  bool fanAutoZero = false;

  VonType_e vonLatch;

  setStateStruct changeMsg;
  setStateStruct localSetState;
  size_t msgBytes;
  bool stateReceived = false;

  // Setup Temp ADC
  //tempadc.begin(&I2C_TEMPADC, I2C_TEMPADC_SEM, TEMPADC_ADDRESS);

  // Setup fan controller (and temp measurement)
  fancontrol.begin(&I2C_FANCTRL, I2C_FANCTRL_SEM, FANCTRL_ADDRESS);
  vTaskDelay(3); // Wait for chip reset.??? TODO
  fancontrol.enableTach2(false);
  vTaskDelay(3); // Wait for chip reset.??? TODO
  fancontrol.enableTach1(true); 
  vTaskDelay(3); // Wait for chip reset.??? TODO
  //  fancontrol.setFanSpinUpEnable(false);
  fancontrol.setFanSpinUpEnable(false);
  vTaskDelay(3); // Wait for chip reset.??? TODO
//  fancontrol.setTachFull(true);
  fancontrol.setTachFull(false);
  vTaskDelay(3); // Wait for chip reset.??? TODO
  fancontrol.setPulseStretch(false);
//  fancontrol.setPWMDCRamp(fan_max31760::PWM_DC_RAMP_SLOW_MEDIUM);
  vTaskDelay(3); // Wait for chip reset.??? TODO
  fancontrol.setPWMFreq(fan_max31760::PWM_FREQ_25KHZ);
//  fancontrol.setPWMPolarity(fan_max31760::PWM_POLARITY_NEGATIVE);
  vTaskDelay(3); // Wait for chip reset.??? TODO
  fancontrol.setPWMPolarity(fan_max31760::PWM_POLARITY_POSITIVE);
  vTaskDelay(3); // Wait for chip reset.??? TODO
  fancontrol.setPWMDCRamp(fan_max31760::PWM_DC_RAMP_SLOW_MEDIUM);
  vTaskDelay(3); // Wait for chip reset.??? TODO
  fancontrol.setFFDC(30); // TODO: safe?
  //fancontrol.setTransistorIFR(0x17); // TODO: hardcoded but Depends on transistor (type), something to calibrate?

  for (int i = 0; i<= 47; i++) {
    // LUT0 - LUT10  <= 40C  = off
    if (i <= 10) {
      fancontrol.setLUT(i,0); // Value = 30 for voltage controlled.
      //SERIALDEBUG.printf(" LUT: %2d  = %d\n", i, 0);
    } 
    // LUT11 - LUT26 (42 - )= PWM 10% - 95%  => increment of 5 per LUT.
    if (i > 10 && i <= 26) {
      uint8_t dc = 25 + (i-10)*10;
      fancontrol.setLUT(i,dc);
      //SERIALDEBUG.printf(" LUT: %2d  = %d\n", i, dc);
    } 
    // LUT27 - LUT 47 >= 70C = 100%
    if (i >26) {
      fancontrol.setLUT(i, 255);
      //SERIALDEBUG.printf(" LUT: %2d  = %d\n", i, 255);
    } 
  }
    
//  fancontrol.setFanSpinUpEnable(true);
//  fancontrol.setPWM(64);
//  fancontrol.setDirectFanControl(true);
//  fancontrol.setPWM(64);
  fancontrol.clearFanFail();
  state.setFanPWM(192);
  state.setFanAuto(true);

/* Old MCP23008 
  // Setup HW GPIO extender
  pinMode(PIN_HWGPIO_INT, INPUT);
  gpiokeys.begin(&I2C_KEYS, I2C_KEYS_SEM, HWIO_CHIP_ADDRES);
  vTaskDelay(3); //TODO: remove?
  gpiokeys.pinModes(~(1 << HWIO_PIN_VONLATCH | 1 << HWIO_PIN_resetProt)); // Set output pins.
  vTaskDelay(3); //TODO: remove?
  gpiokeys.pinInterrupts(1 << HWIO_PIN_OCPTRIG | 1 << HWIO_PIN_OVPTRIG | 1 << HWIO_PIN_VON, // Only relevant input pins
                          0x00,  // Compare against 0
                          1 << HWIO_PIN_OCPTRIG | 1 << HWIO_PIN_OVPTRIG); // Only these are compared, other on any change

  ::attachInterrupt(digitalPinToInterrupt(PIN_HWGPIO_INT), ISR_ProtHW, FALLING);
  gpiopinstate = gpiokeys.digitalRead(); //Clear interrupt pin status.
*/
  // Setup HW GPIO extender (MCP23017)
  pinMode(PIN_HWGPIO_INT, INPUT);
  hwio.begin(&I2C_KEYS, I2C_KEYS_SEM, HWIO_CHIP_ADDRES);
  vTaskDelay(100); //TODO: remove?
  hwio.pinModes(0, ~(1 << HWIO_PIN_VONLATCH | 1 << HWIO_PIN_resetProt | 1 << HWIO_PIN_HWProtEnable)); // Set output pins bank0
  vTaskDelay(100); //TODO: remove?
  // TODO: Cleaner implementation, not hardcoded like this.
  hwio.pinModes(0x10, (uint8_t)((~(1 << HWIO_PIN_VOLTSENSECLR | 1 << HWIO_PIN_CURRRANGELOW |1 << HWIO_PIN_VOLTRANGELOW | 1 << HWIO_PIN_VOLTSENSESET)) >> 8)) ; // Set output pins bank1
  vTaskDelay(100); //TODO: remove?
  hwio.pinInterrupts  (0,  // Bank 
                          1 << HWIO_PIN_OCPTRIG | 1 << HWIO_PIN_OVPTRIG | 1 << HWIO_PIN_VON | 1 << HWIO_PIN_SENSE_ERROR, // Only relevant input pins
                          0x00,  // Compare against 0
                          1 << HWIO_PIN_OCPTRIG | 1 << HWIO_PIN_OVPTRIG); // Only these are compared, other on any change
  vTaskDelay(100); //TODO: remove?
  hwio.digitalWrite(HWIO_PIN_HWProtEnable, false); //TODO: Implement functionality, for now keep pin low.

  ::attachInterrupt(digitalPinToInterrupt(PIN_HWGPIO_INT), ISR_ProtHW, FALLING);
  gpiopinstate = hwio.digitalRead(0); //Clear interrupt pin status. Only needed for bank0

  taskProtHWReady = true;
  for (;;)
  {
    // Notified by interrupt or wait 100ms.
    ulTaskNotifyTake(pdTRUE, (TickType_t)100 / portTICK_PERIOD_MS); 

    gpiointerruptflagged = hwio.interruptFlagged(0);
    gpiopinstate = hwio.digitalRead(0); // Inputs are on bank0, therefor we only need to read bank0

    ocptrig = (gpiopinstate & 1 << HWIO_PIN_OCPTRIG) || (gpiointerruptflagged & 1 << HWIO_PIN_OCPTRIG); 
    ovptrig = (gpiopinstate & 1 << HWIO_PIN_OVPTRIG) || (gpiointerruptflagged & 1 << HWIO_PIN_OVPTRIG);
    sense_error =  not ((gpiopinstate & 1 << HWIO_PIN_SENSE_ERROR) || (gpiointerruptflagged & 1 << HWIO_PIN_SENSE_ERROR));
    sense_error = sense_error && localSetState.senseVoltRemote && localSetState.on; // Sense error only matters if we use it and load is on.
    polarity_error = false; // TODO: HW pin not implemented yet. 
    von = gpiopinstate & 1 << HWIO_PIN_VON;

    // Something has changed
    if (ocptrig != ocptrig_prev || ovptrig != ovptrig_prev || von != von_prev || localSetState.protection != protection_prev ||
        sense_error != sense_error_prev) 
    {

      // State has changed, update it.
      // All necessary changed are handled in state functions (protection/off/...)
      state.setHWstate(ocptrig, ovptrig, von, sense_error, polarity_error);

      ocptrig_prev = ocptrig;
      ovptrig_prev = ovptrig;
      von_prev = von;
      sense_error_prev = sense_error;
      protection_prev = localSetState.protection;

    }

    // NTC temperature reading. This ADC is slow and 1 channel at a time.
    // Using a small state machine without busy loops to check where we are.
    /*
    switch (tempReadState)
    {
    case tempReadState::chan2ready:
      tempadc.startConversion(ADC_ADS1X1X_MUX_0_3);
      tempReadState = tempReadState::chan1reading;
      break;
    case tempReadState::chan1reading:
      if (tempadc.isReady()) 
      {
        temp1Raw = tempadc.getValue();
        Rntc1 = 1.0f/(1.0f/(NTC_R1 + NTC_R2) + tempadc.toVoltage(temp1Raw)/(NTC_VDD * NTC_R1)) - NTC_R1;
        temp1 = NTCResistanceToTemp(Rntc1, NTC_BETA, NTC_T0, NTC_R0);
        //state.setTemp1(temp1);
        tempReadState = tempReadState::chan1ready;
      }
      break;
    case tempReadState::chan1ready:
      tempadc.startConversion(ADC_ADS1X1X_MUX_1_3);
      tempReadState = tempReadState::chan2reading;
      break;
    case tempReadState::chan2reading:
      if (tempadc.isReady()) 
      {
        temp2Raw = tempadc.getValue();
        Rntc2 = 1.0f/(1.0f/(NTC_R1 + NTC_R2) + tempadc.toVoltage(temp2Raw)/(NTC_VDD * NTC_R1)) - NTC_R1;
        temp2 = NTCResistanceToTemp(Rntc2, NTC_BETA, NTC_T0, NTC_R0);
        state.setTemp2(temp2);
        tempReadState = tempReadState::chan2ready;
      }
      break;
    default:
      tempReadState = tempReadState::chan2ready;
      break;
    }
    */

    // Fan controll
    fanstatus = fancontrol.getStatus();
    uint32_t rpm = fancontrol.readRPM();
    state.setFanRPMread(rpm);
    temp1 = fancontrol.readTempRemote();
    state.setTemp1(temp1);
    temp2 = fancontrol.readTempLocal();
    state.setTemp2(temp2);

/* DC controlled logic 
    // Manually stop the fan below 40C, doesn't work via LUT it keeps spinning up due to failure dection and 
    // PWM = 0 will disable RPM readout.... TODO: Change Fan voltage in HW for PWM = 0
    if (localSetState.FanAuto == true && fanAutoStopped == false && max(temp1, temp2) < 39 && rpm > 0)
    {
        fanAutoStopped = true;
        fancontrol.setDirectFanControl(true);
        fancontrol.setPWM(15);
    }

    if (localSetState.FanAuto == true && fanAutoStopped == true && max(temp1, temp2) > 41) 
    {
        fanAutoStopped = false;
        fancontrol.setPWM(30);
        fancontrol.setDirectFanControl(false);
        fanAutoZero == false;
    }
    

    // Wait for RPM measure to become 0 before setting PWM to zero
    // 0 PWM also disables fan error detection in MAX31760
    if (fanAutoStopped == true && fanAutoZero == false && rpm == 0)
    {
      fancontrol.setPWM(0);
      fanAutoZero == true;
    }

*/

    // OTP loop
    if (localSetState.on && max(temp1, temp2) > localSetState.OTPset)
    {
      if (!OTPStarted)
      {
        OTPTriggerStart = millis();
        OTPStarted = true;
      }
      else
      {
        if (OTPTriggerStart + localSetState.OTPdelay * 1000 <= millis())
        {
          state.setProtection();
          state.OTPtriggered();
        }
      }
    }
    else
    {
      OTPStarted = false;
    }


    // Receive changed settings.
    // Receive copy of state if send. Using a copy to avoid a mutex lock.
    // TODO: Changes might take the loop delay (nofity wait time) to execute. Fast enough?
    msgBytes = xQueueReceive(changeHWIOSettings, &changeMsg, 0);
    if (msgBytes > 0)
    {
      localSetState = changeMsg;
      stateReceived = true;
     
      vonLatch = localSetState.VonLatched;
      if (vonLatch == VonType_e_Latched) {
        hwio.digitalWrite(HWIO_PIN_VONLATCH, false); // vonLatch pin is active low in hardware!
      } else {
        hwio.digitalWrite(HWIO_PIN_VONLATCH, true); // vonLatch pin is active low in hardware!
      };

      if (localSetState.protection == false && protection_prev2 == true)
      {
        hwio.digitalWrite(HWIO_PIN_resetProt, true);
        //vTaskDelay(1 / portTICK_PERIOD_MS);
        hwio.digitalWrite(HWIO_PIN_resetProt, false);
      }
      protection_prev2 = localSetState.protection;

      if (localSetState.senseVoltRemote != senseVoltage) {
        if (localSetState.senseVoltRemote == true) {
          //Trigger set coil.
          hwio.digitalWrite(HWIO_PIN_VOLTSENSESET, HIGH);
          vTaskDelay(100); // TODO: lazy implementation
          hwio.digitalWrite(HWIO_PIN_VOLTSENSESET, LOW);
        } else {
          //Trigger clear coil.
          hwio.digitalWrite(HWIO_PIN_VOLTSENSECLR, HIGH);
          vTaskDelay(100); // TODO: lazy implementation
          hwio.digitalWrite(HWIO_PIN_VOLTSENSECLR, LOW);
        }
        senseVoltage = localSetState.senseVoltRemote;
      }

      if (localSetState.rangeCurrentLow != rangeCurrentLow) 
      {
          hwio.digitalWrite(HWIO_PIN_CURRRANGELOW, localSetState.rangeCurrentLow);
          rangeCurrentLow = localSetState.rangeCurrentLow;
      };

      if (localSetState.rangeVoltageLow != rangeVoltageLow) 
      {
          hwio.digitalWrite(HWIO_PIN_VOLTRANGELOW, localSetState.rangeVoltageLow);
          rangeVoltageLow = localSetState.rangeVoltageLow;
      };

      
    }
  watchdogProtHW = 0;
  }
};

// This task exclusivlly handles ADC and DAC SPI channels.
void __not_in_flash_func(taskMeasureAndOutputFunction(void *pvParameters))
{
  uint32_t ulNotifiedValue;

  newMeasurementMsg measured;
  setStateStruct changeMsg;
  setStateStruct localSetState;
  size_t msgBytes;
  bool stateReceived = false;

  float imon;
  float umon;
  float iset = 0.0f, isetPrev = -0.1f; // DACs init at 0.
  float uset, usetPrev = -0.1f;
  float vonset = 1.1f, vonsetPrev = -0.1f;
  float ocpset = 10.1f, ocpsetPrev = -0.1f;
  float ovpset = 80.1f, ovpsetPrev = -0.1f;
  bool  rangeCurrentLowPrev = false;
  bool  rangeVoltLowPrev = false;
  uint32_t isetRaw, isetRawPrev = 0;
  uint32_t usetRaw, usetRawPrev = 0;
  uint32_t vonsetRaw, vonsetRawPrev = 0;
  uint32_t ocpsetRaw, ocpsetRawPrev = 0;
  uint32_t ovpsetRaw, ovpsetRawPrev = 0;

  //vTaskDelay(200); // Wait for affinity.

#ifndef FAKE_HARDWARE
  // Setup all hardware. First set SPI CS correct before starting interrupt 
  //SERIALDEBUG.println("INFO: Initializing ADC & DAC.");
  currentADC.begin(true); // Also start ADC clock abd interrupt... (ads131m02)
  voltADC.begin(false);
  //SERIALDEBUG.println("INFO: ADC done.");
  iSetDAC.begin(false);
  uSetDAC.begin(false);
  vonSetDAC.begin(false);
#endif

  //SERIALDEBUG.println("INFO: Going into measure loop.");

#ifndef FAKE_HARDWARE
  currentADC.attachInterrupt();
#endif

  taskMeasureAndOutputReady = true;
  for (;;)
  {
    // Notify is set by interrupt to trigger this task (takes around 20-30us)
    ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(2)); // Last argument was portMAX_DELAY

#ifdef FAKE_HARDWARE
    measured.ImonRaw = 700000;
    measured.UmonRaw = 700000;
#else
    measured.ImonRaw = currentADC.readRaw();
    measured.UmonRaw = voltADC.readRaw(); // TODO: ADS131: always call secondary after primary.....
#endif

    // No mutexes around calibration data! (it doesn't change while running)
    //imon = state.cal.Imon->remapADC(measured.ImonRaw);
    //imon = remap((float)measured.ImonRaw, (float)currentADC.ADC_MIN, currentMinVal, (float)currentADC.ADC_MAX, currentMaxVal);
    //umon = remap((float)measured.UmonRaw, (float)voltADC.ADC_MIN, voltMinVal, (float)voltADC.ADC_MAX, voltMaxVal);

    if (stateReceived) {
        vonset = localSetState.VonSet;
        ocpset = localSetState.OCPset;
        ovpset = localSetState.OVPset;
    }

    if (stateReceived && localSetState.on == true && localSetState.protection == false)
    {

      switch (localSetState.mode)
      {
      case ELmode::START:
        iset = 0.0f;
        uset = localSetState.Uset; // Max
        break;

      case ELmode::CP:
        umon = localSetState.rangeVoltageLow ? state.cal.UmonLow->remapADC(measured.UmonRaw) : state.cal.Umon->remapADC(measured.UmonRaw);
        iset = localSetState.Pset / umon; // TODO: Set to 0 if Von is active. This avoids inrush current.
        uset = 0.0f; // Do not clamp to max to avoid glitch in switching on.
        break;

      case ELmode::CR:
        umon = localSetState.rangeVoltageLow ? state.cal.UmonLow->remapADC(measured.UmonRaw) : state.cal.Umon->remapADC(measured.UmonRaw);
        iset = umon / localSetState.Rset; // // TODO: Set to 0 if Von is active. This avoids inrush current.
        uset = 0.0f; // Do not clamp to max to void inrush glitch.
        break;

      case ELmode::CC:
        iset = localSetState.Iset;
        uset = 0.0f; // No limit.
        break;

      case ELmode::CV:
        iset = 100.0f;  // No limit.
        uset = localSetState.Uset;;
        break;

      //default: // CC, CV and SHORT (max/min if not needed)
      //  iset = localSetState.Iset;
      //  uset = localSetState.Uset;
      //  break;

      }
    }
    else
    {
      // OFF/Safe Mode
      iset = -1.0f; // Will clamp ADC to 0
      uset = 0.0f;  // Do not clamp otherwise a startup glitch will be appear.
      //vonset = 1.0f;
      isetPrev = -2.0f; // Make sure we update
      usetPrev = -2.0f;
    } 

    // Only recalc and set if changed
    if (iset != isetPrev || localSetState.rangeCurrentLow != rangeCurrentLowPrev)
    {
      if (localSetState.CalibrationIset == true) {
        isetRaw = (uint32_t)localSetState.Iset;
      } else {
        iset = localSetState.rangeCurrentLow ? state.cal.IsetLow->remapDAC(iset) : state.cal.Iset->remapDAC(iset);
        isetRaw = iset;
      }
      if (isetRaw != isetRawPrev)
      {
        isetRaw = (uint32_t)clamp(isetRaw, iSetDAC.DAC_MIN, iSetDAC.DAC_MAX);
#ifndef FAKE_HARDWARE
        iSetDAC.write(isetRaw);
#endif
        isetRawPrev = isetRaw;
        isetPrev = iset;
      }
    }
    // Time critical part ends here. CP and CR loop have changing iset, not uset.

    if (uset != usetPrev || localSetState.rangeVoltageLow != rangeVoltLowPrev)
    {
      if (localSetState.CalibrationUset == true) {
        usetRaw = (uint32_t)localSetState.Uset;
      } else {
      //uset = remap(uset, iSetMinVal, (float)uSetDAC.DAC_MIN, uSetMaxVal, (float)uSetDAC.DAC_MAX);
        uset =  localSetState.rangeVoltageLow ? state.cal.UsetLow->remapDAC(uset) : state.cal.Uset->remapDAC(uset);
        usetRaw = (uint32_t)clamp(uset, uSetDAC.DAC_MIN, uSetDAC.DAC_MAX);
      }
      if (usetRaw != usetRawPrev)
      {
#ifndef FAKE_HARDWARE
        uSetDAC.write(usetRaw);
#endif
        usetRawPrev = usetRaw;
        usetPrev = uset;
      }
    }
    // Only recalc and set if changed
    if (vonset != vonsetPrev || localSetState.CalibrationVonSet == true || localSetState.rangeVoltageLow != rangeVoltLowPrev)
    {
      if (localSetState.CalibrationVonSet == true) {
        vonsetRaw = (uint32_t)localSetState.VonSet;
      } else {
      //vonset = remap(vonset, iSetMinVal, (float)vonSetDAC.DAC_MIN, vonSetMaxVal, (float)vonSetDAC.DAC_MAX);
      vonset = localSetState.rangeVoltageLow ? state.cal.VonLow->remapDAC(vonset) : state.cal.Von->remapDAC(vonset);
      vonsetRaw = (uint32_t)clamp(vonset, vonSetDAC.DAC_MIN, vonSetDAC.DAC_MAX);
      }
      if (vonsetRaw != vonsetRawPrev)
      {
#ifndef FAKE_HARDWARE
        vonSetDAC.write(vonsetRaw);
#endif
        vonsetRawPrev = vonsetRaw;
        vonsetPrev = vonset;
      }
    }

    // Only recalc and set if changed
    if (ocpset != ocpsetPrev || localSetState.CalibrationOCPset == true || localSetState.rangeCurrentLow != rangeCurrentLowPrev)
    {
      if (localSetState.CalibrationOCPset == true) {
        ocpsetRaw = (uint32_t)localSetState.OCPset;
      } else {
      ocpset = localSetState.rangeCurrentLow ? state.cal.OCPsetLow->remapDAC(ocpset) : state.cal.OCPset->remapDAC(ocpset);
      ocpsetRaw = (uint32_t)clamp(ocpset, OCPSetDAC.DAC_MIN, OCPSetDAC.DAC_MAX);
      }
      if (ocpsetRaw != ocpsetRawPrev)
      {
#ifndef FAKE_HARDWARE
        OCPSetDAC.write(ocpsetRaw);
#endif
        ocpsetRawPrev = ocpsetRaw;
        ocpsetPrev = ocpset;
      }
      rangeCurrentLowPrev = localSetState.rangeCurrentLow;
    }

    // Only recalc and set if changed
    if (ovpset != ovpsetPrev || localSetState.CalibrationOVPset == true || localSetState.rangeVoltageLow != rangeVoltLowPrev)
    {
      if (localSetState.CalibrationOVPset == true) {
        ovpsetRaw = (uint32_t)localSetState.OVPset;
      } else {
      ovpset = localSetState.rangeVoltageLow ? state.cal.OVPsetLow->remapDAC(ovpset) : state.cal.OVPset->remapDAC(ovpset);
      ovpsetRaw = (uint32_t)clamp(ovpset, OVPSetDAC.DAC_MIN, OVPSetDAC.DAC_MAX);
      }
      if (ovpsetRaw != ovpsetRawPrev)
      {
#ifndef FAKE_HARDWARE
        OVPSetDAC.write(ovpsetRaw);
#endif
        ovpsetRawPrev = ovpsetRaw;
        ovpsetPrev = ovpset;
      }
      rangeVoltLowPrev = localSetState.rangeVoltageLow;
    }

    // Send measurements to avg task.
    xMessageBufferSend(newMeasurements, &measured, sizeof(measured), 0);

    if (localSetState.rangeCurrentLow != rangeCurrentLowPrev) {
      rangeCurrentLowPrev = localSetState.rangeCurrentLow;
    }
    if (localSetState.rangeVoltageLow != rangeVoltLowPrev) {
      rangeVoltLowPrev = localSetState.rangeVoltageLow;
    }

    // Receive changed settings.
    // Receive copy of state if send. Using a copy to avoid a mutex lock.
    msgBytes = xQueueReceive(changeMeasureTaskSettings, &changeMsg, 0);
    if (msgBytes > 0)
    {
      localSetState = changeMsg;
      stateReceived = true;
    }
  watchdogMeasureAndOutput = 0;
  }
}

void taskAveragingFunction(void *pvParameters)
{
  // Message buffer
  newMeasurementMsg newMsg;
  changeAverageSettingsMsg settingsMsg;
  size_t msgBytes;

  // Setup and clear memories
  int32_t avgSampleWindow = 100;
  int32_t avgRawCount = 0;
  int64_t avgCurrentRawSum = 0; // TODO: hardcoded to 2's complemnet because of ADS131M02
  int32_t avgCurrentRaw = 0;
  int64_t avgVoltRawSum = 0;   // TODO: see current above.
  int32_t avgVoltRaw = 0;
  
  float imon;
  float umon;
  double As = 0;
  double Ws = 0;
  double time = 0;
  bool record = true;
  bool on = true;
  double interval = 0;
  bool update = false;
  bool sendCalData = false;

  // OPP calculation
  float localOPPset = 0;
  float localOPPdelay = 0;
  unsigned long OPPTriggerStart = 0;
  bool OPPStarted = false;

  // Ragne settings
  bool localRangeCurrentLow = false;
  bool localRangeVoltageLow = false;

  // Capacity limits
  float localVoltStop = 0, prevVoltStop = 0;
  float localAsStop   = 0, prevAsStop = 0;
  float localTimeStop = 0, prevTimeStop = 0;

  //SERIALDEBUG.println("INFO: Going into average loop.");
  // state.updateAverageTask(); // Prepare message for myself to load defaults.
  taskAveragingReady = true;
  for (;;)
  {
    xMessageBufferReceive(newMeasurements, &newMsg, sizeof(newMsg), portMAX_DELAY);
    //digitalWrite(PIN_TEST, HIGH);
    avgCurrentRawSum = avgCurrentRawSum + newMsg.ImonRaw;
    avgRawCount++;
    avgVoltRawSum = avgVoltRawSum + newMsg.UmonRaw;

    if (avgRawCount >= avgSampleWindow)
    {
      avgCurrentRaw = avgCurrentRawSum / avgRawCount;
      avgCurrentRawSum = 0;
      avgVoltRaw = avgVoltRawSum / avgRawCount;
      avgVoltRawSum = 0;
      avgRawCount = 0;
      update = true;
    }

    if (update)
    {
      //digitalWrite(PIN_TEST, HIGH);
      imon = localRangeCurrentLow ?  state.cal.ImonLow->remapADC(avgCurrentRaw) : state.cal.Imon->remapADC(avgCurrentRaw);
      umon = localRangeVoltageLow ?  state.cal.UmonLow->remapADC(avgVoltRaw) :  state.cal.Umon->remapADC(avgVoltRaw);
      //imon = remap((float)avgCurrentRaw, (float)currentADC.ADC_MIN, currentMinVal, (float)currentADC.ADC_MAX, currentMaxVal);
      //umon = remap((float)avgVoltRaw, (float)voltADC.ADC_MIN, voltMinVal, (float)voltADC.ADC_MAX, voltMaxVal);
      imon = max(imon, 0); // Avoid negative values (around 0mA)
      umon = max(umon, 0); // Avoid negative values (around 0V)

      if (record && on)
      {
        interval = (double)(avgSampleWindow * (float)CLOCK_DIVIDER_ADC * 2.0f * (float)ADC_OSR / ((float)F_CPU)); // TODO: Use variables/constants. 15 = clock divider, 2 = ADC fmod, 4096 = ADC OSR.
        // TODO: ? Power is calcuated based on average Volt and Current, this is ok for DC but for AC this results in AV and not W... Change this (more realtime processing...)?
        time += interval;
        As += (double)imon * interval;
        Ws += (double)umon * (double)imon * interval;
      }

      // Perform OPP and OTP checks
      if (on && umon * imon > localOPPset)
      {
        if (!OPPStarted)
        {
          OPPTriggerStart = millis();
          OPPStarted = true;
        }
        else
        {
          if (OPPTriggerStart + localOPPdelay * 1000 <= millis())
          {
            state.setProtection();
            state.OPPtriggered();
          }
        }
      }
      else
      {
        OPPStarted = false;
      }

/*
      // Perform Capacity limit checks.
      if (on && record && (localVoltStop >= umon || localAsStop >= As || localTimeStop != time))
      {
        state.setCapacityTriggers(localVoltStop, localAsStop, localTimeStop);
        prevVoltStop = localVoltStop;
        prevAsStop = localAsStop;
        prevTimeStop = localTimeStop;
      }
*/
      // Notify main task.
      state.setAvgMeasurements(imon, umon, As, Ws, time, avgCurrentRaw, avgVoltRaw);
      update = false;
    }

    // Settings changed if there is a message for it.
    msgBytes = xQueueReceive(changeAverageSettings, &settingsMsg, 0);
    if (msgBytes > 0)
    {
      if (settingsMsg.avgSamples != 0)
      {
        avgSampleWindow = settingsMsg.avgSamples;
        // Next calculation will adjust. It doesn't matter if window size increases or decreased. All samples are still counted.
      }
        
      if (settingsMsg.clear == true)
      {
        time = 0.0f;
        As = 0.0f;
        Ws = 0.0f;
      }
      record = settingsMsg.record;
      on = settingsMsg.on;
      sendCalData = settingsMsg.sendCalData; // obsolete?
      localOPPset = settingsMsg.OPPset;
      localOPPdelay = settingsMsg.OPPdelay;
      localRangeCurrentLow = settingsMsg.rangeCurrentLow;
      localRangeVoltageLow = settingsMsg.rangeVoltageLow;
      localAsStop = settingsMsg.CapAhStop * 3600.0f; // As is in Amp * seconds not Amp * hours.
      localVoltStop = settingsMsg.CapVoltStop;
      localVoltStop = settingsMsg.CapTimeStop;
    }
    //digitalWrite(PIN_TEST, LOW);
    watchdogAveraging = 0;
  }
}

// For debugging / testing without hardware.
// Simulate a fake interrupt of ADC.
void timerFakeADCInterruptFunction(TimerHandle_t timerFakeADCInterrupt)
{
    xTaskNotifyGive(taskMeasureAndOutput);
};

extern "C" {
// For debugging (blinking x)  
bool get_var_alive() { return ledstate;};
}