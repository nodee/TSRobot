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
