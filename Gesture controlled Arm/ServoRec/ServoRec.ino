
#include <Servo.h>
#include <Wire.h>
 
Servo myservo1;
Servo myservo2;
int poslr = 90; int posud=90;char x;
void setup()
{
 Serial.begin(115200);
 myservo1.attach(9);
 myservo2.attach(3);
 Wire.begin(8);                // join i2c bus with address #8
  //Wire.onReceive(receiveEvent);
  int pos;
   for (pos = 0; pos <= 90; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);
    myservo2.write(pos);// tell servo to go to position in variable 'pos'
    delay(15);   
  Wire.onReceive(receiveEvent);// waits 15ms for the servo to reach the position
  }
}

void loop()
{
  //x=Wire.read();
 //Serial.println(x);
  
 switch(x){
  case '1':poslr!=180?poslr=poslr-1:poslr;break;
  case '2':poslr!=0?poslr=poslr+1:poslr;break;
  case '3':posud!=70?posud=posud-1:posud;break;
  case '4':posud!=180?posud=posud+1:posud;break;
   
 }
 myservo1.write(poslr);delay(55);
 myservo2.write(posud);delay(55);

}
void receiveEvent(int howMany) {
  /*while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
   Serial.print(c);
   }*/
x=Wire.read();

Serial.println(x); 
}
 



