#include <Arduino.h>
#include <Wire.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include <Rotary.h>

#include "main.h"
#include "keys.h"
#include "ui_glue.h"

#define MCP23x08_ADDR_IODIR 0x00
#define MCP23X08_ADDR_IPOL 0x01
#define MCP23X08_ADDR_GPINTEN 0x02
#define MCP23X08_ADDR_DEFVAL 0x03
#define MCP23X08_ADDR_INTCON 0x04
#define MCP23X08_ADDR_IOCON 0x05
#define MCP23X08_ADDR_GPPU 0x06
#define MCP23X08_ADDR_INTF 0x07
#define MCP23X08_ADDR_INTCAP 0x08
#define MCP23X08_ADDR_GPIO 0x09
#define MCP23X08_ADDR_OLAT 0x0A

// Global keystate structure, used by ui.
keystate_t keystate;

Rotary encoder = Rotary();

static void encTask(void *pvParameter);
TaskHandle_t encTaskHandle;

void keys_task_init(void)
{

    xTaskCreate(encTask, "enc", 1024, NULL, TASK_PRIORITY_KEYS, &encTaskHandle);
};

uint8_t writeI2C(uint8_t addr, uint8_t opcode, uint8_t data)
{
    // Exclusive use, so no Mutex.
    I2C_KEYS.beginTransmission(addr);
    I2C_KEYS.write(opcode);
    I2C_KEYS.write(data);
    return Wire.endTransmission();
}

uint8_t readI2C(uint8_t addr, uint8_t opcode)
{
    I2C_KEYS.beginTransmission(addr);
    I2C_KEYS.write(opcode);
    I2C_KEYS.endTransmission();
    I2C_KEYS.requestFrom(addr, 1);
    return I2C_KEYS.read();
}

static void ISR_KEYS()
    {
        BaseType_t taskWoken = pdFALSE;
        vTaskNotifyGiveFromISR(encTaskHandle, &taskWoken);
        //vTaskNotifyGiveFromISR(taskMeasureAndOutput, NULL);
        //portYIELD_FROM_ISR(taskWoken);
        //digitalWrite(PIN_TEST, LOW);
        //xSemaphoreGiveFromISR(adcReady, &taskWoken);
        //if (taskWoken != pdFALSE) {
        portYIELD_FROM_ISR(taskWoken);
        //}
    };


static void encTask(void *pvParameter)
{

    I2C_KEYS.setSCL(PIN_KEYS_SCL);
    I2C_KEYS.setSDA(PIN_KEYS_SDA);
    I2C_KEYS.setClock(400000);
    I2C_KEYS.begin();

    // MCP23008 defaults are fine..
    // TODO: Eanable interrupts.
    writeI2C(KEYS_CHIP_ADDRESS, MCP23X08_ADDR_GPINTEN, 255);

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
    dcl::setStateStruct localsetcopy;

    pinMode(PIN_KEYS_INT, INPUT);
    ::attachInterrupt(digitalPinToInterrupt(PIN_KEYS_INT), ISR_KEYS, FALLING);

    while (1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); 

        //digitalWrite(PIN_TEST, HIGH);
        gpioval = readI2C(KEYS_CHIP_ADDRESS, MCP23X08_ADDR_GPIO);
        encpin1 = gpioval & KEYS_PIN_ENC0 ? 1 : 0;
        encpin2 = gpioval & KEYS_PIN_ENC1 ? 1 : 0;
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
        keystate.encoderbutton = gpioval & KEYS_PIN_ENCBUT ? false : true ;

        keystate.button0 = gpioval & KEYS_PIN_BUT0 ? false : true ;
        keystate.button1 = gpioval & KEYS_PIN_BUT1 ? false : true ;
        keystate.button2 = gpioval & KEYS_PIN_BUT2 ? false : true ;
        keystate.button3 = gpioval & KEYS_PIN_BUT3 ? false : true ;

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
        vTaskDelay(4); // Debounce margin.
    }
}
