// Data Acquisition Code
// Here, we are going to send Ultrasonic sensor data to Ubidots cloud
// Connect your sensor's input pin to D3 pin
// Firstly, follow instructions in https://ubidots.com/docs/devices/nodeMCU.html
// and see step 1 and download Ubidots zip file

// Header Files
#include "UbidotsMicroESP8266.h"

// Each cloud service works differently
// each of them use different ways to connect your device
// For Ubidots, we need id and token

// Put your variable ID here
#define ID_1 "idididididididid"

// Put here your Ubidots TOKEN
#define TOKEN  "tokentokentokentoken"

// You need to connected to internet to connect to your cloud
// so, we need Data for your WiFi configuration
#define WIFISSID "SSID" // Put here your Wi-Fi SSID
#define PASSWORD "Password" // Put here your Wi-Fi password

// Here, client object is initialised
Ubidots client(TOKEN);

// void setup() runs only once
// And its important you do your initalisations
void setup(){
  // Beginning serial comm. with your
  // computer, set your baud rate accordingly
  Serial.begin(115200);
  // Starting your connection to your WiFi
  client.wifiConnection(WIFISSID, PASSWORD);
}

// void loop() runs continously
// generally codes in microcontrollers are meant to run forever
void loop(){
  long duration, inches, cm;

  // The PING is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(D7, OUTPUT);
  digitalWrite(D7, LOW);
  delayMicroseconds(2);
  digitalWrite(D7, HIGH);
  delayMicroseconds(5);
  digitalWrite(D7, LOW);

  // The same pin is used to read the signal from the PING: a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(D3, INPUT);
  duration = pulseIn(D3, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  Serial.println(cm);
  client.add(ID_1, cm);
  //upload the value to ubidots
  client.sendAll(false);
  delay(2000);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
