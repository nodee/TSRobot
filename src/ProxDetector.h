#ifndef PROXDETECTOR_H
#define PROXDETECTOR_H

#include <Arduino.h>

class ProxDetector{
	public:
    ProxDetector(int leftSensorPin, int frontSensorPin, int rightSensorPin, int enablePin);
    void printValues(void);
  private:
    int readSensor(int sensor);
    int _leftSensorPin;
    int _frontSensorPin;
    int _rightSensorPin;
    int _enablePin;
  }

  #endif
