#ifndef IRPROX_H
#define IRPROX_H

#include <Arduino.h>

class IRProx{
	public:
    IRProx();
    IRProx(int analogPin);
		uint16_t getValue(void);
		void calibrate(uint16_t value);
    void calibrate(void);
    uint8_t update(void);
    void printValues(void);
    void reset(void);
	protected:
	private:
		uint16_t _maxValue;
		uint16_t _minValue;
    uint16_t _analogPin;
};

#endif
