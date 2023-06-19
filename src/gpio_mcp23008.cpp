
#include <Arduino.h>
#include <Wire.h>
#include <FreeRTOS.h>
#include <semphr.h>

#include "gpio_mcp23008.h"

#define MCP23008_SPEED 400000

void gpio_mcp23008::begin(TwoWire *Wire, SemaphoreHandle_t WireSemaphore, uint8_t Address)
{
    _wire = Wire;
    _sem = WireSemaphore;
    _addr = Address;
    reset();
};

void gpio_mcp23008::reset()
{
    // Set default POR/RST values (in case reset pin is not connected/used).
    writeI2C(MCP23x08_ADDR_IODIR, 0xff);
    // All other registers default to 0x00.
    // Not the fastest way but it works.
    for (int i = 1; i <= MCP23X08_ADDR_LAST; i++)
    {
        writeI2C(i, 0x00);
        _regs[i] = 0x00;
    }
};

uint8_t gpio_mcp23008::digitalRead()
{
    return readI2C(MCP23X08_ADDR_GPIO);
};

uint8_t gpio_mcp23008::digitalWrites(uint8_t values)
{
    return writeI2C(MCP23X08_ADDR_OLAT, values);
}

uint8_t gpio_mcp23008::digitalWrite(uint8_t pin, bool value)
{
    return digitalWrites((_regs[MCP23X08_ADDR_OLAT] &  ~(1 << pin)) | (value << pin));
}

uint8_t gpio_mcp23008::pinModes(uint8_t pins)
{
    return writeI2C(MCP23x08_ADDR_IODIR, pins);
}

uint8_t gpio_mcp23008::pinMode(uint8_t pin, bool input) 
{
    return pinModes(_regs[MCP23x08_ADDR_IODIR] | (input << pin));
}

uint8_t gpio_mcp23008::pinInterrupts(uint8_t enable, uint8_t onValue, uint8_t compValue)
{
    uint8_t result = writeI2C(MCP23X08_ADDR_DEFVAL, compValue);
    result = result || writeI2C(MCP23X08_ADDR_INTCON, onValue);
    return result || writeI2C(MCP23X08_ADDR_GPINTEN, enable);
}

uint8_t gpio_mcp23008::pinInterrupt(uint8_t pin, bool enable, bool onValue, bool compValue)
{
    return pinInterrupts(_regs[MCP23X08_ADDR_GPINTEN] | (enable << pin), 
                         _regs[MCP23X08_ADDR_IOCON] | (onValue << pin), 
                         _regs[MCP23X08_ADDR_DEFVAL] | ( compValue << pin));
}

uint8_t gpio_mcp23008::writeI2C(uint8_t opcode, uint8_t data)
{
    if (_sem != NULL)
    {
        if (xSemaphoreTake(_sem, (TickType_t)100) == pdTRUE)
        {
            _wire->setClock(MCP23008_SPEED);
            _wire->beginTransmission(_addr);
            _wire->write(opcode);
            _wire->write(data);
            uint8_t result = _wire->endTransmission(true);
            xSemaphoreGive(_sem);
            if (result == 0) {
                _regs[opcode] = data;
            }
            return result;
        }
        return 5; // timeout. Arduino-ish convention
    }
    return 4; // Arduino-ish convention
}

uint8_t gpio_mcp23008::readI2C(uint8_t opcode)
{
    if (_sem != NULL)
    {
        if (xSemaphoreTake(_sem, (TickType_t)100) == pdTRUE)
        {
            _wire->setClock(MCP23008_SPEED);
            _wire->beginTransmission(_addr);
            _wire->write(opcode);
            _wire->endTransmission();
            _wire->requestFrom(_addr, 1);
            uint8_t result = _wire->read();
            xSemaphoreGive(_sem);
            _regs[opcode] = result;
            return result;
        }
    }
    return 0; // TODO: proper error handling?
}