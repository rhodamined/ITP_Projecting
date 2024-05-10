#include <Conceptinetics.h>
#include "const.h"

// The master will control up to 100 Channels (1-100)
#define DMX_MASTER_CHANNELS 16 

// Pin number to change read or write mode on the shield
#define RXEN_PIN 2

// Configure a DMX master controller, the master controller
// will use the RXEN_PIN to control its write operation 
// on the bus
DMX_Master dmx_master ( DMX_MASTER_CHANNELS, RXEN_PIN );


int minDMX = 0;
int maxDMX = 255;
int maxChannels = DMX_MASTER_CHANNELS;
int phasePeriod = 10000;

// the setup routine runs once when you press reset:
void setup() {             
  // Serial.begin(9600);
  
  // Enable DMX master interface and start transmitting
  dmx_master.enable ();  
  
  // Set channel 1 - 25 @ 0
  dmx_master.setChannelRange ( 1, 25, 0 );
}

// the loop routine runs over and over again forever:
void loop() 
{
  static int dimmer_val;

  // calculate vals
  for (int i = 1; i <= maxChannels; i++) {

    double mod = millis() % phasePeriod;
    double a = dblmap(mod, 0, phasePeriod-1, 0, TWO_PI);
    double lvl = dblmap(sin(a) + 1, 0, 2, minDMX, maxDMX);

    // Serial.print(mod);
    // Serial.print("\t");
    // Serial.print(a);
    // Serial.print("\t");
    // Serial.println(lvl);

    dmx_master.setChannelValue( i, lvl );
  }
  
  // send Vals  
  
  delay ( 10 );
}

// custome map function for doubles; arduino library map uses long, but we need decimals for MATH
double dblmap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
