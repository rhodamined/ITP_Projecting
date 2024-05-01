#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
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

// ---------------
// Button
// ---------------
int ledState = HIGH;        // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 30;  

// ---------------
// Global Vars
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

int motorPins[6];

// testing only
int dataIn;

bool REST_SUCCESS;

void setup() {
  // Serial
  Serial.begin(9600); 

  // Wifi
  connectWifi();

  // Test only
  pinMode(13, OUTPUT); // led
  pinMode(21, INPUT); // button

  // to Arduino UNO
  pinMode(out0, OUTPUT);  // Motor DIRECTION
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(out5, OUTPUT);

}

void loop() {

  // make API call, update receivedMotorSpd and receivedMotorDir
  REST_SUCCESS = getData();

  // Update states
  if (REST_SUCCESS == true) {
    
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
    
    // parse to pin states
    parseData();
  }

  // send to Uno 
  digitalWrite(out0, motorPins[0]);
  digitalWrite(out1, motorPins[1]);
  digitalWrite(out2, motorPins[2]);
  digitalWrite(out3, motorPins[3]);
  digitalWrite(out4, motorPins[4]);
  digitalWrite(out5, motorPins[5]);

  Serial.println("Waiting 10 minutes...");
  // wait 10 minutes lol
  delay(600000);



  // ---- BUTTON NONSENSE ----
  // Button reading
  int reading = digitalRead(21);

  // Button is a test
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        ledState = !ledState;
        getData();
      }
    }
  }
  // set the LED:
  digitalWrite(13, ledState);

}

bool getData() {
  // assemble the path for the GET message:
  String path = "/x88uv9"; // this endpoint sends motorspd, motordir
  String contentType = "application/json";
  
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

  Serial.println("function: parseData");

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

