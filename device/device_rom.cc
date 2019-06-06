#include "device_rom.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>

DeviceROM::DeviceROM(uint16_t address_start, size_t region_length) {
	address_start_ = address_start;
	region_length_ = region_length;

	buffer_contents_ = (uint8_t*) malloc(region_length_ * sizeof(uint8_t));
}

DeviceROM::DeviceROM(uint16_t address_start, size_t region_length,
	std::string file_path
) {
	address_start_ = address_start;
	region_length_ = region_length;

	buffer_contents_ = (uint8_t*) malloc(region_length_ * sizeof(uint8_t));


	std::ifstream f(file_path);

	// Bail if file wasn't found.
	if (!f.good()) {
		std::cout
			<< "[FATL] [device_rom.cc] Specified file does not exist!"
			<< std::endl;
		exit(ENOENT);
	}

	f.seekg(0, f.end);
	size_t file_length = f.tellg();
	f.seekg(0, f.beg);

	/*
		Check that file length <= buffer space.
		If not, only read until buffer is filled.
	*/
	if (file_length > region_length_) {
		// Warn that we will truncate the read.
		std::cout
			<< "[WARN] [device_rom.cc] Specified romfile is too long for virtual ROM!"
			<< "Truncating read!" << std::endl;

		// Warn how large the file was.
		printf(
			"[WARN] [device_rom.cc] "
			"Attempting to load %s (%li bytes), into virtual ROM with size of %li bytes!\n",
			file_path.c_str(), file_length, region_length_
		);

		// Truncate read.
		file_length = sizeof(buffer_contents_);
	} else {
		printf(
			"[INFO] [device_rom.cc] "
			"Loaded %s (%li bytes), into virtual ROM with size of %li bytes\n",
			file_path.c_str(), file_length, region_length_
		);
	}

	// Read the file into our buffer.
	f.read((char*) buffer_contents_, file_length);
}

DeviceROM::~DeviceROM() {
	free(buffer_contents_);
}

void DeviceROM::Clock() {
	if (bus_->MemoryRequestActive()) {
		if (bus_->ReadRequestActive()) {
			if (bus_->Address() >= address_start_ &&
				bus_->Address() < (address_start_ + region_length_))
			{
				printf("[INFO] [device_rom.cc] /RD request made for 0x%04x\n",
					bus_->Address());
				bus_->PushData(
					buffer_contents_[bus_->Address() - address_start_]);
			}
		}
	}
}

void DeviceROM::BindToBus(Bus* bus) {
	bus_ = bus;
}
