#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <Arduino.h>

class IRSensor{
	public:
		IRSensor(int inputPin);
		int readSensor(void);
		void resetSensor(void);
		void setThreshold(int thresholdValue);
		bool getBoolValue(void);
		void findRange(void);
		int getPercentValue(void);
	private:
		int _inputPin;
		int _minValue;
		int _maxValue;
		int _sensorRange;
		int _threshold;
};

#endif
