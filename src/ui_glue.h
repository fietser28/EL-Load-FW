// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef UI_GLUE_H
#define UI_GLUE_H
#include "Arduino.h"
#include <stdint.h>
#include <stdbool.h>
#include <lvgl.h>
#include "state.h"

extern struct measuredStateStruct localstatecopy;
extern struct setStateStruct      localsetcopy;

extern void printlogval(int val1, int val2, int val3, int val4);
extern void printlogstr(const char* txt);

extern void printstr(const char* txt);
extern char logtxt[512];

#endif