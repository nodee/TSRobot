#include "LineDetector.h"

LineDetector::LineDetector(int SensorLeft, int SensorMidLeft, int SensorMid, int SensorMidRight, int SensorRight, int Enable){
  _LeftPin.setPin(SensorLeft);
  _MidLeftPin.setPin(SensorMidLeft);
  _MidPin.setPin(SensorMid);
  _MidRightPin.setPin(SensorMidRight);
  _RightPin.setPin(SensorRight);
  _EnablePin = Enable;
  pinMode(_EnablePin, OUTPUT);
}

void LineDetector::calibrateAll(void){
    digitalWrite(_EnablePin, HIGH);
    delay(5);
    _MidLeftPin.calibrate();
    _MidPin.calibrate();
    _MidRightPin.calibrate();
    _LeftPin.calibrate();
    _RightPin.calibrate();
    digitalWrite(_EnablePin, LOW);
}

int LineDetector::getError(void){

  float result = 0.0;

  digitalWrite(_EnablePin, HIGH);
  delay(1);
  _MidLeftPin.update();
  _MidPin.update();
  _MidRightPin.update();
  _LeftPin.update();
  _RightPin.update();
  digitalWrite(_EnablePin, LOW);
  result = (float)(_LeftPin.getPercentValue() + (_MidLeftPin.getPercentValue() * 2) + (_MidPin.getPercentValue() * 3) + (_MidRightPin.getPercentValue() * 4) + (_RightPin.getPercentValue() * 5));
  result = result / (float)(_LeftPin.getPercentValue() + _MidLeftPin.getPercentValue() + _MidPin.getPercentValue() + _MidRightPin.getPercentValue() + _RightPin.getPercentValue());
  result *= 100;
  result = 300-result;

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
   _RightPin.printValues();
   _LeftPin.printValues();
}

void LineDetector::setBoolThreshold(int threshold){
  _BoolThreshold = threshold;
  return;
}

int LineDetector::getBoolValues(void){

  int results = 0;
  digitalWrite(_EnablePin, HIGH);
  delay(1);

  _RightPin.update();
  _MidRightPin.update();
  _MidPin.update();
  _MidLeftPin.update();
  _LeftPin.update();

  digitalWrite(_EnablePin, LOW);

  //Serial.print("RP: "); Serial.println(_RightPin.getPercentValue());
  if(_RightPin.getPercentValue() < _BoolThreshold){
    results |= 1;
  }

  //Serial.print("MRP: "); Serial.println(_MidRightPin.getPercentValue());
  if(_MidRightPin.getPercentValue() < _BoolThreshold){
    results |= (1<<1);
  }

  //Serial.print("MP: "); Serial.println(_MidPin.getPercentValue());
  if(_MidPin.getPercentValue() < _BoolThreshold){
    results |= (1<<2);
  }

  //Serial.print("MLP: "); Serial.println(_MidLeftPin.getPercentValue());
  if(_MidLeftPin.getPercentValue() < _BoolThreshold){
    results |= (1<<3);
  }

  //Serial.print("LP: "); Serial.println(_LeftPin.getPercentValue());
  if(_LeftPin.getPercentValue() < _BoolThreshold){
    results |= (1<<4);
  }

  return results;
}
