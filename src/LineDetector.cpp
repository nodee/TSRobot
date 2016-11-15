#include "LineDetector.h"

LineDetector::LineDetector(int SensorMidLeft, int SensorMid, int SensorMidRight, int Enable){
  _MidLeftPin.setPin(SensorMidLeft);
  _MidPin.setPin(SensorMid);
  _MidRightPin.setPin(SensorMidRight);
  _EnablePin = Enable;
  pinMode(_EnablePin, OUTPUT);
  _allSensors = 0;
}

LineDetector::LineDetector(int SensorLeft, int SensorMidLeft, int SensorMid, int SensorMidRight, int SensorRight, int Enable){
  _LeftPin.setPin(SensorLeft);
  _MidLeftPin.setPin(SensorMidLeft);
  _MidPin.setPin(SensorMid);
  _MidRightPin.setPin(SensorMidRight);
  _RightPin.setPin(SensorRight);
  _EnablePin = Enable;
  pinMode(_EnablePin, OUTPUT);
  _allSensors = 1;
}

void LineDetector::calibrateAll(void){
    digitalWrite(_EnablePin, HIGH);
    delay(10);

    _MidLeftPin.calibrate();
    _MidPin.calibrate();
    _MidRightPin.calibrate();
    if(_allSensors){
      _LeftPin.calibrate();
      _RightPin.calibrate();
    }
    digitalWrite(_EnablePin, LOW);
}

int LineDetector::getError(void){

  float result = 0.0;

  digitalWrite(_EnablePin, HIGH);
  delay(10);

  _MidLeftPin.update();
  _MidPin.update();
  _MidRightPin.update();

  if(_allSensors){
    _LeftPin.update();
    _RightPin.update();
    digitalWrite(_EnablePin, LOW);
    result = (float)(_LeftPin.getValue() + (_MidLeftPin.getValue() * 2) + (_MidPin.getValue() * 3) + (_MidRightPin.getValue() * 4) + (_RightPin.getValue() * 5));
    result = result / (float)(_LeftPin.getValue() + _MidLeftPin.getValue() + _MidPin.getValue() + _MidRightPin.getValue() + _RightPin.getValue());
    result *= 100;
    result = 280-result;
  }
  else{
    digitalWrite(_EnablePin, LOW);
    result = (float)(_MidLeftPin.getValue() + (_MidPin.getValue() * 2) + (_MidRightPin.getValue() * 3));
    result = result / (float)(_MidLeftPin.getValue() + _MidPin.getValue() + _MidRightPin.getValue());
    result *= 100;
    result = 280-result;
  }

  return (int)result;
}

void LineDetector::printValues(void){
   _MidLeftPin.printValues();
   _MidPin.printValues();
   _MidRightPin.printValues();
   if(_allSensors){
     _RightPin.printValues();
     _LeftPin.printValues();
   }
}
