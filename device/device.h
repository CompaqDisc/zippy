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
	virtual uint8_t MemoryRead(uint16_t address) {return (uint8_t) 0;};
	virtual void MemoryWrite(uint16_t address, uint8_t value) {};
};

#endif	// ZIPPY_DEVICE_H_