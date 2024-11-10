// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <lvgl.h>
#include "state.h"
#include "main.h"
#include "ui/vars.h"
#include "ui/structs.h"

#include "ui/screens.h"

extern "C" {

dcl::measuredStateStruct localstatecopy;
dcl::setStateStruct localsetcopy;

const u_int16_t logsize = 512;
char logtxt[logsize];
uint16_t logpointer = 0;

} // extern "C"

void printlogval(int val1, int val2, int val3, int val4) {
    snprintf(logtxt, 60, "pin1: %d\npin2: %d\nenccount:  %d\ngpio:  %d", val1, val2, val3, val4);
}

void printlogstr(const char* txt) {
    uint16_t written = snprintf(logtxt + logpointer, logsize - 1 - logpointer, "%s\n", txt);
    if (written > 0 && written < logsize - 1 - logpointer) {
        logpointer = logpointer + written;
    } else if (written > logsize - logpointer) {
        logpointer = logsize - 1;
    } 
}

void clearlog() {
    logpointer = 0;
    logtxt[0] = '\x00';
}
