// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

struct keystate_t 
{
    int encodercount;
    bool encoderbutton;
    bool button0;
    bool button1;
    bool button2;
    bool button3;
};

extern "C" {
extern keystate_t keystate;
}

extern void keys_task_init(void);
extern void keys_update(void);

extern TaskHandle_t encTaskHandle;

extern volatile uint8_t watchdogEncTask;
extern volatile bool encTaskReady;
