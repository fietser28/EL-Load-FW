// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <Arduino.h>
#include <Wire.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include <Rotary.h>

#include "main.h"
#include "keys.h"
#include "ui_glue.h"
#include "gpio_mcp23008.h"

// Global keystate structure, used by ui.
keystate_t keystate;

Rotary encoder = Rotary();
gpio_mcp23008 gpiokeys = gpio_mcp23008();

static void encTask(void *pvParameter);
TaskHandle_t encTaskHandle;
bool encTaskInitiated = false;
volatile uint8_t watchdogEncTask;

void keys_task_init(void)
{

    xTaskCreate(encTask, "enc", 1024, NULL, TASK_PRIORITY_KEYS, &encTaskHandle);
};

void keys_update(void)
{
    if (encTaskInitiated) {
        xTaskNotifyGive(encTaskHandle);
    };
};

static void __not_in_flash_func(ISR_KEYS())
    {
        BaseType_t taskWoken = pdFALSE;
        vTaskNotifyGiveFromISR(encTaskHandle, &taskWoken);
        if (taskWoken != pdFALSE) {
            portYIELD_FROM_ISR(taskWoken);
        }
    };

static void encTask(void *pvParameter)
{

    // MCP23008 defaults are fine..
    // Enable interrupts.
    // writeI2C(KEYS_CHIP_ADDRESS, MCP23X08_ADDR_GPINTEN, 255);
    pinMode(PIN_KEYS_INT, INPUT);
    gpiokeys.begin(&I2C_KEYS, I2C_KEYS_SEM, KEYS_CHIP_ADDRESS);
    vTaskDelay(3); //TODO: remove?
    gpiokeys.pinInterrupts(0xff, 0x00, 0x00); // All pins on any change.
    vTaskDelay(3); //TODO: remove?
    gpiokeys.pinModes(~(1 << KEYS_PIN_LED0)); // Only led pin is output.

    encoder.begin(true);

    keystate.encodercount = 0;

    int slowtick = 0;
    uint8_t iodir, ipol, gppu, gpioval;
    int8_t encdir;
    int enccount = 0;
    int pin1count = 0;
    int pin2count = 0;
    unsigned char encpin1, encpin2, encpin1prev, encpin2prev;
    uint testcounter = 0;

    encpin1prev = true; // pullup
    encpin2prev = true;

    bool button3prev = false;
    bool ledstateon  = false;
    dcl::setStateStruct localsetcopy;


    ::attachInterrupt(digitalPinToInterrupt(PIN_KEYS_INT), ISR_KEYS, FALLING);
    gpiokeys.digitalRead(); //Clear interrupt pin status.
 
    encTaskInitiated = true; 

    while (1)
    {
        ulTaskNotifyTake(pdTRUE, 100 / portTICK_PERIOD_MS); 

        //digitalWrite(PIN_TEST, HIGH);
        //gpioval = readI2C(KEYS_CHIP_ADDRESS, MCP23X08_ADDR_GPIO);
        gpioval = gpiokeys.digitalRead();
        encpin1 = gpioval & (1 << KEYS_PIN_ENC0) ? 1 : 0;
        encpin2 = gpioval & (1 << KEYS_PIN_ENC1) ? 1 : 0;
        encdir = encoder.process(encpin1, encpin2);
        if (encdir == DIR_CCW)
        {
            enccount--;
        }
        if (encdir == DIR_CW)
        {
            enccount++;
        }
        encpin1prev = encpin1;
        encpin2prev = encpin2;

        // Lazy 'Atomic' transfers.
        keystate.encodercount = enccount;
        keystate.encoderbutton = gpioval & (1 << KEYS_PIN_ENCBUT) ? false : true ;

        //keystate.button0 = gpioval & (1 << KEYS_PIN_BUT0) ? false : true ;
        //keystate.button1 = gpioval & (1 << KEYS_PIN_BUT1) ? false : true ;
        //keystate.button2 = gpioval & (1 << KEYS_PIN_BUT2) ? false : true ;
        keystate.button3 = gpioval & (1 << KEYS_PIN_BUT0) ? false : true ; // TODO: Fix button assignment for different setups.

        if( keystate.button3 != button3prev)   // Button state changed 
        {
            button3prev = keystate.button3;
            if (keystate.button3 == true)       // Button pressed (not released)
            {
                state.getSetStateCopy(&localsetcopy, 25);
                if (localsetcopy.on) {
                    state.setOff();
                } else {
                    state.setOn();
                }
            }
        }

        state.getSetStateCopy(&localsetcopy, 25);        
        if (localsetcopy.on != ledstateon) {
            ledstateon = localsetcopy.on;
            gpiokeys.digitalWrite(KEYS_PIN_LED0, ledstateon);
        } 

        // For debugging (of rotary encoder)
        if (encpin1 != encpin1prev)
        {
            pin1count++;
        };
        if (encpin2 != encpin2prev)
        {
            pin2count++;
        };
        // TODO: Remove slowtick stuff, it's just for testing.
        slowtick++;
        if (slowtick > 10)
        {
            slowtick = 0;
            printlogval(pin1count, pin2count, enccount / 2, keystate.encoderbutton);
        }
        //vTaskDelay(4); // Debounce margin. - not needed with interrupts
    watchdogEncTask = 0;
    }
}
