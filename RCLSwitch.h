/*
This is a minimal sketch without using the library at all but only works for
 the 10 pole dip switch sockets. It saves a lot of memory and thus might be
 very useful to use with ATTinys :)
 
 http://code.google.com/p/rc-switch/
 */

#ifndef RCLSwitch_h
#define RCLSwitch_h

#include "Arduino.h"

class RCLSwitch {
public:
  RCLSwitch(uint8_t RCLpin);
  void changeInput(uint16_t &code);
  void sendInput(uint16_t code);

private:
  uint8_t _RCLpin;
  void transmit(uint8_t nHighPulses, uint8_t nLowPulses);
};

#endif











