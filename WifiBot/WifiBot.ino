// Header files
#include <ESP8266WiFi.h>

// Code written here is for the global scope

// Data for your WiFi configuration
const char* ssid = "GiveYourWiFiSSID";
const char* password = "Password";

// Define your motors pins here
int m11 = D0;
int m12 = D1;
int m21 = D2;
int m22 = D3;

// Initialising server object
WiFiServer server(80);

// delay variable, feel free to change it
// remember in delay() input is in milliseconds
int t_delay = 1500; 

// void setup() runs only once
// And its important you do your initalisations
void setup() {
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
  delay(5);

  // Initialisation, pretty much not required
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
  
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
  // use this function to manipulate your motors
  switch(choice){
    case 1:{
      digitalWrite(m11, HIGH);
      digitalWrite(m12, LOW);
      digitalWrite(m21, HIGH);
      digitalWrite(m22, LOW);
      delay(t_delay);
    }break;
    case 2:{
      digitalWrite(m11, LOW);
      digitalWrite(m12, HIGH);
      digitalWrite(m21, LOW);
      digitalWrite(m22, HIGH);
      delay(t_delay);
    }break;
    case 3:{
      digitalWrite(m11, HIGH);
      digitalWrite(m12, LOW);
      digitalWrite(m21, LOW);
      digitalWrite(m22, LOW);
      delay(t_delay);
    }break;
    case 4:{
      digitalWrite(m11, LOW);
      digitalWrite(m12, LOW);
      digitalWrite(m21, HIGH);
      digitalWrite(m22, LOW);
      delay(t_delay);
    }break;
    case 0:{
      digitalWrite(m11, LOW);
      digitalWrite(m12, LOW);
      digitalWrite(m21, LOW);
      digitalWrite(m22, LOW);
      delay(t_delay);
    }break;
  }
}

// void loop() runs continously
// generally codes in microcontrollers are meant to run forever
void loop() {
 // Check if a client has connected
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




