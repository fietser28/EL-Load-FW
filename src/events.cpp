// SPDX-FileCopyrightText: 2025 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later


#include "main.h"
#include "ui/vars.h"
#include "events.h"
//#include <string.h>

using namespace dcl;

namespace dcl {
namespace events {

const size_t eventQueueSize = 50;
event g_eventList[eventQueueSize];
uint32_t g_eventListHead = 0;
uint32_t g_eventListTail = 1;
bool g_eventListFull = false;
uint32_t g_eventListSize = 0;
uint32_t g_eventCounter = 0;
uint32_t g_eventFifoSize = 0;
uint32_t g_eventFifoFirst = 1;
SemaphoreHandle_t eventsMutex;
uint32_t eventsMutexTimeouts;

void init()
{
    eventsMutex = xSemaphoreCreateMutex();
    eventsMutexTimeouts = 0;
};

// Copied from BB3 firmware
const char *getEventMessage(int16_t eventId) {
    static char message[eventTextMaxSize];

    const char *p_message = 0;

    if (eventId < EVENT_INFO_START_ID) {
        switch (eventId) {
#define EVENT_INFO(NAME,ID, TEXT)
#define EVENT_WARNING(NAME, ID, TEXT)
#define EVENT_ERROR(NAME, ID, TEXT)
#define EVENT_FATAL(NAME, ID, TEXT)
#define EVENT_DEBUG(NAME, ID, TEXT)         \
    case EVENT_DEBUG_START_ID + ID:         \
        p_message = TEXT;                   \
        break;
            EVENTLIST
#undef EVENT_DEBUG
#undef EVENT_INFO
#undef EVENT_WARNING
#undef EVENT_ERROR
#undef EVENT_FATAL
        }
    } else if (eventId < EVENT_WARNING_START_ID) {
        switch (eventId) {
#define EVENT_DEBUG(NAME,ID, TEXT)
#define EVENT_WARNING(NAME, ID, TEXT)      
#define EVENT_ERROR(NAME, ID, TEXT)
#define EVENT_FATAL(NAME, ID, TEXT)
#define EVENT_INFO(NAME, ID, TEXT)        \
    case EVENT_INFO_START_ID + ID:        \
        p_message = TEXT;                 \
        break;
            EVENTLIST
#undef EVENT_DEBUG
#undef EVENT_INFO
#undef EVENT_WARNING
#undef EVENT_ERROR
#undef EVENT_FATAL
        }
    } else if (eventId < EVENT_ERROR_START_ID) {
        switch (eventId) {
#define EVENT_DEBUG(NAME,ID, TEXT)
#define EVENT_INFO(NAME, ID, TEXT)
#define EVENT_ERROR(NAME, ID, TEXT)
#define EVENT_FATAL(NAME, ID, TEXT)
#define EVENT_WARNING(NAME, ID, TEXT)      \
    case EVENT_WARNING_START_ID + ID:      \
        p_message = TEXT;                  \
        break;
            EVENTLIST
#undef EVENT_DEBUG
#undef EVENT_INFO
#undef EVENT_WARNING
#undef EVENT_ERROR
#undef EVENT_FATAL
        }
    } else if (eventId >= EVENT_ERROR_START_ID) {
        switch (eventId) {
#define EVENT_DEBUG(NAME,ID, TEXT)
#define EVENT_INFO(NAME, ID, TEXT)
#define EVENT_WARNING(NAME, ID, TEXT)
#define EVENT_FATAL(NAME, ID, TEXT)
#define EVENT_ERROR(NAME, ID, TEXT)      \
    case EVENT_ERROR_START_ID + ID:      \
        p_message = TEXT;                \
        break;
            EVENTLIST
#undef EVENT_DEBUG
#undef EVENT_INFO
#undef EVENT_WARNING
#undef EVENT_ERROR
#undef EVENT_FATAL
        }
    } else if (eventId >= EVENT_FATAL_START_ID) {
        switch (eventId) {
#define EVENT_DEBUG(NAME,ID, TEXT)
#define EVENT_INFO(NAME, ID, TEXT)
#define EVENT_WARNING(NAME, ID, TEXT)
#define EVENT_ERROR(NAME, ID, TEXT)
#define EVENT_FATAL(NAME, ID, TEXT)      \
    case EVENT_FATAL_START_ID + ID:      \
        p_message = TEXT;                \
        break;
            EVENTLIST
#undef EVENT_DEBUG
#undef EVENT_INFO
#undef EVENT_WARNING
#undef EVENT_ERROR
#undef EVENT_FATAL
        default:
            p_message = 0;
        }
    } 

    if (p_message) {
        memccpy(message, p_message, 0, sizeof(message));
        return message;
    }

    return 0;
}

void addEvent(uint16_t e, const char *msg) {
    if (eventsMutex != NULL) {
        if (xSemaphoreTake(eventsMutex, 10))
        {
//            else
            {
                // Next slot
                g_eventListHead++;
                g_eventListSize++;
                g_eventFifoSize++;    
            }
            // Wrap head around when full
            if (g_eventListHead >= eventQueueSize)
            {
                g_eventListHead = 0;
                g_eventListFull = true;
            }
            // Head reached tail? Overflow it.
            if (g_eventListTail == g_eventListHead && g_eventListFull)
            {
                // If fifo first equals tail, also remove it (overflow)
                if (g_eventFifoFirst == g_eventListTail)
                {
                    g_eventFifoFirst++;
                    g_eventFifoSize--;
                }
                g_eventListTail++;
                g_eventListSize--;

                // Wrap around
                if (g_eventListTail == eventQueueSize)
                {
                    g_eventListTail = 0;
                }
            }
            g_eventList[g_eventListHead].timeStamp = millis();
            memccpy(&g_eventList[g_eventListHead].msg, msg, 0, sizeof(g_eventList[g_eventListHead].msg));

            if (e < EVENT_INFO_START_ID)
            {
                g_eventList[g_eventListHead].type = eventType_e_debug;
            }
            else if (e < EVENT_WARNING_START_ID)
            {
                g_eventList[g_eventListHead].type = eventType_e_info;
            }
            else if (e < EVENT_ERROR_START_ID)
            {
                g_eventList[g_eventListHead].type = eventType_e_warning;
            }
            else if (e < EVENT_FATAL_START_ID)
            {
                g_eventList[g_eventListHead].type = eventType_e_error;
            }
            else
            {
                g_eventList[g_eventListHead].type = eventType_e_fatal;
                SERIALDEBUG.printf("FATAL ERROR: %d %s\n", EVENT_TYPE_NAMES[g_eventList[g_eventListHead].type], g_eventList[g_eventListHead].timeStamp/1000, g_eventList[g_eventListHead].msg);
            };
            SERIALDEBUG.printf("%s %d %s\n", EVENT_TYPE_NAMES[g_eventList[g_eventListHead].type], g_eventList[g_eventListHead].timeStamp/1000, g_eventList[g_eventListHead].msg);
            g_eventList[g_eventListHead].count = g_eventCounter++;
            xSemaphoreGive(eventsMutex);
        } else {
            eventsMutexTimeouts++;
        }
    } 
}

void addEvent(uint16_t e)
{
    addEvent(e, getEventMessage(e));
}

uint32_t eventCounter() { return g_eventCounter; }
uint32_t eventListSize() { return g_eventListSize; }

size_t eventListGetEvent(uint32_t item, eventType_e filter, char* msg, size_t size)
{
        // Item and eventList range check
        if (g_eventListSize == 0 || g_eventListSize <= item) { return 0; }

        uint32_t l = 0;
        // Find location
        if (item < (eventQueueSize - g_eventListTail)) 
        {
            l = g_eventListTail + item;
        } 
        else
        {
            l = item - (eventQueueSize - g_eventListTail);
        }

        if (g_eventList[l].type < filter) { return 0; }

        uint32_t h = g_eventList[l].timeStamp / (3600 * 1000);
        uint32_t m = g_eventList[l].timeStamp / (60 * 1000) - h * 3600;
        uint32_t s = g_eventList[l].timeStamp / 1000 - h * 3600 - m * 60;

        return snprintf(msg, size, "%s %02d:%02d:%02d %s", EVENT_TYPE_NAMES[g_eventList[l].type], h, m, s, 
                                                         &g_eventList[l].msg);
}

uint32_t eventFifoSize() { return g_eventFifoSize; }
bool eventFifoReset()
{
    if (eventsMutex != NULL)
    {
        if (xSemaphoreTake(eventsMutex, 10))
        {
            g_eventFifoSize = g_eventListSize;
            g_eventFifoFirst = g_eventListTail;
            xSemaphoreGive(eventsMutex);
            return true;
        } else {
            eventsMutexTimeouts++;
        }
    }
    return false;
}

size_t eventFifoPop(char *msg, size_t size)  {
    if (g_eventFifoSize == 0) { return 0; }

    size_t r = 0;
    if (eventsMutex != NULL) {
        if (xSemaphoreTake(eventsMutex, 20))
        {
            r = snprintf(msg, size, "%d,%s,%d,%s", g_eventList[g_eventFifoFirst].count, 
                                                EVENT_TYPE_NAMES[g_eventList[g_eventFifoFirst].type],
                                                g_eventList[g_eventFifoFirst].timeStamp, 
                                                &g_eventList[g_eventFifoFirst].msg);
            g_eventFifoSize--;
            g_eventFifoFirst++;
            // Overflow
            if (g_eventFifoFirst >= eventQueueSize)
            {
                g_eventFifoFirst = 0;
            }
            xSemaphoreGive(eventsMutex);
        } else {
            eventsMutexTimeouts++;
        }
    }
    return r;
};

} // namespace events
} // namespace dcl