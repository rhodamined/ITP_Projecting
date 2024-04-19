String dataOut;
String dataIn;

String thisArduino = "301: ";
String thatArduino = "401: ";

int ledState = HIGH;        // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW; 

unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // usb
  Serial1.begin(9600); // rx tx
  pinMode(13, OUTPUT); // led
  pinMode(21, INPUT); // button
}

void loop() {
  // debounce later
  if (digitalRead(21) == HIGH) {
    if (lastButtonState == LOW) {
      digitalWrite(13, HIGH);
      // Serial1.print("Serial1: ");
      Serial1.println('1');
    }
    lastButtonState = HIGH;
  } 
  
  if (digitalRead(21) == LOW) {
    if (lastButtonState == HIGH) {
      digitalWrite(13, LOW);
      Serial1.println('0');
    }
    lastButtonState = LOW;
  }

  if (Serial1.available() > 0) {
    dataIn = Serial1.readStringUntil('\n');
    
    Serial.println(dataIn);
  }
}
