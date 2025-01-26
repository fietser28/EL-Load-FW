// SPDX-FileCopyrightText: 2024 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
/// Hardware definition
///////////////////////
//#define FAKE_HARDWARE   1

#ifndef HARDWARE_VERSION
#define HARDWARE_VERSION 3
#endif

#if HARDWARE_VERSION == 3

#define PIN_UART_TX     0           // GPIO 0 - debug/scpi
#define PIN_UART_RX     1           // GPIO 1 - debug/scpi

#define SPI_ADC_SCK     2           // GPIO 2 - measure task
#define PIN_DAC1_SCK    2           // GPIO 2
#define PIN_DAC2_SCK    2           // GPIO 2

#define SPI_ADC_TX      3           // GPIO 3 - measure task 
#define PIN_DAC1_TX     3           // GPIO 3
#define PIN_DAC2_TX     3           // GPIO 3

#define SPI_ADC_RX      4           // GPIO 4 - measure task
#define PIN_DAC1_RX     4           // GPIO 4 - measure task
#define PIN_DAC2_RX     4           // GPIO 4 - measure task

#define PIN_DAC2_CS     5           // GPIO 5 - measure task
#define PIN_DAC1_CS     6           // GPIO 6 - measure task
#define PIN_ADC_RDY     7           // GPIO 7 - interrupt

#define PIN_LCD_DC      8           // GPIO 8 - display task
#define PIN_LCD_CS      9           // GPIO 9 - display task

#define PIN_LCD_SCK     10          // GPIO 10 - display task
#define PIN_TP_SCK      10          // GPIO 10 - display task
//#define PIN_KEYS_SCK    10          // GPIO 10 - display task

#define PIN_LCD_MOSI    11          // GPIO 11 - display task
#define PIN_TP_MOSI     11          // GPIO 11 - display task
//#define PIN_KEYS_MOSI   11          // GPIO 11 - display task

#define PIN_LCD_MISO    12          // GPIO 12 - display task
#define PIN_TP_MISO     12          // GPIO 12 - display task
//#define PIN_KEYS_MISO   12          // GPIO 12 - display task

#define PIN_LCD_BL      13          // GPIO 13 - display task

// GPIO14 - check if waveshare has no resistor on R11. 
//    => CS pin for MCP23S08 connected to SPI0 = Analog hardware
// => Interrupt pin MCP23008 hardware signals.
#define PIN_HWGPIO_INT    14          // GPIO 14 - interrupt pin for hadware MCP23008

#define PIN_LCD_RESET   15          // GPIO 15 - display task
#define PIN_TP_CS       16          // GPIO 16 - display task
#define PIN_TP_IRQ      17          // GPIO 17 - display task

//18 KEYS_SDA
//19 KeYS_SCL

#define SPI_ADC_CS      20          // GPIO 20 - measure task 

#define PIN_ADC_CLK      21          // GPIO 21 (unconnected SDIO_CLK) - HW clock pin

// GPIO 22 - connected to SD_CD with 47k 3V3 pullup. - TODO:CHECK.
// GPIO 23 = TP4 & controls DC convertor efficiency mode    
// GPIO 25 = LED & TP5 (GPIO 25 -> 470R -> TP5 -> LED -> GND)

//#define PIN_TEMP1_ADC     26         // GPIO 26 - ADC0 => I2C for keys & hw
#define PIN_KEYS_SDA      26
#define PIN_HWGPIO_SDA    26

//#define PIN_TEMP2_ADC     27         // GPIO 27 - ADC1 => I2C for keys & hw
#define PIN_KEYS_SCL      27
#define PIN_HWGPIO_SCL    27

//#define PIN_TEST          28  
#define PIN_KEYS_INT        28        // GPIO 28 - MCP23008 INT signal from keys.    
// GPIO 28 - change to interrupt pin for MCP2308 on I2C = UI hardware keys

#define SPI_ADC        SPI                // Wiring setup by ADC class
#define SPI_DAC1       SPI
#define SPI_DAC2       SPI
#define SPI_LCD        SPI1               // Wiring setup by display task
#define SPI_TP         SPI1
//#define SPI_KEYS       SPI1
#define I2C_KEYS       Wire1              // Setup done in main (shared bus)
#define I2C_KEYS_SEM   Wire1Sem
#define I2C_HWGPIO     Wire1
#define I2C_HWGPIO_SEM Wire1Sem
#define I2C_EEPROM     Wire1
#define I2C_EEPROM_SEM Wire1Sem
//#define I2C_TEMPADC     Wire1
//#define I2C_TEMPADC_SEM Wire1Sem
#define I2C_FANCTRL     Wire1
#define I2C_FANCTRL_SEM Wire1Sem
#define SERIALDEBUG      Serial1

#define EEPROM_ADDR     0x50
#define EEPROM_SIZE     8192    // 8292 * 8 = 64kbit.
#define FANCTRL_ADDRESS 0x51
#define FANCTRL_DUAlFAN 1

// GPIO extender (MCP23x08) for keys
#define KEYS_CHIP_ADDRESS   0x20
#define KEYS_PIN_ENC0       4   // GP4
#define KEYS_PIN_ENC1       2   // GP2
#define KEYS_PIN_ENCBUT     3   // GP3
#define KEYS_PIN_BUT0       7   // GP7
#define KEYS_PIN_BUT1       6   // GP6
#define KEYS_PIN_BUT2       1   // GP1
#define KEYS_PIN_BUT3       0   // GP0
#define KEYS_PIN_LED0       5   // GP5 

// GPIO extender (MCP23008) for hardware signals
#define HWIO_CHIP_ADDRES      0x27
#define HWIO_PIN_VONLATCH     0u   // GPA0 =output ///TODO: VON and VONLATCH are swapped in MCU PCB v4
#define HWIO_PIN_resetProt    1u   // GPA1 =output
#define HWIO_PIN_HWProtEnable 2u   // GPA2 =output
#define HWIO_PIN_SENSE_ERROR  3u   // GPA3 =input
#define HWIO_CLAMPOFF         4u   // GPA4 =input
#define HWIO_PIN_OVPTRIG      5u   // GPA5 =input
#define HWIO_PIN_OCPTRIG      6u   // GPA6 =input
#define HWIO_PIN_VON          7u   // GPA7 =input   ///TODO: VON and VONLATCH are swapped in MCU PCB v4
#define HWIO_PIN_REVERSEPOL   11u  // GPB3 =input   DFake, does not exist in V3!
#define HWIO_PIN_VOLTSENSECLR 12u  // GPB4 =output  (12-8=4)
#define HWIO_PIN_CURRRANGELOW 13u  // GPB5 =output
#define HWIO_PIN_VOLTRANGELOW 14u  // GPB6 =output
#define HWIO_PIN_VOLTSENSESET 15u  // GPB7 =output
// Set pins to output direction:
#define HWIO_DIR (1<<HWIO_PIN_VONLATCH|1<<HWIO_PIN_resetProt|1<<HWIO_PIN_HWProtEnable|1<<HWIO_PIN_VOLTSENSECLR|1<<HWIO_PIN_CURRRANGELOW|1<<HWIO_PIN_VOLTRANGELOW|1<<HWIO_PIN_VOLTSENSESET)
// Set pins to interrrupt (bank A only)
#define HWIO_INT (1<<HWIO_PIN_OCPTRIG|1<<HWIO_PIN_OVPTRIG|1<<HWIO_PIN_VON|1<<HWIO_PIN_SENSE_ERROR|1<<HWIO_PIN_REVERSEPOL)
// Set pins to compare to 0 instead of each change
#define HWIO_INT_COMP0 (uint8_t)(1<<HWIO_PIN_OCPTRIG|1<<HWIO_PIN_OVPTRIG)

#define TEMPADC_ADDRESS    0x48
#define NTC_T0              25+273.15
#define NTC_R0              10000
#define NTC_BETA            3435
#define TEMP1_CHANNEL       ADC_ADS1X1X_MUX_0_3
#define TEMP2_CHANNEL       ADC_ADS1X1X_MUX_1_3

#define NTC_R1              3300.0f
#define NTC_R2              6800.0f
#define NTC_VDD             3.3f

// TODO: Find new pins and rewire
#define PIN_OVPTRIGGERED 20         // GPIO 20  - pin 26
#define PIN_OCPTRIGGERED 20         // GPIO 19  - pin 25
#define PIN_VONLATCHSET  0
#define PIN_VON          0
#define PIN_RESETPROT    0

#endif  // HARDWARE_VERSION == 3
////////////////////////////////

#if HARDWARE_VERSION == 4

#define PIN_UART_TX     0           // GPIO 0 - debug/scpi
#define PIN_UART_RX     1           // GPIO 1 - debug/scpi

#define SPI_ADC_SCK     2           // GPIO 2 - measure task
#define PIN_DAC1_SCK    2           // GPIO 2
#define PIN_DAC2_SCK    2           // GPIO 2

#define SPI_ADC_TX      3           // GPIO 3 - measure task 
#define PIN_DAC1_TX     3           // GPIO 3
#define PIN_DAC2_TX     3           // GPIO 3

#define SPI_ADC_RX      4           // GPIO 4 - measure task
#define PIN_DAC1_RX     4           // GPIO 4 - measure task
#define PIN_DAC2_RX     4           // GPIO 4 - measure task

#define PIN_DAC2_CS     5           // GPIO 5 - measure task
#define PIN_DAC1_CS     6           // GPIO 6 - measure task
#define PIN_ADC_RDY     7           // GPIO 7 - interrupt

#define PIN_LCD_DC      8           // GPIO 8 - display task
#define PIN_LCD_CS      9           // GPIO 9 - display task

#define PIN_LCD_SCK     10          // GPIO 10 - display task
#define PIN_TP_SCK      10          // GPIO 10 - display task
//#define PIN_KEYS_SCK    10          // GPIO 10 - display task

#define PIN_LCD_MOSI    11          // GPIO 11 - display task
#define PIN_TP_MOSI     11          // GPIO 11 - display task
//#define PIN_KEYS_MOSI   11          // GPIO 11 - display task

#define PIN_LCD_MISO    12          // GPIO 12 - display task
#define PIN_TP_MISO     12          // GPIO 12 - display task
//#define PIN_KEYS_MISO   12          // GPIO 12 - display task

#define PIN_LCD_BL      13          // GPIO 13 - display task

// GPIO14 - check if waveshare has no resistor on R11. 
//    => CS pin for MCP23S08 connected to SPI0 = Analog hardware
// => Interrupt pin MCP23008 hardware signals.
#define PIN_HWGPIO_INT    14          // GPIO 14 - interrupt pin for hadware MCP23008

#define PIN_LCD_RESET   15          // GPIO 15 - display task
#define PIN_KEYS_SDA      16
#define PIN_KEYS_SCL      17
#define PIN_TP_CS       18          // GPIO 18 - display task

#define PIN_IO_RESET   19          // MCP IO chip resets - HWIO & KEys!

#define PIN_TP_IRQ      20         // display task  - TODO: not USED??? 


#define PIN_ADC_CLK      21          // GPIO 21 - HW clock pin
#define SPI_ADC_CS      22          // GPIO 22  - measure task 

// GPIO 23 = TP4 & controls DC convertor efficiency mode    
// GPIO 25 = LED & TP5 (GPIO 25 -> 470R -> TP5 -> LED -> GND)

#define PIN_HWGPIO_SDA    26

#define PIN_HWGPIO_SCL    27

//#define PIN_TEST          28  
#define PIN_KEYS_INT        28        // GPIO 28 - MCP23008 INT signal from keys.    
// GPIO 28 - change to interrupt pin for MCP2308 on I2C = UI hardware keys

#define SPI_ADC        SPI                // Wiring setup by ADC class
#define SPI_DAC1       SPI
#define SPI_DAC2       SPI
#define SPI_LCD        SPI1               // Wiring setup by display task
#define SPI_TP         SPI1
#define I2C_KEYS       Wire              // Setup done in main (shared bus)
#define I2C_KEYS_SEM   WireSem
#define I2C_HWGPIO     Wire1
#define I2C_HWGPIO_SEM Wire1Sem
#define I2C_EEPROM     Wire1
#define I2C_EEPROM_SEM Wire1Sem
#define I2C_FANCTRL     Wire1
#define I2C_FANCTRL_SEM Wire1Sem
#define SERIALDEBUG     Serial1
#define SERIALDEBUGIRQ  UART0_IRQ
#define SERIALDEBUGUART uart0 

#define EEPROM_ADDR     0x50
#define EEPROM_SIZE     8192    // 8292 * 8 = 64kbit.
#define FANCTRL_ADDRESS 0x51
#define FANCTRL_DUAlFAN 1

// GPIO extender (MCP23x08) for keys
#define KEYS_CHIP_ADDRESS   0x20
#define KEYS_PIN_ENC0       4   // GP4
#define KEYS_PIN_ENC1       2   // GP2
#define KEYS_PIN_ENCBUT     3   // GP3
#define KEYS_PIN_BUT0       7   // GP7
#define KEYS_PIN_BUT1       6   // GP6
#define KEYS_PIN_BUT2       1   // GP1
#define KEYS_PIN_BUT3       0   // GP0
#define KEYS_PIN_LED0       5   // GP5 

// GPIO extender (MCP23017) for hardware signals
#define HWIO_CHIP_ADDRES      0x27
#define HWIO_PIN_VON          0u   // GPA0 =input, int, 
#define HWIO_PIN_resetProt    1u   // GPA1 =output
#define HWIO_PIN_HWProtEnable 2u   // GPA2 =output
#define HWIO_PIN_SENSE_ERROR  3u   // GPA3 =input, int
#define HWIO_PIN_CLAMPOFF     4u   // GPA4 =input
#define HWIO_PIN_OVPTRIG      5u   // GPA5 =input, int, comp0
#define HWIO_PIN_OCPTRIG      6u   // GPA6 =input, int, comp0
#define HWIO_PIN_REVERSEPOL   7u   // GPA7 =input, int  
#define HWIO_PIN_BUZZER       10u  // GPB2 =output
#define HWIO_PIN_VOLTSENSECLR 11u  // GPB3 =output
#define HWIO_PIN_VONLATCH     12u  // GPB4 =output   
#define HWIO_PIN_CURRRANGELOW 13u  // GPB5 =output
#define HWIO_PIN_VOLTRANGELOW 14u  // GPB6 =output
#define HWIO_PIN_VOLTSENSESET 15u  // GPB7 =output
// Set pins to output direction:
#define HWIO_DIR (1<<HWIO_PIN_resetProt|1<<HWIO_PIN_HWProtEnable|1<<HWIO_PIN_VONLATCH|1<<HWIO_PIN_BUZZER|1<<HWIO_PIN_VOLTSENSECLR|1<<HWIO_PIN_CURRRANGELOW|1<<HWIO_PIN_VOLTRANGELOW|1<<HWIO_PIN_VOLTSENSESET)
// Set pins to interrrupt (bank A only)
#define HWIO_INT (1<<HWIO_PIN_OCPTRIG|1<<HWIO_PIN_OVPTRIG|1<<HWIO_PIN_VON|1<<HWIO_PIN_SENSE_ERROR|1<<HWIO_PIN_REVERSEPOL)
// Set pins to compare to 0 instead of each change
#define HWIO_INT_COMP0 (1<<HWIO_PIN_OCPTRIG|1<<HWIO_PIN_OVPTRIG)

#endif // HARDWARE_VERSION == 4
/////////////////////////////

