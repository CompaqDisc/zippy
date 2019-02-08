#ifndef ZIPPY_DEVICE_ROM_H_
#define ZIPPY_DEVICE_ROM_H_

#include "../bus/bus.h"
#include "device.h"

#include <stdint.h>
#include <string>

class DeviceROM: public IDevice {
private:
	uint8_t* buffer_contents_;
	uint16_t address_start_;
	size_t region_length_;
	Bus* bus_;

public:
	DeviceROM(uint16_t address_start, size_t region_length, std::string file_path);
	DeviceROM(uint16_t address_start, size_t region_length);
	~DeviceROM();
	void Clock();
	void BindToBus(Bus* bus);
};

#endif	// ZIPPY_DEVICE_ROM_H_