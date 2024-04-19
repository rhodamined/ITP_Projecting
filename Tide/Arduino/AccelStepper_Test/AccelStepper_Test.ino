// Include the AccelStepper Library
#include <AccelStepper.h>

// Motor Connections (constant current, step/direction bipolar motor driver)
const int dirPin = 6;
const int stepPin = 7;
const int enPin = 4;

int count = 0;

// Creates an instance - Pick the version you want to use and un-comment it. That's the only required change.
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);

long int dataIn;

void setup()
{  
  Serial.begin(9600);
  myStepper.setMaxSpeed(10000);   // this limits the value of setSpeed(). Raise it if you like.
  myStepper.setSpeed(5000);	   // runSpeed() will run the motor at this speed - set it to whatever you like.
}

void loop()
{  
  myStepper.runSpeed();
}
