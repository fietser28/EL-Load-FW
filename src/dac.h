#pragma once
#ifndef DAC_H
#define DAC_H

#include "SPI.h"

namespace dcl
{

    class dac
    {
    public:
        virtual void begin(bool setupSPI) = 0;
        virtual bool write(uint32_t data) = 0;
        const uint32_t DAC_MIN = 0;
        const uint32_t DAC_MAX = 1; // Override in real class
    };

    class dac_dac8555 : public dac
    {
    public:
        dac_dac8555(SPIClassRP2040 &selSPI, uint8_t CS, uint8_t mychannel);
        void begin(bool setupSPI);
        bool write(uint32_t data);
        const uint32_t DAC_MIN = 0;
        const uint32_t DAC_MAX = (1L << 16) - 1;

    private:
        SPIClassRP2040 &spi = SPI;
        int pin_chipSel;
        int channelBits;
    };

}

#endif
