// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <Arduino.h>
#include "FreeRTOS.h"
#include <Wire.h>
#include <semphr.h>

#include "main.h"
#include "scpi-def.h"
//#include "eeprom.h"
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
        _magicFound = false;

        xTaskEepromFullWrite = NULL;
        xSemEepromTask = xSemaphoreCreateBinary();
        xSemaphoreGive(xSemEepromTask);
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
        _magicFound = magicok;
        return magicok;
    }

    bool eeprom::magicWrite()
    {
        for (int i = 0; i < sizeof(eeprom_magic) / sizeof(eeprom_magic[0]); i++)
        {
            write(EEPROM_ADDR_MAGIC + i, eeprom_magic[i]);
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }

        write(EEPROM_ADDR_VERSION, dcl::eeprom::eeprom_version);
        vTaskDelay(5 / portTICK_PERIOD_MS);

        // And try to read it back as a test....
        return magicDetect();
    };

    bool eeprom::magicFound() { return _magicFound; };

    bool eeprom::fullWrite(uint8_t data) 
    {
        if (xSemEepromTask != NULL) 
        {
            if (xSemaphoreTake(xSemEepromTask, 500 / portTICK_PERIOD_MS)) 
            //if (xTaskEepromFullWrite != NULL)
            {
                BaseType_t xTaskRet;
                xTaskRet = xTaskCreate(this->startFullWriteTask, "", 1024, this, TASK_PRIORITY_EEPROM, &xTaskEepromFullWrite);
                //xSemaphoreGive(xSemEepromTask);
                if (xTaskRet != pdPASS) 
                { // TODO: reset, something is really wrong;
                    SERIALDEBUG.println("ERROR: Error starting EEPROM task.");
                    return false;
                }
                SERIALDEBUG.print("3");
                return true;
            } else {
                SERIALDEBUG.println("ERROR: EEprom task already/still running.....");
                return false;
            }
            //}
        }
        return false;
    };

    void eeprom::startFullWriteTask(void *pvParameters)
    {
        SERIALDEBUG.print("1");
        ((eeprom*)pvParameters)->fullWriteTask(pvParameters);
    };

    void eeprom::fullWriteTask(void *pvParameters) {
        dcl::scpi::scpi_busy_inc();
        SERIALDEBUG.print("2");
        for (int i = 0; i < EEPROM_SIZE; i++)
        {
            write(i, 0xff);
            vTaskDelay(5 / portTICK_PERIOD_MS);
            if (read(i) != 0xff) {
                SERIALDEBUG.printf("ERROR: eeprom full write failed at %x.\n",i);
                //return;
            }
        }
        SERIALDEBUG.print("done");
        dcl::scpi::scpi_busy_dec(); 
        xSemaphoreGive(xSemEepromTask);            
        vTaskDelete(xTaskEepromFullWrite);
        while (true) { vTaskDelay(1000); };
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