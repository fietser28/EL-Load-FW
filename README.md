<!--
  SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
  SPDX-License-Identifier: GPL-3.0-or-later
-->

## Introduction

Firmware for the EL-Load Electronic Load hardware project (URL to be included). This project is setup as a reference design to be converted in a [EEZ BB3](https://github.com/eez-open/modular-psu) module OR a standalone unit.

## Build

On Linxu/Mac OS (windows probably similar):
Make sure platformio is installed and in your PATH and use the following commands:
```
git clone https://github.com/fietser28/el-load-fw.git
cd el-load-fw
pio run
```

## Hardware requirements

The firmware is designed for the following hardware:
-  [Raspberry Pi Pico RP2350 MCU](https://www.raspberrypi.com/products/rp2350/) (the standard [Raspberry Pi Pico 2](https://www.raspberrypi.com/products/raspberry-pi-pico-2/) board will work)
-  Screen. Either one of (choose an environment in from platformio.ini): 
  -  [Waveshare 2.8 inch IPS-TFT-LCD Display 320*240 pixels - with Touchscreen - for Raspberry Pi Pico](https://www.waveshare.com/wiki/Pico-ResTouch-LCD-2.8)
  -  Generic 320*240 TFT Display with touch interface based on il9341 chipset.
-  24C64 eepromm (using I2C) for storage of calibration data
-  Rotary encoder with push button and a seperate push button connected to an MCP23008 (using I2C)
-  ADS131M02 ADC for reading analog voltage and current measurements
-  2x DAC8555 DAC's for setting all the analog values 
-  MCP23017 for reading/writing the digital signals of the analog board.
-  MAX31760 for fan control and temperature measurment

Most hardware and pin configurations are currently in the main.h file
For the ADC and DAC some provisions are in place to be able to replace them with other chips.

If the ADC is not present FAKE_HARDWARE can be set to 1 in src/main.h to run a timer to simulate the presence of an ADC.

## Software setup

The firmware is using:
- [EEZ studio](https://www.envox.eu/studio/studio-introduction/) used the Flow part of studio to design and generate the UI code and interactions
- [Raspberry Pi Pico Arduino core](https://github.com/earlephilhower/arduino-pico)
- [FreeRTOS](https://www.freertos.orghttps://www.freertos.org) included in the arduino core
- [PlatromIO](https://platformio.org) for building and library management.
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) a feature rich Arduino IDE compatible graphics and fonts library for 32 bit processors.
- [LVGL](https://lvgl.io) - Light and Versatile Graphics Library
- [EEZ framework](https://github.com/eez-open/eez-framework)
- [Rotary](https://github.com/brianlow/Rotary.git) modified and included locally.
- [SCPI Parser](https://github.com/j123b567/scpi-parser). Note: The depencency is not correct yet, I'm using a locally modified version to make it platformio compatible.

Due to the fact most arduino libraries are not thread safe, they are exclusivly used in a single thread.
For the chipsets local implementation are made. The I2C chips share the bus and run in different tasks, they are made thread safe with a mutex.

## Design

### State
The software is structured around a central state and few tasks with different priorities. The state actually has two main structures determining the state: 
- The *set state* is the desired state. Changes to this state are made by UI, SCPI and (stored) startup values.
- The *measured state* is the state as a result of the actual hardware signals etc.
This split state (hopefully) allows to change the firmware to be used as a BB3 module (reusing the SPI interface of the display for BB3 communication).
Threads receive/retrieve local copies of the state to avoid blockings, changes to the main copies of the state are protected with semaphores. 

Note: writes to calibration structures in memory are NOT thread safe / protected for speed reasons. Calibration data is only written during startup OR calibration.


### (FreeRTOS)Tasks
High prioriry task are not blocked by lower priority tasks by sending messages asynchronously. The messages are picked up at the end of an iteration of the task. These messages are mainly used to notify of changed settings/perform changes.

The task are:
- high priority measure task. It reads the ADC and depending on the mode the DAC values are set as fast as possible. Uses a dedicated SPI bus and is triggered via an interrupt from the ADC activating the task. If the ADC is not present FAKE_HARDWARE can be set to run a timer to simulate the presence of an ADC.
- averaging task. Calculates the averages, statistics and determines OTP and OPP. This task receives raw measurement messages from the measurement task. This taks sets most values in the measurement state struct.
- HW IO task. Reads and set the digital IO pins of the analog board. It also manages the fan controller. All using I2C bus.
- display task: EEZ Flow, TFT and touch task
- keys: task reading the MCP23008 keys, using the a different I2C bus as the HW IO task in Hardware version 4 (all prior versions shared a single I2C bus).
- arduino loop: this implements the SCPI loop to the UART pins.
- watchdog thread: This thread check if al other threads (except beeper thread) are still runing regulary if so it pets the hardware watchdog.
- beeper thread: schedules beeper duration.

### Flow

There are several screens and a few reused widgets. The most complicated widget is the keyboard, based on a setType variable it displays content (basically from a constant structure) and checks the values for limits. The calibarion screen has a similar setup: Based on a data structure values are displayed. Due to the complex nature part of this structure and variables are implemented native.

There are a lot of mappings to native variables, most are straight forward to and from the state (copy). Exceptions are the calibration structures and the formatting of the measurement values, this is done using an C implementation of the value2str action (for speed, but maybe not needed after all).

UI interactions and dynamics are mostly implemented in flow: disabling based on a changed value or a specific state are all checked for in the UI.

The event log text area widgets are there, but is is just a string used for some debugging now.

The ui_glue.cpp file has a function to map certain types of widgets (sliders and textarea's) to a buttongroup that the rotary encoder dynamically connects to. There is a feature request to have native Flow support for this. 

Changing numbers with the encoder is done using patch to the encoder widget.

### Calibration

The Dashboard project has a tab to allow for automatic calibration of all DAC and ADC ranges agains a BB3 DCP405, BB3 AIO16 with AFE3 or Siglent SDM3045X.

You can also manually calibrate the load using the UI, a configurable CV/CC power supply and a voltage and current DMM: You first need to calibrate the voltage and current measurements (calibrating the ADC). After that the Iset and Vset (using the DAC's) are done using the ADC measurements. Next, the Von, OCP and OVP calibrations can not be measured using single measurements but are iteratively calibrated by iterating each bit of precision. This iteration is done in a flow action.

### SCPI

For documentation of SCPI commands look in  [docs/SCPI/DCL8010 SCPI reference.pdf](docs/SCPI/DCL8010%20SCPI%20reference.pdf).
A EEZ studio IEXT instrument file is available at [docs/SCPI/DCL8010-Standalone-0.0.1.zip](docs/SCPI/DCL8010-Standalone-0.0.1.zip)