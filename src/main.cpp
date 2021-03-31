#include <Arduino.h>
#include "CapacitiveSensor.h"

CapacitiveSensor mat = CapacitiveSensor(4, 2);
long readyTimer;
long mainTimer;
bool lock = false;

#define isHeld (mat.capacitiveSensor(30) > 1000)

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (isHeld)
  {
    Serial.println("Hold 2 Seconds");
    readyTimer = millis();
    while (isHeld)
    {
      if (readyTimer + 2000 < millis())
      {
        if (lock == false)
        {
          Serial.println("Ready");
          lock = true;
        }
      }
    }
    if (lock)
    {
      mainTimer = millis();
      Serial.println("Start!");
      while (!isHeld)
      {
      }
      Serial.println((millis() - mainTimer) / 1000.0, 3);
      while (isHeld)
      {
      }
    }
  }
  lock = false;
}