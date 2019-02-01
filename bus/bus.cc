#include "bus.h"

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
}

void Bus::Interrupt() {}
void Bus::NonMaskableInterrupt() {}
void Bus::Refresh() {}

void Bus::PushAddress(uint16_t address) {
	address_ = address;
}

uint16_t Bus::Address() {
	return address_;
}

void Bus::PushData(uint8_t data) {
	data_ = data;
}

uint8_t Bus::Data() {
	return data_;
}

void Bus::PushHalt(bool state) {
	halt_ = state;
}

bool Bus::HaltActive() {
	return halt_;
}

void Bus::PushMemoryRequest(bool state) {
	mreq_ = state;
}

bool Bus::MemoryRequestActive() {
	return mreq_;
}

void Bus::PushIORequest(bool state) {
	iorq_ = state;
}

bool Bus::IORequestActive() {
	return iorq_;
}

void Bus::PushReadRequest(bool state) {
	rd_ = state;
}

bool Bus::ReadRequestActive() {
	return rd_;
}

void Bus::PushWriteRequest(bool state) {
	wr_ = state;
}

bool Bus::WriteRequestActive() {
	return wr_;
}

void Bus::PushBusAcknowledge(bool state) {
	busak_ = state;
}

bool Bus::BusAcknowledgeActive() {
	return busak_;
}

void Bus::PushBusRequest(bool state) {
	busrq_ = state;
}

bool Bus::BusRequestActive() {
	return busrq_;
}

void Bus::PushWait(bool state) {
	wait_ = state;
}

bool Bus::WaitActive() {
	return wait_;
}

void Bus::PushM1(bool state) {
	m1_ = state;
}

bool Bus::M1Active() {
	return m1_;
}