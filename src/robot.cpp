#include "robot.h"

const int Led_pin = 13;

void setup()
{
  pinMode(Led_pin, OUTPUT);
}

void loop()
{
  digitalWrite(Led_pin, HIGH);
  delay(100);
  digitalWrite(Led_pin, LOW);
  delay(500);
}
