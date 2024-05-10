// Libraries
#include <AccelStepper.h>     // Stepper Motor control
#include <Conceptinetics.h>   // DMX 
#include "const.h"            // Math constants

// ------------------
// MOTOR SETUP
// ------------------

// Motor Connections (constant current, step/direction bipolar motor driver)
const int stepPin = 13;
const int dirPin = 12;
const int enPin = 11;

// Creates an instance - Pick the version you want to use and un-comment it. That's the only required change.
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

// in pins for commmunicating with Nano 33 IOT
int in0 = 5;
int in1 = 6; 
int in2 = 7;
int in3 = 8;
int in4 = 9;
int in5 = 10;

// to store all in pin data
int pinArr[6];

// manually set min and max -- should reflect node.js
int motorSpdMax = 2000;
int motorSpdMin = 40;
int motorStep = (motorSpdMax - motorSpdMin)/ 32;

int motorDir = 1; // Nano sends motorDir as 0 or 1
                  // Uno uses +1 or -1 as multiplier for spd

int spd_last = 250;
int spd = spd_last;
int spd_binary = 0;

// ------------------
// DMX SETUP
// ------------------

#define DMX_MASTER_CHANNELS 16 
#define RXEN_PIN 2    // pin to read/write mode on DMX Shield
DMX_Master dmx_master ( DMX_MASTER_CHANNELS, RXEN_PIN );

// DMX constants
int minDMX = 0;
int maxDMX = 255;
int maxChannels = DMX_MASTER_CHANNELS;
int phasePeriod = 10000;
int phaseStep = phasePeriod / maxChannels;
int allDMXValues[16];


void setup()
{  
  // Serial.begin(9600);

  // INPUT 
  pinMode(in0, INPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);
  pinMode(in4, INPUT);
  pinMode(in5, INPUT);

  // STEPPER
  stepper.setMaxSpeed(1000); // can go VERY fast, this is probably the cap
  stepper.setAcceleration(100);
  stepper.setSpeed(spd_last); // slowest should be 40...

  // DMX
  dmx_master.enable ();  
  dmx_master.setChannelRange (1, 16, 0);  // set default ch 1-16 at 0

}
 
void loop()
{
  readPins();
  parseFromBinary();

  spd = motorDir*(spd_binary * motorStep + motorSpdMin);

  if (spd != spd_last) {
    stepper.setSpeed(spd);
    spd_last = spd;
  }
  // Serial.println(spd);

  // calculate DMX vals
  double mod = millis() % phasePeriod;

  for (int i = 1; i <= maxChannels; i++) {
    allDMXValues[i-1] = getDMXValue(mod, i);
  }
  
  // send DMX values
  for (int i = 1; i <= maxChannels; i++) {
    int lvl = allDMXValues[i-1];
    dmx_master.setChannelValue( i, lvl );

    // Print DMX values
    // Serial.print(allDMXValues[i-1]);
    // Serial.print("\t");
    // if (i == 16) {
    //   Serial.println("\n");
    // }
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

void parseFromBinary() {

  if (pinArr[0] == 1) {
    motorDir = 1;
  } else {
    motorDir = -1;
  }

  bitWrite(spd_binary, 0, pinArr[1]);
  bitWrite(spd_binary, 1, pinArr[2]);
  bitWrite(spd_binary, 2, pinArr[3]);
  bitWrite(spd_binary, 3, pinArr[4]);
  bitWrite(spd_binary, 4, pinArr[5]);
}

void printArr() {
  for (int i = 0; i < 5; i++) {
    // Serial.print(pinArr[i]);
    // Serial.print(", ");
  }
  // Serial.println(pinArr[5]);
}



// custome map function for doubles; arduino library map uses long, but we need decimals for MATH
double dblmap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int getDMXValue(int mod, int chan) {

  // offset by channel using time -- easier for my brain than radians
  int newMod = (mod + (phaseStep*chan)) % phasePeriod;

  // remap place in phase to period of sin(x), which is 2PI
  double rad = dblmap(newMod, 0, phasePeriod-1, 0, TWO_PI);

  // remap radians to level
  double lvl = dblmap(sin(rad) + 1, 0, 2, minDMX, maxDMX);

  // Serial.print(mod);
  // Serial.print("\t");
  // Serial.print(newMod);
  // Serial.print("\t");
  
  // Serial.print(rad);
  // Serial.print("\t");
  // Serial.println(lvl);

  return (int)lvl;
}

