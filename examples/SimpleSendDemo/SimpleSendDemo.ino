/*
  Copyright (c) 2014-2016 NicoHood
  See the readme for credit to other people.

  SimpleSendDemo
  Turns on/off a remote unit
*/

#include "RCLSwitch.h"

#define RCLpin 7
CRCLSwitch<RCLpin> RCLSwitch;

bool state = false;

void setup() {
  // Prepare pin for sending
  RCLSwitch.begin();
}

void loop() {
  // Send input
  RCLSwitch.write(RCL_CHANNEL_1, RCL_BUTTON_A, state);

  // Change state
  state = !state;

  // Wait some time
  delay(3000);
}

