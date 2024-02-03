// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>

#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <FreeRTOS.h>
#include <semphr.h>

#define MAX31760_DEVICE_ADDRESS 0xA0;

class fan_max31760
{
    public:
        enum PWMPolarity {
            PWM_POLARITY_POSITIVE = 0,
            PWM_POLARITY_NEGATIVE = 1
        };

        enum PWMFreq {
            PWM_FREQ_33HZ   = 0,
            PWM_FREQ_150HZ  = 1,
            PWM_FREQ_1500HZ = 2,
            PWM_FREQ_25KHZ  = 3
        };

        enum PWM_DC_Ramp {
            PWM_DC_RAMP_SLOW = 0,
            PWM_DC_RAMP_SLOW_MEDIUM = 1,
            PWM_DC_RAMP_MEDIUM_FAST = 2,
            PWM_DC_RAMP_FAST = 3
        };

        fan_max31760() {}; 
        void begin(TwoWire *Wire, SemaphoreHandle_t WireSemaphore, uint8_t Address);
        void reset();
        float readTempLocal();
        float readTempRemote();
        uint32_t readRPM();
        uint8_t getStatus();
        uint8_t setPWMFreq(PWMFreq freq);
        uint8_t setPWMPolarity(PWMPolarity setPWMPolarity);
        uint8_t setFanSpinUpEnable(bool spinup);
        uint8_t setDirectFanControl(bool dfc);
        uint8_t setPWM(uint8_t dutycycle);
        uint8_t clearFanFail();
        uint8_t setPWMDCRamp(PWM_DC_Ramp ramp);
        uint8_t setTachFull(bool enable);
        uint8_t setPulseStretch(bool enable);
        uint8_t enableTach1(bool enable);
        uint8_t enableTach2(bool enable);
        uint8_t setLUT(uint8_t lut, uint8_t value);
        uint8_t setFFDC(uint8_t dutycycle);
        uint8_t setTransistorIFR(uint8_t ifr);

    private:
        TwoWire *_wire;
        uint8_t _addr;
        SemaphoreHandle_t _sem;

        uint8_t readI2C(uint8_t reg);
        uint8_t writeI2C(uint8_t reg, uint8_t data);
        float tempRaw2Float(uint8_t msb, uint8_t lsb);

};

