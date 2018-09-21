#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <ESP8266WiFi.h>


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

WiFiServer server(80);

// delay variable, feel free to change it
// remember in delay() input is in milliseconds
int t_delay = 1500; 

char* ssid = "ganeshr4";
char* password  = "ganesh123";

Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

int incomingByte = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin();

  myMotor1->setSpeed(150);
  myMotor2->setSpeed(150);

  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  // WiFi connecting starts
  WiFi.begin(ssid, password);
  // while loop to wait for your connection
  // Here status() function is for checking your connection
  // WL_CONNECTED is in-built variable
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // If dots are printing continously, NodeMCU is not connecting
  // properly to WiFi, check your SSID and Password
  // Or keep restarting your NodeMCU
  
  Serial.println("");
  Serial.println("WiFi connected");
  // Start the server 
  // In this case, your NodeMCU is your server
  // so only one time initialisation is enough
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void motor(int choice){
  switch(choice){
    case 1:{
      Serial.println("Straight");
      myMotor1->run(FORWARD);
      myMotor2->run(FORWARD);
      delay(100);
    }break;
    case 2:{
      Serial.println("Sharp Right");
      myMotor1->run(FORWARD);
      myMotor2->run(BACKWARD);
      delay(100);
    }break;
    case 3:{
      Serial.println("Sharp Left");
      myMotor1->run(BACKWARD);
      myMotor2->run(FORWARD);
      delay(100);
    }break;
    case 4:{
      Serial.println("Right");
      myMotor1->run(FORWARD);
      myMotor2->run(RELEASE);
      delay(100);
    }break;
    case 5:{
      Serial.println("Left");
      myMotor1->run(RELEASE);
      myMotor2->run(FORWARD);
      delay(100);
    }break;
    case 0:{
      Serial.println("Still");
      myMotor1->run(RELEASE);
      myMotor2->run(RELEASE);
      delay(100);
    }break;
  }
}

void loop() {
//  // put your main code here, to run repeatedly:
//  if (Serial.available() > 0) {
//                // read the incoming byte:
//                incomingByte = Serial.read();
//
//                // say what you got:
//                Serial.print("I received: ");
//                Serial.println(incomingByte-48, DEC);
//        }
////  Serial.println(j);
//  motor(incomingByte-48);
//  delay(100);
WiFiClient client = server.available();
 // we put client in loop, because we want to check the
 // connection with client continously
 if (!client) {
  // If there is no client, we cancel this instance of loop()
  return;
 }
 
 // Wait until the client sends some data
 Serial.println("New Client");
 // Checking connection
 while(!client.available()){
  delay(1);
 }
 // String is somewhat easier to handle char array
 // Read the first line of the request
 // request is going to contain client requests to server
 String request = client.readStringUntil('\r');
 Serial.println(request);
 client.flush();

 // Match the request
 // indexOf() function checks the string and
 // returns the index of the first occurence of
 // your search element 
 // Here, we use this to our advantage and 
 // manipulate your bot's movements
 
 if (request.indexOf("/FORWARD") != -1) {
  motor(1);
 }
 if (request.indexOf("/BACKWARD") != -1) {
  motor(2);
 }
 if (request.indexOf("/LEFT") != -1) {
  motor(3);
 }
 if (request.indexOf("/RIGHT") != -1) {
  motor(4);
 }
 if (request.indexOf("/STOP") != -1) {
  motor(0);
 }

 // some data you need to send your client
 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println(""); // do not forget this one

 // Put your Website code here:
 client.println("<!DOCTYPE HTML>");
 client.println("<html>");
 client.println("<br><br>");
 client.println("<h1><center>WiFi-Bot</center></h1><br>");
 client.println("<h3><center>Powered By RCS</center></h3><br>");
 client.println("<hr color = green>");
 client.println("<center><a href=\"/FORWARD\"\"><button>MOVE FORWARD </button></a>");
 client.println("<a href=\"/BACKWARD\"\"><button>MOVE BACKWARD</button></a><br />");
 client.println("<a href=\"/RIGHT\"\"><button>MOVE LEFT</button></a><br />");
 client.println("<a href=\"/LEFT\"\"><button>MOVE RIGHT</button></a><br />");
 client.println("<a href =\"/STOP\"\"><button>STOP</button></a><br/>");
 client.println(" </center> <hr color= green>");
 client.println("</html>");

 delay(1);
 Serial.println("");


  
}
