// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef ADC_ADS131XXX_H
#define ADC_ADS131XXX_H

#include <SPI.h>

// Hardcoded setting (default)
#define CRC_CCITT

/* SPI Settings */
#define ADC_ADS131XXX_SPI_ORDER         MSBFIRST                       // SPI ORDER
#define ADC_ADS131XXX_SPI_MODE          SPI_MODE1                  // SPI MODE
//#define ADC_ADS131XXX_SPI_ADR           (MCP3x6x_DEVICE_ADDRESS << 6)  // SPI ADDRESS
#define ADC_ADS131XXX_SPI_SPEED         (8000000)                       // SPI SPEED Value (was 200000)

/* SPI Commands in 16 bits format */
#define ADC_ADS131XXX_CMD_NULL          0x0000
#define ADC_ADS131XXX_CMD_RESET         0x0011
#define ADC_ADS131XXX_CMD_STANDBY       0x0022
#define ADC_ADS131XXX_CMD_WAKEUP        0x0033
#define ADC_ADS131XXX_CMD_LOCK          0x0555
#define ADC_ADS131XXX_CMD_UNLOCk        0x0655
#define ADC_ADS131XXX_CMD_RREG          0xA000
#define ADC_ADS131XXX_CMD_WREG          0x6000

/* Register addresses (5 bits)*/
#define ADC_ADS131XXX_ADR_ID            0x00
#define ADC_ADS131XXX_ADR_STATUS        0x01
#define ADC_ADS131XXX_ADR_MODE          0x02
#define ADC_ADS131XXX_ADR_CLOCK         0x03
#define ADC_ADS131XXX_ADR_GAIN          0x04
#define ADC_ADS131XXX_ADR_CFG           0x06
#define ADC_ADS131XXX_ADR_THRSHLD_MSB   0x07
#define ADC_ADS131XXX_ADR_THRSHLD_LSB   0x08
#define ADC_ADS131XXX_ADR_CH0_CFG       0x09
#define ADC_ADS131XXX_ADR_CH0_OCAL_MSB  0x0A
#define ADC_ADS131XXX_ADR_CH0_OCAL_LSB  0x0B
#define ADC_ADS131XXX_ADR_CH0_GCAL_MSB  0x0C
#define ADC_ADS131XXX_ADR_CH0_GCAL_LSB  0x0D
#define ADC_ADS131XXX_ADR_CH1_CFG       0x0E
#define ADC_ADS131XXX_ADR_CH1_OCAL_MSB  0x0F
#define ADC_ADS131XXX_ADR_CH1_OCAL_LSB  0x10
#define ADC_ADS131XXX_ADR_CH1_GCAL_MSB  0x11
#define ADC_ADS131XXX_ADR_CH1_GCAL_LSB  0x12
#define ADC_ADS131XXX_ADR_REGMAP_CRC    0x3E
#define ADC_ADS131XXX_RESERVED          0x3F

/* Register defaults */
#define ADC_ADS131X02_DEFAULT_ID            0x2200
#define ADC_ADS131XXX_DEFAULT_STATUS        0x0500
#define ADC_ADS131XXX_DEFAULT_MODE          0x0510
#define ADC_ADS131XXX_DEFAULT_CLOCK         0x030E
#define ADC_ADS131XXX_DEFAULT_GAIN          0x0000
#define ADC_ADS131XXX_DEFAULT_CFG           0x0600
#define ADC_ADS131XXX_DEFAULT_THRSLD_MSB    0x0000
#define ADC_ADS131XXX_DEFAULT_THRSLD_MSB    0x0000
#define ADC_ADS131XXX_DEFAULT_CH0_CFG       0x0000
#define ADC_ADS131XXX_DEFAULT_CH0_OCAL_MSB  0x0000
#define ADC_ADS131XXX_DEFAULT_CH0_OCAL_LSB  0x0000
#define ADC_ADS131XXX_DEFAULT_CH0_GCAL_MSB  0x8000
#define ADC_ADS131XXX_DEFAULT_CH0_GCAL_LSB  0x0000
#define ADC_ADS131XXX_DEFAULT_CH1_CFG       0x0000
#define ADC_ADS131XXX_DEFAULT_CH1_OCAL_MSB  0x0000
#define ADC_ADS131XXX_DEFAULT_CH1_OCAL_LSB  0x0000
#define ADC_ADS131XXX_DEFAULT_CH1_GCAL_MSB  0x8000
#define ADC_ADS131XXX_DEFAULT_CH1_GCAL_LSB  0x0000
#define ADC_ADS131XXX_DEFAULT_REGMAP_CRC    0x0000
#define ADC_ADS131XXX_DEFAULT_RESERVED      0x0000

namespace dcl {

class ads131xxx {
    public:
        enum class __attribute__((packed)) drdy_source : uint8_t
        {
            leading = 2,
            logicOR = 1,
            lagging = 0 // default
        };

        enum class __attribute__((packed)) data_word_length : uint8_t
        {
            bits32MSBs = 3,
            bits32LSBz = 2,
            bits24 = 1, // default
            bits16 = 0
        };

        enum class __attribute__((packed)) power : uint8_t
        {
            verylow = 0,
            very = 1,
            high = 2,
            high2 = 3
        };

        enum class __attribute__((packed)) osr_types : uint8_t
        {
            osr128 = 0,
            osr256 = 1,
            osr512 = 2,
            osr1024 = 3, // default
            osr2048 = 4,
            osr4096 = 5,
            osr8192 = 6,
            osr16384 = 7
        };

        enum class __attribute__((packed)) again : uint8_t
        {
            again1 = 0,
            again2 = 1,
            again4 = 2,
            again8 = 3,
            again16 = 4,
            again32 = 5,
            again64 = 6,
            again128 = 7
        };

        enum class __attribute__((packed)) gc_delays : uint8_t
        {
            dly2 = 0,
            dly4 = 1,
            dly8 = 2,
            dly16 = 3, // default
            dly32 = 4,
            dly64 = 5,
            dly128 = 6,
            dly65535 = 15
        };

        union reg_id
        {
            struct
            {
                byte reserved1 : 8;
                byte chancnt : 4;
                byte reserved2 : 4;
            };
            uint16_t raw;
        };

        union reg_status
        {
            struct
            {
                bool drdy0 : 1;
                bool drdy1 : 1;
                byte reserved : 6;
                byte wlength : 2;
                bool reset : 1;
                bool crc_type : 1;
                bool crc_err : 1;
                bool reg_map : 1;
                bool f_resync : 1;
                bool lock : 1;
            };
            uint16_t raw;
        };

        union reg_mode
        {
            struct
            {
                bool drdy_fmt : 1;
                bool drdy_hiz : 1;
                enum drdy_source drdy_sel : 2;
                bool timeout : 1;
                byte reserved : 3;
                byte wlength : 2;
                bool reset : 1;
                bool crc_type : 1;
                bool rx_crc_en : 1;
                bool reg_crc_en : 1;
                byte reserved2 : 2;
            };
            uint16_t raw;
        };

        union reg_clock
        {
            struct
            {
                enum power pwr : 2;
                enum osr_types osr : 3;
                bool tbm : 1;
                byte reserved : 2;
                bool ch0_en : 1;
                bool ch1_en : 1;
                byte reserved2 : 6;
            };
            uint16_t raw;
        };

        union reg_gain1
        {
            struct
            {
                again pgagain0 : 3;
                bool reserved : 1;
                again pgagain1 : 3;
                uint16_t reserved1 : 9;
            };
            uint16_t raw;
        };

        union reg_cfg
        {
            struct
            {
                bool cd_en : 1;
                byte cd_len : 3;
                byte cd_num : 3;
                bool cd_allch : 1;
                bool gc_en : 1;
                gc_delays gc_dly : 4;
                byte reserved : 3;
            };
            uint16_t raw;
        };

        union reg_thrshld_msb
        {
            uint16_t cd_th_msb;
            uint16_t raw;
        };

        union reg_thrshld_lsb
        {
            struct
            {
                byte dcblock : 4;
                byte reserved : 4;
                byte cd_th_lsb : 8;
            };
            uint16_t raw;
        };

        union reg_ch0_cfg
        {
            struct
            {
                byte mux0 : 2;
                bool dcblk0_dis0 : 1;
                byte reserved : 3;
                uint16_t phase0 : 10;
            };
            uint16_t raw;
        };

        union reg_ch0_ocal_msb
        {
            uint16_t ch0_ocal_msb;
            uint16_t raw;
        };

        union reg_ch0_ocal_lsb
        {
            struct
            {
                uint8_t reserved : 8;
                uint8_t ch0_ocal_lsb : 8;
            };
            uint16_t raw;
        };

        union reg_ch0_gcal_msb
        {
            uint16_t ch0_gcal_msb;
            uint16_t raw;
        };

        union reg_ch0_gcal_lsb
        {
            struct
            {
                uint8_t reserved : 8;
                uint8_t ch0_gcal_lsb : 8;
            };
            uint16_t raw;
        };

        union reg_ch1_cfg
        {
            struct
            {
                byte mux1 : 2;
                bool dcblk1_dis0 : 1;
                byte reserved : 3;
                uint16_t phase1 : 10;
            };
            uint16_t raw;
        };

        union reg_ch1_ocal_msb
        {
            uint16_t ch1_ocal_msb;
            uint16_t raw;
        };

        union reg_ch1_ocal_lsb
        {
            struct
            {
                uint8_t reserved : 8;
                uint8_t ch1_ocal_lsb : 8;
            };
            uint16_t raw;
        };

        union reg_ch1_gcal_msb
        {
            uint16_t ch1_gcal_msb;
            uint16_t raw;
        };

        union reg_ch1_gcal_lsb
        {
            struct
            {
                uint8_t reserved : 8;
                uint8_t ch1_gcal_lsb : 8;
            };
            uint16_t raw;
        };

        union reg_regmap_crc
        {
            uint16_t reg_crc;
            uint16_t raw;
        };

        ads131xxx(SPIClassRP2040 &selSPI, int CS, int adc_clk, int adc_rdy);
        bool begin(bool setupSPI);
        void attachInterrupt();
        static void ISR_ADC();
        int32_t readChannelsNow();
        int32_t lastSecondaryData();
        

    private:
        //uint8_t _transfer(uint8_t *data, uint8_t addr, size_t size);
        uint16_t _readreg(uint16_t reg);
        void _writereg(uint16_t reg, uint16_t data);

        uint32_t spiTransferWord(uint16_t inputData);
        bool spiCommFrame(uint32_t * outPtr, uint16_t command);
        uint16_t calculateCRC(const uint32_t responseArr[], uint8_t numberBytes, uint16_t initialValue);
        //uint16_t crc_16( const unsigned char *input_str, size_t num_bytes );
       
        SPIClassRP2040 &_spi = SPI;
        int _pinCS;
        int _pinCLK;
        int _pinRDY;
        int32_t _lastPriData;
        int32_t _lastSecData;
};

}
#endif
