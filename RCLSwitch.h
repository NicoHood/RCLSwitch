/*
This is a minimal sketch without using the library at all but only works for
the 10 pole dip switch sockets. It saves a lot of memory and thus might be
very useful to use with ATTinys :)

Copyright (c) 2014 NicoHood.  All right reserved.

Original library:
http://code.google.com/p/rc-switch/
*/

#ifndef RCLSwitch_h
#define RCLSwitch_h

#include "Arduino.h"

class RCLSwitch {
public:
	inline RCLSwitch(uint8_t RCLpin){
		_RCLpin=RCLpin;
		pinMode(_RCLpin, OUTPUT);
	};

	inline void changeInput(uint16_t &code){
		//if ending is 10(on) -> 01(off), substract 1
		if ((code&B1)==0) code--; 
		else code++;
		sendInput(code);
	};

	inline void sendInput(uint16_t code){
		for (int nRepeat=0; nRepeat<6; nRepeat++) {
			for (int i=11; i>=0; i--) { //check every input bit
				transmit(1,3); //always send this before Tristate (part of Tri-State actually)
				if ((code>>i) &0x01==1) {
					transmit(1,3); //send Tri-State'0'
				} 
				else {
					transmit(3,1); //send Tri-State'F'
				}
			}
			transmit(1,31); //sendSync
		}
	};

	//just a test
	inline void write(uint16_t letter, uint8_t &state){
		state^=1;
		uint16_t code =  (letter<<2) | (1 << state) ;


				for (int nRepeat=0; nRepeat<6; nRepeat++) {
			for (int i=11; i>=0; i--) { //check every input bit
				transmit(1,3); //always send this before Tristate (part of Tri-State actually)
				if ((code>>i) &0x01==1) {
					transmit(1,3); //send Tri-State'0'
				} 
				else {
					transmit(3,1); //send Tri-State'F'
				}
			}
			transmit(1,31); //sendSync
		}
	};

private:
	uint8_t _RCLpin;

	void transmit(uint8_t nHighPulses, uint8_t nLowPulses);
};

#endif











