//------ INCLUDE ------//
#include <ArduinoMqttClient.h>
#include <Adafruit_VL53L0X.h>
#include <WiFiNINA.h>
#include "config.h"

//------ WIFI & MQTT CONFIG ------//
WiFiClient wifi;
MqttClient mqtt(wifi);

//WiFi network info: ssid and password
const char wifi_ssid[] = TETHER_WIFI_SSID;
const char wifi_pass[] = TETHER_WIFI_PASS;

//MQTT broker info: url and port (1883 default for MQTT)
const char broker[] = YONE_MQTT_URL;
const int  port = YONE_MQTT_PORT;

//if needed: broker authentication credentials
const char mqtt_user[] = YONE_MQTT_USER;
const char mqtt_pass[] = YONE_MQTT_PASS;

//the topic this device will publish messages to
const char pubTopic[] = "Jasper_TOF";


//------ TIME OF FLIGHT INIT ------//
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

//------ HARDWARE ------//
const int redLedPin = 14;
const int greenLedPin = 15;
const int buttonPin = 12;

//------ Global vars ------//
// char lastMeasure[] = "";
int lastMeasure = 9999;
int buttonState = 0;
const int sendInterval = 1000;


void setup() {

  // indicator lights, button
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buttonPin, INPUT);


  // serial begin
  Serial.begin(9600);

  // init TOF sensor
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  //------ WIFI ------//
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    WiFi.begin(wifi_ssid, wifi_pass);

    digitalWrite(greenLedPin, HIGH);  // green indic light while trying to connect to wifi

    delay(1000);
  }
  digitalWrite(greenLedPin, LOW);  // green indic light off once wifi connected
  Serial.println("\nWiFi connected!");


  //------ MQTT ------//
  digitalWrite(redLedPin, HIGH);  // red indic light while trying to connect to mqtt

  //give your device any name, to use for identification
  mqtt.setId("Jasper");

  //set mqtt credentials, if needed
  mqtt.setUsernamePassword(mqtt_user, mqtt_pass);

  if (!mqtt.connect(broker, port)) {
    //error codes
    //  -1: credentials rejected
    //  -2: can't connect to broker
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqtt.connectError());
    while (true) {}; //do nothing forever
  } else {
    Serial.println("MQTT connected.");
    digitalWrite(redLedPin, LOW);  // red indic light off once mqtt connected

  }
}



void loop() {

  buttonState = digitalRead(buttonPin);

  VL53L0X_RangingMeasurementData_t measure;
        
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    lastMeasure = measure.RangeMilliMeter;
  } else {
    lastMeasure = 9999;
  }

  if (millis() % sendInterval < 10) {
    Serial.println(lastMeasure);
    mqtt.beginMessage(pubTopic);
    // mqtt.print(lastMeasure + ',' + String(buttonState));
    mqtt.print(lastMeasure);
    mqtt.endMessage();
    delay(10);
  }
 
}


