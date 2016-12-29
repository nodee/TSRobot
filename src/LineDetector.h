#ifndef LINE_DETECTOR_H
#define LINE_DETECTOR_H

#include <Arduino.h>
#include "IRSensor.h"

class LineDetector{
  public:
    LineDetector(int sLeft, int sMidLeft, int sMid, int sMidRight, int sRight, int sEnable);
    int getError(void);
    void calibrate(void);
    void setThreshold(int threshold);
    int getBoolValues(void);
  protected:
  private:
    IRSensor _left;
		IRSensor _midLeft;
		IRSensor _mid;
		IRSensor _midRight;
		IRSensor _right;
    int _enablePin;
    int _BoolThreshold;
};

#endif
