/*
  SendDemo
 Turns on/off Switch A, changes B
 
 Change the DIP config to your own wishes
 Make sure to use uint16_t and feed the changeInput only with a variable, not a static value
 */

#include "RCLSwitch.h"
const uint8_t RCLpin=9;
RCLSwitch myRCLSwitch(RCLpin);

uint16_t mhzUnit1 = 0B000110100001; //default off to turn it on

void setup(){
}

void loop(){
  //send input
  myRCLSwitch.sendInput(0B000111000010); // DIPs: 00011 100000 On: 10
  delay(1000);
  myRCLSwitch.sendInput(0B000111000001); // DIPs: 00011 100000 Off:01
  delay(1000);

  //change the Unit
  myRCLSwitch.changeInput(mhzUnit1);
  delay(1000);
}

