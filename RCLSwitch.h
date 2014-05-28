/*
Copyright (c) 2014 NicoHood
See the readme for credit to other people.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/*
This is a minimal sketch without using the library at all but only works for
the 10 pole dip switch sockets. It saves a lot of memory and thus might be
very useful to use with ATTinys :)

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

	void changeInput(uint16_t &code);
	void sendInput(uint16_t code);

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











