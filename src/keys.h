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
