#include "IRSensor.h"

IRSensor::IRSensor(int inputPin){
	_inputPin = inputPin;
	resetSensor();
}

void IRSensor::resetSensor(void){
	_minValue = 1024;
	_maxValue = 0;
	_sensorRange = 0;
}

int IRSensor::readSensor(void){

	return analogRead(_inputPin);
}

void IRSensor::setThreshold(int thresholdValue){

	_threshold = thresholdValue;
}

bool IRSensor::getBoolValue(void){

	int sensorValue;
	bool boolValue;

	sensorValue = readSensor();

	if(sensorValue > _threshold){
		boolValue = 1;
	}
	else{
		boolValue = 0;
	}

	return boolValue;
}

void IRSensor::findRange(void){

	int sensorValue;

	sensorValue = readSensor();

	if(sensorValue > _maxValue){
		_maxValue = sensorValue;
	}
	if(sensorValue < _minValue){
		_minValue = sensorValue;
	}

	_sensorRange = _maxValue - _minValue;

	return;
}

int IRSensor::getPercentValue(void){

	int sensorValue;

	sensorValue = readSensor();

	if(sensorValue > _maxValue){
		sensorValue = _maxValue;
	}
	if(sensorValue < _minValue){
		sensorValue = _minValue;
	}
	else{
		sensorValue -= _minValue;
	}

	sensorValue *= 100;
	sensorValue /= _sensorRange;

	return sensorValue;
}
