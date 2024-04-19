// Include the AccelStepper Library
#include <AccelStepper.h>

// Motor Connections (constant current, step/direction bipolar motor driver)
const int dirPin = 6;
const int stepPin = 7;
const int enPin = 4;

// Creates an instance - Pick the version you want to use and un-comment it. That's the only required change.
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);


// Serial!
String dataIn;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // uno only has 1 serial port
  pinMode(13, OUTPUT);

  myStepper.setMaxSpeed(10000);   // this limits the value of setSpeed(). Raise it if you like.
  myStepper.setSpeed(5000);	

  myStepper.runToNewPosition(200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) { // usb

    dataIn = Serial.parseInt();
    Serial.println(dataIn);
    
    if (dataIn == "1") {
      // Serial.println("LED is ON");
      digitalWrite(13, HIGH);
    } 
    
    else if (dataIn == "0") {
      // Serial.println("LED is OFF");
      digitalWrite(13, LOW);
    }

    Serial.println(">");

  }

  // myStepper.run();

}
