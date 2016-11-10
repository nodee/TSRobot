#include "robot.h"

// Analog sensors tested OK.
// PWM tested OK.


const int Led_pin = 13;
int AIN1 = 5;
int AIN2 = 6;
int BIN1 = 11;
int BIN2 = 3;

void setup()
{
  pinMode(Led_pin, OUTPUT);
  delay(1000);
}
void loop()
{
  analogWrite(AIN2, 0);
  analogWrite(BIN2, 0);
  analogWrite(AIN1, 250);
  analogWrite(BIN1, 250);
  digitalWrite(Led_pin, HIGH);
  delay(2000);
  analogWrite(AIN1, 0);
  analogWrite(BIN1, 0);
  analogWrite(AIN2, 250);
  analogWrite(BIN2, 250);
  digitalWrite(Led_pin, LOW);
  delay(2000);
}
