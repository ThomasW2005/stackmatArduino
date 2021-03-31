#include <Arduino.h>
#include "CapacitiveSensor.h"

#define HOLDTIME 2000
#define TOUCHVALUE 1000
#define isHeld (mat.capacitiveSensor(30) > TOUCHVALUE)

CapacitiveSensor mat = CapacitiveSensor(4, 2);
long readyTimer;
long mainTimer;
bool lock = false;

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
      if (readyTimer + HOLDTIME < millis())
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