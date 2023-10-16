/* PComp - Fall 2023 - Midterm Project */
/* Mingxuan Li & Christina Tang */

/* Testing.... */
const int LEDPin = 13;

/* MOTOR A - CURTAIN OPEN & CLOSE */
const int buttonPinUp = 2;    // pushbutton - to go UP
const int buttonPinDown = 6;    // pushbutton - to go DOWN
const int buttonPinSolenoid = 7;

const int motorA1Pin = 3;   // Motor Driver - Motor A Leg 1
const int motorA2Pin = 4;   // Motor Driver - Motor A Leg 2
const int pwmAPin = 5;      // Motor Driver - PWM Motor A

/* SOLENOID - for 'shaking' the curtain */
const int solenoidPin = 8;  // Solenoid - the tugging?

/* DISTANCE SENSOR */
const int EtrigPin = 18;
const int EechoPin = 19;
float Eduration, Edistance;
float e1, e2;

/* "DEBOUNCE" */
int lastState = 0; // 0 is TOO FAR / CLOSED, 1 is NEAR ENOUGH / OPEN
unsigned long lastDebounceTime = 0;   // the last time the output pin was toggled
unsigned long debounceDelay = 1000;   // length of time someone is within distance before curtains open/close
float hingeDistance = 50;             // The distance at which things change: 50cm


/* TESTING */
int testing = 0;  // 0: run as normal 1: manual control only, no sensor input

void setup() {
  // LED for testing
  pinMode(LEDPin, OUTPUT);

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

  // 2 buttons for LIFT UP curtain and LET DOWN curtain
  // lift up -- green button
  if (digitalRead(buttonPinUp) == HIGH){
    openCurtain();
  }
  // let down -- red button
  else if (digitalRead(buttonPinDown) == HIGH){
    closeCurtain();
  } 
  // when not pressing either -- do nothing
  else {
    digitalWrite(LEDPin, LOW);
    digitalWrite(pwmAPin, LOW);
  }

  // press button to fire solenoid
  if (digitalRead(buttonPinSolenoid) == HIGH){
    Serial.println("solenoid");
    solenoidStrike();
  }

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
  delay(200);
  

  //
  if (Edistance < hingeDistance) {
    Serial.println("Hdistance close enough");
  } 

  /* "DEBOUNCE" */
  // borrowed & adapted from: https://docs.arduino.cc/built-in-examples/digital/Debounce

  // close enough and has previously been far
  if (Edistance < hingeDistance && lastState == 1) {   
    // reset the debouncing timer
    lastDebounceTime = millis();
  }   
  else if (Edistance > hingeDistance && lastState == 0) { 
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    if (lastState == 0){    // move from FAR to NEAR
      Serial.println("OPEN");
      openCurtain();
      delay(200);
      lastState = 1;
    }
    else if (lastState == 1){    // move from NEAR to FAR
      Serial.println("CLOSE");
      closeCurtain();
      delay(200);
      lastState = 0;
    }
  }


}


void ASpinCW() {
  digitalWrite(pwmAPin, HIGH);
  digitalWrite(motorA1Pin, HIGH);
  digitalWrite(motorA2Pin, LOW);
}

void ASpinCCW() {
  digitalWrite(pwmAPin, HIGH);
  digitalWrite(motorA1Pin, LOW);
  digitalWrite(motorA2Pin, HIGH);
}

void solenoidStrike() {
  digitalWrite(solenoidPin, HIGH);
  delay(100);
  digitalWrite(solenoidPin, LOW);
}

void openCurtain() {
  digitalWrite(LEDPin, HIGH);
  Serial.println("yay UP");
  ASpinCW();
  delay(900);                 // run motor for this amt of time
  digitalWrite(pwmAPin, LOW); // stop
}

void closeCurtain() {
  digitalWrite(LEDPin, HIGH);
  Serial.println("yay DOWN");
  ASpinCCW();
  delay(900);                 // run motor for this amt of time
  digitalWrite(pwmAPin, LOW); // stop
}
