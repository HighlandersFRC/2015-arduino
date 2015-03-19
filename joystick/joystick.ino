//DigiJoystick test and usage documentation

#include "DigiJoystick.h"

const int DIN_START = 7;                     // Start of digital inputs
const int DIN_END = 13;                      // One past the last pin index
const int DIN_COUNT = DIN_END - DIN_START;

void setup() {
  for (int i = DIN_START; i < DIN_END; ++i) {
    pinMode(i, INPUT);
  }
}

void loop() {
  byte lbyte = 0x00;
  
  for(int i = DIN_START; i < DIN_END; ++i) {
    byte buttonState = digitalRead(i);
    lbyte |= (buttonState << (i - DIN_START));
  }
  
  
  // Set buttons like this (lowByte, highByte)
  DigiJoystick.setButtons(lbyte, 0x00);

  // it's best to use DigiJoystick.delay() because it knows how to talk to
  // the connected computer - otherwise the USB link can crash with the 
  // regular arduino delay() function
  DigiJoystick.delay(50); // wait 50 milliseconds
}
