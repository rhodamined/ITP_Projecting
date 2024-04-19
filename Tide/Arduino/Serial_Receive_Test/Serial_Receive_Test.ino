String dataIn;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // uno only has 1 serial port
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) { // usb

    dataIn = Serial.parseInt();
    Serial.println(dataIn);
    
    if (dataIn == "1") {
      // Serial.println("LED is ON");
      digitalWrite(13, HIGH);
    } 
    
    else if (dataIn == "0") {
      // Serial.println("LED is OFF");
      digitalWrite(13, LOW);
    }

    Serial.println(">");
    
  }
}
