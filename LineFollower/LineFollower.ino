// This line follower code works for
// two IR sensors given
// If you have more, your code and logic should change

// Code written here is for the global scope

// Define your motors pins here
int m11 = D0;
int m12 = D1;
int m21 = D2;
int m22 = D3;

// Define your IR input pins
int ir1 = D7;
int ir2 = D8;

// Here, we're using PWM
// so, we'll use some value in analogWrite()
// to set the percentage value to control speed of your motors
int a = 450;
// void setup() runs only once
// And its important you do your initalisations

void setup() {
  // Setting your motor pins as OUTPUT
  pinMode(m11,OUTPUT);
  pinMode(m12,OUTPUT);
  pinMode(m21,OUTPUT);
  pinMode(m22,OUTPUT);

  // If you're using enable of Motor Driver
  //pinMode(D4,OUTPUT);
  //pinMode(D5,OUTPUT);
  //digitalWrite(D4, HIGH);
  //digitalWrite(D5, HIGH);
  
  // Beginning serial comm. with your
  // computer, set your baud rate accordingly
  Serial.begin(9600);
  Serial.println("Line Follower");

}

void motor(int choice){
  // use this function to manipulate your motors
  switch(choice){
    case 1:{
      analogWrite(m11, a);
      analogWrite(m12, 0);
      analogWrite(m21, a);
      analogWrite(m22, 0);
      }break;
    // no case 2 as we don't go backwards with line follower
    case 3:{
      analogWrite(m11, a);
      analogWrite(m12, 0);
      analogWrite(m21, 0);
      analogWrite(m22, 0);
    }break;
    case 4:{
      analogWrite(m11, 0);
      analogWrite(m12, 0);
      analogWrite(m21, a);
      analogWrite(m22, 0);
    }break;
    case 0:{
      analogWrite(m11, 0);
      analogWrite(m12, 0);
      analogWrite(m21, 0);
      analogWrite(m22, 0);
    }break;
  }
}
// void loop() runs continously
// generally codes in microcontrollers are meant to run forever
void loop() {
  // We get two inputs from our 2 IR sensors
  int input1, input2;
  // taking inputs
  input1 = digitalRead(ir1);
  input2 = digitalRead(ir2);
  
  // Printing your input values
  Serial.println(input1);
  Serial.print(",");
  Serial.print(input2);
  
  // Put your logic here
  if(input1 ==1 && input2 == 1){
    motor(1);
  }
  else if(input1 == 1 && input2 == 0){
    motor(2);
  }
  else if(input1 ==0 && input2 == 1){
    motor(3);
  }
  // stopping is not required but it depends....
  else{
    motor(0);
  }
  
}
