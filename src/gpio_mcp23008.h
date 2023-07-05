#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <FreeRTOS.h>
#include <semphr.h>
//#include <task.h>

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

#define MCP23X08_ADDR_LAST 0x0A

class gpio_mcp23008
{
    public:
        gpio_mcp23008() {}; 
        void begin(TwoWire *Wire, SemaphoreHandle_t WireSemaphore, uint8_t Address);
        void reset();
        uint8_t digitalRead();
        uint8_t interruptFlagged();
        uint8_t digitalWrites(uint8_t values);
        uint8_t digitalWrite(uint8_t pin, bool value);
        uint8_t pinModes(uint8_t pins);
        uint8_t pinMode(uint8_t pin, bool mode);
        uint8_t pinInterrupts(uint8_t enable, uint8_t onValue, uint8_t compValue);
        uint8_t pinInterrupt(uint8_t pin, bool enable, bool onValue, bool compValue);

    private:
        TwoWire *_wire;
        uint8_t _addr;
        SemaphoreHandle_t _sem;

        // chip registers 
        uint8_t _regs[MCP23X08_ADDR_LAST];

        uint8_t readI2C(uint8_t opcode);
        uint8_t writeI2C(uint8_t opcode, uint8_t data);

};

