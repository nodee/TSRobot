#include "ProxDetector.h"

ProxDetector::ProxDetector(int sLeft, int sFront, int sRight, int sEnable)
:_pLeft(sLeft), _pFront(sFront), _pRight(sRight)
{
    _enablePin = sEnable;
    pinMode(sEnable, OUTPUT);
}

void ProxDetector::setThreshold(int threshold)
{
  _pLeft.setThreshold(threshold);
  _pFront.setThreshold(threshold);
  _pRight.setThreshold(threshold);
  return;
}

void ProxDetector::caliThreshold(){

  float result = 0.0;

  digitalWrite(_enablePin, HIGH);
  delay(5);

  result = (float)_pLeft.readSensor();
  result = result * THRESHOLD_MULTIPLIER;
  _pLeft.setThreshold((int)result);

  result = (float)_pFront.readSensor();
  result = result * THRESHOLD_MULTIPLIER;
  _pFront.setThreshold((int)result);

  result = (float)_pRight.readSensor();
  result = result * THRESHOLD_MULTIPLIER;
  _pRight.setThreshold((int)result);

  digitalWrite(_enablePin, LOW);

  return;

}

int ProxDetector::getBoolValues()
{
  int result = 0;

  digitalWrite(_enablePin, HIGH);
  delay(5);

	if(_pLeft.getBoolValue()){
		result |= (1<<2);
	}
	if(_pFront.getBoolValue()){
		result |= (1<<1);
	}
	if(_pRight.getBoolValue()){
		result |= 1;
	}

  digitalWrite(_enablePin, LOW);

	return result;
}
