/*
Copyright (c) 2014-2018 NicoHood
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

// Include guard
#pragma once

// Software version
#define RCLSWITCH_VERSION 141

#ifdef ARDUINO
#include "Arduino.h"
#endif

// Definitions for the tiny DIP switch to set channel and button trigger
#define RCL_DIP(a, b, c, d, e) (((a) & 0x01 << 4) | ((b) & 0x01 << 3) \
| ((c) & 0x01 << 2) | ((d) & 0x01 << 1) | ((e) & 0x01 << 0))

#define RCL_CHANNEL_1 (1 << 4)
#define RCL_CHANNEL_2 (1 << 3)
#define RCL_CHANNEL_3 (1 << 2)
#define RCL_CHANNEL_4 (1 << 1)
#define RCL_CHANNEL_5 (1 << 0)

#define RCL_BUTTON_A (1 << 4)
#define RCL_BUTTON_B (1 << 3)
#define RCL_BUTTON_C (1 << 2)
#define RCL_BUTTON_D (1 << 1)
#define RCL_BUTTON_E (1 << 0)


template <uint8_t pin>
class CRCLSwitch{
public:
	inline CRCLSwitch(void){
		// Empty
	}

	inline void begin(void){
		// Prepare pin for sending
		pinMode(pin, OUTPUT);
	}

	inline void end(void){
		// End transmitting mode
		pinMode(pin, INPUT);
		digitalWrite(pin, LOW);
	}

	inline void write(const uint8_t channel, const uint8_t button, const bool state){
		// Transforms simple input into the other function overload
		uint16_t code = (channel << 7) | ((button & 0x1F) << 2) | (state + 1);
		write(code);
	}

	inline void write(const uint16_t code){
		// Repeat sending
		for (uint8_t nRepeat = 0; nRepeat < 5; nRepeat++) {

			// Check every input bit
			for (uint8_t i = 0; i < 12; i++) {

				// Always send Tri-State'0' first
				transmit(1, 3);

				// Send Tri-State'0'
				if ((code >> (11 - i) & 0x01) == 1)
					transmit(1, 3);

				// Send Tri-State'F'
				else
					transmit(3, 1);
			}
			// Send Sync
			transmit(1, 31);
		}
	}

private:
	inline void transmit(const uint8_t nHighPulses, const uint8_t nLowPulses){
		// Transmits data
		digitalWrite(pin, HIGH);
		delayMicroseconds(350 * nHighPulses);
		digitalWrite(pin, LOW);
		delayMicroseconds(350 * nLowPulses);
	}
};
