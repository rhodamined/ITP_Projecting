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

int receivedMotorSpd;
int receivedMotorDir;
int motorSpd;
int motorDir;

int dataIn;

void setup() {
  // Serial
  Serial.begin(9600); 

  // Wifi
  connectWifi();

  // Test only
  pinMode(13, OUTPUT); // led
  pinMode(21, INPUT); // button

  // to Arduino UNO
  pinMode(out0, OUTPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(out5, OUTPUT);

}

void loop() {

  int reading = digitalRead(21);

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        getData();
      }
    }
  }
  // set the LED:
  digitalWrite(13, ledState);

  if (Serial.available() > 0) { // usb

    dataIn = Serial.parseInt();
    Serial.println(dataIn);

    if (dataIn == 1) {
      Serial.println("yay");
      digitalWrite(out5, HIGH);
    } else if (dataIn == 0) {
      Serial.println("boo");
      digitalWrite(out5, LOW);
    }
  }

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

