/*
This is a minimal sketch without using the library at all but only works for
 the 10 pole dip switch sockets. It saves a lot of memory and thus might be
 very useful to use with ATTinys :)
 
 http://code.google.com/p/rc-switch/
 */

#include "RCLSwitch.h"

RCLSwitch::RCLSwitch(uint8_t RCLpin){
  _RCLpin=RCLpin;
  pinMode(_RCLpin, OUTPUT);
}

void RCLSwitch::changeInput(uint16_t &code) {
  if ((code&B1)==0) code--; //if ending is 10(on) -> 01(off), substract 1
  else code++;
  sendInput(code);
}

void RCLSwitch::sendInput(uint16_t code) {
  for (int nRepeat=0; nRepeat<6; nRepeat++) {
    for (int i=11; i>=0; i--) { //check every input bit
      transmit(1,3); //always send this before Tristate (part of Tri-State actually)
      if (code>>i &B1==1) {
        transmit(1,3); //send Tri-State'0'
      } 
      else {
        transmit(3,1); //send Tri-State'F'
      }
    }
    transmit(1,31); //sendSync
  }
}

void RCLSwitch::transmit(uint8_t nHighPulses, uint8_t nLowPulses) {
  digitalWrite(_RCLpin, HIGH);
  delayMicroseconds( 350 * nHighPulses);
  digitalWrite(_RCLpin, LOW);
  delayMicroseconds( 350 * nLowPulses);
}










