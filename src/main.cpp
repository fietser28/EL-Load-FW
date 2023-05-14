#include <limits.h>

#include <Arduino.h>
#include <Wire.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "message_buffer.h"
#include "SPI.h"

#include "main.h"
#include "state.h"
#include "util.h"
#include "cal.h"
#include "adc.h"
#include "dac.h"
#include "display.h"
#include "keys.h"
#include "ui_glue.h"

// Fixes lvgl include. TODO: remove?
#include "LittleFS.h"

using namespace dcl;

#ifdef FAKE_HARDWARE
TimerHandle_t timerFakeADCInterrupt;
#endif

// I2C bus semaphores
SemaphoreHandle_t WireSem;       // Manage sharing between tasks 
SemaphoreHandle_t Wire1Sem;      // Manage sharing between tasks

// Tasks and buffer allocations
// HW protection task
TaskHandle_t taskProtHW;

// Measurement and Ouput Task
TaskHandle_t taskMeasureAndOutput;
SemaphoreHandle_t adcReady;
QueueHandle_t changeMeasureTaskSettings;

// Averaging and power calculation task 
TaskHandle_t taskAveraging;
MessageBufferHandle_t newMeasurements;
QueueHandle_t changeAverageSettings;

// UI task
TaskHandle_t taskDisplay;

// Workaround for reset after SWD upload
TaskHandle_t taskBootBug;
QueueHandle_t bootbugtestQueue;

// adc_MCP3202 currentADC = adc_MCP3202(SPI_ADC, PIN_SPI0_SS, 0);
// adc_MCP3202 voltADC = adc_MCP3202(SPI_ADC, PIN_SPI0_SS, 1);
// adc_MCP3462 currentADC = adc_MCP3462(SPI_ADC, SPI_ADC_CS, 0);
// adc_MCP3462 voltADC = adc_MCP3462(&currentADC, 1);
adc_ADS131M02 currentADC = adc_ADS131M02(SPI_ADC, SPI_ADC_CS, PIN_ADC_CLK, PIN_ADC_RDY);
adc_ADS131M02 voltADC = adc_ADS131M02(&currentADC, 1); // volt = secondary channel

dac_dac8555 iSetDAC = dac_dac8555(SPI_DAC1, PIN_DAC1_CS, 0);
dac_dac8555 uSetDAC = dac_dac8555(SPI_DAC1, PIN_DAC1_CS, 1);
dac_dac8555 vonSetDAC = dac_dac8555(SPI_DAC1, PIN_DAC1_CS, 2);
dac_dac8555 OCPSetDAC = dac_dac8555(SPI_DAC1, PIN_DAC1_CS, 3);
// dac_dac8555 OVPSetDAC = dac_dac8555(SPI_DAC1, PIN_DAC1_CS, 0);



// Global state manager
stateManager state;

// TODO: put this in a class somewhere

CalibrationValueConfiguration currentCal;
float currentMinVal;
float currentMaxVal;
CalibrationValueConfiguration voltCal;
float voltMinVal;
float voltMaxVal;
CalibrationValueConfiguration iSetCal;
float iSetMinVal;
float iSetMaxVal;
CalibrationValueConfiguration uSetCal;
float uSetMinVal;
float uSetMaxVal;
CalibrationValueConfiguration vonSetCal;
float vonSetMinVal;
float vonSetMaxVal;

// TODO for debug/test
volatile uint32_t i = -10;

bool ledstate;

// TODO Change this to a watchdog (including checking other tasks?)
void blinkloop1(void *pvParameters)
{
  for (;;)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    ledstate = true;
    vTaskDelay(500);
    digitalWrite(LED_BUILTIN, LOW);
    ledstate = false;
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


void setup()
{
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
  I2C_KEYS.setClock(400000);
  I2C_KEYS.begin();

  // TODO Workaround: Testing proper multi-core boot, otherwise reboot.
  //////////////
  /*
  SERIALDEBUG.println("INFO: Core1 FreeRTOS running? (SWD restart bug)");
  bootbugtestQueue = xQueueCreate(40, sizeof(uint8_t));
  BaseType_t bootTaskRet = xTaskCreate(corerunningtest, "BootTest", 200, (void *)1, 5, &taskBootBug);
  if (bootTaskRet != pdPASS)
  {
    SERIALDEBUG.println("FATAL: Unable to start FreeRTOS task...");
    rp2040.reboot();
  }
  vTaskCoreAffinitySet(taskBootBug, 1 << 1); // Runs on core1

  bool core1running = false;
  uint8_t bootbugmsg = 0;
  BaseType_t queueresult;
  while (!core1running)
  {
    if (xQueueReceive(bootbugtestQueue, &bootbugmsg, 2000) == pdPASS)
    {
      core1running = true;
    }
    else
    {
      // No message from core1, reset
      SERIALDEBUG.println("FATAL: Core1 not running, rebooting...");
      rp2040.reboot();
    }
  }
  vTaskSuspend(taskBootBug);
  vTaskDelete(taskBootBug);
  vTaskDelay(10);
  vQueueDelete(bootbugtestQueue);
  SERIALDEBUG.println("INFO: FreeRTOS@Core1 running fine.");
  */
  // End of multi-core boot workaround.
  ///////////////
  /*
        // Setup SPI
        pinMode(SPI_ADC_CS, OUTPUT);
        digitalWrite(SPI_ADC_CS, HIGH);
        pinMode(PIN_DAC1_CS, OUTPUT);
        digitalWrite(PIN_DAC1_CS, HIGH);

        SERIALDEBUG.println("INFO: ADC SPI.set... done");
          // Setup ADC SPI
        SPI_ADC.setRX(SPI_ADC_RX);
        SPI_ADC.setTX(SPI_ADC_TX);
        SPI_ADC.setSCK(SPI_ADC_SCK);
        SERIALDEBUG.println("INFO: ADC SPI.begin... done");

        SPI_ADC.begin();
        SERIALDEBUG.println("INFO: ADC SPI done");
*/

  state.begin(); // Setup memory, mutexes and queues.
  snprintf(logtxt, 200, "- Empty log -");
  gui_task_init(); // Takes lot of memory?


  // TODO: Hardcoded calibration values for now
  state.cal.Imon = new calLinear2P();
  CalibrationValueConfiguration currentCal;
  currentCal.numPoints = 2;
  currentCal.points[0].value = 0.050; // 50mV
  currentCal.points[0].adc = 349700;
  currentCal.points[1].value = 1.100 * 4.4 * 2.1 ; // 1.100V => >10A
  currentCal.points[1].adc = 7643800;

  state.cal.Imon->setCalConfig(currentCal);
  state.cal.Imon->setADCConfig(currentADC.ADC_MIN, currentADC.ADC_MAX);


  float currentC = (currentCal.points[1].value - currentCal.points[0].value) / (currentCal.points[1].adc - currentCal.points[0].adc);
  float currentO = currentCal.points[0].value - currentCal.points[0].adc * currentC;

  currentMinVal = currentO;
  currentMaxVal = (float)currentADC.ADC_MAX * currentC;

  SERIALDEBUG.printf("INFO: Current calibration min,max,coeff: %.4f  %.4f %.4e\n", currentMinVal, currentMaxVal, currentC);


  voltCal.numPoints = 2;
  voltCal.points[0].value = 0.050; // 50mV
  voltCal.points[0].adc = 349700;
  voltCal.points[1].value = 1.100 * 34 * 2.1; // 1.100V => >80V
  voltCal.points[1].adc = 7643800;

  float voltC = (voltCal.points[1].value - voltCal.points[0].value) / (voltCal.points[1].adc - voltCal.points[0].adc);
  float voltO = voltCal.points[0].value - voltCal.points[0].adc * voltC;

  voltMinVal = voltO;
  voltMaxVal = (float)voltADC.ADC_MAX * voltC;

  SERIALDEBUG.printf("INFO: Volt calibration min,max,coeff: %.4f  %.4f %.4e\n", voltMinVal, voltMaxVal, voltC);

  iSetCal.numPoints = 2;
  iSetCal.points[0].value = 0.00299; // @3.3Vinput (AMS1117)
  iSetCal.points[0].dac = 100;
  iSetCal.points[1].value = 3.2374; // @3.3Vinput (AMS1117)
  iSetCal.points[1].dac = 64000;

  float iSetC = (iSetCal.points[1].value - iSetCal.points[0].value) / (iSetCal.points[1].dac - iSetCal.points[0].dac);
  float iSetO = iSetCal.points[0].value - iSetCal.points[0].dac * iSetC;

  iSetMinVal = iSetO;
  iSetMaxVal = (float)iSetDAC.DAC_MAX * iSetC;

  SERIALDEBUG.printf("INFO: Iset calibration min,max,coeff: %.4f  %.4f %.4e\n", iSetMinVal, iSetMaxVal, iSetC);


  //// FreeRTOS setup.
  //////////////////////////

  WireSem = xSemaphoreCreateMutex();
  Wire1Sem = xSemaphoreCreateMutex();
  
  // ADC ready semasphore between ISR and measure task
  adcReady = xSemaphoreCreateBinary();

  // Message straam from Measure to Averaging task
  const size_t newMeasurementsMsgBuffer = 60; // 1 msg = 4bytes + 2x4bytes = 12 bytes => 5 messages.
  newMeasurements = xMessageBufferCreate(newMeasurementsMsgBuffer);
  if (newMeasurements == NULL)
  { // TODO: reset, something is really wrong....
  }

  // Message stream from state functions to averaging task.
  const size_t changeAverageSettingsBuffer = 42; // 1 msg = 4bytes + 3bytes = 7 bytes => 6 messages.
  changeAverageSettings = xQueueCreate(6, sizeof(changeAverageSettingsMsg));
  if (changeAverageSettings == NULL)
  { // TODO: reset, something is really wrong....
  };

  // Message stream from state functions to measure task.
  const size_t changeMeasureTaskSettingsBuffer = 42; // TODO: 1 msg = 4bytes + 3bytes = 7 bytes => 6 messages.
  changeMeasureTaskSettings = xQueueCreate(6, sizeof(changeAverageSettingsMsg));
  if (changeMeasureTaskSettings == NULL)
  { // TODO: reset, something is really wrong....
  }

  state.setDefaults();
  state.record(true);
  state.setOff();
  state.clearPower();

  vTaskDelay(4000);

  keys_task_init();

  vTaskDelay(4000);

  //gui_task_init();

  vTaskDelay(4000);

  // Next create the protection tasks.
  BaseType_t xTaskRet;
  // xTaskRet = xTaskCreate(taskProtHWFunction, "HWProt", 200, (void *) 1, 4, &taskProtHW);
  // if (xTaskRet != pdPASS) { // TODO: reset, something is really wrong;
  //   SERIALDEBUG.println("ERROR: Error starting ProtHW task.");
  // }
  // vTaskCoreAffinitySet(taskProtHW, 0x03); // Can run on both cores.

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
  timerFakeADCInterrupt = xTimerCreate("", FAKE_HARDWARE_TIMER_TICKS, pdTRUE, ( void * ) 0, timerFakeADCInterruptFunction);
  if (timerFakeADCInterrupt == NULL ) {
    SERIALDEBUG.println("ERROR: Unable to create FakeADCTimer.");
  } else {
    xTimerStart(timerFakeADCInterrupt, 0);
  }
#endif


  xTaskRet = xTaskCreate(blinkloop1, "", 200, (void *)1, 1, &taskDisplay);
  if (xTaskRet != pdPASS)
  { // TODO: reset, something is really wrong;
    SERIALDEBUG.println("ERROR: Error starting blink task.");
  }
  vTaskCoreAffinitySet(taskDisplay, 1 << 0);

  state.startupDone();
  SERIALDEBUG.println("INFO: Setup done.");

  state.setOn();

}

const TickType_t ondelay = 1000;
measuredStateStruct loopmystate;
setStateStruct loopmysetstate;

int heaptotal, heapused, heapfree; 
int cyclecount = 0;

void loop()
{
  // TODO: Replace with SCPI reading class/task?
  if (SERIALDEBUG.available())
  {
    SERIALDEBUG.write(SERIALDEBUG.read());
  }
  
  bool getok = state.getMeasuredStateCopy(&loopmystate, 20);
  getok = getok && state.getSetStateCopy(&loopmysetstate, 20);

  //SERIALDEBUG.printf("%.4f (%.5f/%.5f) %d %d\n", loopmystate.Imon, loopmystate.As/3600.0f, loopmystate.Ptime, getok, loopmysetstate.startupDone);
  heaptotal = rp2040.getTotalHeap();
  heapused = rp2040.getUsedHeap();
  heapfree = rp2040.getFreeHeap();
//  cyclecount = rp2040.getCycleCount64()/rp2040.f_cpu();
  cyclecount++;
  SERIALDEBUG.printf("Heap total: %d, used: %d, free:  %d, uptime: %d\n", heaptotal, heapused, heapfree, cyclecount);
  snprintf(logtxt, 120, "Heap total: %d\nHeap used: %d\nHeap free:  %d\n", heaptotal, heapused, heapfree);
  vTaskDelay(ondelay);
}

// HW Protection interrupt & task
/////////////////////////////////
static void ISR_ProtHW()
{
  // Just start a high priority task and force immediate context switch if task is available.
  // digitalWrite(LED_BUILTIN, HIGH);
  BaseType_t taskProtHWWoken = pdFALSE;
  vTaskNotifyGiveFromISR(taskProtHW, &taskProtHWWoken);
  portYIELD_FROM_ISR(taskProtHWWoken);
};

void taskProtHWFunction(void *pvParameters)
{
  uint32_t ulNotifiedValue;

  // Setup HW pins
  // pinMode(PIN_OCPTRIGGERED, INPUT_PULLDOWN);  // TODO: Change to floating on final PCB, for testing this avoids spurios triggers if unconnected
  pinMode(PIN_OVPTRIGGERED, INPUT_PULLDOWN); // TODO: ,,

  // attachInterrupt(digitalPinToInterrupt(PIN_OCPTRIGGERED), ISR_ProtHW, FALLING);
  // attachInterrupt(digitalPinToInterrupt(PIN_OVPTRIGGERED), ISR_ProtHW, FALLING);

  for (;;)
  {
    // Notified by interrupt, wait forever on any notification
    xTaskNotifyWaitIndexed(0,                /* Wait for 0th notification. */
                           0x00,             /* Don't clear any notification bits on entry. */
                           ULONG_MAX,        /* Reset the notification value to 0 on exit. */
                           &ulNotifiedValue, /* Notified value pass out in
                                                 ulNotifiedValue. */
                           portMAX_DELAY);   /* Block indefinitely. */
    // Go to a safe hardware state as fast as possible
    safeMode(); // Safe mode sets state of OFF.

    // TODO: move to safeMode function.
    xSemaphoreTake(setStateMutex, UNKOWN_ERROR_TASK_TIMEOUT);
    if (setStateMutex != NULL)
    {
      if (xSemaphoreTake(setStateMutex, (TickType_t)UNKOWN_ERROR_TASK_TIMEOUT) == pdTRUE)
      {
        setState.protection = true;
        xSemaphoreGive(setStateMutex);
      }
      else
      {
        // TODO: Force reset
      }
      // TODO: Force reset, init is not ok.
    }
  }
};

// This task exclusivlly handles ADC and DAC SPI channels.
void taskMeasureAndOutputFunction(void *pvParameters)
{
  uint32_t ulNotifiedValue;
  newMeasurementMsg measured;
  setStateStruct changeMsg;
  setStateStruct localSetState;

  float imon;
  float umon;
  float iset = 0.0f, isetPrev = -0.1f; // DACs init at 0.
  float uset, usetPrev = -0.1f;
  float vonset, vonsetPrev = -0.1f;
  uint32_t isetRaw, isetRawPrev = 0;
  uint32_t usetRaw, usetRawPrev = 0;
  uint32_t vonsetRaw, vonsetRawPrev = 0;
  size_t msgBytes;
  bool stateReceived = false;

  vTaskDelay(200); // Wait for affinity.

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

    // No mutexes around calibration data.
    imon = state.cal.Imon->remap(measured.ImonRaw);
    //imon = remap((float)measured.ImonRaw, (float)currentADC.ADC_MIN, currentMinVal, (float)currentADC.ADC_MAX, currentMaxVal);
    umon = remap((float)measured.UmonRaw, (float)voltADC.ADC_MIN, voltMinVal, (float)voltADC.ADC_MAX, voltMaxVal);

    if (stateReceived && localSetState.on == true && localSetState.protection == false)
    {
      vonset = localSetState.VonSet;
      switch (localSetState.mode)
      {
      case ELmode::START:
        iset = 0.0f;
        uset = localSetState.Uset; // Max
        break;

      case ELmode::CP:
        iset = localSetState.Pset / umon;
        uset = localSetState.Uset; // Max
        break;

      case ELmode::CR:
        iset = umon / localSetState.Rset;
        uset = localSetState.Uset; // Max
        break;

      default: // CC, CV and SHORT (max/min if not needed)
        iset = localSetState.Iset;
        uset = localSetState.Uset;
        break;
      }
    }
    else
    {
      iset = 0.0f;
      uset = 1000.0f; // Will clamp DAC
      vonset = 1.0f;
    }

    // Only recalc and set if changed
    if (iset != isetPrev)
    {
      iset = remap(iset, iSetMinVal, (float)iSetDAC.DAC_MIN, iSetMaxVal, (float)iSetDAC.DAC_MAX);
      isetRaw = (uint32_t)clamp(iset, iSetDAC.DAC_MIN, iSetDAC.DAC_MAX);
      if (isetRaw != isetRawPrev)
      {
#ifndef FAKE_HARDWARE
        iSetDAC.write(isetRaw);
#endif
        isetRawPrev = isetRaw;
        isetPrev = iset;
      }
    }
    // Time critical part ends here. CP and CR loop have changing iset, not uset.

    // Only recalc and set if changed
    if (uset != usetPrev)
    {
      uset = remap(uset, iSetMinVal, (float)uSetDAC.DAC_MIN, uSetMaxVal, (float)uSetDAC.DAC_MAX);
      usetRaw = (uint32_t)clamp(uset, uSetDAC.DAC_MIN, uSetDAC.DAC_MAX);
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
    if (vonset != vonsetPrev)
    {
      vonset = remap(vonset, iSetMinVal, (float)vonSetDAC.DAC_MIN, vonSetMaxVal, (float)vonSetDAC.DAC_MAX);
      vonsetRaw = (uint32_t)clamp(vonset, vonSetDAC.DAC_MIN, vonSetDAC.DAC_MAX);
      if (vonsetRaw != vonsetRawPrev)
      {
#ifndef FAKE_HARDWARE
        vonSetDAC.write(vonsetRaw);
#endif
        vonsetRawPrev = vonsetRaw;
        vonsetPrev = vonset;
      }
    }


    xMessageBufferSend(newMeasurements, &measured, sizeof(measured), 0);
    // Receive copy of state if send. Using copy to avoid a mutex lock.
    msgBytes = xQueueReceive(changeMeasureTaskSettings, &changeMsg, 0);
    if (msgBytes > 0)
    {
      localSetState = changeMsg;
      stateReceived = true;
    }
  }
}

void taskAveragingFunction(void *pvParameters)
{
  // Message buffer
  newMeasurementMsg newMsg;
  changeAverageSettingsMsg settingsMsg;
  size_t msgBytes;

  // Setup and clear memories
  uint32_t avgSampleWindow = 100;
  uint32_t avgRawCount = 0;
  uint64_t avgCurrentRawSum = 0;
  uint32_t avgCurrentRaw = 0;
  uint64_t avgVoltRawSum = 0;
  uint32_t avgVoltRaw = 0;
  
  float imon;
  float umon;
  double As = 0;
  double Ws = 0;
  double time = 0;
  bool record = true;
  bool on = true;
  double interval = 0;
  bool update = false;

  SERIALDEBUG.println("INFO: Going into average loop.");
  state.updateAverageTask(); // Prepare message for myself to load defaults.

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
      //imon = state.cal.Imon->remap(avgCurrentRaw);
      imon = remap((float)avgCurrentRaw, (float)currentADC.ADC_MIN, currentMinVal, (float)currentADC.ADC_MAX, currentMaxVal);
      umon = remap((float)avgVoltRaw, (float)voltADC.ADC_MIN, voltMinVal, (float)voltADC.ADC_MAX, voltMaxVal);
      if (record && on)
      {
        interval = (double)(avgSampleWindow * (float)CLOCK_DIVIDER_ADC * 2.0f * (float)ADC_OSR / ((float)F_CPU)); // TODO: Use variables/constants. 15 = clock divider, 2 = ADC fmod, 4096 = ADC OSR.
        // TODO: ? Power is calcuated based on average Volt and Current, this is ok for DC but for AC this results in AV and not W... Change this (more realtime processing...)?
        time += interval;
        As += (double)imon * interval;
        Ws += (double)umon * (double)imon * interval;
      }
      state.setAvgMeasurements(imon, umon, As, Ws, time);
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
    }
    //digitalWrite(PIN_TEST, LOW);
  }
}

void safeMode()
{
  // TODO
}

// For debugging / testing without hardware.
// Genrate a fake interrupt of ADC.
void timerFakeADCInterruptFunction(TimerHandle_t timerFakeADCInterrupt)
{
    xTaskNotifyGive(taskMeasureAndOutput);
};

extern "C" {
// For debugging (blinking x)  
bool get_var_alive() { return ledstate;};
}