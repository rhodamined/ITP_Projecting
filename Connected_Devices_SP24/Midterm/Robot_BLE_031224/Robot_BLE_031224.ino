#include <ArduinoBLE.h>
#include <Servo.h>

//-------- BLUETOOTH --------
// UUID
char serviceUUID[] = "8dc9513c-4675-45ed-88c6-251640154f83";
BLEService roboService(serviceUUID);

//create a UUID for each characteristic to be advertised on your service
char modeCharacteristicUUID[] = "8dc9513c-4675-45ed-88c6-251640154f84";
char sensorCharacteristicUUID[] = "8dc9513c-4675-45ed-88c6-251640154f85";

BLEIntCharacteristic sensorCharacteristic(sensorCharacteristicUUID, BLERead | BLEWrite| BLENotify); // Int
BLEIntCharacteristic modeCharacteristic(modeCharacteristicUUID, BLERead | BLEWrite|  BLENotify);    // Int


//-------- SERVO --------
// Servo pins
int PAN_PIN = 15;
int TILT_PIN = 21;

// create servo objects
Servo PAN_SERVO;
Servo TILT_SERVO;

// homed servos to 90 and installed the arms after
int homePan = 90; //  Pencilnub
int homeTilt = 90; // Eraserhead

// X: PAN aka PENCILNUB
long xGoalAngle = homePan; 
long xCurrAngle;

// Y: TILT aka ERASERHEAD
long yGoalAngle = homeTilt;
long yCurrAngle;
int stepRate = 70; // update every ___ millis

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

// Modes
int MODE = 0;
int MODE_LAST = 0;
int MODE_TS = 0;
bool MODE_CHANGED = false;
bool MODE_AUTO = false;  // if TRUE, will automatically cycle through modes
                        // TRUE for Intangible Interaction, FALSE for Connected Devices
    // ---- MODE GLOSSARY AO 3/12/24 ----
    // 0: still / turtle pose
    // 1: Tilt (Eraserhead) ONLY
    // 2: Pan (Pencilnub) ONLY
    // 3: still and scribbling (Pencilnub)
    // 4: big scribble (PencilNub)
    // 5: Lurchy quickstep
    // 6: Two step
    // 7: two step v 2 
    // 8: flipping out

// Manage time
long lastUpdate = 0;    // more forgiving but less precise than exact millis
long counter = 0;       // used as factor by which to slow down time

int waveRate = 250;       // millis, time between up and down
bool waveState = false;   // movement is 2-step; wave UP and wave DOWN (names vestigial from arm pat project)
bool subWaveState = false; // subdivides movement into 4 step for certain modes

//****** SETUP ******
void setup() {
  
  //-------- OUTPUT --------
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  //-------- BLUETOOTH --------
  if (!BLE.begin()) {
    Serial.println("BLE initialization failed.");
    while (1); //do nothing forever
  }
  BLE.setLocalName("TANG_Arduino");
  BLE.setAdvertisedService(roboService);
  roboService.addCharacteristic(modeCharacteristic);    // 0
  roboService.addCharacteristic(sensorCharacteristic);  // 1
  BLE.addService(roboService);
  BLE.advertise();
  Serial.println("BLE peripheral initialized.");

  //-------- SERVO --------
  PAN_SERVO.attach(PAN_PIN);
  TILT_SERVO.attach(TILT_PIN);
  

}

//****** LOOP ******
void loop() {

  // instead of delay
  if ((millis() - lastUpdate > stepRate)) {

    //-------- WEIRD TIMEKEEPING --------
    lastUpdate = millis();
    counter++;

    //-------- BLUETOOTH --------
    BLEDevice central = BLE.central();

    if (central && central.connected()) {
      // Serial.println("test");

      // write to characteristic
      sensorCharacteristic.writeValue(sensorVal);   // stream sensor unless impacting performance

      // Serial.println(MODE);
      // Serial.println(MODE_CHANGED);
      if (MODE_CHANGED) {
        modeCharacteristic.writeValue(MODE);      // only write if changed
      }
      
      // if characteristic has BLEWrite access:
      if (modeCharacteristic.written()) {
        // get the value here - make sure to use the correct data type!
        int dataIn = modeCharacteristic.value();
        int val = parseForHumans(dataIn);
        Serial.println(val);
        changeMode(val);
      } else {
        digitalWrite(LED_BUILTIN, LOW);
      }
    }

    // reset mode changed
    if (MODE_CHANGED) {
      MODE_CHANGED = false;
    }

    //-------- SERIAL INPUT to change modes etc --------
    if (Serial.available() > 0) {
      int input = Serial.parseInt();
      Serial.println(input);
      changeMode(input);
    }

    //-------- SENSOR DATA --------
    sensorVal = analogRead(sensorPin);  // read the input pin
    // Serial.println(sensorVal);          // debug value

    // DARK - go to work!
    if (sensorVal < sensorThreshold && lastSensorState == true && (lastUpdate - lastSensorChange > bounceThreshold)){
      lastSensorState = false;
      lastSensorChange = lastUpdate;
      digitalWrite(ledPin, LOW);
      // Serial.println("DARK");
      changeMode(1);
    } 
    // LIGHT - flip out then keel over
    else if (sensorVal >= sensorThreshold && lastSensorState == false){
      lastSensorState = true;
      lastSensorChange = lastUpdate;
      digitalWrite(ledPin, HIGH);
      MODE_LAST = MODE;
      if (MODE_AUTO == true) {
        changeMode(8);  // when auto, flip out -- will autodirect to MODE 0, be a turtle
      } else {
        changeMode(0);  // be still
      }
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

    // ---- GLOSSARY ----
    // 0: still / turtle pose
    // 1: Tilt (Eraserhead) ONLY
    // 2: Pan (Pencilnub) ONLY
    // 3: still and scribbling (Pencilnub)
    // 4: big scribble (PencilNub)
    // 5: Lurchy quickstep
    // 6: Two step
    // 7: two step v 2 
    // 8: flipping out

    // should probably refactor to switch/case one day
    //-------- 0: BE STILL / TURTLE POSE --------
    if (MODE == 0) {
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
      if (MODE_AUTO == true) {
        if (lastUpdate > MODE_TS+8000) {
          Serial.println("Mode change inside MODE 1");
          newMode();
        }
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
      if (MODE_AUTO == true) {
        if (lastUpdate > MODE_TS+14000) {
          Serial.println("Mode change inside MODE 2");
          newMode();
        }
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
      if (MODE_AUTO == true) {
        if (lastUpdate > MODE_TS+8000) {
          Serial.println("Mode change inside MODE 3");
          newMode();
        }
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
      if (MODE_AUTO == true) {
        if (lastUpdate > MODE_TS+8000) {
          Serial.println("Mode change inside MODE 4");
          newMode();
        }
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
      if (MODE_AUTO == true) {
        if (lastUpdate > MODE_TS+5000) {
          Serial.println("Mode change inside MODE 5");
          newMode();
        }
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
      if (MODE_AUTO == true) {
        if (lastUpdate > MODE_TS+4000) {
          Serial.println("Mode change inside MODE 6");
          newMode();
        }
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
      if (MODE_AUTO == true) {
        if (lastUpdate > MODE_TS+4000) {
          Serial.println("Mode change inside MODE 7");
          newMode();
        }
      }
    }
  
    //-------- 8: flipping out --------
    // actually just a faster version of MODE 7
    if (MODE == 8) {

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
      if (MODE_AUTO == true) {
        if (lastUpdate > MODE_TS+1000) {
          Serial.println("Mode change inside MODE 8");
          changeMode(0);
        }
      }
    }
  }
}


// Maps the angle to the servos -- not all actually do the full motion as expected.
long adjAngle(int servoNum, long angle) {
  //Serial.println("adjangle");
  switch (servoNum) {
    case 0: // Left Pan
      return angle;
    case 1: // Left Tilt
      return 180-angle;
  }
}

void newMode() {
  MODE_LAST = MODE;
  MODE = getNewMode(sensorVal);
  Serial.println(MODE);
  MODE_TS = lastUpdate;
  MODE_CHANGED = true;
}

void changeMode(int pickMode) {
  MODE_LAST = MODE;
  MODE = pickMode;
  Serial.println(MODE);
  MODE_TS = lastUpdate;
  MODE_CHANGED = true;
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

// I can't figure out byte arrays so fuck it
// 0 is 48, etc
int parseForHumans(int num) {
  return abs(48-num);
}


