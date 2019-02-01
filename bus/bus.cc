#include "bus.h"

#include <iostream>

void Bus::RegisterDevice(IDevice* device) {
	devices_.push_back(device);
}

void Bus::Bind(Bus* bus) {
	for (auto d : devices_) {
		d->BindToBus(bus);
	}
}

void Bus::Clock() {
	for (auto d : devices_) {
		d->Clock();
	}
}

void Bus::Reset() {
	for (auto d : devices_) {
		d->Reset();
	}

	halt_ = false;
	mreq_ = false;
	iorq_ = false;
	rd_ = false;
	wr_ = false;
	busak_ = false;
	busrq_ = false;
	wait_ = false;
	m1_ = false;
}

void Bus::Interrupt() {}
void Bus::NonMaskableInterrupt() {}
void Bus::Refresh() {}

void Bus::PushAddress(uint16_t address) {
	if (address_ != address)
		printf("[INFO] [bus.cc] Address bus is now 0x%04x\n", address);
	address_ = address;
}

uint16_t Bus::Address() {
	return address_;
}

void Bus::PushData(uint8_t data) {
	if (data_ != data)
		printf("[INFO] [bus.cc] Data bus is now 0x%02x\n", data);
	data_ = data;
}

uint8_t Bus::Data() {
	return data_;
}

void Bus::PushHalt(bool state) {
	if (halt_ != state)
		std::cout
			<< "[INFO] [bus.cc] /HALT is now "
			<< (!halt_ ? "" : "in") << "active" << std::endl;
	halt_ = state;
}

bool Bus::HaltActive() {
	return halt_;
}

void Bus::PushMemoryRequest(bool state) {
	if (mreq_ != state)
		std::cout
			<< "[INFO] [bus.cc] /MREQ is now "
			<< (!mreq_ ? "" : "in") << "active" << std::endl;
	mreq_ = state;
}

bool Bus::MemoryRequestActive() {
	return mreq_;
}

void Bus::PushIORequest(bool state) {
	if (iorq_ != state)
		std::cout
			<< "[INFO] [bus.cc] /IORQ is now "
			<< (!iorq_ ? "" : "in") << "active" << std::endl;
	iorq_ = state;
}

bool Bus::IORequestActive() {
	return iorq_;
}

void Bus::PushReadRequest(bool state) {
	if (rd_ != state)
		std::cout
			<< "[INFO] [bus.cc] /RD is now " << (!rd_ ? "" : "in") << "active"
			<< std::endl;
	rd_ = state;
}

bool Bus::ReadRequestActive() {
	return rd_;
}

void Bus::PushWriteRequest(bool state) {
	if (wr_ != state)
		std::cout
			<< "[INFO] [bus.cc] /WR is now " << (!wr_ ? "" : "in") << "active"
			<< std::endl;
	wr_ = state;
}

bool Bus::WriteRequestActive() {
	return wr_;
}

void Bus::PushBusAcknowledge(bool state) {
	if (busak_ != state)
		std::cout
			<< "[INFO] [bus.cc] /BUSAK is now "
			<< (!busak_ ? "" : "in") << "active" << std::endl;
	busak_ = state;
}

bool Bus::BusAcknowledgeActive() {
	return busak_;
}

void Bus::PushBusRequest(bool state) {
	if (busrq_ != state)
		std::cout
			<< "[INFO] [bus.cc] /BUSRQ is now "
			<< (!busrq_ ? "" : "in") << "active" << std::endl;
	busrq_ = state;
}

bool Bus::BusRequestActive() {
	return busrq_;
}

void Bus::PushWait(bool state) {
	if (wait_ != state)
		std::cout
			<< "[INFO] [bus.cc] /WAIT is now "
			<< (!wait_ ? "" : "in") << "active" << std::endl;
	wait_ = state;
}

bool Bus::WaitActive() {
	return wait_;
}

void Bus::PushM1(bool state) {
	if (m1_ != state)
		std::cout
			<< "[INFO] [bus.cc] /M1 is now " << (!m1_ ? "" : "in") << "active"
			<< std::endl;
	m1_ = state;
}

bool Bus::M1Active() {
	return m1_;
}