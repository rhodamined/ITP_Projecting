int testPin = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 

  pinMode(13, OUTPUT); // led
  pinMode(21, INPUT); // button
  pinMode(7, OUTPUT);
}

void loop() {

  digitalWrite(testPin, digitalRead(21));
}
