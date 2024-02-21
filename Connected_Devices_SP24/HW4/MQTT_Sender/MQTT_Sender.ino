#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "config.h"

WiFiClient wifi;
MqttClient mqtt(wifi);

//WiFi network info: ssid and password
const char wifi_ssid[] = "Samsung Galaxy S7 6061";
const char wifi_pass[] = "dnup0849";

//MQTT broker info: url and port (1883 default for MQTT)
const char broker[] = "public.cloud.shiftr.io";
const int  port = 1883;

//if needed: broker authentication credentials
const char mqtt_user[] = "theyonetwork";
const char mqtt_pass[] = "ConnDevSP24";
// const char mqtt_user[] = "public";
// const char mqtt_pass[] = "public";

//the topic this device will publish messages to
const char pubTopic[] = "xtina";

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    WiFi.begin(wifi_ssid, wifi_pass);
    delay(1000);
  }
  Serial.println("\nWiFi connected!");

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
  } else Serial.println("MQTT connected.");
}

const int sendInterval = 1000;
void loop() {

  if (millis() % sendInterval < 10) {
    mqtt.beginMessage(pubTopic);
    mqtt.print(millis());
    mqtt.endMessage();
    delay(10);
  }
  
}