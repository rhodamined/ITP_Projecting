//------ INCLUDE ------//
#include <WiFiNINA.h>                    
#include "config.h" 

//------ WIFI CONFIG ------//
WiFiClient client;

const char server[] = IGOE_server;        // local IP address of receiver device goes here
const int portNum = IGOE_portNum;         // desired port #. Make sure the receiver is listening on the same port!
const char WIFI_SSID[] = ITP_WIFI_SSID;  // WiFi network name
const char WIFI_PASS[] = ITP_WIFI_PASS;  // WiFi password 

//------ BUTTON CONFIG ------//
const int upButtonPin = 11;
const int downButtonPin = 12;
const int leftButtonPin = 9;
const int rightButtonPin = 10;
const int blackButtonPin = 8;

int totalButtons = 5;
int lastState[5];
int currentState[5];
int lastFive[5];
int password[5] = {4, 3, 2, 1, 0}; // not needed anymore alas

int buttonState;
int lastButtonState;

//------ LED CONFIG ------//

const int greenLedPin = 6;
const int yellowLedPin = 7;


void setup() {
  // Serial
  Serial.begin(9600);

  // Buttons
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(blackButtonPin, INPUT_PULLUP);

  // LEDs
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // retry connection until WiFi is connected successfully
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect to SSID: ");
    // Attempt connection to WPA/WPA2 network.
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    digitalWrite(yellowLedPin, HIGH);  // green indic light while trying to connect to wifi

  }
  digitalWrite(yellowLedPin, LOW);  // green indic light off once wifi connected
  digitalWrite(greenLedPin, HIGH);  // green indic light off once wifi connected

  Serial.println("connected!");

}

void loop() {
  // update 
  updateButtonStates();

  if (client.connected()) {
    digitalWrite(yellowLedPin, HIGH);  // yellow indic light off once client connected
  } else {
    digitalWrite(yellowLedPin, LOW);  // yellow indic light off once client disconnected
  }

  delay(50);

}

// this has been brute forced lol
void updateButtonStates() {

  // 0
  if (digitalRead(upButtonPin) == LOW) {  // button is pressed
    currentState[0] = 1; 
    if (currentState[0] != lastState[0]) { // state has changed
      pushLastFive(0);            // add new button push
      lastState[0] = currentState[0];   // update state
    }
  } 
  else { 
    currentState[0] = 0; 
    if (currentState[0] != lastState[0]) { // state has changed
      lastState[0] = currentState[0];   // update state
    }
  }
  
  // 1
  if (digitalRead(downButtonPin) == LOW) {  // button is pressed
    currentState[1] = 1; 
    if (currentState[1] != lastState[1]) { // state has changed
      pushLastFive(1);            // add new button push
      lastState[1] = currentState[1];   // update state
    }
  } 
  else { 
    currentState[1] = 0; 
    if (currentState[1] != lastState[1]) { // state has changed
      lastState[1] = currentState[1];   // update state
    }
  }

  // 2
  if (digitalRead(leftButtonPin) == LOW) {  // button is pressed
    currentState[2] = 1; 
    if (currentState[2] != lastState[2]) { // state has changed
      pushLastFive(2);            // add new button push
      lastState[2] = currentState[2];   // update state
    }
  } 
  else { 
    currentState[2] = 0; 
    if (currentState[2] != lastState[2]) { // state has changed
      lastState[2] = currentState[2];   // update state
    }
  }

  // 3
  if (digitalRead(rightButtonPin) == LOW) {  // button is pressed
    currentState[3] = 1; 
    if (currentState[3] != lastState[3]) { // state has changed
      pushLastFive(3);            // add new button push
      lastState[3] = currentState[3];   // update state
    }
  } 
  else { 
    currentState[3] = 0; 
    if (currentState[3] != lastState[3]) { // state has changed
      lastState[3] = currentState[3];   // update state
    }
  }

  // 4
  if (digitalRead(blackButtonPin) == LOW) {  // button is pressed
    currentState[4] = 1; 
    if (currentState[4] != lastState[4]) { // state has changed
      pushLastFive(4);            // add new button push
      lastState[4] = currentState[4];   // update state
    }
  } 
  else { 
    currentState[4] = 0; 
    if (currentState[4] != lastState[4]) { // state has changed
      lastState[4] = currentState[4];   // update state
    }
  }
}

// not graceful but it does the damn thing
void printCurrentState() {
  for (int i = 0; i < totalButtons; i++) {
    Serial.print(currentState[i]); Serial.print(',');
  }
  Serial.println();
}

void printLastFive() {
  for (int i = 0; i < totalButtons; i++) {
    Serial.print(lastFive[i]); Serial.print(',');
  }
  Serial.println();
}

void pushLastFive(int newNumber) {
  for (int i = totalButtons; i >= 0; i--) {
    if (i == 0) {
      lastFive[i] = newNumber;
    } else {
      lastFive[i] = lastFive[i - 1];
    }
  }


  if (newNumber == 0) {
    Serial.println("w");
    client.print("w");
    // if (client.connected()) {
    //   client.println("w\n");
    // }
  } else if (newNumber == 1) {
    Serial.println("s");
    client.print("s");
  } else if (newNumber == 2) {
    Serial.println("a");
    client.print("a");
  } else if (newNumber == 3) {
    Serial.println("d");
    client.print("d");
  } else if (newNumber == 4) {
    toggleClient();
  }

  printLastFive();
}

void toggleClient() {

  if (!client.connected()) {
    Serial.println("connecting");
    client.connect(server, portNum);
    delay(10);
    return;
  } else {
    Serial.println("disconnecting");
    client.print("x");
    client.stop();

    delay(10);
  }

}

