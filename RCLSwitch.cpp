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

#include "RCLSwitch.h"

void RCLSwitch::changeInput(uint16_t &code) {
// if ending is 10(on) -> 01(off), substract 1
	if ((code&B1)==0) code--; 
	else code++;
	sendInput(code);
}

void RCLSwitch::sendInput(uint16_t code) {
	for (int nRepeat=0; nRepeat<6; nRepeat++) {
		for (int i=11; i>=0; i--) { //check every input bit
			transmit(1,3); //always send this before Tristate (part of Tri-State actually)
			if (code>>i &0x01==1) {
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










