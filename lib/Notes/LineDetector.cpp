#include "LineDetector.h"

LineDetector::LineDetector(int SensorLeft, int SensorMidLeft, int SensorMid, int SensorMidRight, int SensorRight)
{
  _LeftPin = new IRProx(SensorLeft);
  _MidLeftPin = new IRProx(SensorMidLeft);
  _MidPin = new IRProx(SensorMid);
  _MidRightPin = new IRProx(SensorMidRight);
  _RightPin = new IRProx(SensorRight);
}
