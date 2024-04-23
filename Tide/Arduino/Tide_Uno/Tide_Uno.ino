// Include the AccelStepper Library
#include <AccelStepper.h>

// Motor Connections (constant current, step/direction bipolar motor driver)
const int stepPin = 12;
const int dirPin = 11;
const int enPin = 10;

// Creates an instance - Pick the version you want to use and un-comment it. That's the only required change.
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

// in pins for commmunicating with Nano 33 IOT
int in0 = 2;
int in1 = 3; 
int in2 = 4;
int in3 = 5;
int in4 = 6;
int in5 = 7;

// to store all in pin data
int pinArr[6];

// i

void setup()
{  
  Serial.begin(9600);
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(2000); // can go VERY fast, this is probably the cap
  stepper.setAcceleration(100);
  stepper.setSpeed(200); // slowest should be 40...

  pinMode(in0, INPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);
  pinMode(in4, INPUT);
  pinMode(in5, INPUT);

}
 
void loop()
{

  readPins();
  // printArr();

  if (pinArr[5]== HIGH) {
    digitalWrite(13, HIGH);
    stepper.setSpeed(0);
  } 
  else if (pinArr[5] == LOW) {
    digitalWrite(13, LOW);
    stepper.setSpeed(200);
  }

  stepper.runSpeed();
}

// read 6 pins
// these pins correspond to outputs from arduino Nano 33 IOT
// is there a better way to do this? probably. Do I know what that is? No.
void readPins() {

  pinArr[0] = digitalRead(in0);
  pinArr[1] = digitalRead(in1);
  pinArr[2] = digitalRead(in2);
  pinArr[3] = digitalRead(in3);
  pinArr[4] = digitalRead(in4);
  pinArr[5] = digitalRead(in5);

}

void printArr() {
  for (int i = 0; i < 5; i++) {
    Serial.print(pinArr[i]);
    Serial.print(", ");
  }
  Serial.println(pinArr[5]);
}

