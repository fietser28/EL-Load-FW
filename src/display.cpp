// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <Arduino.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <lvgl.h>
#include <TFT_eSPI.h>

#include "math.h" 

#include "ui/ui.h"
#include "ui/screens.h"
#include "main.h"
#include "state.h"
#include "ui_glue.h"
#include "keys.h"

#define MY_LV_TICK_TIME 20     // ms
#define MY_LV_UPDATE_TIME 100  // ms

#ifndef TFT_BUFFERLINES
#define TFT_BUFFERLINES 10
#endif

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */

static void guiTask(void *pvParameter);
TaskHandle_t guiTaskHandle;
volatile uint8_t watchdogGuiTask;
volatile bool guiTaskReady = false;

static TimerHandle_t guiTimerHandle;
volatile uint8_t watchdogGuiTimerFunction;

static const uint32_t screenWidth = EEZ_WIDTH;
static const uint32_t screenHeight = EEZ_HEIGHT;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[TFT_BUFFERLINES * screenWidth];

static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;     // Touchscreen
static lv_indev_drv_t indev_enc_drv; // Encoder

changeScreen_s newScreenMsg; // new Flow screen ID msg.
size_t screenMsgBytes;       // queue messages size

void my_log_cb(const char* logline) 
{
  SERIALDEBUG.println(logline);
}

// TODO: Replace with: vApplicationTickHook
static void guiTimerFunction(TimerHandle_t tm)
{
  lv_tick_inc(MY_LV_TICK_TIME);
  watchdogGuiTimerFunction = 0;
}


void __not_in_flash_func(gui_task_init(void))
{

  // Turn backlight on (hide garbage)
  digitalWrite(TFT_BL, LOW);

  guiTimerHandle = xTimerCreate("", pdMS_TO_TICKS(MY_LV_TICK_TIME), pdTRUE, (void *) 0, guiTimerFunction);
  //xTimerStart(guiTimerHandle, 10);

  xTaskCreate(guiTask, "", 2048, NULL, TASK_PRIORITY_UI, &guiTaskHandle);
  //vTaskCoreAffinitySet(guiTaskHandle, TASK_AFFINITY_UI);
};

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Display flushing */
static void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
// TODO: Add calibration
static void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  // data->state = LV_INDEV_STATE_REL;

  uint16_t touchX, touchY;

  bool touched = tft.getTouch(&touchX, &touchY, 600);

  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;

  #ifdef TOUCH_ROTATE90
    // Set the coordinates (note the rotation X <-> Y, also scaled...)
    data->point.x = 320 - (touchX * 4) / 3;
    data->point.y = 240 - (touchY * 3) / 4;
  #else
    data->point.x = 320 - touchX + 10; // - 20 = manual calibration, TODO
    data->point.y = 240 - touchY;
  #endif
  }
}

// Encoder vars
static int encoderLastState = 0;
static bool encoderButLastState = false;
static char newtext[40];

// Read the encoder
static void my_encoder_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  // Get the current focussed object
  lv_obj_t *obj = lv_group_get_focused(encoder_group);

  // Move cursus out of 

  // Encoder stuff
  if (obj == 0)
  {
    return;
  } // No focus = no action.
  // if (lv_obj_get_state(obj) != LV_STATE_EDITED) { return; } // no edit = no action
  if (obj->class_p != &lv_textarea_class && obj->class_p != &lv_slider_class)
  {
    return;
  } // just to be sure....

  // Current active object is textarea
  if (obj->class_p == &lv_textarea_class) {
  const char *text = lv_textarea_get_text(obj);
  uint32_t pos = lv_textarea_get_cursor_pos(obj);
  uint32_t textsize = strlen(text);


  // Encoder Button pressed
  if (keystate.encoderbutton && encoderButLastState == false)
  {
    int newpos = pos - 1; // -1 scrolls left, +1 scrolls right
    if (text[newpos] == '.')
    {
      newpos--;
    } // Skip .
    // if (newpos >= textsize) { newpos = 0; }
    if (newpos < 0)
    {
      newpos = textsize - 1;
    }
    lv_textarea_set_cursor_pos(obj, newpos);
    encoderButLastState = true;
  }

  // Encoder Button released
  if (!keystate.encoderbutton && encoderButLastState == true)
  {
    encoderButLastState = false;
  }

  // Encoder movement
  // TODO: Increment >9.
  // TODO: Clean number implementation not just string manipulation
  int enccount = keystate.encodercount / 2; // 2 changes per dent (on current combination HW/SW)
  if (encoderLastState != enccount)
  {
    strcpy(newtext, text);
    bool textchanged = false;
    if (encoderLastState < enccount)
    {
      // Up
      if (newtext[pos] != '9')
      {
        newtext[pos] = newtext[pos] + 1;
        textchanged = true;
      }
    }
    else
    {
      // Down
      if (newtext[pos] != '0')
      {
        newtext[pos] = newtext[pos] - 1;
        textchanged = true;
      }
    }
    if (textchanged)
    {
      lv_textarea_set_text(obj, newtext);
      lv_textarea_set_cursor_pos(obj, pos);
      // lv_event_send(obj, LV_EVENT_VALUE_CHANGED, NULL); // TODO: Needed?
    }
    encoderLastState = enccount;
  }
  }

  // Current active object is slider
  if (obj->class_p == &lv_slider_class) {
    int32_t sliderpos = lv_slider_get_value(obj);
    int32_t slidermin = lv_slider_get_min_value(obj);
    int32_t slidermax = lv_slider_get_max_value(obj);
    int32_t newsliderpos = sliderpos;
    
    // Encoder movement
    int enccount = keystate.encodercount / 2; // 2 changes per dent (on current combination HW/SW)
    if (encoderLastState != enccount)
    {
    bool sliderchanged = false;
    if (encoderLastState < enccount)
    {
      // Increase
      if (sliderpos < slidermax)
      {
        newsliderpos = sliderpos + 1;
        sliderchanged = true;
      }
    }
    else
    {
      // Decrease
      if (sliderpos > slidermin)
      {
        newsliderpos = sliderpos - 1;
        sliderchanged = true;
      }
    }
    if (sliderchanged)
    {
      lv_slider_set_value(obj,newsliderpos, LV_ANIM_OFF);
      lv_event_send(obj, LV_EVENT_VALUE_CHANGED, NULL);
    }
    encoderLastState = enccount;
  }

  }
  // Already handled....
  data->enc_diff = 0;
  data->state = LV_INDEV_STATE_REL;
}

static void __not_in_flash_func(guiTask(void *pvParameter))
{
  //vTaskDelay(100); // Wait for core affinity.

  lv_init();

  tft.begin();        /* TFT init */
  tft.setRotation(TFT_ROTATION); /* Landscape orientation, flipped */
  tft.initDMA();
  /*Set the touchscreen calibration data,
    the actual data for your display can be aquired using
    the Generic -> Touch_calibrate example from the TFT_eSPI library*/
  //  uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
  //  tft.setTouch( calData );

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, TFT_BUFFERLINES * screenWidth);

  /*Initialize the display*/
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver for touchpad*/
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  lv_log_register_print_cb(&my_log_cb);

  //  Set to 1 if you do not see any GUI
#if 0
   /* Create simple label */
   lv_obj_t *label = lv_label_create( lv_scr_act() );
   lv_label_set_text( label, "Hello Arduino! (V8.3.0)" );
   lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
   // vTaskDelay(2000);
   lv_obj_t *label2 = lv_label_create( lv_scr_act() );
   lv_label_set_text( label2, "Hello world!" );
   lv_obj_align( label2, LV_ALIGN_TOP_MID, 0, 0 );
   // vTaskDelay(2000);
   //lv_task_handler();

#else
  // EEZ GUI init
  ui_init();

  // Initialize the input device driver for the encoder
  // and assign the encoder to the encoder group
  ui_init_encoder_group();

  lv_indev_drv_init(&indev_enc_drv);
  indev_enc_drv.type = LV_INDEV_TYPE_ENCODER;
  indev_enc_drv.read_cb = my_encoder_read;
  lv_indev_t *encoder_indev = lv_indev_drv_register(&indev_enc_drv);
  lv_indev_set_group(encoder_indev, encoder_group);

#endif

  // Manually turn on backlight (avoid garbage at startup)
  // Now handled by flow itself
  //digitalWrite(TFT_BL, HIGH);

  xTimerStart(guiTimerHandle, 10);
  guiTaskReady = true;
  while (1)
  {
    unsigned long loopstart = millis();
    state.getMeasuredStateCopy(&localstatecopy, 0);
    state.getSetStateCopy(&localsetcopy, 0);
    lv_task_handler();
    ui_tick();
    screenMsgBytes = xQueueReceive(changeScreen, &newScreenMsg, 0);
    if ( screenMsgBytes > 0)
    {
      if (newScreenMsg.pop == true) {
        eez_flow_pop_screen(LV_SCR_LOAD_ANIM_NONE,0,0);
      } else {
        if (newScreenMsg.newScreen != eez_flow_get_current_screen()) {
          eez_flow_push_screen(newScreenMsg.newScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0);
        }
      }
    }
    watchdogGuiTask = 0;
    unsigned long loopend = millis();
    TickType_t loopdelay = pdMS_TO_TICKS(MY_LV_UPDATE_TIME);
    if (loopend > loopstart) // No millis overflow.
    {
      if ((loopend-loopstart) < MY_LV_UPDATE_TIME) {
      loopdelay = pdMS_TO_TICKS(loopend-loopstart);
      } else { 
        loopdelay = 0;
      }
    }
    vTaskDelay(loopdelay);
  }

  /* A task should NEVER return */
}

