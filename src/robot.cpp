#include "robot.h"

IRProx oSensor(A0);

const int Led_pin = 13;
const int SensorEnable = 2;

int sensorValue = 0;

void setup()
{
  pinMode(Led_pin, OUTPUT);
  pinMode(SensorEnable, OUTPUT);
  digitalWrite(SensorEnable, HIGH);
  Serial.begin(115200);
  delay(1000);
}

void loop()
{
  oSensor.calibrate();
  oSensor.printValues();
  delay(500);
}
