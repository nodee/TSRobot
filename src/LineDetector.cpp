#include "LineDetector.h"

LineDetector::LineDetector(int sLeft, int sMidLeft, int sMid, int sMidRight, int sRight, int sEnable)
:_left(sLeft), _midLeft(sMidLeft), _mid(sMid), _midRight(sMidRight), _right(sRight)
{
	_enablePin = sEnable;
	pinMode(_enablePin, OUTPUT);
}

void LineDetector::calibrate(void){
    digitalWrite(_enablePin, HIGH);
    delay(5);
    _midLeft.findRange();
    _mid.findRange();
    _midRight.findRange();
    _left.findRange();
    _right.findRange();
    digitalWrite(_enablePin, LOW);
}

void LineDetector::setThreshold(int threshold){
  _left.setThreshold(threshold);
  _midLeft.setThreshold(threshold);
  _mid.setThreshold(threshold);
  _midRight.setThreshold(threshold);
  _right.setThreshold(threshold);
  return;
}

int LineDetector::getBoolValues(void){

	int result = 0;

  digitalWrite(_enablePin, HIGH);
  delay(5);

	if(_left.getBoolValue()){
		result |= (1<<4);
	}
	if(_midLeft.getBoolValue()){
		result |= (1<<3);
	}
	if(_mid.getBoolValue()){
		result |= (1<<2);
	}
	if(_midRight.getBoolValue()){
		result |= (1<<1);
	}
	if(_right.getBoolValue()){
		result |= 1;
	}

  digitalWrite(_enablePin, LOW);

	return result;
}

int LineDetector::getError(){

	enum sensors{SL, SML, SM, SMR, SR};
	int sensorValues[5] = {0,0,0,0,0};
	long resultCalc;
	int result;

	digitalWrite(_enablePin, HIGH);
	delay(2);

	sensorValues[SL] = _left.getPercentValue();
	sensorValues[SML] = _midLeft.getPercentValue();
	sensorValues[SM] = _mid.getPercentValue();
	sensorValues[SMR] = _midRight.getPercentValue();
	sensorValues[SR] = _right.getPercentValue();

	digitalWrite(_enablePin, LOW);

	resultCalc = (sensorValues[SL] + (2*sensorValues[SML]) + (3*sensorValues[SM]) + (4*sensorValues[SMR]) + (5*sensorValues[SR]));
	resultCalc *= 100;
	resultCalc = resultCalc / (sensorValues[SL] + sensorValues[SML] + sensorValues[SM] + sensorValues[SMR] + sensorValues[SR]);
	result = 300 - (int)resultCalc;

	if(result > 75){ result = 75; }
	if(result < -75){ result = -75; }

	return result;
}
