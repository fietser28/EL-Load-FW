// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <Arduino.h>
#include "FreeRTOS.h"
#include <Wire.h>
#include <semphr.h>

#include "eeprom.h"
#include "util.h"

// Only does 100kHz at 3.3V.
#define EEPROM_SPEED 100000

using namespace dcl;

namespace dcl::eeprom
{

    void eeprom::begin(TwoWire *Wire, SemaphoreHandle_t WireSemaphore, uint8_t Address,
                       uint16_t capacity, uint16_t pagesize)
    {
        _wire = Wire;
        _sem = WireSemaphore;
        _addr = Address;
    };

    uint8_t eeprom::write(uint32_t addr, uint8_t value)
    {
        if (_sem != NULL)
        {
            if (xSemaphoreTake(_sem, (TickType_t)100) == pdTRUE)
            {
                _wire->setClock(EEPROM_SPEED);
                _wire->beginTransmission(_addr);
                _wire->write((uint8_t)(addr >> 8));   // MSB part
                _wire->write((uint8_t)(addr & 0xff)); // LSB part
                _wire->write(value);
                uint8_t result = _wire->endTransmission(true);
                xSemaphoreGive(_sem);
                return result;
            }
            return 5; // timeout. Arduino-ish convention
        }
        return 4; // Arduino-ish convention
    }

    int16_t eeprom::read(uint32_t addr)
    {
        if (_sem != NULL)
        {
            if (xSemaphoreTake(_sem, (TickType_t)100) == pdTRUE)
            {
                _wire->setClock(EEPROM_SPEED);
                _wire->beginTransmission(_addr);
                _wire->write((uint8_t)(addr >> 8));
                _wire->write((uint8_t)(addr & 0xff));
                _wire->endTransmission();
                _wire->requestFrom(_addr, 1, false);
                uint8_t result = _wire->read();
                xSemaphoreGive(_sem);
                return result;
            }
        }
        return -1; // TODO: proper error handling?
    }

    bool eeprom::magicDetect()
    {
        bool magicok = true;
        for (int i = 0; i < sizeof(eeprom_magic) / sizeof(eeprom_magic[0]); i++)
        {
            if (eeprom_magic[i] != read(EEPROM_ADDR_MAGIC + i))
            {
                magicok = false;
                break;
            }
        }
        return magicok;
    }

    bool eeprom::magicWrite()
    {
        for (int i = 0; i < sizeof(eeprom_magic) / sizeof(eeprom_magic[0]); i++)
        {
            write(EEPROM_ADDR_MAGIC + i, eeprom_magic[i]);
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
        // TODO: error checking and reporting.
        return 0;
    };

CalibrationValueConfiguration testdata;

    uint8_t eeprom::calibrationValuesWrite(CalibrationValueConfiguration *caldata, uint32_t startaddress)
    {
        uint8_t *src = (uint8_t *)caldata;
        for (int i = 0; i < sizeof(CalibrationValueConfiguration); i++)
        {
            write(startaddress + i, *(src++));
            vTaskDelay(20/ portTICK_PERIOD_MS);
        }

        // TODO: Remove this test.
        vTaskDelay(50);
        calibrationValuesRead(&testdata, startaddress);
        // TODO: Implement validation run (read and compare)
        return 0;
    };

    uint8_t eeprom::calibrationValuesRead(CalibrationValueConfiguration *caldata, uint32_t startaddress)
    {
        uint8_t *dst = (uint8_t *)caldata;
        for (int i = 0; i < sizeof(CalibrationValueConfiguration); i++)
        {
            *(dst++) = read(startaddress + i);
        }
        // TODO: Implement validation run (=read twice and compare)
        return 0;
    };

}