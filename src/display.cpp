// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <Arduino.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include <lvgl.h>
#include <lvgl_private.h>
#include <TFT_eSPI.h>

#include "math.h" 

#include "main.h"
#include "ui/vars.h"
#include "state.h"
#include "ui/ui.h"
#include "ui/screens.h"
#include "ui_glue.h"
#include "keys.h"

#define MY_LV_TICK_TIME 20     // ms
#define MY_LV_UPDATE_TIME 50  // ms

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

static lv_draw_buf_t *draw_buf;  // LVGL Draw buffer
static lv_display_t  *disp_drv;  // LVGL Display
static lv_indev_t    *indev_drv; // Touchscreen
static lv_indev_t    *indev_enc; // Encoder

changeScreen_s newScreenMsg; // new Flow screen ID msg.
size_t screenMsgBytes;       // queue messages size

void my_log_cb(lv_log_level_t level, const char* logline) 
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
  vTaskPrioritySet(xTimerGetTimerDaemonTaskHandle(), TASK_PRIORITY_UI_TIMER);

  xTaskCreate(guiTask, "", 4096, NULL, TASK_PRIORITY_UI, &guiTaskHandle);
  //vTaskCoreAffinitySet(guiTaskHandle, TASK_AFFINITY_UI);
};

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Display flushing */
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, unsigned char *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)color_p, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
// TODO: Add calibration
static void my_touchpad_read(lv_indev_t *indev_driver, lv_indev_data_t *data)
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
static bool encoderEventHandled = false;
static char newtext[40];

// Read the encoder
static void my_encoder_read(lv_indev_t *indev_driver, lv_indev_data_t *data)
{
  // Get the current focussed object
  lv_obj_t *obj = lv_group_get_focused(groups.encoder_group);
  encoderEventHandled = false;

  if (obj == 0 || (keystate.encoderbutton == encoderButLastState && keystate.encodercount == encoderLastState))
  {
    return;
  } // No focus and/or no action.

  // Current active object is textarea
  // For textarea send key events based on encoder actions.
  if (obj->class_p == &lv_textarea_class || obj->class_p == &lv_spinbox_class)
  {
    //const char *text = lv_textarea_get_text(obj);
    //uint32_t pos = lv_textarea_get_cursor_pos(obj);
    //uint32_t textsize = strlen(text);
    lv_group_set_editing(groups.encoder_group, true);

    // Encoder Button pressed
    if (keystate.encoderbutton && encoderButLastState == false)
    {
      //uint32_t t = LV_KEY_ENTER;
      //lv_obj_send_event(obj,LV_EVENT_KEY, &t);
      //int32_t curstep = lv_spinbox_get_step(obj);
      //int32_t maxdigits = (lv_spinbox_t *)obj->digit_count;
      //int32_t newstep = min(curstep * 10, pow(10,maxdigits));
      data->state = LV_INDEV_STATE_PRESSED;
      data->enc_diff = 0;
      
      encoderButLastState = true;
      encoderEventHandled = true;
    }
    // Encoder Button released
    if (!keystate.encoderbutton && encoderButLastState == true)
    {
      encoderButLastState = false;
    }

    // Encoder movement
    int enccount = keystate.encodercount; // 2; // 2 changes per dent (on current combination HW/SW)
    if (encoderLastState != enccount)
    {
      if (encoderLastState < enccount)
      {
        uint32_t t = LV_KEY_UP;
        lv_obj_send_event(obj,LV_EVENT_KEY, &t);
        encoderEventHandled = true;
        encoderLastState++; // We only processed 1 event now.
      } else {
        uint32_t t = LV_KEY_DOWN;
        lv_obj_send_event(obj,LV_EVENT_KEY, &t);
        encoderEventHandled = true;
        encoderLastState--; //We only processed 1 event now.
      }
      if (encoderLastState != enccount) data->continue_reading = true;
    }
  }

  // Current active object is slider
  if (obj->class_p == &lv_slider_class) 
  {
    int32_t sliderpos = lv_slider_get_value(obj);
    int32_t slidermin = lv_slider_get_min_value(obj);
    int32_t slidermax = lv_slider_get_max_value(obj);
    int32_t newsliderpos = sliderpos;
        
    // Encoder Button pressed
    if (keystate.encoderbutton && encoderButLastState == false)
    {
      //uint32_t t = LV_KEY_LEFT;
      //lv_obj_send_event(obj,LV_EVENT_KEY, &t);
      lv_group_focus_next(groups.encoder_group);
      lv_group_set_editing(groups.encoder_group, false);
      encoderButLastState = true;
      encoderEventHandled = true;
    }

    // Encoder Button released
    if (!keystate.encoderbutton && encoderButLastState == true)
    {
      encoderButLastState = false;
    }

    // Encoder movement
    int enccount = keystate.encodercount; // 2; // 2 changes per dent (on current combination HW/SW)
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
        encoderLastState++; 
      }
    }
    else
    {
      // Decrease
      if (sliderpos > slidermin)
      {
        newsliderpos = sliderpos - 1;
        sliderchanged = true;
        encoderLastState--; 
      }
    }
    if (sliderchanged)
    {
      lv_slider_set_value(obj,newsliderpos, LV_ANIM_OFF);
      lv_obj_send_event(obj, LV_EVENT_VALUE_CHANGED, NULL);
    }
    if (encoderLastState != enccount) data->continue_reading = true;
    }  
  }

  if (obj->class_p == &lv_dropdown_class)
  {

    int32_t dropdownpos = lv_dropdown_get_selected(obj); 
    int32_t dropdownmin = 0;
    int32_t dropdownmax = lv_dropdown_get_option_cnt(obj) - 1;  
    int32_t newdropdownpos = dropdownpos;

    // Encoder Button pressed
    if (keystate.encoderbutton && encoderButLastState == false)
    {
      if (lv_group_get_editing(groups.encoder_group) == true) {
        // Edit mode
        lv_obj_send_event(obj,LV_EVENT_VALUE_CHANGED, NULL);
        //uint32_t t = LV_KEY_ENTER;
        //lv_obj_send_event(obj,LV_EVENT_KEY, &t); 
        lv_group_set_editing(groups.encoder_group, false);        
      } else {
        // Navigation mode.
        //uint32_t t = LV_KEY_LEFT;
        //lv_obj_send_event(obj,LV_EVENT_KEY, &t);
        lv_group_focus_next(groups.encoder_group);
        lv_group_set_editing(groups.encoder_group, false);
      }

      encoderButLastState = true;
      encoderEventHandled = true;        
    }

    // Encoder Button released
    if (!keystate.encoderbutton && encoderButLastState == true)
    {
      encoderButLastState = false;
    }

    // Encoder movement
    int enccount = keystate.encodercount; // 2; // 2 changes per dent (on current combination HW/SW)
    if (encoderLastState != enccount)
    {
    bool dropdownchanged = false;
    if (encoderLastState < enccount)
    {
      // Increase
      if (dropdownpos < dropdownmax)
      {
        newdropdownpos = dropdownpos + 1;
        lv_group_set_editing(groups.encoder_group, true);
        //data->enc_diff = + 1;
        dropdownchanged = true;
      }
    }
    else
    {
      // Decrease
      if (dropdownpos > dropdownmin)
      {
        newdropdownpos = dropdownpos - 1;
        lv_group_set_editing(groups.encoder_group, true);
        //data->enc_diff = -1;
        dropdownchanged = true;
      }
    }
    if (dropdownchanged)
    {
      lv_dropdown_set_selected(obj,newdropdownpos);
      //lv_obj_send_event(obj, LV_EVENT_VALUE_CHANGED, NULL);
      encoderEventHandled = true;        

    }
    encoderLastState = enccount;
    }
  }

 if (obj->class_p == &lv_checkbox_class || obj->class_p == &lv_switch_class)
  {
    lv_group_set_editing(groups.encoder_group, true);

    // Encoder Button pressed
    if (keystate.encoderbutton && encoderButLastState == false)
    {
      //uint32_t t = LV_KEY_LEFT;
      //lv_obj_send_event(obj,LV_EVENT_KEY, &t);
      lv_group_focus_next(groups.encoder_group);
      lv_group_set_editing(groups.encoder_group, false);
      encoderButLastState = true;
      encoderEventHandled = true;        
    }

    // Encoder Button released
    if (!keystate.encoderbutton && encoderButLastState == true)
    {
      encoderButLastState = false;
      encoderEventHandled = true;
    }

    // Encoder movement
    int enccount = keystate.encodercount; // 2; // 2 changes per dent (on current combination HW/SW)
    if (encoderLastState != enccount)
    {
    bool dropdownchanged = false;
    if (encoderLastState < enccount)
    {
      // Increase = on
      if (!lv_obj_has_state(obj, LV_STATE_CHECKED)) {
        //uint32_t t = LV_KEY_UP;
        //lv_obj_send_event(obj,LV_EVENT_KEY, &t);
        //lv_obj_add_state(obj, LV_STATE_CHECKED); 
        data->enc_diff = 1;
        encoderEventHandled = true;
      }
    }
    else
    {
      // Decrease = off
      if (lv_obj_has_state(obj, LV_STATE_CHECKED)) {
        //uint32_t t = LV_KEY_DOWN;
        //lv_obj_send_event(obj,LV_EVENT_KEY, &t);
        //lv_obj_clear_state(obj, LV_STATE_CHECKED); 
        data->enc_diff = -1;
        encoderEventHandled = true;
      }
    }
    encoderLastState = enccount;
    }
  }

 if (obj->class_p == &lv_button_class )
  { 
    // Encoder Button pressed
    if (keystate.encoderbutton && encoderButLastState == false)
    {
      uint32_t t = LV_EVENT_PRESSED;
      lv_obj_send_event(obj,LV_EVENT_KEY, &t);
      encoderButLastState = true;
      encoderEventHandled = true;        
    }

    // Encoder Button released
    if (!keystate.encoderbutton && encoderButLastState == true)
    {
      uint32_t t = LV_EVENT_RELEASED;
      lv_obj_send_event(obj,LV_EVENT_KEY, &t);
      encoderButLastState = false;
      encoderEventHandled = true;
    }

    // Encoder movement
    int enccount = keystate.encodercount; // 2; // 2 changes per dent (on current combination HW/SW)
    if (encoderLastState != enccount)
    {
    bool dropdownchanged = false;
    if (encoderLastState < enccount)
    {
      lv_group_focus_next(groups.encoder_group);
      lv_group_set_editing(groups.encoder_group, false);
    }
    else
    {
      lv_group_focus_prev(groups.encoder_group);
      lv_group_set_editing(groups.encoder_group, false);
    }
    encoderLastState = enccount;
    }
  }

  if (obj->class_p == &lv_table_class)
  {
    // Encoder Button pressed
    if (keystate.encoderbutton && encoderButLastState == false)
    {
      uint32_t t = LV_EVENT_PRESSED;
      lv_obj_send_event(obj, LV_EVENT_KEY, &t);
      encoderButLastState = true;
      encoderEventHandled = true;
    }

    // Encoder Button released
    if (!keystate.encoderbutton && encoderButLastState == true)
    {
      uint32_t t = LV_EVENT_RELEASED;
      lv_obj_send_event(obj, LV_EVENT_KEY, &t);
      encoderButLastState = false;
      encoderEventHandled = true;
    }

    // Encoder movement
    int enccount = keystate.encodercount; // 2; // 2 changes per dent (on current combination HW/SW)
    if (encoderLastState != enccount)
    {
      if (encoderLastState < enccount)
      {
      uint32_t t = LV_KEY_DOWN;
      lv_obj_send_event(obj, LV_EVENT_KEY, &t);
      encoderEventHandled = true;
      }
      else
      {
      uint32_t t = LV_KEY_UP;
      lv_obj_send_event(obj, LV_EVENT_KEY, &t);
      encoderEventHandled = true;
      }
      encoderLastState = enccount;
    }
  }

  // Already handled....
  //data->enc_diff = 0;
  if (encoderEventHandled == false) {
    data->state = LV_INDEV_STATE_RELEASED;
  }
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

  /*Initialize the LVGL display*/
  disp_drv = lv_display_create(screenWidth, screenHeight);
  lv_display_set_flush_cb(disp_drv, my_disp_flush);
  draw_buf = lv_draw_buf_create(screenHeight, TFT_BUFFERLINES, LV_COLOR_FORMAT_RGB565, LV_STRIDE_AUTO);
  lv_display_set_draw_buffers(disp_drv, draw_buf, NULL);
  lv_display_set_color_format(disp_drv, LV_COLOR_FORMAT_RGB565);
  lv_display_set_flush_cb(disp_drv, my_disp_flush);

  /*Initialize the input device driver for touchpad*/
  indev_drv = lv_indev_create();
  lv_indev_set_type(indev_drv, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev_drv, my_touchpad_read);

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
    digitalWrite(TFT_BL, HIGH);
    lv_tick_inc(MY_LV_TICK_TIME);
    lv_timer_handler();
    vTaskDelay(5000);
    lv_tick_inc(5000);
    lv_task_handler();
    vTaskDelay(5000);
    SERIALDEBUG.println("printed Hello, world!");
#else
  // EEZ GUI init
  ui_init();

  // Initialize the input device driver for the encoder
  // and assign the encoder to the encoder group
  indev_enc = lv_indev_create();
  lv_indev_set_type(indev_enc, LV_INDEV_TYPE_ENCODER);
  lv_indev_set_read_cb(indev_enc, my_encoder_read);
  lv_indev_set_group(indev_enc, groups.encoder_group);

  lv_obj_set_parent(objects.popup_container, lv_layer_top());

#endif

  // Manually turn on backlight (avoid garbage at startup)
  // Now handled by flow itself
  //digitalWrite(TFT_BL, HIGH);

  xTimerStart(guiTimerHandle, 10);
  guiTaskReady = true;
  while (1)
  {
    unsigned long loopstart = millis();
    // Create stable local data structures used in ui_tick()
    state.getMeasuredStateCopy(&localstatecopy, 0);
    state.getSetStateCopy(&localsetcopy, 0);
    ui_tick();
    tick_screen_popup();
    lv_task_handler();
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

