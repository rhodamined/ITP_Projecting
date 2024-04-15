//Adapted from: https://github.com/Picaio/pasoapasoDriverHBS860H_TB6600/blob/master/paso_a_paso_HBS8606H_TB6600.ino

int PUL = 7; // Pulse
int DIR = 6; // Direction
int EN = 4; // Enable 

void setup() {

  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN,HIGH);

  digitalWrite(DIR,LOW);
}

void loop() {
  // the delayMicroseconds decides the timing, make it higher to move slower, and vice versa

  digitalWrite(PUL, HIGH); 
  delayMicroseconds(100);
  digitalWrite(PUL, LOW);
  delayMicroseconds(100);

}