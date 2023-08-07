// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <FreeRTOS.h>
#include <semphr.h>

#include "util.h"

// In bytes, not words.
#define EEPROM_ADDR_MAGIC 0x00
#define EEPROM_ADDR_VERSION 0x08
#define EEPROM_ADDR_CAL_IMON 0x100
#define EEPROM_ADDR_CAL_UMON 0x200
#define EEPROM_ADDR_CAL_ISET 0x300
#define EEPROM_ADDR_CAL_USET 0x400
#define EEPROM_ADDR_CAL_VON 0x500
#define EEPROM_ADDR_CAL_OCP 0x600
#define EEPROM_ADDR_CAL_OVP 0x700

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
    uint8_t calibrationValuesWrite(CalibrationValueConfiguration *caldata, uint32_t startaddress);
    uint8_t calibrationValuesRead(CalibrationValueConfiguration *caldata, uint32_t startaddress);

private:
    TwoWire *_wire;
    uint8_t _addr;
    SemaphoreHandle_t _sem;

    uint16_t _capacity;
    uint16_t _pagesize;
};

}