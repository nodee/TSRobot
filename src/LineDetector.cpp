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
    result = (float)(_LeftPin.getPercentValue() + (_MidLeftPin.getPercentValue() * 2) + (_MidPin.getPercentValue() * 3) + (_MidRightPin.getPercentValue() * 4) + (_RightPin.getPercentValue() * 5));
    result = result / (float)(_LeftPin.getPercentValue() + _MidLeftPin.getPercentValue() + _MidPin.getPercentValue() + _MidRightPin.getPercentValue() + _RightPin.getPercentValue());
    result *= 100;
    result = 300-result;
  }
  else{
    digitalWrite(_EnablePin, LOW);
    result = (float)(_MidLeftPin.getPercentValue() + (_MidPin.getPercentValue() * 2) + (_MidRightPin.getPercentValue() * 3));
    result = result / (float)(_MidLeftPin.getPercentValue() + _MidPin.getPercentValue() + _MidRightPin.getPercentValue());
    result *= 100;
    result = 300-result;
  }
  if(result > 75){
    result = 75;
  }
  if(result < -75){
    result = -75;
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

int LineDetector::getBoolValues(void){

  int results = 0;

  if(_MidLeftPin.update() > 50){
    results &= (1<<3);
  }
  if(_MidPin.update() > 50){
    results &= (1<<2);
  }
  if(_MidRightPin.update() > 50){
    results &= (1<<1);
  }

  if(_allSensors){
    if(_LeftPin.update() > 50){
      results &= (1<<4);
    }
    if(_RightPin.update() > 50){
      results &= 0x01;
    }
  }
  return results;
}
