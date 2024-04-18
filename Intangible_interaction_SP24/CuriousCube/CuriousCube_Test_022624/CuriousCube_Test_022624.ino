#include <Servo.h>

// Servo pins
int PAN_PIN = 14;
int TILT_PIN = 15;

// create servo objects
Servo PAN_SERVO;
Servo TILT_SERVO;

// homed servos to 90 and installed the arms after
int homePan = 90;
int homeTilt = 90;

// X: PAN aka PENCIL TIP
long xGoalAngle = homePan; 
long xCurrAngle;

// Y: TILT aka ERASERHEAD
long yGoalAngle = homeTilt;
long yCurrAngle;
int stepRate = 70; // update every ___ millis

// JOYSTICK
// #define VRX_PIN  A7 // Arduino pin connected to VRX pin
// #define VRY_PIN  A6 // Arduino pin connected to VRY pin

// int xValue = 0; // To store value of the X axis
// int yValue = 0; // To store value of the Y axis


bool CAP_SERIAL = true;  // turn on/off capacitor readings for testing
bool JOY_SERIAL = false;  // turn on/off debugging for joystick
bool SERVO_SERIAL = false; // turn on/off debugging for servo angles

int MODE = 1;
// 0: Still / Home

// for MODES 1 & 2
bool waveState = false;  // default DOWN = false
int waveRate = 250;   // millis, time between up and down

bool subWave = false;

// TIMING
long lastUpdate = 0;
long counter = 0;


void setup() {
  // Serial monitoring
  Serial.begin(9600);

  //-------- START SERVO setup code --------
  // attach Servos
  PAN_SERVO.attach(PAN_PIN);
  TILT_SERVO.attach(TILT_PIN);

  //-------- END SERVO setup code --------

}

void loop() {

  // instead of delay
  if ((millis() - lastUpdate > stepRate)) {

    lastUpdate = millis();
    counter++;

    // Serial input to change modes etc
    if (Serial.available() > 0) {
      int input = Serial.parseInt();
      Serial.println(input);
      MODE = input;

      if (MODE == 9 && input >= 10) {
        if (input >20)
      }


    }

    //-------- MOVE SERVO --------
    if ((xCurrAngle != xGoalAngle) || (yCurrAngle != yGoalAngle) ) {

      xCurrAngle = xGoalAngle;
      yCurrAngle = yGoalAngle;
      
      PAN_SERVO.write(adjAngle(0, xCurrAngle));
      TILT_SERVO.write(adjAngle(1, yCurrAngle));

      // Servo position debugging
      if (SERVO_SERIAL){
        Serial.print("xcurr = ");
        Serial.print(xCurrAngle);
        Serial.print(", ycurr = ");
        Serial.println(yCurrAngle);
      }
    }

    // 0: still
    // 1: moving forward 'normal'
    // 2: lunging
    // 3: still and scribbling
    // 4: test


    //-------- 0: BE STILL --------
    if (MODE == 0) {
      xGoalAngle = homePan;
      yGoalAngle = homeTilt-15;
    }

    //-------- 1: MOVING ("frog squat") --------
    if (MODE == 1) {

      xGoalAngle = homePan+10;

      // timing of wave
      if (counter%5 == 0) { 
        waveState = !waveState; 
        if (waveState) {                // UP
          //Serial.println("Up");
          yGoalAngle = homeTilt+30; 
        } else {                        // DOWN
          //Serial.println("down");
          yGoalAngle = homeTilt; 
        }
      }
    }

    //-------- 2: lunging --------
    if (MODE == 2) {

      xGoalAngle = homePan+10;

      // timing of wave
      if (counter%5 == 0) { 
        waveState = !waveState; 
        if (waveState) {                // UP
          //Serial.println("Up");
          yGoalAngle = homeTilt; 
        } else {                        // DOWN
          //Serial.println("down");
          yGoalAngle = homeTilt+75; 
        }
      }
    }

    //-------- 3: Scribble - short strokes --------
    if (MODE == 3) {

      yGoalAngle = homeTilt+55;

      // timing of wave
      if (counter%2 == 0) { 
        waveState = !waveState; 
        if (waveState) {                // UP
          //Serial.println("Left");
          xGoalAngle = homePan-15;
        } else {                        // DOWN
          //Serial.println("Right");
          xGoalAngle = homePan+15;
        }
      }
    }

    //-------- 4: Scribble - wide strokes --------
    if (MODE == 4) {

      yGoalAngle = homeTilt+55;

      // timing of wave
      if (counter%7 == 0) { 
        waveState = !waveState; 
        if (waveState) {                // UP
          //Serial.println("Left");
          xGoalAngle = homePan-45;
        } else {                        // DOWN
          //Serial.println("Right");
          xGoalAngle = homePan+45;
        }
      }
    }

    //-------- 5: Lurchy quick step--------
    if (MODE == 5) {

      yGoalAngle = homeTilt+55;

      // timing of wave
      if (counter%3 == 0) { 
        waveState = !waveState; 
        if (waveState) {                // STEP
          yGoalAngle = homeTilt+30;
          // delay(200);
          // yGoalAngle = homeTilt;
        } else {                        // WAIT
          //Serial.println("Right");
        }
      }
    }
  
    //-------- 6: test --------
    if (MODE == 6) {

      yGoalAngle = homeTilt+55;

      // timing of wave
      if (counter%3 == 0) { 
        waveState = !waveState; 
        if (waveState) {                // STEP
          yGoalAngle = homeTilt+30;
          // delay(200);
          // yGoalAngle = homeTilt;
        } else {                        // WAIT
          //Serial.println("Right");
        }
      }
    }
  
  } 

  if (MODE == 7) {
      if (counter%2 == 0) {
        xGoalAngle = homePan-15;
      }
      if (counter%5 == 0) {
        xGoalAngle = homePan+15;
      }
      if (counter % 5 == 0) {
        yGoalAngle = homeTilt+15;
      }
      if (counter % 11 == 0) {
        yGoalAngle = homeTilt;
      }
    }
}

// Maps the angle to the servos -- not all actually do the full motion as expected.
long adjAngle(int servoNum, long angle) {
  //Serial.println("adjangle");
  switch (servoNum) {
    case 0: // Left Pan
      return map(angle, 0, 250, 0, 180);
    case 1: // Left Tilt
      return map(angle, 0, 180, 0, 180);
  }
}



