#ifndef ZIPPY_DEVICE_ROM_H_
#define ZIPPY_DEVICE_ROM_H_

#include "device.h"

#include <stdint.h>
#include <string>

class DeviceROM: public IDevice {
protected:
	uint8_t* buffer_contents_;
	uint16_t address_start_;
	size_t region_length_;

public:
	DeviceROM(uint16_t address_start, size_t region_length, std::string file_path);
	DeviceROM(uint16_t address_start, size_t region_length);
	~DeviceROM();

	uint8_t MemoryRead(uint16_t address);
};

#endif	// ZIPPY_DEVICE_ROM_H_