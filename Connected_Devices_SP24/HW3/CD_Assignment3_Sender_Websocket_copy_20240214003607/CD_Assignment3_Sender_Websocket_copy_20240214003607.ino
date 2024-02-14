//------ INCLUDE ------//
#include <Adafruit_VL53L0X.h>
#include <WiFiNINA.h>                    
#include "config.h"                       // network config

//------ WIFI CONFIG ------//
WiFiClient client;

const char server[] = MATT_server;        // local IP address of receiver device goes here
const int portNum = MATT_portNum;         // desired port #. Make sure the receiver is listening on the same port!

const char WIFI_SSID[] = MATT_WIFI_SSID;  // WiFi network name
const char WIFI_PASS[] = MATT_WIFI_PASS;  // WiFi password 

//------ TIME OF FLIGHT INIT ------//
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

//------ LEDS ------//
const int redLedPin = 14;
const int greenLedPin = 15;

//------ Global vars ------//
// char lastMeasure[] = "";
int lastMeasure = 9999;

void setup() {
  // init serial
  Serial.begin(9600);

  // indicator lights
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // init TOF sensor
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // lox.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE);

  // retry connection until WiFi is connected successfully
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect to SSID: ");
    // Attempt connection to WPA/WPA2 network.
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    digitalWrite(greenLedPin, HIGH);  // green indic light while trying to connect to wifi

    delay(3000);
  }
  digitalWrite(greenLedPin, LOW);  // green indic light off once wifi connected

  Serial.println("connected!");

  
}

void loop() {

  VL53L0X_RangingMeasurementData_t measure;
        
  lox.rangingTest(&measure, true); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    lastMeasure = measure.RangeMilliMeter;
  } else {
    lastMeasure = 9999;
  }

  // connect to client if disconnected, or send TCP message if conected
  if (!client.connected()) {
    toggleLED("red");
    Serial.println("connecting");
    client.connect(server, portNum);
    delay(1000);
    return;
  } else {
    // add something more interesting here
    toggleLED("green");
    // Serial.print("sending TCP message");
    Serial.println(lastMeasure);
    client.println(lastMeasure);

    delay(50);
  }
}

void toggleLED(String color) {
  if (color == "red") {
    digitalWrite(greenLedPin, LOW); 
    digitalWrite(redLedPin, HIGH); 
  }

  else if (color == "green") {
    digitalWrite(greenLedPin, HIGH); 
    digitalWrite(redLedPin, LOW); 
  }

  else {
    Serial.println("Color arg not found: " + color);
  }
}