#include "LineDetector.h"

LineDetector::LineDetector(int sLeft, int sMidLeft, int sMid, int sMidRight, int sRight, int sEnable)
:_lLeft(sLeft), _lMidLeft(sMidLeft), _lMid(sMid), _lMidRight(sMidRight), _lRight(sRight)
{
	_enablePin = sEnable;
	pinMode(_enablePin, OUTPUT);
}

void LineDetector::calibrate(void){
    digitalWrite(_enablePin, HIGH);
    delay(5);
    _lMidLeft.findRange();
    _lMid.findRange();
    _lMidRight.findRange();
    _lLeft.findRange();
    _lRight.findRange();
    digitalWrite(_enablePin, LOW);
}

void LineDetector::setThreshold(int threshold){
  _lLeft.setThreshold(threshold);
  _lMidLeft.setThreshold(threshold);
  _lMid.setThreshold(threshold);
  _lMidRight.setThreshold(threshold);
  _lRight.setThreshold(threshold);
  return;
}

int LineDetector::getBoolValues(void){

	int result = 0;

  digitalWrite(_enablePin, HIGH);
  delay(5);

	if(_lLeft.getBoolValue()){
		result |= (1<<4);
	}
	if(_lMidLeft.getBoolValue()){
		result |= (1<<3);
	}
	if(_lMid.getBoolValue()){
		result |= (1<<2);
	}
	if(_lMidRight.getBoolValue()){
		result |= (1<<1);
	}
	if(_lRight.getBoolValue()){
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

	sensorValues[SL] = _lLeft.getPercentValue();
	sensorValues[SML] = _lMidLeft.getPercentValue();
	sensorValues[SM] = _lMid.getPercentValue();
	sensorValues[SMR] = _lMidRight.getPercentValue();
	sensorValues[SR] = _lRight.getPercentValue();

	digitalWrite(_enablePin, LOW);

	resultCalc = (sensorValues[SL] + (2*sensorValues[SML]) + (3*sensorValues[SM]) + (4*sensorValues[SMR]) + (5*sensorValues[SR]));
	resultCalc *= 100;
	resultCalc = resultCalc / (sensorValues[SL] + sensorValues[SML] + sensorValues[SM] + sensorValues[SMR] + sensorValues[SR]);
	result = 300 - (int)resultCalc;

	if(result > 75){ result = 75; }
	if(result < -75){ result = -75; }

	return result;
}
