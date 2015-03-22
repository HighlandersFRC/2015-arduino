//DigiJoystick test and usage documentation

#include "DigiJoystick.h"

const int DOUT_GROUND = 6; // Just a pin that is set low to act as a ground
const int DIN_START = 7;                     // Start of digital inputs
const int DIN_END = 13;                      // One past the last pin index
const int DIN_COUNT = DIN_END - DIN_START;

const int DIN_B1 = 0;
const int DIN_B2 = 1;
const int DIN_B3 = 2;

void setup() {
  pinMode(DOUT_GROUND, OUTPUT);
  digitalWrite(DOUT_GROUND, LOW);
  
  for (int i = DIN_START; i < DIN_END; ++i) {
    pinMode(i, INPUT);
  }
  
  pinMode(DIN_B1, INPUT);
  pinMode(DIN_B2, INPUT);
  pinMode(DIN_B3, INPUT);
}

void loop() {
  byte lbyte = 0x00;
  
  for(int i = DIN_START; i < DIN_END; ++i) {
    byte buttonState = digitalRead(i);
    lbyte |= (buttonState << (i - DIN_START));
  }
  byte buttonState = digitalRead(DIN_B1);
  lbyte |= (buttonState << 5);
  buttonState = digitalRead(DIN_B2);
  lbyte |= (buttonState << 6);
  buttonState = digitalRead(DIN_B3);
  lbyte |= (buttonState << 7);
  
  // Set buttons like this (lowByte, highByte)
  DigiJoystick.setButtons(lbyte, 0x00);

  // it's best to use DigiJoystick.delay() because it knows how to talk to
  // the connected computer - otherwise the USB link can crash with the 
  // regular arduino delay() function
  DigiJoystick.delay(50); // wait 50 milliseconds
}
