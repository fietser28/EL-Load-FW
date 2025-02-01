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
SemaphoreHandle_t eventsMutex;


void init()
{
    eventsMutex = xSemaphoreCreateMutex();
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
            }
            // Wrap head around when full
            if (g_eventListHead >= eventQueueSize)
            {
                g_eventListHead = 0;
                g_eventListFull = true;
            }
            // Head reached tail?
            if (g_eventListTail == g_eventListHead && g_eventListFull)
            {
                g_eventListTail++;
                g_eventListSize--;
                // Wrap around
                if (g_eventListTail == eventQueueSize)
                {
                    g_eventListTail = 0;
                }
            }
            g_eventList[g_eventListHead].timeStamp = millis();

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

            char tmpmsg[eventTextMaxSize];
            snprintf(&tmpmsg[0], eventTextMaxSize, "%d %s", eventCounter(), msg);
            memccpy(&g_eventList[g_eventListHead].msg, tmpmsg, 0, sizeof(g_eventList[g_eventListHead].msg));
            g_eventCounter++;

            xSemaphoreGive(eventsMutex);
        } 
    };
}

void addEvent(uint16_t e)
{
    addEvent(e, getEventMessage(e));
}

uint32_t eventCounter() { return g_eventCounter; }
uint32_t eventListSize() { return g_eventListSize; }

}
}