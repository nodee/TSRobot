#ifndef IRPROX_H
#define IRPROX_H

#include <Arduino.h>

class IRProx{
	public:
    IRProx();
		uint16_t readSensor(void);
		uint16_t getValue(void);
		int getPercentValue(void);
		void calibrate(uint16_t value);
    void calibrate(void);
    uint8_t update(void);
    void printValues(void);
    void reset(void);
		void setPin(int analogPin);
	private:
		uint16_t _maxValue;
		uint16_t _minValue;
    uint16_t _analogPin;
		uint16_t _currentValue;
	  int _percentValue;
};

#endif
