#include "IRProx.h"

IRProx::IRProx(int analogPin){
  _minValue = 1024;
  _maxValue = 0;
  _analogPin = analogPin;
}

// reads the analogPin associated with this proximity sensor
uint16_t IRProx::getValue()
{
  return analogRead(_analogPin);
}

// updates the range if value lies outside current range
void IRProx::calibrate(uint16_t value)
{
	if (value < _minValue){
		_minValue = value;
	}
	if (value > _maxValue){
		_maxValue = value;
	}
	return;
}

// gives the current analog reading as a % of the range
uint8_t IRProx::update(void)
{
	uint16_t value = 0;

	value = this->getValue();

	if(value > _maxValue){
		value = _maxValue;
	}
	if(value < _minValue){
		value = 0;
	}
	else{
		value -= _minValue;
	}
	value *= 100;
	value = value / (_maxValue - _minValue);
	return (uint8_t)value;
}

// prints pin, min, max and current values of this sensor
void IRProx::printValues(void){
  Serial.print(_analogPin);
  Serial.print(" - ");
  Serial.print("Min: ");
  Serial.print(_minValue);
  Serial.print(", Max: ");
  Serial.print(_maxValue);
  Serial.print(", Cur: ");
  Serial.println(this->update());
}
