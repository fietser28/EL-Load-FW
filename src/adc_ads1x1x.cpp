#include "adc_ads1x1x.h"
#include "main.h"
#include "Arduino.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Wire.h"

// Wire speed
#define ADC_ADS1X1X_WIRE_SPEED      (400000)

// Registers
#define ADC_ADS1X1X_REG_CONVERSION   0x00
#define ADC_ADS1X1X_REG_CONFIG       0x01
#define ADC_ADS1X1X_REG_LOW_TRESH    0x02   // TODO: implement
#define ADC_ADS1X1X_REG_HIGH_TRESH   0x03   // TODO: implement

// Config register parts
#define ADC_ADS1X1X_CONFIG_OS        0x8000
#define ADC_ADS1X1X_CONFIG_MUX       0x7000
#define ADC_ADS1X1X_CONFIG_PGA       0x0E00
#define ADC_ADS1X1X_CONFIG_MODE      0x0100
#define ADC_ADS1X1X_CONFIG_DR        0x00E0
#define ADC_ADS1X1X_CONFIG_COMP_MODE 0x0010
#define ADC_ADS1X1X_CONFIG_COMP_POL  0x0008
#define ADC_ADS1X1X_CONFIG_COMP_LAT  0x8004
#define ADC_ADS1X1X_CONFIG_COMP_QUE  0x8003

#define ADC_ADS1X1X_CONFIG_RESET     0x8583

#define ADC_ADS1X1X_OS_START         0x8000  // write
#define ADC_ADS1X1X_OS_IDLE          0x8000  // read
#define ADC_ADS1X1X_OS_READY         0x8000  // read

// ADS111X - 16 bit
#define ADC_ADS111X_DR_8SPS          0x0000
#define ADC_ADS111X_DR_16SPS         0x0020
#define ADC_ADS111X_DR_32SPS         0x0040
#define ADC_ADS111X_DR_64SPS         0x0060
#define ADC_ADS111X_DR_128SPS        0x0080
#define ADC_ADS111X_DR_250SPS        0x00A0
#define ADC_ADS111X_DR_475SPS        0x00C0
#define ADC_ADS111X_DR_860SPS        0x00E0

// Comp stuff not implemented.

    void adc_ads1x1x::begin(TwoWire *Wire, SemaphoreHandle_t WireSemaphore, uint8_t Address)
    {
        _wire = Wire;
        _sem = WireSemaphore;
        _addr = Address;
        reset();
    };

    void adc_ads1x1x::reset() 
    {
        writeI2C(ADC_ADS1X1X_REG_CONFIG, ADC_ADS1X1X_CONFIG_RESET & ~ADC_ADS1X1X_CONFIG_OS); // Default with trigger cleared.

        // TODO: gain and mode are hardcoded.
        uint16_t newconfig = (_regs[ADC_ADS1X1X_REG_CONFIG] & ~ADC_ADS1X1X_CONFIG_PGA) | ADC_ADS1X1X_PGA_2_048V; // Default + gain
        newconfig = (newconfig  & ~ADC_ADS1X1X_CONFIG_MUX) | ADC_ADS1X1X_MUX_0_3; // select channel
        newconfig = (newconfig  & ~ADC_ADS1X1X_CONFIG_DR)  | ADC_ADS111X_DR_8SPS; // set datarate (incl. OSR)
        newconfig = (newconfig  & ~ADC_ADS1X1X_CONFIG_OS); // clear OS to avoid tigger.
        writeI2C(ADC_ADS1X1X_REG_CONFIG, newconfig );
    };    

    void adc_ads1x1x::startConversion(uint16_t channelconf) 
    {
        uint16_t newconfig = (_regs[ADC_ADS1X1X_REG_CONFIG] | ADC_ADS1X1X_OS_START);
        newconfig = (newconfig & ~ADC_ADS1X1X_CONFIG_MUX) | channelconf;
        writeI2C(ADC_ADS1X1X_REG_CONFIG, newconfig );
    };

    bool adc_ads1x1x::isReady() 
    {
        uint16_t result = readI2C(ADC_ADS1X1X_REG_CONFIG);
        return ((result & ADC_ADS1X1X_CONFIG_OS) == ADC_ADS1X1X_OS_READY);
    };

    int16_t adc_ads1x1x::getValue() 
    {
        return readI2C(ADC_ADS1X1X_REG_CONVERSION);
    };

    float adc_ads1x1x::toVoltage(int16_t rawValue)
    {
        if (rawValue == 0) { return 0; }

        float volt = 2.048f; //TODO: hardcoded 
        volt *= rawValue;
        volt /= 32767; // TODO: hardcoded 16-bits.
        return volt;
    }

uint8_t adc_ads1x1x::writeI2C(uint8_t opcode, uint16_t data)
{
    if (_sem != NULL)
    {
        if (xSemaphoreTake(_sem, (TickType_t)100) == pdTRUE)
        {
            _wire->setClock(ADC_ADS1X1X_WIRE_SPEED);
            _wire->beginTransmission(_addr);
            _wire->write(opcode);
            _wire->write(data >> 8);   // MSB
            _wire->write(data & 0xFF); // LSB
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
};

uint16_t adc_ads1x1x::readI2C(uint8_t opcode)
{
    if (_sem != NULL)
    {
        if (xSemaphoreTake(_sem, (TickType_t)100) == pdTRUE)
        {
            _wire->setClock(ADC_ADS1X1X_WIRE_SPEED);
            _wire->beginTransmission(_addr);
            _wire->write(opcode);
            _wire->endTransmission();
            int rv = _wire->requestFrom((int) _addr, (int) 2);
            uint16_t result = _wire->read();
            result = result << 8;  // MSB
            result += _wire->read(); // add LSB
            xSemaphoreGive(_sem);
            //_regs[opcode] = result;
            return result;
        }
    }
    return 0; // TODO: proper error handling?
}

