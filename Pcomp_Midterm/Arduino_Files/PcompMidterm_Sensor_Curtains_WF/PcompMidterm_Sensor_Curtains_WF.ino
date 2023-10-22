/* PComp - Fall 2023 - Midterm Project */
/* Mingxuan Li & Christina Tang */

/* TESTING */
const int LEDPin = 13;    // used for testing
const int RedLEDPin = 10;  // used for calibrating
const int buttonPinMode = 9;  // blue button for calibrating


const int testing = 0; // testing mode: actually open or close curtains
// 0: testing OFF, run as normal
// 1: testing ON, do not open curtains, only give sensor data

// 0: CALIBRATING: use pushbuttons for calibration of motors, sensor OFF
// 1: RUN: sensor ON, all things behave as expected
int runMode = 0;        // always start in CALIBRATING
int lastRunButtonState = LOW;  // the previous reading from the input pin
int timeA = 0;
int timeB = 0;
int curtainState = 0; // 0: curtain is closed 1: curtain is open

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastRunButtonDebounceTime = 0;  // the last time the output pin was toggled
unsigned long runButtonDebounceDelay = 50;    // the debounce time; increase if the output flickers


/* MOTOR A - CURTAIN OPEN & CLOSE */
const int buttonPinUp = 2;      // pushbutton - to go UP
const int buttonPinDown = 6;    // pushbutton - to go DOWN
const int buttonPinSolenoid = 7;

const int motorA1Pin = 3;   // Motor Driver - Motor A Leg 1
const int motorA2Pin = 4;   // Motor Driver - Motor A Leg 2
const int pwmAPin = 5;      // Motor Driver - PWM Motor A

/* SOLENOID - for 'shaking' the curtain */
const int solenoidPin = 8;  // Solenoid 

/* DISTANCE SENSOR */
const int EtrigPin = 18;
const int EechoPin = 19;
float Eduration, Edistance;
float e1, e2;

/* "DEBOUNCE" */
int lastDebounceState = 0; // 0 is TOO FAR / CLOSED, 1 is NEAR ENOUGH / OPEN
unsigned long lastDebounceTime = 0;   // the last time the output pin was toggled
unsigned long debounceDelay = 500;   // length of time someone is within distance before curtains open/close
float hingeDistance = 50;             // The distance at which things change: 50cm



void setup() {
  // LED for testing
  pinMode(LEDPin, OUTPUT);
  pinMode(RedLEDPin, OUTPUT);
  
  // pushbutton switch for mode
  pinMode(buttonPinMode, INPUT);

  // pushbutton switch as input
  pinMode(buttonPinUp, INPUT);
  pinMode(buttonPinDown, INPUT);

  // motor pins as output
  pinMode(motorA1Pin, OUTPUT);
  pinMode(motorA2Pin, OUTPUT);
  pinMode(pwmAPin, OUTPUT);
  
  // set pwm A to HIGH so motor can turn on
  digitalWrite(pwmAPin, HIGH);

  // solenoid Pins for testing
  pinMode(buttonPinSolenoid, INPUT);
  pinMode(solenoidPin, OUTPUT);

  // Distance sensor pin setup
  pinMode(EtrigPin, OUTPUT);
  pinMode(EechoPin, INPUT);

  // start Serial
  Serial.begin(9600);

}

void loop() {


  // TOGGLE calibration / run mode with button
  int modePinReading = digitalRead(buttonPinMode);

  if (modePinReading == HIGH && lastRunButtonState == LOW) {
    timeA = millis();
    lastRunButtonState = HIGH;
  }
  if (modePinReading == LOW && lastRunButtonState == HIGH) {
    timeB = millis();
    lastRunButtonState = LOW;
    if (timeB - timeA > runButtonDebounceDelay) {
      if (runMode == 0) {
        runMode = 1;
      } else if (runMode == 1) {
        runMode = 0;
      }
    }
  }

  // Red LED indicator light: ON is CALIBRATING, OFF is RUNNING
  if (runMode == 0) {
    digitalWrite(RedLEDPin, HIGH);
  } else if (runMode == 1){
    digitalWrite(RedLEDPin, LOW);
  } 

  /* CALIBRATION */
  if (runMode == 0) { 
        
    // 2 buttons for debugging - hold down button to turn motor
    // lift up / open curtain -- green button
    if (digitalRead(buttonPinUp) == HIGH){
      ASpinCW();
    }
    // let down -- red button
    else if (digitalRead(buttonPinDown) == HIGH){
      ASpinCCW();
    } 
    // when not pressing either -- do nothing
    else {
      digitalWrite(LEDPin, LOW);  // indicator light
      stopMotor();                // stop 
    }

    // press button to fire solenoid
    if (digitalRead(buttonPinSolenoid) == HIGH){
      solenoidStrikeSpeed(50);
    }

  }
  
  else if (runMode == 1) {
    Serial.println("mode is RUNNING");
    Serial.println(lastDebounceState);
  
    // distance sensor
    digitalWrite(EtrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(EtrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(EtrigPin, LOW);

    Eduration = pulseIn(EechoPin, HIGH);
    Edistance = (Eduration / 2) * 0.0343;

    // Serial monitoring: distance sensed
    Serial.print("EDistance = ");
    Serial.print(Edistance);
    Serial.println(" cm");
  
      
    // monitoring
    if (Edistance < hingeDistance) {
      Serial.println("Edistance close enough");
    } 

    // CURTAIN IS CLOSED
    if (curtainState == 0) {
      // if distance is greater than 1m and curtain is CLOSED - shake slowly, but faster as ppl approach
      if (Edistance > 100) {
        int spd = map(Edistance, 50, 400, 50, 3000);
        Serial.println(spd);
        solenoidStrikeSpeed(spd);
        lastDebounceState = 0;
      
      // if distance is between 50cm-1m and curtain is CLOSED - shake fast!
      } else if (Edistance >= 50 && Edistance <= 100) {
        Serial.println("50-100");
        solenoidStrike();
        lastDebounceState = 0;

      } 
      
      else if (0 < Edistance < hingeDistance) {

        if (lastDebounceState == 0) { // person comes close for first time
          lastDebounceTime = millis();
          lastDebounceState = 1;
          Serial.println(lastDebounceTime);
          if (lastDebounceState == 1) {
            if (millis() - lastDebounceTime > debounceDelay) {
              Serial.println("OPEN");
              if (testing == 0) {         // not testing mode: open curtain
                openCurtain();
              }
              delay(200);
              curtainState = 1;
              lastDebounceState = 0;
            }
          }
        }

      } else { // moves far away

        lastDebounceState = 0;
        
      }

    }

    
    // CURTAIN IS OPEN

    if (curtainState == 1) {

      if (Edistance > hingeDistance) {
        if (lastDebounceState == 0) { // person comes close for first time
        lastDebounceTime = millis();
        lastDebounceState = 1;
        } else if (lastDebounceState == 1) {
          if (millis() - lastDebounceTime > debounceDelay) {
            Serial.println("CLOSE");
            if (testing == 0) {         // not testing mode: open curtain
              closeCurtain();
            }
            delay(200);
            curtainState = 0;
            lastDebounceState = 0;
          }
        }
      } else {
        lastDebounceState = 0;
      }
      
    
    }
  }
}

// spin motor A clockwise (CW) when viewed from behind (programming view lol)
void ASpinCW() {
  digitalWrite(pwmAPin, HIGH);
  digitalWrite(motorA1Pin, HIGH);
  digitalWrite(motorA2Pin, LOW);
}

// spin motor A counterclockwise (CCW) when viewed from behind (programming view lol)
void ASpinCCW() {
  digitalWrite(pwmAPin, HIGH);
  digitalWrite(motorA1Pin, LOW);
  digitalWrite(motorA2Pin, HIGH);
}

// do not spin motor
void stopMotor() {
  digitalWrite(pwmAPin, LOW); // stop
}

// pulse solenoid at constant rate
void solenoidStrike() {
  digitalWrite(solenoidPin, HIGH);
  delay(50);
  digitalWrite(solenoidPin, LOW);
  delay(50);
}

// pulse solenoid with [arg] rate -- rate is in milliseconds
void solenoidStrikeSpeed(int speed) {
  digitalWrite(solenoidPin, HIGH);
  delay(50);
  digitalWrite(solenoidPin, LOW);
  delay(speed);
}

// open curtain: spin 'CW' for hard-coded value of time in ms
void openCurtain() {
  digitalWrite(LEDPin, HIGH);
  Serial.println("yay UP");
  ASpinCW();
  delay(800);                 // run motor for this amt of time
  stopMotor();                // stop
}

// close curtain: spin 'CCW' for had-coded value of time in ms
void closeCurtain() {
  digitalWrite(LEDPin, HIGH);
  Serial.println("yay DOWN");
  ASpinCCW();
  delay(800);                 // run motor for this amt of time
  stopMotor();                // stop
}
