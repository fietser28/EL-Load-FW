// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef ADC_H
#define ADC_H

#include "SPI.h"
#include "adc_mcp3x6x.h"
#include "adc_ads131xxx.h"

#define MCP3202_SPI_SETTINGS SPISettings(5000000, MSBFIRST, SPI_MODE3)
//#define ADS131M02_SPI_SETTINGS SPISettings(5000000, MSBFIRST, SPI_MODE0)

namespace dcl {

// TODO: Fix make adc virtual, didn't work for linker somehow
class adc {
    public:
        void begin(bool setupSPI) {};
        int32_t readRaw() { return 0; };
        const uint32_t ADC_MIN = 0;
        const uint32_t ADC_MAX = 1; //Override in real class
};

class adc_MCP3202:  public  adc {
    public:
        adc_MCP3202(SPIClassRP2040 &selSPI, int CS, int myCh);
        void begin(bool setupSPI);
        //bool read();
        int32_t readRaw();
        const uint32_t ADC_MIN = 0;
        const uint32_t ADC_MAX = (1L << 12) - 1;

    private:
        SPIClassRP2040 &spi = SPI;
        int chipSel;
        int channel;

        uint32_t dataIn1;
        uint32_t dataIn2;
        uint32_t dataOut1;
        uint32_t dataOut2;
};

class adc_MCP3462: public  adc {
    public:
        adc_MCP3462(SPIClassRP2040 &selSPI, int CS, int Interrupt, int myCh);
        adc_MCP3462(SPIClassRP2040 &selSPI, int CS, int myCh);
        adc_MCP3462(adc_MCP3462 *primary, int myCh); // secondary channels
        void begin(bool setupSPI);
        int32_t readRaw();
        const uint32_t ADC_MIN = 0;
        const uint32_t ADC_MAX = (1L << 16) - 1;


    private:
        bool secondary;
        MCP3462 mcp;

        SPIClassRP2040 &spi = SPI;
        adc_MCP3462 *primary_channel;
        int chipSel;
        int channel;

};

class adc_ADS131M02: public adc {
    public:
        adc_ADS131M02(SPIClassRP2040 &selSPI, int CS, int adc_clk, int adc_rdy);
        adc_ADS131M02(adc_ADS131M02 *primary, int myCh); // secondary channel
        void begin(bool setupSPI);
        void attachInterrupt();
        int32_t readRaw();
        const uint32_t ADC_MIN = 0;
        const uint32_t ADC_MAX = (1L << 23) - 1;

    private:
        bool secondary;

        SPIClassRP2040 &spi = SPI;
        ads131xxx      *ads131;
        adc_ADS131M02  *primary_channel;
        int pin_chipSel;
        int channel;
        int pin_clk;
        int pin_rdy;
};

}

#endif