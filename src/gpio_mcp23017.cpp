// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <Arduino.h>
#include <Wire.h>
#include <FreeRTOS.h>
#include <semphr.h>

#include "gpio_mcp23017.h"

#define MCP23017_SPEED 400000

void gpio_mcp23017::begin(TwoWire *Wire, SemaphoreHandle_t WireSemaphore, uint8_t Address)
{
    _wire = Wire;
    _sem = WireSemaphore;
    _addr = Address;
    reset();
};

void gpio_mcp23017::reset()
{
    // First Set bank mode to 1 and combine interrupt pins
    writeI2C(MCP23X17_ADDR_NOBANK_IOCON, 0xC0);   // First switch to BANK mode.
    _regs[0][MCP23X17_ADDR_IOCON] = 0xC0;
    _regs[1][MCP23X17_ADDR_IOCON] = 0xC0;

    // Set default POR/RST values (in case reset pin is not connected/used).
    writeI2C(MCP23X17_BANKA | MCP23X17_ADDR_IODIR, 0xff);
    _regs[0][MCP23X17_ADDR_IODIR] = 0xff;

    writeI2C(MCP23X17_BANKB | MCP23X17_ADDR_IODIR, 0xff);
    _regs[1][MCP23X17_ADDR_IODIR] = 0xff;
    // All other registers default to 0x00, except for IOCON!
    // Not the fastest way but it works.
    for (int i = 1; i <= MCP23X17_ADDR_LAST; i++)
    {
        // Skip IOCON
        if (i != MCP23X17_ADDR_IOCON) {
            writeI2C(MCP23X17_BANKA | i, 0x00);
            _regs[0][i] = 0x00;
            writeI2C(MCP23X17_BANKB | i, 0x00);
            _regs[1][i] = 0x00;
        }
    }
};

uint8_t gpio_mcp23017::digitalRead(uint8_t bank)
{
    return readI2C(bank | MCP23X17_ADDR_GPIO);
};

uint8_t gpio_mcp23017::interruptFlagged(uint8_t bank)
{
    return readI2C(bank | MCP23X17_ADDR_INTF);
};

uint8_t gpio_mcp23017::digitalWrites(uint8_t bank, uint8_t values)
{
    return writeI2C(bank | MCP23X17_ADDR_OLAT, values);
}

uint8_t gpio_mcp23017::digitalWrite(uint8_t bank, uint8_t pin, bool value)
{
    return digitalWrites(bank, (_regs[bank == MCP23X17_BANKB][MCP23X17_ADDR_OLAT] &  ~(1 << pin)) | (value << pin));
}

uint8_t gpio_mcp23017::digitalWrite(uint8_t pin, bool value)
{
    return digitalWrite(pin < 8 ? 0x00 : 0x10, pin < 8 ? pin : pin - 8, value);
}

uint8_t gpio_mcp23017::pinModes(uint8_t bank, uint8_t pins)
{
    return writeI2C(bank | MCP23X17_ADDR_IODIR, pins);
}

uint8_t gpio_mcp23017::pinMode(uint8_t bank, uint8_t pin, bool input) 
{
    return pinModes(bank, _regs[bank == MCP23X17_BANKB][MCP23X17_ADDR_IODIR] | (input << pin));
}

uint8_t gpio_mcp23017::pinInterrupts(uint8_t bank, uint8_t enable, uint8_t onValue, uint8_t compValue)
{
    uint8_t result = writeI2C(bank | MCP23X17_ADDR_DEFVAL, compValue);
    result = result || writeI2C(bank | MCP23X17_ADDR_INTCON, onValue);
    return result || writeI2C(bank | MCP23X17_ADDR_GPINTEN, enable);
}

uint8_t gpio_mcp23017::pinInterrupt(uint8_t bank, uint8_t pin, bool enable, bool onValue, bool compValue)
{
    return pinInterrupts(bank, _regs[bank == MCP23X17_BANKB][MCP23X17_ADDR_GPINTEN] | (enable << pin), 
                         _regs[bank == MCP23X17_BANKB][MCP23X17_ADDR_IOCON] | (onValue << pin), 
                         _regs[bank == MCP23X17_BANKB][MCP23X17_ADDR_DEFVAL] | ( compValue << pin));
}

uint8_t gpio_mcp23017::writeI2C(uint8_t opcode, uint8_t data)
{
    if (_sem != NULL)
    {
        if (xSemaphoreTake(_sem, (TickType_t)100) == pdTRUE)
        {
            _wire->setClock(MCP23017_SPEED);
            _wire->beginTransmission(_addr);
            _wire->write(opcode);
            _wire->write(data);
            uint8_t result = _wire->endTransmission(true);
            xSemaphoreGive(_sem);
            if (result == 0) {
                _regs[(opcode & 0x10) == MCP23X17_BANKB][opcode] = data;
            }
            return result;
        }
        return 5; // timeout. Arduino-ish convention
    }
    return 4; // Arduino-ish convention
}

uint8_t gpio_mcp23017::readI2C(uint8_t opcode)
{
    if (_sem != NULL)
    {
        if (xSemaphoreTake(_sem, (TickType_t)100) == pdTRUE)
        {
            _wire->setClock(MCP23017_SPEED);
            _wire->beginTransmission(_addr);
            _wire->write(opcode);
            _wire->endTransmission();
            _wire->requestFrom(_addr, 1);
            uint8_t result = _wire->read();
            xSemaphoreGive(_sem);
            _regs[(opcode & 0x10) == MCP23X17_BANKB][opcode] = result;
            return result;
        }
    }
    return 0; // TODO: proper error handling?
}