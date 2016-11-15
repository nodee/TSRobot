#include "robot.h"

// Analog sensors tested OK.
// PWM tested OK.
LineDetector ld(A5, A2, A1, A0, A4, 2);

const int Led_pin = 13;
int AIN1 = 5;
int AIN2 = 6;
int BIN1 = 11;
int BIN2 = 3;

void setup()
{
  pinMode(Led_pin, OUTPUT);
  Serial.begin(115200);
  delay(1000);
  Serial.println("calibrating...");
  for(int x = 0; x < 1000; x++){
    ld.calibrateAll();
  }
  Serial.println("DONE.");
  ld.printValues();
}

void loop()
{
  delay(250);
  Serial.println(ld.getError());
}
