#include "robot.h"

IRProx sensorMid(A1);

const int Led_pin = 13;
const int SensorEnable = 2;

int sensorValue = 0;

void setup()
{
  pinMode(Led_pin, OUTPUT);
  pinMode(SensorEnable, OUTPUT);
  digitalWrite(SensorEnable, HIGH);
  Serial.begin(115200);
}

void loop()
{
  sensorValue = sensorMid.getValue();
  sensorMid.calibrate(sensorValue);
  sensorMid.printValues();
  delay(100);
}
