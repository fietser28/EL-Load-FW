// SPDX-FileCopyrightText: 2025 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later


#pragma once

#include <Arduino.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "ui/vars.h"

namespace dcl {
namespace events {

const uint16_t eventTextMaxSize = 120;
const size_t eventQueueSize = 50;

static const char *EVENT_TYPE_NAMES[] = {
    "D",
    "I",
    "W",
    "E",
    "F"
};

struct event { 
    uint32_t count;
    uint16_t id;
    unsigned long timeStamp;
    eventType_e type;
    bool read;
    char msg[eventTextMaxSize];
};

#define EVENTLIST \
    EVENT_INFO(GENERIC, 0, "") \
    EVENT_INFO(STARTUP,1,"Startup done.") \
    EVENT_INFO(FAKE, 2, "Using FAKE HARDWARE.") \
    EVENT_INFO(SCPI_WDOG_ON, 3, "SCPI Watchdog enabled.") \
    EVENT_INFO(SCPI_WDOG_OFF, 4, "SCPI Watchdog disabled.") \
    EVENT_INFO(SCPI_DETECTED, 5, "Remote SCPI received.") \
    EVENT_DEBUG(GENERIC, 0, "") \
    EVENT_DEBUG(EEPROM_MAGIC_FOUND, 1, "EEPROM magic found.") \
    EVENT_DEBUG(CAL_CRC_OK, 2, "Calibration data CRC OK.") \
    EVENT_WARNING(GENERIC, 0, "") \
    EVENT_WARNING(EEPROM_NO_MAGIC, 1, "EEPROM magic not found.") \
    EVENT_WARNING(WATCHDOG_AVERAGING, 2, "Watchdog not seeing Averaging task.") \
    EVENT_WARNING(WATCHDOG_KEYS, 3, "Watchdog not seeing Keys task.") \
    EVENT_WARNING(WATCHDOG_GUI, 4, "Watchdog not seeing GUI task.") \
    EVENT_WARNING(WATCHDOG_GUI_TIMER, 5, "Watchdog not seeing GUI Timer task.") \
    EVENT_WARNING(WATCHDOG_SCPI_LOOP, 6, "Watchdog not seeing SCPI loop task.") \
    EVENT_WARNING(WATCHDOG_PROTHW, 7, "Watchdog not seeing ProtHW task.") \
    EVENT_WARNING(WATCHDOG_MEASURE, 8, "Watchdog not seeing Measure task.") \
    EVENT_WARNING(WATCHDOG_UART, 9, "Watchdog not seeing UART task.") \
    EVENT_WARNING(CAP_VOLT, 10, "Capacity Volt Stop reached.") \
    EVENT_WARNING(CAP_AH, 11, "Capacity Ah limit reached.") \
    EVENT_WARNING(CAP_WH, 12, "Capacity Wh limit reached.") \
    EVENT_WARNING(CAP_TIME, 13, "Capacity Time limit reached.") \
    EVENT_ERROR(GENERIC, 0, "") \
    EVENT_ERROR(CAL_CRC, 1, "Calibration data CRC NOT OK.") \
    EVENT_ERROR(OCP, 2, "Over Current Protection") \
    EVENT_ERROR(OVP, 3, "Over Voltage Protection") \
    EVENT_ERROR(OPP, 4, "Over Power Protection") \
    EVENT_ERROR(OTP, 5, "Over Temperature Protection") \
    EVENT_ERROR(SENSE, 6, "Remote sense error") \
    EVENT_ERROR(SCPI_WATCHDOG, 7, "SCPI Watchdog triggered.") \
    EVENT_ERROR(FLOW, 8, "") \
    EVENT_FATAL(GENERIC, 0, "")

// Copied from BB3 firmware
#define EVENT_DEBUG_START_ID      0
#define EVENT_INFO_START_ID    1000
#define EVENT_WARNING_START_ID 2000
#define EVENT_ERROR_START_ID   3000
#define EVENT_FATAL_START_ID   4000

#define EVENT_DEBUG(NAME, ID, TEXT) EVENT_DEBUG_##NAME = EVENT_DEBUG_START_ID + ID,
#define EVENT_INFO(NAME, ID, TEXT) EVENT_INFO_##NAME = EVENT_INFO_START_ID + ID,
#define EVENT_WARNING(NAME, ID, TEXT) EVENT_WARNING_##NAME = EVENT_WARNING_START_ID + ID,
#define EVENT_ERROR(NAME, ID, TEXT) EVENT_ERROR_##NAME = EVENT_ERROR_START_ID + ID,
#define EVENT_FATAL(NAME, ID, TEXT) EVENT_FATAL_##NAME = EVENT_FATAL_START_ID + ID,

enum Events { EVENTLIST };

#undef EVENT_DEBUG
#undef EVENT_INFO
#undef EVENT_WARNING
#undef EVENT_ERROR
#undef EVENT_FATAL

extern event g_eventList[];
extern uint32_t g_eventListHead;
extern uint32_t g_eventListTail;
extern bool g_eventListFull;
extern uint32_t eventsMutexTimeouts;

extern void init();
extern void addEvent(uint16_t e, const char* msg);
extern void addEvent(uint16_t e);
extern uint32_t eventCounter();
extern uint32_t eventListSize();
extern size_t eventListGetEvent(uint32_t item, eventType_e filter, char* msg, size_t size);
extern uint32_t eventFifoSize();
extern bool eventFifoReset();
extern size_t eventFifoPop(char *msg, size_t size);

}
}