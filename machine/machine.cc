#include <thread>
#include <chrono>
#include <stdint.h>
#include "machine.h"
#include "../peripheral/peripheral_rom.h"

Machine::Machine() {
	sMachineID = "default";
	lTargetClockSpeedHz = 1;
}

void Machine::Start() {
	bAtomActive = true;

	std::thread t = std::thread(&Machine::TaskThread, this);
	t.join();
}

void Machine::TaskThread() {
	cpu = Z80();
	pv.push_back(PeripheralROM((uint16_t) 0, (size_t) 1024, "test.rom"));

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	while (bAtomActive) {
		// Magic inner loop?
		while (bAtomActive) {
			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsedTime = tp2 - tp1;
			tp1 = tp2;
			float fElapsedTime = elapsedTime.count();
			static float fAccumulatedTime;
			fAccumulatedTime += fElapsedTime;

			if (fAccumulatedTime >= 1.0f / this->lTargetClockSpeedHz) {
				cpu.clock();
				fAccumulatedTime = 0.0f;
			}
			
			if (cpu.halted) {
				bAtomActive = false;
			}
		}
	}
}

std::atomic<bool> Machine::bAtomActive(false);