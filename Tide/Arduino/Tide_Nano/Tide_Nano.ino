#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include <elapsedMillis.h>
#include <Bounce2.h>
#include "arduino_secrets.h"

// ---------------
// WIFI Setup
// ---------------
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// DNS alias doesn't work -- needs to be heroku endpoint TT^TT
const char serverAddress[] = SECRET_ADDRESS;  // server address
int port = 443;

WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

int status = WL_IDLE_STATUS;

// ---------------
// Motor Control
// ---------------
// in pins for commmunicating with Nano 33 IOT
int out0 = 2;
int out1 = 3; 
int out2 = 4;
int out3 = 5;
int out4 = 6;
int out5 = 7;

// ------------------------
// Button & State tracking
// ----------------------
int buttonPin = 21;
Bounce2::Button button = Bounce2::Button(); // INSTANTIATE A Bounce2::Button OBJECT
int ledState = HIGH;        // tester for button & mode
int MODE = HIGH;        // HIGH: poll real-time data
                        // HIGH: poll manual web data

// ---------------
// Time-keeping
// ---------------
elapsedMillis clock;

// ---------------
// Motors....
// ---------------

// manually set min and max -- should reflect node.js
int motorSpdMax = 1000;
int motorSpdMin = 40;

// received data from web call
int receivedMotorSpd;
int receivedMotorDir;

// current state 
int motorSpd;
int motorDir;

// to send to Uno
int motorPins[6];


bool REST_SUCCESS;

void setup() {
  // Serial
  Serial.begin(9600); 

  // Wifi
  connectWifi();

  // LED
  pinMode(13, OUTPUT);

  // Button
  button.attach(buttonPin, INPUT);
  button.interval(30);
  button.setPressedState(HIGH); 

  // to Arduino UNO
  pinMode(out0, OUTPUT);  // Motor DIRECTION
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(out5, OUTPUT);


  // make initial API call
  REST_SUCCESS = getData();
    
  if (REST_SUCCESS == true) {
    parseData();
  }

}

void loop() {

  // Read button
  button.update();
  if ( button.pressed() ) {

    Serial.println("Button Pushed");
    ledState = !ledState;
    MODE = !MODE;

    Serial.print("Mode: ");
    Serial.println(MODE);

    REST_SUCCESS = getData();
      
    // only process if api call successful
    if (REST_SUCCESS == true) {
      Serial.println("success");
      parseData();
      clock = 0;
    }
  }

  // make API call every 10 minutes
  if (MODE == 1) {
    if (clock > 600000) {
      REST_SUCCESS = getData();
      
      // only process if api call successful
      if (REST_SUCCESS == true) {
        parseData();
      }
      clock = 0; // remember to reset!
    }
  }

  if (MODE == 0) {
    if (clock > 5000) {
      Serial.println("blah blah blah");
      clock = 0;
    }
  }

  // Send to Uno 
  digitalWrite(out0, motorPins[0]);
  digitalWrite(out1, motorPins[1]);
  digitalWrite(out2, motorPins[2]);
  digitalWrite(out3, motorPins[3]);
  digitalWrite(out4, motorPins[4]);
  digitalWrite(out5, motorPins[5]);

  // update LED lol
  digitalWrite(13, ledState);

}

bool getData() {
  // assemble the path for the GET message:

  String path;
  String contentType = "application/json";

  if (MODE == HIGH) { // default
    path = "/x88uv9"; // this endpoint sends realtime data mapped motorspd, motordir
  } else {
    path = "/v89sd0"; // this endpoint sends manual data from website
  }
  
  
  // send the GET request
  Serial.println("making GET request");
  Serial.println(path);   
  
  client.get(path);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  if (statusCode == 200) {
    // parse the response to get the value of aqius 
    int labelStart = response.indexOf("motor_spd");
    int valueStart = response.indexOf(":", labelStart);
    int valueEnd = response.indexOf(",", labelStart);
    String valueS = response.substring(valueStart + 1, valueEnd);
    receivedMotorSpd = valueS.toInt();

    labelStart = response.indexOf("motor_dir");
    valueStart = response.indexOf(":", labelStart);
    valueEnd = response.indexOf(",", labelStart);
    valueS = response.substring(valueStart + 1, valueEnd);
    receivedMotorDir = valueS.toInt();

    Serial.print("Received Motor Speed: ");
    Serial.println(receivedMotorSpd);
    Serial.print("Received Motor Dir: ");
    Serial.println(receivedMotorDir);

    return true;
  } 
  else {
    return false;
  }
}

void parseData() {

  Serial.println("Function: parseData");

  // clean garbage speeds
    if (receivedMotorSpd <= motorSpdMax && receivedMotorSpd >= motorSpdMin) {
      motorSpd = receivedMotorSpd;
      Serial.print("Motor speed: ");
      Serial.println(motorSpd);
    }

  // clean garbage dir
  if (receivedMotorDir == 0 || receivedMotorDir == 1) {
    motorDir = receivedMotorDir;
    Serial.print("Motor dir: ");
    Serial.println(motorDir);
  }

  // divide max-min by 32 bits
  // auto floors bc int
  int motorStep = (motorSpdMax - motorSpdMin)/ 32;

  // dumb way to handle range being 0-31
  if (motorSpd == motorSpdMax) {
    motorSpd--;
  }

  // speed as a int from 0 to 31
  int spd = (receivedMotorSpd - motorSpdMin) / motorStep;
  Serial.print("Speed out of 32: ");
  Serial.println(spd);

  // update pinStates
  motorPins[0] = receivedMotorDir; // should be received as 1 or 0
  motorPins[1] = bitRead(spd, 0);
  motorPins[2] = bitRead(spd, 1);
  motorPins[3] = bitRead(spd, 2);
  motorPins[4] = bitRead(spd, 3);
  motorPins[5] = bitRead(spd, 4); // dumb dumb dumb

  // print binary for idiot check
  for (int i = 0; i < 6; i++) {
    Serial.print(motorPins[i]);
  }
  Serial.println("\n");
}


void connectWifi() {
  
  while (!Serial);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);     // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

}

