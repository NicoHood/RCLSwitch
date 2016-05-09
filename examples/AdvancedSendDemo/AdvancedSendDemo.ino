/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 AdvancedSendDemo
 Turns on/off a remote unit
 */

#include "RCLSwitch.h"

const uint8_t RCLpin = 7;
CRCLSwitch<RCLpin> RCLSwitch;

// Channel: 00001 Button: 100000 Off: 01 On :10
uint16_t remoteUnit = 0B0000011000010;

void setup() {
}

void loop() {
  // send input
  RCLSwitch.write(remoteUnit);

  // switch the last 2 bits
  remoteUnit ^= 0x03;

  delay(3000);
}

