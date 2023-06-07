#include "Arduino.h"
#include "SPI.h"
#include "main.h"
#include "util.h"
#include "adc.h"

using namespace dcl;

namespace dcl {


adc_MCP3202::adc_MCP3202(SPIClassRP2040 &selSPI, int CS, int myCh)
{
    spi = selSPI;
    chipSel = CS;
    channel = myCh;

    dataOut1 = 0b00000001;
    dataOut2 = (channel == 0) ? 0b10100000 : 0b11100000;

};

void adc_MCP3202::begin(bool setupSPI)
{
  pinMode(chipSel,OUTPUT);
  digitalWrite(chipSel, HIGH);


          if (setupSPI)
        {
        // Setup ADC SPI
        spi.setRX(SPI_ADC_RX);
        spi.setTX(SPI_ADC_TX);
        spi.setSCK(SPI_ADC_SCK);
        //SERIALDEBUG.println("INFO: ADC SPI.begin... done");

        spi.begin();
        //SERIALDEBUG.println("INFO: ADC SPI done");
        }

};

int32_t adc_MCP3202::readRaw()
{
  spi.beginTransaction(MCP3202_SPI_SETTINGS);
  digitalWrite(chipSel, LOW);
  dataIn1 = (uint32_t)spi.transfer(dataOut1);
  dataIn1 = (uint32_t)spi.transfer(dataOut2);
  dataIn2 = (uint32_t)spi.transfer(0x00);
  digitalWrite(chipSel, HIGH);
  spi.endTransaction();
  return (((dataIn1 & 0x0F) << 8) | dataIn2);
  }

adc_MCP3462::adc_MCP3462(SPIClassRP2040 &selSPI, int CS, int Interrupt, int myCh) 
{
    secondary = false;

    spi = selSPI;
    chipSel = CS;
    channel = myCh;

    mcp = MCP3462((uint8_t)CS, &selSPI); // mux mode for now


};

adc_MCP3462::adc_MCP3462(SPIClassRP2040 &selSPI, int CS, int myCh) 
{
    secondary = false;

    spi = selSPI;
    chipSel = CS;
    channel = myCh;

    mcp = MCP3462((uint8_t)CS, &selSPI); // mux mode for now
};

adc_MCP3462::adc_MCP3462(adc_MCP3462 *primary, int myCh) // secondary channels
{
    secondary = true;
    channel = myCh;
    primary_channel = primary;

};

void adc_MCP3462::begin(bool setupSPI)
{
if (!mcp.begin(0x03)) { // TOdo: fix mask stuff
    // failed to initialize
    while (1)
      ;
  }
};

int32_t adc_MCP3462::readRaw()
{
//    if (secondary) {
//        return (uint32_t)primary_channel->mcp.analogRead(channel);
//    } else {
        return (uint32_t)mcp.analogRead(channel);
//    }
};

adc_ADS131M02::adc_ADS131M02(SPIClassRP2040 &selSPI, int CS, int adc_clk, int adc_rdy)
{
    secondary = false;
    spi = selSPI;
    pin_chipSel = CS;
    channel = 0;
    pin_clk = adc_clk;
    pin_rdy = adc_rdy;


};

adc_ADS131M02::adc_ADS131M02(adc_ADS131M02 *primary, int myCh) // secondary channels
{
    secondary = true;
    channel = myCh;
    primary_channel = primary;

};

void adc_ADS131M02::begin(bool setupSPI) 
{
    if (secondary == false) {
        //SERIALDEBUG.println("INFO starting primairy ADC.");
        ads131 = new ads131xxx(spi, pin_chipSel, pin_clk, pin_rdy);
        ads131->begin(setupSPI);
    }
};

void adc_ADS131M02::attachInterrupt() 
{
    ads131->attachInterrupt();
};

int32_t adc_ADS131M02::readRaw() {
    if (secondary == false) {
        return ads131->readChannelsNow();
    } else {
        return primary_channel->ads131->lastSecondaryData();
    }
};

}