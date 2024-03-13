#include <Servo.h>

// Servo pins
int PAN_PIN = 15;
int TILT_PIN = 21;

// create servo objects
Servo PAN_SERVO;
Servo TILT_SERVO;

// homed servos to 90 and installed the arms after
int homePan = 90; //  Pencilnub
int homeTilt = 90; // Eraserhead

// X: PAN aka PENCIL TIP
long xGoalAngle = homePan; 
long xCurrAngle;

// Y: TILT aka ERASERHEAD
long yGoalAngle = homeTilt;
long yCurrAngle;
int stepRate = 70; // update every ___ millis

// light sensor: phototransistor
int ledPin = 13;
int sensorPin = A6;
int sensorVal = 0;
int sensorThreshold = 30; 
bool lastSensorState = false; // false: dark, true: light
int lastSensorChange = 0;
int bounceThreshold = 3000; // wait 3 seconds once sensing dark before moving again

// JOYSTICK
// #define VRX_PIN  A7 // Arduino pin connected to VRX pin
// #define VRY_PIN  A6 // Arduino pin connected to VRY pin

// int xValue = 0; // To store value of the X axis
// int yValue = 0; // To store value of the Y axis

// bool JOY_SERIAL = false;  // turn on/off debugging for joystick
bool SERVO_SERIAL = false; // turn on/off debugging for servo angles

int MODE = 0;
int MODE_LAST = 0;
int MODE_TS = 0;

bool MODE_AUTO = true;

// for MODES 1 & 2
bool waveState = false;  // default DOWN = false
int waveRate = 250;   // millis, time between up and down
int subWaveState = false;

bool subWave = false;

// TIMING
long lastUpdate = 0;
long counter = 0;


void setup() {
  // Serial monitoring
  pinMode(ledPin, OUTPUT);
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

    //-------- WEIRD TIMEKEEPING --------
    lastUpdate = millis();
    counter++;

    //-------- SERIAL INPUT to change modes etc --------
    if (Serial.available() > 0) {
      int input = Serial.parseInt();
      Serial.println(input);
      MODE_LAST = MODE;
      MODE = input;
      MODE_TS = lastUpdate;
    }

    //-------- SENSOR DATA --------
    sensorVal = analogRead(sensorPin);  // read the input pin
    // Serial.println(sensorVal);          // debug value

    // Dark - work!
    if (sensorVal < sensorThreshold && lastSensorState == true && (lastUpdate - lastSensorChange > bounceThreshold)){
      lastSensorState = false;
      lastSensorChange = lastUpdate;
      digitalWrite(ledPin, LOW);
      // Serial.println("DARK");
      MODE_LAST = MODE;
      MODE = 1;
      MODE_TS = lastUpdate;
    } 
    // Light - keep over
    else if (sensorVal >= sensorThreshold && lastSensorState == false){
      lastSensorState = true;
      lastSensorChange = lastUpdate;
      digitalWrite(ledPin, HIGH);
      MODE_LAST = MODE;
      MODE = 8; // flip out -- will autodirect to MODE 0, be a turtle
      MODE_TS = lastUpdate;
      // Serial.println("LIGHT");
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

    // 0: still / turtle pose
    // 1: Tilt (Eraserhead) ONLY
    // 2: Pan (Pencilnub) ONLY
    // 3: still and scribbling (Pencilnub)
    // 4: big scribble (PencilNub)
    // 5: Lurchy quickstep
    // 6: Two step
    // 7: two step v 2 
    // 8: flipping out

    //-------- 0: BE STILL / TURTLE POSE --------
    if (MODE == 0) {
      // xGoalAngle = homePan;
      // yGoalAngle = homeTilt-15;
      xGoalAngle = 0;
      yGoalAngle = 0;
    }

    //-------- 1: TILT (Eraserhead) ONLY --------
    if (MODE == 1) {

      xGoalAngle = homePan-10;

      // timing of wave
      if (counter%5 == 0) { 
        waveState = !waveState; 
        if (waveState) {           
          yGoalAngle = homeTilt+30; 
        } else {                     
          yGoalAngle = homeTilt-30; 
        }
      }

      // change mode after certain time
      if (lastUpdate > MODE_TS+8000) {
        Serial.println("Mode change inside MODE 1");
        newMode();
      }
    }

    //-------- 2: PAN (Pencil) ONLY (No movement - long strokes) --------
    if (MODE == 2) {

      yGoalAngle = homeTilt;

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

      // change mode after certain time
      if (lastUpdate > MODE_TS+14000) {
        Serial.println("Mode change inside MODE 2");
        newMode();
      }

    }

    //-------- 3: SCRIBBLE - short stabs with pencil --------
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

      // change mode after certain time
      if (lastUpdate > MODE_TS+8000) {
        Serial.println("Mode change inside MODE 3");
        newMode();
      }
    }

    //-------- 4: Scribble - wide strokes --------
    if (MODE == 4) {

      yGoalAngle = 30;

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

      // change mode after certain time
      if (lastUpdate > MODE_TS+8000) {
        Serial.println("Mode change inside MODE 4");
        newMode();
      }
    }

    //-------- 5: Lurchy quick step (Eraserhead only) --------
    if (MODE == 5) {

      yGoalAngle = homeTilt;

      // timing of wave
      if (counter%3 == 0) { 
        waveState = !waveState; 
        if (waveState) {                // STEP
          yGoalAngle = homeTilt+30;
        } else {                        // WAIT
          // do nothing
        }
      }

      // change mode after certain time
      if (lastUpdate > MODE_TS+5000) {
        Serial.println("Mode change inside MODE 5");
        newMode();
      }
    }

    //-------- 6: Big walk,  both move together --------
    if (MODE == 6) { // frog squat moving both arms at once, moves forward

      // timing of wave
      if (counter%5 == 0) { 
        if (subWaveState) {
          if (waveState) {                // UP
            //Serial.println("Up");
            xGoalAngle = homePan-40; 
            Serial.println("1");
            delay(50);
          } else {                        // DOWN
            //Serial.println("down");
            xGoalAngle = homePan+40; 
            Serial.println("3");
            delay(50);
          }
          subWaveState = false;
        } else if (!subWaveState) {
          if (waveState) {
            yGoalAngle = homeTilt+50;
            Serial.println("2");
            delay(50);
          } else {
            yGoalAngle = homeTilt;
            Serial.println("4");
            delay(50);
          }
          subWaveState = true;
          waveState = !waveState;
        }
      }

      // change mode after certain time
      if (lastUpdate > MODE_TS+4000) {
        Serial.println("Mode change inside MODE 6");
        newMode();
      }
    }

    //-------- 7: funny walk, inconclusive --------
    if (MODE == 7) { // frog squat moving both arms at once, moves forward

      // timing of wave
      if (counter%5 == 0) { 
        if (subWaveState) {
          if (waveState) {           
            yGoalAngle = homeTilt+50;
            // Serial.println("2");
            delay(50);
          } else {                     
            xGoalAngle = homePan+40; 
            // Serial.println("3");
            delay(50);
          }
          subWaveState = false;
        } else if (!subWaveState) {
          if (waveState) {

            xGoalAngle = homePan-40; 
            // Serial.println("1");
            delay(50);
          } else {
            yGoalAngle = homeTilt;
            // Serial.println("4");
            delay(50);
          }
          subWaveState = true;
          waveState = !waveState;
        }
      }

      // change mode after certain time
      if (lastUpdate > MODE_TS+4000) {
        Serial.println("Mode change inside MODE 7");
        newMode();
      }
    }
  
    //-------- 8: flipping out --------
    if (MODE == 8) {
    //   if (counter%2 == 0) {
    //     xGoalAngle = homePan-15;
    //   }
    //   if (counter%5 == 0) {
    //     xGoalAngle = homePan+15;
    //   }
    //   if (counter % 5 == 0) {
    //     yGoalAngle = homeTilt+15;
    //   }
    //   if (counter % 11 == 0) {
    //     yGoalAngle = homeTilt;
    //   }
    // timing of wave
      if (counter%1 == 0) { 
        if (subWaveState) {
          if (waveState) {                
            yGoalAngle = homeTilt+50;
            // Serial.println("2");
            delay(50);
          } else {                       
            //Serial.println("down");
            xGoalAngle = homePan+40; 
            // Serial.println("3");
            delay(50);
          }
          subWaveState = false;
        } else if (!subWaveState) {
          if (waveState) {

            xGoalAngle = homePan-40; 
            // Serial.println("1");
            delay(50);
          } else {
            yGoalAngle = homeTilt;
            // Serial.println("4");
            delay(50);
          }
          subWaveState = true;
          waveState = !waveState;
        }
      }

      // be still 
      if (lastUpdate > MODE_TS+1000) {
        Serial.println("Mode change inside MODE 8");
        MODE_LAST = MODE;
        MODE = 0;
        MODE_TS = lastUpdate;
      }
    }
  }
}


// Maps the angle to the servos -- not all actually do the full motion as expected.
long adjAngle(int servoNum, long angle) {
  //Serial.println("adjangle");
  switch (servoNum) {
    case 0: // Left Pan
      // return map(angle, 0, 250, 0, 180);
      return angle;
    case 1: // Left Tilt
      // return map(angle, 0, 180, 0, 180);
      return 180-angle;
  }
}

void newMode() {
  if (MODE_AUTO) {
    MODE_LAST = MODE;
    MODE = getNewMode(sensorVal);
    Serial.println(MODE);
    MODE_TS = lastUpdate;
  } else {
    // do nothing
  }
}

int getNewMode(int seedVal) {
  int num = seedVal % 10; 

  switch (num) {
    case 0:
      return 1;
    case 1:
      return 1;
    case 2:
      return 2;
    case 3:
      return 3;
    case 4:
      return 4;
    case 5:
      return 5;
    case 6:
      return 6;
    case 7:
      return 7;
    case 8:
      return 6;
    case 9:
      return 1;

    default:
      // statements
      break;
  } 

}



