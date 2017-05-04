#ifndef LINE_DETECTOR_H
#define LINE_DETECTOR_H

#include <Arduino.h>
#include "IRSensor.h"

class LineDetector{
  public:
    LineDetector(int sLeft, int sMidLeft, int sMidRight, int sRight, int sEnable);
    int getError(void);
    void calibrate(void);
    void setThreshold(int threshold);
    int getBoolValues(void);
    void printInfo(void);
  protected:
  private:
    IRSensor _lLeft;
		IRSensor _lMidLeft;
		IRSensor _lMidRight;
		IRSensor _lRight;
    int _enablePin;
    int _BoolThreshold;
};

#endif
