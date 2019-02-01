#ifndef ZIPPY_BUS_H_
#define ZIPPY_BUS_H_

#include "../device/device.h"

#include <stdint.h>

#include <vector>

class Bus {
private:
	std::vector<IDevice*> devices_;
	uint16_t address_;
	uint8_t data_;

	bool halt_;
	bool mreq_;
	bool iorq_;
	bool rd_;
	bool wr_;
	bool busak_;
	bool busrq_;
	bool wait_;
	bool m1_;

public:
	void RegisterDevice(IDevice* device);
	void Bind(Bus* bus);
	void Clock();
	void Reset();
	void Interrupt();
	void NonMaskableInterrupt();
	void Refresh();

	void PushAddress(uint16_t address);
	uint16_t Address();
	void PushData(uint8_t data);
	uint8_t Data();

	void PushHalt(bool state);
	bool HaltActive();

	void PushMemoryRequest(bool state);
	bool MemoryRequestActive();

	void PushIORequest(bool state);
	bool IORequestActive();

	void PushReadRequest(bool state);
	bool ReadRequestActive();

	void PushWriteRequest(bool state);
	bool WriteRequestActive();

	void PushBusAcknowledge(bool state);
	bool BusAcknowledgeActive();

	void PushBusRequest(bool state);
	bool BusRequestActive();

	void PushWait(bool state);
	bool WaitActive();

	void PushM1(bool state);
	bool M1Active();
};

#endif	// ZIPPY_BUS_H_