#ifndef PROXDETECTOR_H
#define PROXDETECTOR_H

#include <Arduino.h>
#include "IRSensor.h"

class ProxDetector{
	public:
    ProxDetector(int sLeft, int sFront, int sRight, int sEnable);
		void setThreshold(int threshold);
    int getBoolValues(void);
  private:
    IRSensor _pLeft;
    IRSensor _pFront;
    IRSensor _pRight;
    int _enablePin;
  };

  #endif
