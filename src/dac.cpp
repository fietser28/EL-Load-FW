#include "Arduino.h"
#include "FreeRTOS.h"
#include "main.h"
#include "dac.h"
#include "SPI.h"

namespace dcl
{


#define DAC8555_SPI_SETTINGS SPISettings(5000000, MSBFIRST, SPI_MODE1)
#define DAC8555_SINGLE_UPDATE 0x10

    dac_dac8555::dac_dac8555(SPIClassRP2040 &selSPI, uint8_t CS, uint8_t channel)
    {
        spi = selSPI;
        pin_chipSel = CS;
        channelBits = (channel & 0x03) << 1;
    };

    void dac_dac8555::begin(bool setupSPI)
    {
        pinMode(pin_chipSel, OUTPUT);
        digitalWrite(pin_chipSel, HIGH);

                if (setupSPI)
        {
          // Setup ADC SPI
        spi.setRX(SPI_ADC_RX);
        spi.setTX(SPI_ADC_TX);
        spi.setSCK(SPI_ADC_SCK);
        
        spi.begin();
        }

        // Defaults are fine. Otherwise output it here.
    };

    bool dac_dac8555::write(uint32_t data)
    {
        spi.beginTransaction(DAC8555_SPI_SETTINGS);
        digitalWrite(pin_chipSel, LOW);
        uint8_t configRegister = DAC8555_SINGLE_UPDATE | channelBits;
        spi.transfer(configRegister);
        spi.transfer(data >> 8);
        spi.transfer(data & 0xFF);
        digitalWrite(pin_chipSel, HIGH);
        spi.endTransaction();
        return true; // No error checking.
    };

}
