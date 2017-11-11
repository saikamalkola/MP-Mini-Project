#include "SPI.h"
int latch_pin = P1_3; // using digital pin 10 for SPI slave select

void setup()
{
 pinMode(latch_pin, OUTPUT); // we use this for SS pin
 SPI.begin(); // wake up the SPI bus.
 SPI.setBitOrder(LSBFIRST);
 }

 

void loop()
{
  for(int i = 0; i < 8; i++)
  {
  SPI.transfer(1 << i); 
  latch();
  delay(100);
  }
}


void latch()
{
   digitalWrite(latch_pin, HIGH);
 digitalWrite(latch_pin, LOW);
}

