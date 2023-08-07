// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef ADC_ADS1x1x_H
#define ADC_ADS1x1x_H

#include <Wire.h>

#define ADC_ADS1X1X_MUX_0_1          0x0000
#define ADC_ADS1X1X_MUX_0_3          0x1000
#define ADC_ADS1X1X_MUX_1_3          0x2000
#define ADC_ADS1X1X_MUX_2_3          0x3000
#define ADC_ADS1X1X_MUX_0_GND        0x4000
#define ADC_ADS1X1X_MUX_1_GND        0x5000
#define ADC_ADS1X1X_MUX_2_GND        0x6000
#define ADC_ADS1X1X_MUX_3_GND        0x7000

#define ADC_ADS1X1X_PGA_6_144V       0x0000
#define ADC_ADS1X1X_PGA_4_096V       0x0200
#define ADC_ADS1X1X_PGA_2_048V       0x0400
#define ADC_ADS1X1X_PGA_1_024V       0x0600
#define ADC_ADS1X1X_PGA_0_512V       0x0800
#define ADC_ADS1X1X_PGA_0_256V       0x0A00

#define ADC_ADS1X1X_MODE_CONT        0x0000
#define ADC_ADS1X1X_MODE_SINGLE      0x0100


class adc_ads1x1x {
    public:

        enum class __attribute__((packed)) mux_e : uint8_t
        {
            mux_0_1 = 0,
            mux_0_3 = 1,
            mux_1_3 = 2,
            mux_2_3 = 3,
            mux_0_gnd = 4,
            mux_1_gnd = 5,
            mux_2_gnd = 6,
            mux_3_gnd = 7
        };

        enum class __attribute__((packed)) pga_e : uint8_t
        {
            pga_6_144v = 0,
            pga_4_096v = 1,
            pga_2_048v = 2,
            pga_1_024v = 3,
            pga_0_512v = 4,
            pga_0_256v = 5,
        };

        // 16 bit ADS111x only
        enum class __attribute__((packed)) dr_e : uint8_t
        {
            dr_8sps = 0,
            dr_16sps = 1,
            dr_32sps = 2,
            dr_64sps = 3,
            dr_128sps = 4,
            dr_250sps = 5,
            dr_475sps = 6,
            dr_860sps = 7
        };

        union reg_config
        {
            struct 
            {
                bool       os        : 1;
                enum mux_e mux       : 3;
                enum pga_e pga       : 3;
                bool       mode      : 1;
                enum dr_e  data_rate : 3;
                bool       comp_mode : 1;          
                bool       comp_pol  : 1;
                bool       comp_lat  : 1;
                //byte       comp_que  : 3;
            };
            uint16_t raw;
        };        

        adc_ads1x1x() {};
        void begin(TwoWire *Wire, SemaphoreHandle_t WireSemaphore, uint8_t Address);
        void reset();

        void startConversion(uint16_t channelconf);
        bool isReady();
        int16_t getValue();
        float toVoltage(int16_t rawValue);
        
    private:
        TwoWire *_wire;
        uint8_t _addr;
        SemaphoreHandle_t _sem;

        // chip registers 
        uint16_t _regs[3]; // 3 = HIGH_TRES = last register.

        uint16_t readI2C(uint8_t opcode);
        uint8_t writeI2C(uint8_t opcode, uint16_t data);

};

#endif
