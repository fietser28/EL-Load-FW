#include "adc_ads131xxx.h"
#include "main.h"
#include "Arduino.h"
#include "FreeRTOS.h"
#include "task.h"
#include "SPI.h"

namespace dcl
{

    ads131xxx::ads131xxx(SPIClassRP2040 &selSPI, int CS, int adc_clk, int adc_rdy)
    {

        _spi = selSPI;
        _pinCS = CS;
        _pinCLK = adc_clk;
        _pinRDY = adc_rdy;

    };

    bool ads131xxx::begin(bool setupSPI)
    {
        //SERIALDEBUG.println("INFO: Setup ADC131M02....");


        // Setup SPI
        pinMode(_pinCS, OUTPUT);
        digitalWrite(_pinCS, HIGH);

        if (setupSPI)
        {
          // Setup ADC SPI
        _spi.setRX(SPI_ADC_RX);
        _spi.setTX(SPI_ADC_TX);
        _spi.setSCK(SPI_ADC_SCK);
        //SERIALDEBUG.println("INFO: ADC SPI.begin... done");

        _spi.begin();
        //SERIALDEBUG.println("INFO: ADC SPI done");
        }

        // Setup ouput clock to ADC, ready pin.
        pinMode(_pinRDY, INPUT); // TODO: Change to floating on final PCB, for testing this avoids spurios triggers if unconnected

        pinMode(_pinCLK, OUTPUT);
        clock_gpio_init(_pinCLK, 0, CLOCK_DIVIDER_ADC); // Output system_clk/15 on ADC_CLK pin = 8,2MHz @ 123MHz clock speed.
        //clock_gpio_init(_pinCLK, 0, 7); // Output system_clk/15 on ADC_CLK pin = 8,2MHz @ 123MHz clock speed.
        //clock_gpio_init(_pinCLK, 0, 246); // Output system_clk/15 on ADC_CLK pin = 8,2MHz @ 123MHz clock speed.
        //clock_gpio_init(_pinCLK, 0, 123); // Output system_clk/15 on ADC_CLK pin = 8,2MHz @ 123MHz clock speed.
    
        //SERIALDEBUG.println("Waiting for ADC ready....");
        while(digitalRead(_pinRDY) == LOW) {}; // Wait for ADC to become ready
        
        // Reset
        uint32_t responseArr[6];
        bool resetOK = false;
        uint16_t resetAttempts = 0;
        while (!resetOK)
        {
            //Send reset
            bool crcok = spiCommFrame(&responseArr[0], ADC_ADS131XXX_CMD_RESET );
            delay(5);
            // Read response
            crcok = spiCommFrame(&responseArr[0], ADC_ADS131XXX_CMD_NULL);
            delay(5);
            resetAttempts++;
            if (crcok && responseArr[0] == 0xff220000)
            {
                resetOK = true;
                //SERIALDEBUG.printf("INFO: ADC reset in %d attempts.\n",resetAttempts);
            };
        }

        // Detect chip
        if ((_readreg(ADC_ADS131XXX_ADR_ID) & 0xFF00) != ADC_ADS131X02_DEFAULT_ID) {
            SERIALDEBUG.println("FATAL: ADC not detected!");
            SERIALDEBUG.printf("Read ID: %x\n", _readreg(ADC_ADS131XXX_ADR_ID) & 0xFF00);
        } else {
            //SERIALDEBUG.println("INFO: ADC detected.");
        }

        // Disable channels, allow setup?
        reg_clock regclk;
        regclk.raw = ADC_ADS131XXX_DEFAULT_CLOCK;
        regclk.ch0_en = false;
        regclk.ch1_en = false;
        _writereg(ADC_ADS131XXX_ADR_CLOCK, regclk.raw);
        //SERIALDEBUG.printf("\nRead clock reg: %x\n", _readreg(ADC_ADS131XXX_ADR_CLOCK));

        // Set OSR
        //reg_clock regclk;
        //regclk.raw = ADC_ADS131XXX_DEFAULT_CLOCK;
        if (ADC_OSR == 2048) 
        {
            regclk.osr = osr_types::osr2048;
        } else {
            regclk.osr = osr_types::osr4096;
        }

        //SERIALDEBUG.printf("Write clock: %x\n", regclk.raw);
        _writereg(ADC_ADS131XXX_ADR_CLOCK, regclk.raw);
        
        //SERIALDEBUG.printf("Read  clock: %x\n", _readreg(ADC_ADS131XXX_ADR_CLOCK));

/*
        reg_mode regmode;
        regmode.raw = ADC_ADS131XXX_DEFAULT_MODE;
        regmode.drdy_fmt = true;
        SERIALDEBUG.printf("\nWrite mode: %x\n", regmode.raw);
        _writereg(ADC_ADS131XXX_ADR_MODE, regmode.raw);
        SERIALDEBUG.printf("Read  mode: %x\n", _readreg(ADC_ADS131XXX_ADR_MODE));
*/
/*
        // Enable global chop mode
        reg_cfg regcfg;
        regcfg.raw = ADC_ADS131XXX_DEFAULT_CFG;
        regcfg.gc_en = false;
        //regcfg.gc_dly = gc_delays::dly65535;

        SERIALDEBUG.printf("\nWrite cfg: %x\n", regcfg.raw);
        _writereg(ADC_ADS131XXX_ADR_CFG, regcfg.raw);
        SERIALDEBUG.printf("Read  cfg: %x\n", _readreg(ADC_ADS131XXX_ADR_CFG));
*/
        
        reg_gain1 reggain1;
        reggain1.raw = ADC_ADS131XXX_DEFAULT_GAIN;
        //reggain1.pgagain0 = again::again2;
        //SERIALDEBUG.printf("\nWrite  mode: %x\n", reggain1.raw);
        _writereg(ADC_ADS131XXX_ADR_GAIN, reggain1.raw);
        //SERIALDEBUG.printf("Read mode reg: %x\n\n", _readreg(ADC_ADS131XXX_ADR_GAIN));

        // Enable channels....  
        regclk.ch0_en = true;
        regclk.ch1_en = true;
        _writereg(ADC_ADS131XXX_ADR_CLOCK, regclk.raw);
        //SERIALDEBUG.printf("Read  cfg: %x\n", _readreg(ADC_ADS131XXX_ADR_CFG));
        //SERIALDEBUG.printf("Read  clock: %x\n", _readreg(ADC_ADS131XXX_ADR_CLOCK));
        //SERIALDEBUG.printf("Read mode reg: %x\n\n", _readreg(ADC_ADS131XXX_ADR_GAIN));

        return true;
    };

    void ads131xxx::attachInterrupt() 
    {
        uint32_t responseArr[6];

        ::attachInterrupt(digitalPinToInterrupt(_pinRDY), ISR_ADC, FALLING);
        //SERIALDEBUG.println("INFO: ADS131xxx Interrrupt attached.");
        // Flush data
        spiCommFrame(&responseArr[0], ADC_ADS131XXX_CMD_NULL);
        spiCommFrame(&responseArr[0], ADC_ADS131XXX_CMD_NULL);
        //spiCommFrame(&responseArr[0], ADC_ADS131XXX_CMD_NULL);
    };

    /// Measure interrupt and measure and output task
    void __not_in_flash_func(ads131xxx::ISR_ADC())
    {
        //digitalWrite(PIN_TEST, HIGH); //TODO: Just for debugging
        // Just start a high priority task and force immediate context switch if task is available.
        BaseType_t taskWoken = pdFALSE;
        vTaskNotifyGiveFromISR(taskMeasureAndOutput, &taskWoken);
        //vTaskNotifyGiveFromISR(taskMeasureAndOutput, NULL);
        //portYIELD_FROM_ISR(taskWoken);
        //digitalWrite(PIN_TEST, LOW);
        //xSemaphoreGiveFromISR(adcReady, &taskWoken);
        //if (taskWoken != pdFALSE) {
        portYIELD_FROM_ISR(taskWoken);
        //}
    };

    uint8_t ads131xxx::_transfer(uint8_t *data, uint8_t addr, size_t size)
    {
        uint8_t result;
        _spi.beginTransaction(SPISettings(ADC_ADS131XXX_SPI_SPEED, ADC_ADS131XXX_SPI_ORDER, ADC_ADS131XXX_SPI_MODE));
        digitalWrite(_pinCS, LOW);
        result = _spi.transfer(addr);
        _spi.transfer(data, size);
        digitalWrite(_pinCS, HIGH);
        _spi.endTransaction();
        return result;
    }

    uint16_t ads131xxx::_readreg(uint16_t reg)
    { // Assuming 24bits words (default)

        // Command is 16 bits (zero padded)
        uint16_t commandWord = (ADC_ADS131XXX_CMD_RREG | (reg << 7));
        //SERIALDEBUG.printf("  _readreg cmd: %x\n", commandWord);

        uint32_t responseArr[6];

        // Use first frame to send command
        spiCommFrame(&responseArr[0], commandWord);

        //while(digitalRead(_pinRDY) == HIGH) {}; // Wait for ADC to become ready
        sleep_us(5);

        // Read response
        spiCommFrame(&responseArr[0], ADC_ADS131XXX_CMD_NULL);

        //SERIALDEBUG.printf("  _readreg response 32b: %x\n", responseArr[0]);
        
        return (responseArr[0] >>16);
    };

    void ads131xxx::_writereg(uint16_t reg, uint16_t data)
    { // Assuming 24bits words (default)

        // Command is 16 bits (zero padded)
        uint32_t commandWord = (ADC_ADS131XXX_CMD_WREG| (reg << 7));
        //SERIALDEBUG.printf("  _writereg cmd: %x\n", commandWord);
        //SERIALDEBUG.printf("  _writereg data: %x\n", data);

        digitalWrite(_pinCS, LOW);
        sleep_us(5);
        _spi.beginTransaction(SPISettings(ADC_ADS131XXX_SPI_SPEED, ADC_ADS131XXX_SPI_ORDER, ADC_ADS131XXX_SPI_MODE));

        // Send the command in the first word
        spiTransferWord(commandWord);
        spiTransferWord(data);
        spiTransferWord(0); // not used but need to fill frame
        spiTransferWord(0); // CRC not used

        _spi.endTransaction();
        digitalWrite(_pinCS, HIGH);

        //while(digitalRead(_pinRDY) == HIGH) {}; // Wait for ADC to become ready
        sleep_us(5);

        // Read response
        //uint32_t responseArr[6];
        //spiCommFrame(&responseArr[0], ADC_ADS131XXX_CMD_NULL);
        //SERIALDEBUG.printf("  _writereg response 32b: %x\n", responseArr[0]);
    };

    uint32_t ads131xxx::spiTransferWord(uint16_t inputData)
    {
        /* Transfer a 24 bit word
        Data returned is MSB aligned
        */
        uint32_t data = _spi.transfer(inputData >> 8); 
        data <<= 8;
        data |= _spi.transfer((inputData << 8) >> 8); 
        data <<= 8;
        data |= _spi.transfer(0x00); // was: 0x00

        return data << 8;
    };

    bool ads131xxx::spiCommFrame(uint32_t *outPtr, uint16_t command)
    {
        // Saves all the data of a communication frame to an array with pointer outPtr

        uint32_t *outPtrStart = outPtr;

        digitalWrite(_pinCS, LOW);
        //sleep_us(5);
        _spi.beginTransaction(SPISettings(ADC_ADS131XXX_SPI_SPEED, ADC_ADS131XXX_SPI_ORDER, ADC_ADS131XXX_SPI_MODE));
        // spi->beginTransaction(SPISettings(SCLK_SPD, MSBFIRST, SPI_MODE1));

        // Send the command in the first word
        *outPtr = spiTransferWord(command);

        //SERIALDEBUG.printf("|%8x|", (uint32_t)*outPtr);
        // For the next 2 words, just read the data
        for (uint8_t i = 1; i < 3; i++)
        {
            outPtr++;
            *outPtr = spiTransferWord(0); // >> 8;
            //SERIALDEBUG.printf("|%8x|", (uint32_t)*outPtr);
        }

        // Save CRC bits
        outPtr++;
        *outPtr = spiTransferWord(0);
        //SERIALDEBUG.printf("|%8x|", (uint32_t)*outPtr);

        _spi.endTransaction();
        digitalWrite(_pinCS, HIGH);
        //sleep_us(5);

        // Calculated CRC = received CRC?
        uint16_t calccrc = calculateCRC(outPtrStart, 9, 0xFFFF);
        uint16_t rcvdcrc = (*outPtr) >> 16;
        if  (calccrc != rcvdcrc) {
            //SERIALDEBUG.printf("CRC mismatch: %x  %x\n", calccrc, rcvdcrc);
            return false;
        } else {
            //SERIALDEBUG.print(".");
        };
        return true; //CRC ok
    };

    int32_t ads131xxx::readChannelsNow() {
        // 2 channels = 4 words of 24 bytes....
        uint32_t readwords[4];

        bool crcok = spiCommFrame(&readwords[0], ADC_ADS131XXX_CMD_NULL);
        
        if (crcok) {
            reg_status statusread;
            statusread.raw = readwords[0];
            _lastPriData = ((int32_t)readwords[1]) >>8 ; // TODO: shift to 24 bits, 2's complement,etc...
            _lastSecData = ((int32_t)readwords[2]) >>8 ; // TODO: shift to 24 bits, 2's complement,etc...
        }

        return _lastPriData; // TODO: shift and 2's complement stuff.
    }

    int32_t ads131xxx::lastSecondaryData() {
        return _lastSecData;
    }

// From TI.com website example code for ADS131
//*****************************************************************************
//
//! Calculates the 16-bit CRC for the selected CRC polynomial.
//!
//! \fn uint16_t calculateCRC(const uint8_t dataBytes[], uint8_t numberBytes, uint16_t initialValue)
//!
//! \param dataBytes[] pointer to first element in the data byte array
//! \param numberBytes number of bytes to be used in CRC calculation
//! \param initialValue the seed value (or partial crc calculation), use 0xFFFF when beginning a new CRC computation
//!
//! NOTE: This calculation is shown as an example and is not optimized for speed.
//!
//! \return 16-bit calculated CRC word
//
//*****************************************************************************
uint16_t ads131xxx::calculateCRC(const uint32_t responseArr[], uint8_t numberBytes, uint16_t initialValue)
{
	/* Check that "dataBytes" is not a null pointer */
	//assert(dataBytes != 0x00);
    uint8_t     dataBytes[12];
	int         bitIndex, byteIndex;
	bool        dataMSb;						/* Most significant bit of data byte */
	bool        crcMSb;						    /* Most significant bit of crc byte  */
	//uint8_t     bytesPerWord = 3;               //wlength_byte_values[WLENGTH];

    for (int i = 0; i < 3; i++)
    {
        dataBytes[i * 3] = (uint8_t)(responseArr[i] >> 24);
        dataBytes[i * 3 + 1] = (uint8_t)(responseArr[i] >> 16);
        dataBytes[i * 3 + 2] = (uint8_t)(responseArr[i] >> 8);
    }

    /*
     * Initial value of crc register
     * NOTE: The ADS131M0x defaults to 0xFFFF,
     * but can be set at function call to continue an on-going calculation
     */
    uint16_t crc = initialValue;

    #ifdef CRC_CCITT
    /* CCITT CRC polynomial = x^16 + x^12 + x^5 + 1 */
    const uint16_t poly = 0x1021;
    #endif

    #ifdef CRC_ANSI
    /* ANSI CRC polynomial = x^16 + x^15 + x^2 + 1 */
    const uint16_t poly = 0x8005;
    #endif

    //
    // CRC algorithm
    //

    // Loop through all bytes in the dataBytes[] array
	for (byteIndex = 0; byteIndex < numberBytes; byteIndex++)
	{
        // Skip the 4th byte in the 32bit word (24 bits are MSB ordered in our array)
        //if ((byteIndex == 3) || (byteIndex == 7) || (byteIndex == 11) || (byteIndex == 15)) {
        //    SERIALDEBUG.printf("skip:%x", byteIndex);
        //    byteIndex++;
        //}
	    // Point to MSb in byte
	    bitIndex = 0x80u;

	    // Loop through all bits in the current byte
	    while (bitIndex > 0)
	    {
	        // Check MSB's of data and crc
	        dataMSb = (bool) (dataBytes[byteIndex] & bitIndex);
	        crcMSb  = (bool) (crc & 0x8000u);
	        crc <<= 1;              /* Left shift CRC register */

	        // Check if XOR operation of MSBs results in additional XOR operations
	        if (dataMSb ^ crcMSb)
	        {
	            crc ^= poly;        /* XOR crc with polynomial */
	        }

	        /* Shift MSb pointer to the next data bit */
	        bitIndex >>= 1;
	    }
	}
    	return crc;
};


/*
 * uint16_t crc_16( const unsigned char *input_str, size_t num_bytes );
 *
 * The function crc_16() calculates the 16 bits CRC16 in one pass for a byte
 * string of which the beginning has been passed to the function. The number of
 * bytes to check is also a parameter. The number of the bytes in the string is
 * limited by the constant SIZE_MAX.
 */
/*
uint16_t ads131xxx::crc_16( const unsigned char *input_str, size_t num_bytes ) {

	uint16_t crc;
	uint16_t tmp;
	uint16_t short_c;
	const unsigned char *ptr;
	size_t a;

	if ( ! crc_tab16_init ) init_crc16_tab();

	crc = CRC_START_16;
	ptr = input_str;

	if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

		short_c = 0x00ff & (uint16_t) *ptr;
		tmp     =  crc       ^ short_c;
		crc     = (crc >> 8) ^ crc_tab16[ tmp & 0xff ];

		ptr++;
	}

	return crc;
*/
//}  /* crc_16 */


}
