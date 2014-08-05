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

#ifndef RCLSwitch_h
#define RCLSwitch_h

#include "Arduino.h"

class RCLSwitch{
public:
	inline RCLSwitch(uint8_t RCLpin){
		_RCLpin = RCLpin;
		pinMode(_RCLpin, OUTPUT);
	}

	inline void write(uint8_t channel, uint8_t button, bool state){
		uint16_t code = (channel << 7) | ((button&0x1F) << 2) | (state<<1) | (!state);
		write(code);
	}

	inline void write(uint16_t code){
		for (int nRepeat = 0; nRepeat < 5; nRepeat++) {
			// check every input bit
			for (int i = 0; i <12; i++) { 

				// always send this before Tristate (part of Tri-State actually)
				transmit(1, 3); // send Tri-State'0'

				if (code >> (11-i) & 0x01 == 1)
					// send Tri-State'0'
					transmit(1, 3); 
				else
					// send Tri-State'F'
					transmit(3, 1);
			}
			// sendSync
			transmit(1, 31); 
		}
	}

private:
	uint8_t _RCLpin;

	inline void transmit(uint8_t nHighPulses, uint8_t nLowPulses){
		digitalWrite(_RCLpin, HIGH);
		delayMicroseconds(350 * nHighPulses);
		digitalWrite(_RCLpin, LOW);
		delayMicroseconds(350 * nLowPulses);
	}
};

#endif











