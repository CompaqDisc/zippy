#ifndef ZIPPY_MACHINE_H_
#define ZIPPY_MACHINE_H_

#include <string>
#include <atomic>
#include <vector>
#include "../chip/z80.h"
#include "../peripheral/peripheral.h"

class Machine {
protected:
	long lTargetClockSpeedHz;
	std::string sMachineID;
	static std::atomic<bool> bAtomActive;
	Z80 cpu;
	std::vector<Peripheral> pv;

private:
	void TaskThread();

public:
	Machine();
	void Start();
};

#endif