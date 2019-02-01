#ifndef ZIPPY_PERIPHERAL_ROM_H_
#define ZIPPY_PERIPHERAL_ROM_H_

#include <stdint.h>
#include <string>
#include "peripheral_memory_mapped.h"

class PeripheralROM: public PeripheralMemoryMapped {
protected:
	uint8_t* nBufferMemory;

public:
	PeripheralROM(uint16_t _addressBeginMap, size_t _regionSize, std::string _path);
	PeripheralROM(uint16_t _addressBeginMap, size_t _regionSize);
	~PeripheralROM();

	uint8_t read(uint16_t _address);
	void write(uint16_t _address, uint8_t _value);
};

#endif