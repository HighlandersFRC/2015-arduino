/* 
 * This code is based on the sample code from Pulsed Light 3D: http://pulsedlight3d.com
 */

#include <DigiCDC.h>
#include <Wire.h>

#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x04          // Value to initiate ranging.
#define    RegisterHighLowB    0x8f          // Register to get both High and Low bytes in 1 call.

int reading = 0;
char valueStr[10];

void setup() {
  SerialUSB.begin();     // start serial communication at 9600bps
  Wire.begin();          // join i2c bus
  SerialUSB.refresh();
}

void loop() {
  SerialUSB.refresh();
  
  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterMeasure);               // sets register pointer to  (0x00)  
  Wire.write((int)MeasureValue);                  // value to initiate rangin
  Wire.endTransmission();                         // stop transmitting

  SerialUSB.delay(20); // Wait 20ms for transmit

  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterHighLowB);              // sets register pointer to (0x8f)
  Wire.endTransmission();                         // stop transmitting

  Wire.requestFrom((int)LIDARLite_ADDRESS, 2); // request 2 bytes from LIDAR-Lite

  if(Wire.available() >= 2) {  // if two bytes were received
    reading = Wire.read();     // receive low byte (overwrites previous reading)
    Wire.read();               // discard high byte (seems to be garbage?)
    
    if (SerialUSB.available()) {
      sprintf(valueStr, "%u\n", reading);
      SerialUSB.write(valueStr); // print the reading
    }
  }

}

