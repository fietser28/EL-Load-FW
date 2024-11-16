// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <FreeRTOS.h>
#include <semphr.h>

#include "main.h"
#include "util.h"

// In bytes, not words.
#define EEPROM_ADDR_MAGIC 0x00
#define EEPROM_ADDR_VERSION 0x08
#define EEPROM_ADDR_CAL_IMON_H 0x100
#define EEPROM_ADDR_CAL_IMON_L 0x180
#define EEPROM_ADDR_CAL_UMON_H 0x200
#define EEPROM_ADDR_CAL_UMON_L 0x280
#define EEPROM_ADDR_CAL_ISET_H 0x300
#define EEPROM_ADDR_CAL_ISET_L 0x380
#define EEPROM_ADDR_CAL_USET_H 0x400
#define EEPROM_ADDR_CAL_USET_L 0x480
#define EEPROM_ADDR_CAL_VON_H 0x500
#define EEPROM_ADDR_CAL_VON_L 0x580
#define EEPROM_ADDR_CAL_OCP_H 0x600
#define EEPROM_ADDR_CAL_OCP_L 0x680
#define EEPROM_ADDR_CAL_OVP_H 0x700
#define EEPROM_ADDR_CAL_OVP_L 0x780

namespace dcl::eeprom
{

const uint8_t eeprom_magic[] = {0x70, 0x61, 0x52, 0x43, 0x34, 0x25, 0x16, 0x07};
const uint8_t eeprom_version = 0x01;



class eeprom
{
public:
    eeprom(){};
    void begin(TwoWire *Wire, SemaphoreHandle_t WireSemaphore, uint8_t Address = 0x50,
               uint16_t capacity = 64, uint16_t pagesize = 32);
    uint8_t write(uint32_t addr, uint8_t value);
    // TODO: multibyte reads/writes.
    // uint8_t write(uint32_t addr, uint8_t* values, uint16_t size);
    int16_t read(uint32_t addr);
    // uint8_t read(uint32_t addr, uint8_t* values, uint16_t size);

    bool magicDetect();
    bool magicWrite();
    bool magicFound();
    bool fullWrite(uint8_t data);
    static void startFullWriteTask(void *pvParameters);
    void fullWriteTask(void *pvParameters);
    uint8_t calibrationValuesWrite(CalibrationValueConfiguration *caldata, uint32_t startaddress);
    uint8_t calibrationValuesRead(CalibrationValueConfiguration *caldata, uint32_t startaddress);

private:
    TwoWire *_wire;
    uint8_t _addr;
    SemaphoreHandle_t _sem;

    uint16_t _capacity;
    uint16_t _pagesize;

    bool _magicFound;

    SemaphoreHandle_t xSemEepromTask;
    TaskHandle_t xTaskEepromFullWrite;

};

}