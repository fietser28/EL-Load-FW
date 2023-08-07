/* Rotary encoder handler for arduino.
 *
 * Copyright 2011 Ben Buxton. Licenced under the GNU GPL Version 3.
 * Contact: bb@cactii.net
 *
 * SPDX-FileCopyrightText: 2023 Modifications: Jan Nieuwstad <jan.sources@nieuwstad.net>
 * Downloaded from and modified: https://github.com/brianlow/Rotary.git
 */


#include "Arduino.h"
#include "Rotary.h"

/*
 * The below state table has, for each state (row), the new state
 * to set based on the next encoder output. From left to right in,
 * the table, the encoder outputs are 00, 01, 10, 11, and the value
 * in that position is the new state to set.
 */

#define R_START 0x0

#ifdef HALF_STEP
// Use the half-step state table (emits a code at 00 and 11)
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
const unsigned char ttable[6][4] = {
  // R_START (00)
  {R_START_M,            R_CW_BEGIN,     R_CCW_BEGIN,  R_START},
  // R_CCW_BEGIN
  {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START},
  // R_CW_BEGIN
  {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START},
  // R_START_M (11)
  {R_START_M,            R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},
  // R_CW_BEGIN_M
  {R_START_M,            R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},
  // R_CCW_BEGIN_M
  {R_START_M,            R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW},
};
#else
// Use the full-step state table (emits a code at 00 only)
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};
#endif

/*
 * Constructor. Each arg is the pin number for each encoder contact.
 */
Rotary::Rotary(char _pin1, char _pin2) {
  // Assign variables.
  _managehw = true;
  pin1 = _pin1;
  pin2 = _pin2;
  // Initialise state.
  state = R_START;
  // Don't invert read pin state by default
  inverter = 0;
}

Rotary::Rotary() {
  _managehw = false;
  state = R_START;
  inverter = 0;
}

void Rotary::begin(bool internalPullup, bool flipLogicForPulldown) {
  if (_managehw) {
  if (internalPullup){
    // Enable weak pullups
    pinMode(pin1,INPUT_PULLUP);
    pinMode(pin2,INPUT_PULLUP);
  }else{
    // Set pins to input.
    pinMode(pin1, INPUT);
    pinMode(pin2, INPUT);
  }
  }
  inverter = flipLogicForPulldown ? 1 : 0;
}

void Rotary::begin(bool flipLogic) {
  inverter = flipLogic ? 1 : 0;
}

unsigned char Rotary::process() {
  // Grab state of input pins.
  unsigned char pinstate = ((inverter ^ digitalRead(pin2)) << 1) | (inverter ^ digitalRead(pin1));
  // Determine new state from the pins and state table.
  state = ttable[state & 0xf][pinstate];
  // Return emit bits, ie the generated event.
  return state & 0x30;
}

unsigned char Rotary::process(unsigned char pin1State, unsigned char pin2State) {
	  // Grab state of input pins.
	  //unsigned char pinstate = (pin2State << 1) | pin1State;
    unsigned char pinstate = ((inverter ^ pin2State) << 1) | (inverter ^ pin1State);
	  // Determine new state from the pins and state table.
	  state = ttable[state & 0xf][pinstate];
	  // Return emit bits, ie the generated event.
	  return state & 0x30;
}

uint8_t lrmem = 3;
int lrsum = 0;
int num = 0;

int8_t rotary(int8_t l, int8_t r)
{
   static int8_t TRANS[] = {0,-1,1,14,1,0,14,-1,-1,14,0,1,14,1,-1,0};

   lrmem = ((lrmem & 0x03) << 2) + 2*l + r;
   lrsum = lrsum + TRANS[lrmem];
   /* encoder not in the neutral state */
   if(lrsum % 4 != 0) return(0);
   /* encoder in the neutral state */
   if (lrsum == 4)
      {
      lrsum=0;
      return(1);
      }
   if (lrsum == -4)
      {
      lrsum=0;
      return(-1);
      }
   /* lrsum > 0 if the impossible transition */
   lrsum=0;
   return(0);
}
