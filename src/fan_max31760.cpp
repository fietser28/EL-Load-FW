// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>

#include <Arduino.h>
#include <Wire.h>
#include <FreeRTOS.h>
#include <semphr.h>

#include "fan_max31760.h"

#ifndef FAN_TACH_PULS_PER_REVOLUTION
#define FAN_TACH_PULS_PER_REVOLUTION 2
#endif

#define MAX31760_I2C_SPEED 400000

// R/W registers
#define MAX31760_ADDR_CR1   0x00
#define MAX31760_ADDR_CR2   0x01
#define MAX31760_ADDR_CR3   0x02
#define MAX31760_ADDR_FFDC  0x03
#define MAX31760_ADDR_MASK  0x04
#define MAX31760_ADDR_IFR   0x05
#define MAX31760_ADDR_RHSH  0x06
#define MAX31760_ADDR_RHSL  0x07
#define MAX31760_ADDR_LOTSH 0x08
#define MAX31760_ADDR_LOTSL 0x09
#define MAX31760_ADDR_ROTSH 0x0A
#define MAX31760_ADDR_ROTSL 0x0B
#define MAX31760_ADDR_LHSH  0x0C
#define MAX31760_ADDR_LHSL  0x0D
#define MAX31760_ADDR_TCTH  0x0E
#define MAX31760_ADDR_TCTL  0x0F

// User memory registers
// not implemented. Ues case?

// LUT registers. 48 regsters starting from base (0x20 - 0x4F)
#define MAX31760_ADDR_LUT_BASE  0x20   

#define MAX31760_ADDR_PWMR  0x50
#define MAX31760_ADDR_PWMV  0x51
#define MAX31760_ADDR_TC1H  0x52
#define MAX31760_ADDR_TC1L  0x53
#define MAX31760_ADDR_TC2H  0x54
#define MAX31760_ADDR_TC2L  0x55
#define MAX31760_ADDR_RTH   0x56
#define MAX31760_ADDR_RTL   0x57
#define MAX31760_ADDR_LTH   0x58
#define MAX31760_ADDR_LTL   0x59
#define MAX31760_ADDR_SR    0x5A
#define MAX31760_ADDR_EEX   0x5B

// CR1 bits
#define MAX31760_BIT_PPS    2
#define MAX31760_BIT_DRV    3
#define MAX31760_BIT_POR    6

// CR2 bits
#define MAX31760_BIT_DFC    0
#define MAX31760_BIT_FSST   1
#define MAX31760_BIT_SPEN   5
#define MAX31760_BIT_STBY   7

// CR3 bits
#define MAX31760_BIT_TACH1E   0
#define MAX31760_BIT_TACH2E   1
#define MAX31760_BIT_PSEN     2
#define MAX31760_BIT_TACHFULL 3
#define MAX31760_BIT_RAMP     4

#define MAX31760_TEMP_RESOLUTION 0.125f

void fan_max31760::begin(TwoWire *Wire, SemaphoreHandle_t WireSemaphore, uint8_t Address)
{
    _wire = Wire;
    _sem = WireSemaphore;
    _addr = Address;
    reset();
};

void fan_max31760::reset()
{
    writeI2C(MAX31760_ADDR_CR1, 1 << MAX31760_BIT_POR);
};

float fan_max31760::tempRaw2Float(uint8_t msb, uint8_t lsb) 
{
    // 7 bits of MSB + 8 bits of LSB, shift left 5, multiplied by resolution. Results in unsigned value
    //uint16_t raw = ((((uint16_t)msb | 0x7F) << 3) | (lsb >> 5));
    float temp = (int8_t)msb + (lsb >> 5) * MAX31760_TEMP_RESOLUTION;
    // Apply sign
    if ((msb & 0x80) != 0x00 ) {
        temp = -temp;
    }
    return temp;
}

float fan_max31760::readTempLocal()
{
    uint8_t temp_msb = readI2C(MAX31760_ADDR_LTH);
    uint8_t temp_lsb = readI2C(MAX31760_ADDR_LTL);
    return tempRaw2Float(temp_msb, temp_lsb);
};

float fan_max31760::readTempRemote()
{
    uint8_t temp_msb = readI2C(MAX31760_ADDR_RTH);
    uint8_t temp_lsb = readI2C(MAX31760_ADDR_RTL);
    return tempRaw2Float(temp_msb, temp_lsb);
};

uint32_t fan_max31760::readRPM()
{
    uint8_t tch = readI2C(MAX31760_ADDR_TC1H);
    uint8_t tcl = readI2C(MAX31760_ADDR_TC1L);
    
    uint32_t rpm = (60*100000/FAN_TACH_PULS_PER_REVOLUTION)/(tch * 256 + tcl);
    return rpm < 60 ? 0 : rpm;
};

uint8_t fan_max31760::getStatus()
{
    return readI2C(MAX31760_ADDR_SR);
};

uint8_t fan_max31760::setPWMFreq(PWMFreq freq)
{
    uint8_t cr1 = readI2C(MAX31760_ADDR_CR1);
    return writeI2C(MAX31760_ADDR_CR1, (cr1 & 0b11100111) | (freq << MAX31760_BIT_DRV) );
};

uint8_t fan_max31760::setPWMPolarity(PWMPolarity setPWMPolarity)
{
    uint8_t cr1 = readI2C(MAX31760_ADDR_CR1);
    return writeI2C(MAX31760_ADDR_CR1, (cr1 & 0b11111011) | (setPWMPolarity << MAX31760_BIT_PPS) );
};

uint8_t fan_max31760::setFanSpinUpEnable(bool spinup)
{
    uint8_t cr2 = readI2C(MAX31760_ADDR_CR2);
    return writeI2C(MAX31760_ADDR_CR2, (cr2 & 0b11011111) | ((uint8_t)spinup << MAX31760_BIT_SPEN) );
};

uint8_t fan_max31760::setDirectFanControl(bool dfc)
{
    uint8_t cr2 = readI2C(MAX31760_ADDR_CR2);
    return writeI2C(MAX31760_ADDR_CR2, (cr2 & 0b11111110) | ((uint8_t)dfc << MAX31760_BIT_DFC) );
};

uint8_t fan_max31760::clearFanFail()
{
    uint8_t cr3 = readI2C(MAX31760_ADDR_CR3);
    return writeI2C(MAX31760_ADDR_CR3, cr3 |0b10000000 );
};

uint8_t fan_max31760::setPWMDCRamp(PWM_DC_Ramp ramp)
{
    uint8_t cr3 = readI2C(MAX31760_ADDR_CR3);
    return writeI2C(MAX31760_ADDR_CR3, (cr3 & 0b11001111) | (ramp << MAX31760_BIT_RAMP) );
};

uint8_t fan_max31760::setTachFull(bool enable)
{
    uint8_t cr3 = readI2C(MAX31760_ADDR_CR3);
    return writeI2C(MAX31760_ADDR_CR3, (cr3 & 0b11110111) | ((uint8_t)enable << MAX31760_BIT_TACHFULL) );
};

uint8_t fan_max31760::setPulseStretch(bool enable)
{
    uint8_t cr3 = readI2C(MAX31760_ADDR_CR3);
    return writeI2C(MAX31760_ADDR_CR3, (cr3 & 0b11111011) | ((uint8_t)enable << MAX31760_BIT_PSEN) );
};


uint8_t fan_max31760::enableTach1(bool enable)
{
    uint8_t cr3 = readI2C(MAX31760_ADDR_CR3);
    return writeI2C(MAX31760_ADDR_CR3, (cr3 & 0b11111101) | ((uint8_t)enable << MAX31760_BIT_TACH1E) );
};

uint8_t fan_max31760::enableTach2(bool enable)
{
    uint8_t cr3 = readI2C(MAX31760_ADDR_CR3);
    return writeI2C(MAX31760_ADDR_CR3, (cr3 & 0b11111110) | ((uint8_t)enable << MAX31760_BIT_TACH2E) );
};

uint8_t fan_max31760::setPWM(uint8_t dutycycle)
{
    return writeI2C(MAX31760_ADDR_PWMR, dutycycle);
};

uint8_t fan_max31760::setLUT(uint8_t lut, uint8_t value)
{
    return writeI2C(MAX31760_ADDR_LUT_BASE + lut, value);
};

uint8_t fan_max31760::setFFDC(uint8_t dutycycle)
{
    return writeI2C(MAX31760_ADDR_FFDC, dutycycle);
};


uint8_t fan_max31760::writeI2C(uint8_t opcode, uint8_t data)
{
    if (_sem != NULL)
    {
        if (xSemaphoreTake(_sem, (TickType_t)500) == pdTRUE)
        {
            _wire->setClock(MAX31760_I2C_SPEED);
            _wire->beginTransmission(_addr);
            _wire->write(opcode);
            _wire->write(data);
            uint8_t result = _wire->endTransmission(true);
            xSemaphoreGive(_sem);
            return result;
        }
        return 5; // timeout. Arduino-ish convention
    }
    return 4; // Arduino-ish convention
}

uint8_t fan_max31760::readI2C(uint8_t opcode)
{
    if (_sem != NULL)
    {
        if (xSemaphoreTake(_sem, (TickType_t)500) == pdTRUE)
        {
            _wire->setClock(MAX31760_I2C_SPEED);
            _wire->beginTransmission(_addr);
            _wire->write(opcode);
            _wire->endTransmission();
            _wire->requestFrom(_addr, 1);
            uint8_t result = _wire->read();
            xSemaphoreGive(_sem);
            return result;
        }
    }
    return 0; // TODO: proper error handling?
}