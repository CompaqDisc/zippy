#include "machine.h"

#include "../bus/bus.h"
#include "../device/z80.h"
#include "../device/device_rom.h"

#include <thread>
#include <chrono>
#include <stdint.h>
#include <iostream>
#include <typeinfo>

Machine::Machine() {
	machine_id_ = "default";
	target_speed_hz_ = 1;
}

void Machine::Start() {
	atomic_active_ = true;

	std::thread thread_run = std::thread(&Machine::TaskThread, this);
	thread_run.join();
}

void Machine::TaskThread() {
	bus_.RegisterDevice(new Z80());
	bus_.RegisterDevice(new DeviceROM(0, 1024, "test.rom"));

	bus_.Bind(&bus_);
	bus_.Reset();

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	while (atomic_active_) {
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> duration_elapsed_time = tp2 - tp1;
		tp1 = tp2;
		float elapsed_time = duration_elapsed_time.count();
		static float accumulated_time;
		accumulated_time += elapsed_time;

		if (accumulated_time >= 1.0f / target_speed_hz_) {
			bus_.Clock();
			accumulated_time = 0.0f;
		}
	}
}

std::atomic<bool> Machine::atomic_active_(false);