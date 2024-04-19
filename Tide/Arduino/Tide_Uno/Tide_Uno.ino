// Include the AccelStepper Library
#include <AccelStepper.h>

// Motor Connections (constant current, step/direction bipolar motor driver)
const int stepPin = 12;
const int dirPin = 11;
const int enPin = 10;

// Creates an instance - Pick the version you want to use and un-comment it. That's the only required change.
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);


// Serial!
String dataIn;

int in0 = 2;
int in1 = 3; 
int in2 = 4;
int in3 = 5;
int in4 = 6;
int in5 = 7;

int pinArr[6];

void setup()
{  

  Serial.begin(9600);
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(100);
  stepper.moveTo(500);

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
    Serial.println("high");
    digitalWrite(13, HIGH);
  } 
  else if (pinArr[5] == LOW) {
    digitalWrite(13, LOW);
  }

  // If at the end of travel go to the other end
  if (stepper.distanceToGo() == 0)
    stepper.moveTo(-stepper.currentPosition());
 
  stepper.run();
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

