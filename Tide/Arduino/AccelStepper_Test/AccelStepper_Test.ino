// Include the AccelStepper Library
#include <AccelStepper.h>

// Motor Connections (constant current, step/direction bipolar motor driver)
const int dirPin = 6;
const int stepPin = 7;
const int enPin = 4;

// Creates an instance - Pick the version you want to use and un-comment it. That's the only required change.
AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup()
{  
  Serial.begin(115200);
  myStepper.setMaxSpeed(10000);   // this limits the value of setSpeed(). Raise it if you like.
  myStepper.setSpeed(5000);	   // runSpeed() will run the motor at this speed - set it to whatever you like.
}

void loop()
{  

  //-------- SERIAL INPUT to change modes etc --------
  if (Serial.available() > 0) {
    int input = Serial.parseInt();
    Serial.println(input);
    if (input == 1) {
      myStepper.setSpeed(5000);
    } else if (input == 0) {
      myStepper.setSpeed(1000);
    }
  }

  // if (Serial.available()) {
  //   Serial.println("test");
  // }
  
  myStepper.runSpeed();

}
