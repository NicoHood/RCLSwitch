/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 SimpleSendDemo
 Turns on/off a remote unit
 */

#include "RCLSwitch.h"
const uint8_t RCLpin = 7;
RCLSwitch myRCLSwitch(RCLpin);

uint8_t channel = B00001;
uint8_t button = B10000;
bool state = false;

void setup() {
}

void loop() {
  // send input
  myRCLSwitch.write(channel, button, state);

  // change state
  state = !state;

  delay(3000);
}

