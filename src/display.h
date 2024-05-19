// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "state.h"

extern void gui_task_init(void);

extern volatile uint8_t watchdogGuiTask;
extern volatile uint8_t watchdogGuiTimerFunction;
