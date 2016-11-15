#ifndef LINE_DETECTOR_H
#define LINE_DETECTOR_H

#include <Arduino.h>
#include "IRProx.h"

class LineDetector{
  public:
    LineDetector(int SensorMidLeft, int SensorMid, int SensorMidRight, int Enable);
    LineDetector(int SensorLeft, int SensorMidLeft, int SensorMid, int SensorMidRight, int SensorRight, int Enable);
    int getError(void);
    void calibrateAll(void);
    void printValues(void);
  protected:
  private:
    IRProx _LeftPin;
    IRProx _MidLeftPin;
    IRProx _MidPin;
    IRProx _MidRightPin;
    IRProx _RightPin;
    int _EnablePin;
    boolean _allSensors;
};

#endif
