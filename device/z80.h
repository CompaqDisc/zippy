#ifndef ZIPPY_DEVICE_Z80_H_
#define ZIPPY_DEVICE_Z80_H_

#include "../bus/bus.h"
#include "device.h"

#include <stdint.h>

class Z80: public IDevice {
public:
	void Reset();
	void Clock();
	void BindToBus(Bus* bus);
	Z80();
private:
	Bus* bus_;
	union reg16 {
		uint16_t r;

		struct {
			uint8_t l;
			uint8_t h;
		};
	};

	// AF (accumulator and flags)
	reg16 af_;
	// BC
	reg16 bc_;
	// DE
	reg16 de_;
	// HL (indirect address)
	reg16 hl_;
	
	// AF' (accumulator and flags)
	reg16 af_prime_;
	// BC'
	reg16 bc_prime_;
	// DE'
	reg16 de_prime_;
	// HL' (indirect address)
	reg16 hl_prime_;

	// Index X
	reg16 ix_;
	// Index Y
	reg16 iy_;
	// Stack Pointer
	reg16 sp_;

	// Interrupt Vector
	uint8_t i_;
	// Refresh Counter
	uint8_t r_;

	// Program Counter
	uint16_t pc_;

	/*
		Internal states/signals
	*/
	// Interrupt State
	bool interrupts_enabled_;
	// Interrupt Mode
	uint8_t interrupt_mode_;
	// Current Machine Cycle
	uint8_t machine_cycle_;
	// Current T-State
	uint8_t t_state_;
	// Buffered Data Bus
	uint8_t data_;
	// Instruction Cache
	std::vector<uint8_t> instruction_cache_;
	// Operand Cache
	std::vector<uint8_t> operand_cache_;
};

#endif	// ZIPPY_DEVICE_Z80_H_