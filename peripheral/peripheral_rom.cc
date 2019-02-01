#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include "peripheral_rom.h"
#include "peripheral_memory_mapped.h"

PeripheralROM::PeripheralROM(uint16_t _addressBeginMap, size_t _regionSize) {
	this->nAddressBeginMap = _addressBeginMap;
	this->nRegionSize = _regionSize;

	this->nBufferMemory = (uint8_t*) malloc(this->nRegionSize * sizeof(uint8_t));
}

PeripheralROM::PeripheralROM(uint16_t _addressBeginMap, size_t _regionSize, std::string _path) {
	this->nAddressBeginMap = _addressBeginMap;
	this->nRegionSize = _regionSize;

	this->nBufferMemory = (uint8_t*) malloc(this->nRegionSize * sizeof(uint8_t));


	std::ifstream f(_path);

	// Bail if file wasn't found.
	if (!f.good()) {
		std::cout << "[FATL] [peripheral_rom.cc] Specified file does not exist!" << std::endl;
		exit(ENOENT);
	}

	f.seekg(0, f.end);
	size_t length = f.tellg();
	f.seekg(0, f.beg);

	/*
		Check that file length <= buffer space.
		If not, only read until buffer is filled.
	*/
	if (length > this->nRegionSize) {
		std::cout << "[WARN] [peripheral_rom.cc] Specified file is too long for buffer! Truncating content!" << std::endl;
		length = sizeof(this->nBufferMemory);
		printf("[WARN] [peripheral_rom.cc] %s: %libytes >= %libytes\n", _path.c_str(), length, this->nRegionSize);
	} else {
		printf("[INFO] [peripheral_rom.cc] %s: %libytes -> %libytes\n", _path.c_str(), length, this->nRegionSize);
	}

	f.read((char*) this->nBufferMemory, length);
}

PeripheralROM::~PeripheralROM() {
	free(this->nBufferMemory);
}

uint8_t PeripheralROM::read(uint16_t _address) {
	// Subtract the start address from the given address so we get an index into the buffer.
	uint16_t i = _address - this->nAddressBeginMap;

	/*
		Bail if the calculated index ends up out of bounds.
		(IDK how that would end up occuring, but whatever.)

		TODO: Remove check if unneeded.
	*/
	if (i > this->nRegionSize) {
		std::cout << "[FATL] [peripheral_rom.cc] Calculated index returned out of bounds!" << std::endl;
		exit(ERANGE);
	}

	return this->nBufferMemory[i];
}

void PeripheralROM::write(uint16_t _address, uint8_t _value) {
	// Subtract the start address from the given address so we get an index into the buffer.
	uint16_t i = _address - this->nAddressBeginMap;

	/*
		Bail if the calculated index ends up out of bounds.
		(IDK how that would end up occuring, but whatever.)

		TODO: Remove check if unneeded.
	*/
	if (i > this->nRegionSize) {
		std::cout << "[FATL] [peripheral_rom.cc] Calculated index returned out of bounds!" << std::endl;
		exit(ERANGE);
	}

	this->nBufferMemory[i] = _value;
}