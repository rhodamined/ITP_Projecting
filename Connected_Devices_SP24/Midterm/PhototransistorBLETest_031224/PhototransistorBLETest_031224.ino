int sensorPin = A6; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int sensorVal = 0;
int sensorThreshold = 30;
bool lastSensorState = false;


void setup() {
  Serial.begin(9600);           //  setup serial
}

void loop() {
  sensorVal = analogRead(sensorPin);  // read the input pin
  Serial.println(sensorVal);          // debug value

  if (sensorVal < sensorThreshold && lastSensorState == true){
    lastSensorState = false;
    //Serial.println("DARK");
  } else if (sensorVal >= sensorThreshold && lastSensorState == false){
    lastSensorState = true;
    //Serial.println("LIGHT");
  }
  delay(70);
}