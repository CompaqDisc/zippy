#ifndef ZIPPY_PERIPHERAL_MEMMAPPED_H_
#define ZIPPY_PERIPHERAL_MEMMAPPED_H_

#include <stdint.h>
#include "peripheral.h"

class PeripheralMemoryMapped: public Peripheral {
	public:
		uint16_t nAddressBeginMap;
		size_t nRegionSize;

		virtual uint8_t read(uint16_t _address) {return (uint8_t) 0x00;};
		virtual void write(uint16_t _address, uint8_t _value) {};
};

#endif