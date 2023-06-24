// SPDX-License-Identifier: MIT
// Based on: https://github.com/nerdyscout/Arduino_MCP3x6x_Library from Stefan Herold <stefan.herold@posteo.de>

#include "adc_MCP3x6x.h"

#include <wiring_private.h>

MCP3x6x::MCP3x6x(const uint16_t MCP3x6x_DEVICE_TYPE, const uint8_t pinCS, SPIClass *theSPI) {
  switch (MCP3x6x_DEVICE_TYPE) {
    case MCP3461_DEVICE_TYPE:
      _resolution = 16;
      _channels   = 2;
      break;
    case MCP3462_DEVICE_TYPE:
      _resolution = 16;
      _channels   = 4;
      break;
    case MCP3464_DEVICE_TYPE:
      _resolution = 16;
      _channels   = 8;
      break;
    case MCP3561_DEVICE_TYPE:
      _resolution = 24;
      _channels   = 2;
      break;
    case MCP3562_DEVICE_TYPE:
      _resolution = 24;
      _channels   = 4;
      break;
    case MCP3564_DEVICE_TYPE:
      _resolution = 24;
      _channels   = 8;
      break;
//    default:
// TODO: Fix or remove?
//#warning "undefined MCP3x6x_DEVICE_TYPE"
//      break;
  }

  _spi       = theSPI;
  _pinCS     = pinCS;

  resolution = _resolution;
  //_channel_mask &= (0xff << _channels);  // todo fix this one
  _channel_mask = 0xff;
};

MCP3x6x::MCP3x6x(const uint8_t pinIRQ, const uint8_t pinMCLK, const uint16_t MCP3x6x_DEVICE_TYPE,
                 const uint8_t pinCS, SPIClass *theSPI)
    : MCP3x6x(MCP3x6x_DEVICE_TYPE, pinCS, theSPI) {
  _pinIRQ  = pinIRQ;
  _pinMCLK = pinMCLK;
}

MCP3x6x::status_t MCP3x6x::_transfer(uint8_t *data, uint8_t addr, size_t size) {
  _spi->beginTransaction(SPISettings(MCP3x6x_SPI_SPEED, MCP3x6x_SPI_ORDER, MCP3x6x_SPI_MODE));
  digitalWrite(_pinCS, LOW);
  _status.raw = _spi->transfer(addr);
  _spi->transfer(data, size);
  digitalWrite(_pinCS, HIGH);
  _spi->endTransaction();
  return _status;
}

MCP3x6x::status_t MCP3x6x::_fastcmd(uint8_t cmd) {
  _spi->beginTransaction(SPISettings(MCP3x6x_SPI_SPEED, MCP3x6x_SPI_ORDER, MCP3x6x_SPI_MODE));
  digitalWrite(_pinCS, LOW);
  _status.raw = _spi->transfer(cmd);
  digitalWrite(_pinCS, HIGH);
  _spi->endTransaction();
  return _status;
}

bool MCP3x6x::begin(uint8_t channelmask, uint8_t channelmask2, bool setupSPI) {
  pinMode(_pinCS, OUTPUT);
  digitalWrite(_pinCS, HIGH);

  if (setupSPI)
  {
      // TODO: Differennt from RP2040 class 
      // Setup ADC SPI
      //_spi.setRX(SPI_ADC_RX);
      //_spi.setTX(SPI_ADC_TX);
      //_spi.setSCK(SPI_ADC_SCK);
      //SERIALDEBUG.println("INFO: ADC SPI.begin... done");

      _spi->begin();
  };

#if ARDUINO_ARCH_SAMD
  // todo figure out how to get dynamicaly sercom index
  pinPeripheral(_pinMISO, PIO_SERCOM);
  pinPeripheral(_pinMOSI, PIO_SERCOM);
  pinPeripheral(_pinCLK, PIO_SERCOM);
#endif

  _status = reset();

  setClockSelection(clk_sel::internal);

  if (_pinIRQ != 0 || _pinMCLK != 0) {
    // scan mode
    setScanChannels(channelmask, channelmask2);
    setDataFormat(data_format::id_sgnext_data);
    setConvMode(conv_mode::continuous);
    _status = conversion();
  } else {
    // mux mode
    setDataFormat(data_format::sgn_data);
    setConvMode(conv_mode::oneshot_standby);
//    setOverSampling(osr::OSR256);
    _status = standby();
  }

  uint8_t tmpbuffer[4];
  _status = _transfer(tmpbuffer, MCP3x6x_CMD_SREAD | MCP3x6x_ADR_IRQ,1);
  settings.irq.raw = tmpbuffer[0];
  settings.irq.irq_mode = 1;
  settings.irq.en_stp = 0;
  _status = write(settings.irq);

  Serial1.printf("%X, ", tmpbuffer[0]);

  _status = _transfer(tmpbuffer, MCP3x6x_CMD_SREAD | MCP3x6x_ADR_CONFIG1,1);
  Serial1.printf("%X, ", tmpbuffer[0]);

  _status = _transfer(tmpbuffer, MCP3x6x_CMD_SREAD | MCP3x6x_ADR_CONFIG2,1);
  Serial1.printf("%X, ", tmpbuffer[0]);

  _status = _transfer(tmpbuffer, MCP3x6x_CMD_SREAD | MCP3x6x_ADR_CONFIG3,1);
  Serial1.printf("%X, ", tmpbuffer[0]);

  return true;
}

MCP3x6x::status_t MCP3x6x::read(Adcdata *data) {
  uint8_t buffer[4];
  uint8_t length;

  if (settings.config3.data_format == data_format::sgn_data) {
    length = 2; // 16 bit
  } else {
    length = 4; // 32 bits.
  }
  _status = _transfer(buffer, MCP3x6x_CMD_SREAD | MCP3x6x_ADR_ADCDATA, length);
  
/*
  if (settings.config3.data_format == data_format::sgn_data) {
    _status = _transfer(buffer, MCP3x6x_CMD_SREAD | MCP3x6x_ADR_ADCDATA, 3); // was 3
  } else {
    _status = _transfer(buffer, MCP3x6x_CMD_SREAD | MCP3x6x_ADR_ADCDATA, 4);
  }
*/
/* 
  // reversing byte order
  for (size_t i = 0, e = sizeof(buffer); i < e / 2; i++, e--) {
    uint8_t temp  = buffer[i];
    buffer[i]     = buffer[e - 1];
    buffer[e - 1] = temp;
  }
 */
  if (settings.config3.data_format == data_format::sgn_data) {
    data->value     = (buffer[0] <<8 ) | (buffer[1] << 0);
  } else {
    data->channelid = _getChannel((uint32_t &)buffer);
    data->value     = _getValue((uint32_t &)buffer);
  } 

#if MCP3x6x_DEBUG
  Serial1.print("buffer: 0x");
  Serial1.print(buffer[3], HEX);
  Serial1.print(buffer[2], HEX);
  Serial1.print(buffer[1], HEX);
  Serial1.println(buffer[0], HEX);
#endif

  return _status;
}

void MCP3x6x::ISR_handler() {
//  uint8_t tmpbuffer[4];
//  _status = _transfer(tmpbuffer, MCP3x6x_CMD_IREAD | MCP3x6x_ADR_CONFIG0,1);
//  Serial1.printf("%X, ", _status);

  read(&adcdata);
  channel.raw[(uint8_t)adcdata.channelid] = adcdata.value;
#if MCP3x6x_DEBUG
  Serial1.print("channel: ");
  Serial1.println((uint8_t)adcdata.channelid);
  Serial1.print("value: ");
  Serial1.println(adcdata.value);
#endif
}

void MCP3x6x::lock(uint8_t key) {
  settings.lock.raw = key;
  write(settings.lock);
}

void MCP3x6x::unlock() {
  settings.lock.raw = MCP3x6x_DEFAULT_LOCK;
  write(settings.lock);
}

void MCP3x6x::setDataFormat(data_format format) {
  settings.config3.data_format = format;

  switch (format) {
    case data_format::sgn_data:
    case data_format::sgn_data_zero:
      resolution--;
      break;
    case data_format::sgnext_data:
    case data_format::id_sgnext_data:
      break;
    default:
      resolution = -1;
      break;
  }

  _status = write(settings.config3);

}

/*  
  bool MCP3x6x::dataReadyBusyWait() {
    uint16_t ic = 0;
    uint8_t buf[1];
    while(!_status.dr && (ic < 20)) {
        Serial1.print(".");
        _status = _transfer(buf, MCP3x6x_CMD_SREAD | MCP3x6x_ADR_IRQ,1);
        if (!(buf[0] && 0x40)) {
            Serial1.print("x");
            return true;
        }
        sleep_ms(500);
        ic++;// TODO: implement timeout.
    }
    Serial1.printf("(%d)   ", ic);
    return true;
  }
 */

void MCP3x6x::setConvMode(conv_mode mode) {
  settings.config3.conv_mode = mode;
  _status                    = write(settings.config3);
}

void MCP3x6x::setAdcMode(adc_mode mode) {
  settings.config0.adc = mode;
  _status              = write(settings.config0);
}

void MCP3x6x::setClockSelection(clk_sel clk) {
  settings.config0.clk = clk;
  _status              = write(settings.config0);
}

void MCP3x6x::setOverSampling(osr ratio) {
    settings.config1.osr = ratio;
    _status = write(settings.config1);
}


void MCP3x6x::setScanChannels(uint8_t mask, uint8_t mask2) {
  settings.scan.channels.single_ended = mask;
  settings.scan.channels.differential = 0x0F & mask2;
  settings.scan.channels.temp         = 0x10 & mask2;
  settings.scan.channels.avdd         = 0x20 & mask2;
  settings.scan.channels.vcm          = 0x40 & mask2;
  settings.scan.channels.offset       = 0x80 & mask2;
  _status                             = write(settings.scan);
}

// returns signed ADC value from raw data
int32_t MCP3x6x::_getValue(uint32_t raw) {
  switch (settings.config3.data_format) {
    case (data_format::sgn_data):
      bitWrite(raw, 31, bitRead(raw, 24));
      return raw;
      break;
    case (data_format::sgn_data_zero):
      return raw >> 8;
      break;
    case (data_format::sgnext_data):
    case (data_format::id_sgnext_data):
      bitWrite(raw, 31, bitRead(raw, 25));
      return raw & 0x80FFFFFF;
      break;
  };
  return -1;
}

// returns channelID from raw data
MCP3x6x::channelID_t MCP3x6x::_getChannel(uint32_t raw) {
  if (settings.config3.data_format == data_format::id_sgnext_data) {
    return (channelID)((raw >> 28) & 0x0F);
  }
  return (channelID)0; //  todo return current mux channel
}

// actual triggers read in mux mode, but in scan mode only returns latest value from channel structure
int32_t MCP3x6x::analogRead(uint8_t channelid) {
  if (settings.scan.channels.raw == 0) {
    // mux mode
    //settings.mux.raw = channelid & _channel_mask;
    if (channelid == 0) {
        settings.mux.vin_minus = mux::mux_AGND;
        settings.mux.vin_plus = mux::mux_CH0;
    } else {
        settings.mux.vin_minus = mux::mux_AGND;
        settings.mux.vin_plus = mux::mux_CH1;
    }
    
    _status          = write(settings.mux);
    _status          = conversion();
    //dataReadyBusyWait();
    sleep_ms(5);
    ISR_handler();
  }
  // both modes
  return channel.raw[channelid];
}