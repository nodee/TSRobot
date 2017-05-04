#include "LineDetector.h"

LineDetector::LineDetector(int sLeft, int sMidLeft, int sMidRight, int sRight, int sEnable)
:_lLeft(sLeft), _lMidLeft(sMidLeft), _lMidRight(sMidRight), _lRight(sRight)
{
	_enablePin = sEnable;
	pinMode(_enablePin, OUTPUT);
}

void LineDetector::calibrate(void){
    digitalWrite(_enablePin, HIGH);
    delay(10);
    _lMidLeft.findRange();
    _lMidRight.findRange();
    _lLeft.findRange();
    _lRight.findRange();
    digitalWrite(_enablePin, LOW);
}

void LineDetector::setThreshold(int threshold){
  _lLeft.setThreshold(threshold);
  _lMidLeft.setThreshold(threshold);
  _lMidRight.setThreshold(threshold);
  _lRight.setThreshold(threshold);
  return;
}

int LineDetector::getBoolValues(void){

	int result = 0;

  digitalWrite(_enablePin, HIGH);
  delay(5);

	if(_lLeft.getBoolValue()){
		result |= (1<<3);
	}
	if(_lMidLeft.getBoolValue()){
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

	enum sensors{SL, SML, SMR, SR};
	int sensorValues[4] = {0,0,0,0};
	long resultCalc;
	int result;

	digitalWrite(_enablePin, HIGH);
	delay(5);

	sensorValues[SL] = _lLeft.getPercentValue();
	sensorValues[SML] = _lMidLeft.getPercentValue();
	sensorValues[SMR] = _lMidRight.getPercentValue();
	sensorValues[SR] = _lRight.getPercentValue();

	digitalWrite(_enablePin, LOW);

	Serial.print("L:");Serial.print(sensorValues[SL]);
	Serial.print(" ML:");Serial.print(sensorValues[SML]);
	Serial.print(" MR:");Serial.print(sensorValues[SMR]);
	Serial.print(" R:");Serial.println(sensorValues[SR]);

	resultCalc = (sensorValues[SL] + (2*sensorValues[SML]) + (3*sensorValues[SMR]) + (4*sensorValues[SR]));
	resultCalc *= 100;
	resultCalc = resultCalc / (sensorValues[SL] + sensorValues[SML] + sensorValues[SMR] + sensorValues[SR]);
	result = 250 - (int)resultCalc;

	if(result > 75){ result = 75; }
	if(result < -75){ result = -75; }

	return result;
}

void LineDetector::printInfo(void){
	digitalWrite(_enablePin, HIGH);
	delay(20);
	Serial.println("Sensors");
	_lLeft.printInfo();
	_lMidLeft.printInfo();
	_lMidRight.printInfo();
	_lRight.printInfo();
	digitalWrite(_enablePin, LOW);
}
