#include <Servo.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

//-------- WIFI & WEATHER API --------
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// wifi setup
const char serverAddress[] = "147.182.255.4";  // server address - droplet node-red
int port = 1880;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;


//-------- SENSOR / INPUT --------
// light sensor: phototransistor
int ledPin = 13;
int sensorPin = A6;
int sensorVal = 0;
int sensorThreshold = 30; 
bool lastSensorState = false; // false: dark, true: light
int lastSensorChange = 0;
int bounceThreshold = 3000; // wait 3 seconds once sensing dark before moving again

//-------- CONTROL --------
// turn certain features on/off
bool SERVO_SERIAL = false; // turn on/off debugging for servo angles

// Manage time
long lastUpdate = 0;    // more forgiving but less precise than exact millis
int stepRate = 1000;

//****** SETUP ******
void setup() {

  //-------- INIT --------
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  //-------- WIFI --------
  while(!Serial);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

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

//****** LOOP ******
void loop() {

  // instead of delay
  if ((millis() - lastUpdate > stepRate)) {

    //-------- WEIRD TIMEKEEPING --------
    lastUpdate = millis();

    //-------- SENSOR DATA --------
    sensorVal = analogRead(sensorPin);  // read the input pin
    // Serial.println(sensorVal);          // debug value

    Serial.println("making POST request");

    //if sending raw text:
    String contentType = "text/plain";
    String postData = String(sensorVal);

    //if sending a formatted JSON object (useful for updating multiple values)
    // String contentType = "application/json"; //if sending a formatted JSON object
    // String postData = "{\"deviceID\": 1, \"value\": VALUE}"; //use single-quotes inside a JSON object literal
    // postData.replace("VALUE", String(millis())); //replace millis() with your own sensor data
    
    char endpoint[] = "/textData?deviceID=arduino_CT";
    client.post(endpoint, contentType, postData); //use client.put() to make a put request

    // read the status code and body of the response
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();

    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
  }
}


