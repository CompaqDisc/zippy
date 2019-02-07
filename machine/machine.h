#ifndef ZIPPY_MACHINE_H_
#define ZIPPY_MACHINE_H_

#include <string>
#include <atomic>
#include <vector>
#include "../bus/bus.h"

class Machine {
protected:
	long target_speed_hz_;
	std::string machine_id_;
	static std::atomic<bool> atomic_active_;
	Bus bus_;

private:
	virtual void TaskThread();

public:
	Machine();
	virtual void Start();
};

#endif	// ZIPPY_MACHINE_H_