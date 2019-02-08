#ifndef ZIPPY_DEVICE_H_
#define ZIPPY_DEVICE_H_

#include <stdint.h>

class Bus;

class IDevice {
public:
	virtual void BindToBus(Bus* bus) {};
	virtual void Clock() {};
	virtual void Reset() {};
	virtual void Interrupt() {};
	virtual void NonMaskableInterrupt() {};
	virtual void Refresh() {};
};

#endif	// ZIPPY_DEVICE_H_