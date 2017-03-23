// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include<VirtualWire.h>
#include <Wire.h>

void setup() {
     Serial.begin(115200);
      vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(5000);   // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;
char msg[2];
void loop() {

    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  int i;

        digitalWrite(13, true); // Flash a light to show received good message
  // Message with a good checksum received, dump it.
  Serial.print("Got: ");
  
  for (i = 0; i < buflen; i++)
  {
      msg[i]=char(buf[i]);
      
  }
 Serial.print(msg[0]);
 
 digitalWrite(13, false);
    




  
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(msg[0]);       

  Wire.endTransmission();    // stop transmitting


  delay(500);
}}
