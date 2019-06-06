#include <iostream>
#include <stdint.h>
#include "z80.h"

Z80::Z80() {}

void Z80::Reset() {
	pc_ = (uint16_t) 0x0000;
	i_ = (uint8_t) 0x00;
	r_ = (uint8_t) 0x00;

	interrupts_enabled_ = false;
	interrupt_mode_ = (uint8_t) 0;

	machine_cycle_ = (uint8_t) 1;
	t_state_ = (uint8_t) 1;

	std::cout << "[INFO] [z80.cc] Reset Complete" << std::endl;
}

/*
	Single-cycle step of the processor.
*/
void Z80::Clock() {
	std::cout << "[INFO] [z80.cc] Clock" << std::endl;

	uint8_t x = instruction_cache_ >> 6;
	uint8_t y = (instruction_cache_ >> 3) & 0b111;
	uint8_t z = instruction_cache_ & 0b111;

	uint8_t p = y >> 1;
	uint8_t q = y & 1;

	uint8_t d, n;
	uint16_t nn;

	//printf("[INFO] [z80.cc] X: %d Y: %d Z: %d P: %d Q: %d\n",
	//	x, y, z, p, q);

	switch (machine_cycle_) {
	case 1:
		// M1 - Opcode Fetch
		std::cout << "[INFO] [z80.cc] M1" << std::endl;
		switch (t_state_) {
		case 1:
			/*
				T1 of opcode fetch.

				Per documentation and Figure 5 of Architectural Overview:
				|*	/M1 is activated.
				|*	The program counter is placed on the address bus at the
				|	beginning of the M1 cycle.
				|*	The /MREQ signal goes active.
				|*	The /RD line also goes active.
			*/

			std::cout << "[INFO] [z80.cc] T1" << std::endl;
			// TODO: Implement /RFSH reset
			// /M1 goes active.
			bus_->PushM1(true);
			// The program counter is placed on the address bus.
			bus_->PushAddress(pc_);
			// /MREQ goes active.
			bus_->PushMemoryRequest(true);
			// /RD also goes active.
			bus_->PushReadRequest(true);

			// Advance to next t-state.
			t_state_ = 2;
			break;
		case 2:
			/*
				T2 of opcode fetch.

				Per documentation and Figure 5 of Architectural Overview:
				|*	/WAIT is sampled. Repeat T2 while active.
			*/

			std::cout << "[INFO] [z80.cc] T2" << std::endl;
			if (!bus_->WaitActive()) {
				// If not waiting, advance to next t-state.
				t_state_ = 3;
			} else {
				std::cout << "[INFO] [z80.cc] /WAIT Active" << std::endl;
			}

			pc_ += 1;
			break;
		case 3:
			/*
				T3 of opcode fetch.

				Per documentation and Figure 5 of Architectural Overview:
				|*	The CPU samples the data from the memory space on the
				|	data bus with the rising edge of the clock of state T3.
				|*	This same edge is used by the CPU to turn off the
				|	/RD and /MREQ signals.
			*/

			std::cout << "[INFO] [z80.cc] T3" << std::endl;
			data_ = bus_->Data();
			instruction_cache_ = data_;

			x = instruction_cache_ >> 6;
			y = (instruction_cache_ >> 3) & 0b111;
			z = instruction_cache_ & 0b111;

			p = y >> 1;
			q = y & 1;

			DebugDisassemble();
			bus_->PushReadRequest(false);
			bus_->PushMemoryRequest(false);

			// TODO: Clock States T3 and T4 of a fetch cycle are used to refresh
			//       dynamic memories.

			t_state_ = 4;
			break;
		case 4:
			/*
				T4 of opcode fetch (refresh cycle).
			*/
			// TODO: Refresh
			std::cout << "[INFO] [z80.cc] T4" << std::endl;

			machine_cycle_ = 2;
			t_state_ = 1;

			printf("[INFO] [z80.cc] X: %d Y: %d Z: %d P: %d Q: %d\n",
				x, y, z, p, q);

			if (x == 0) {
				if (z == 0) {
					// Z = 0: Relative jumps and assorted ops.
					if (y == 0) {
						// NOP
						// Instruction finished, set m_cycle to 1.
						machine_cycle_ = 1;
					} else if (y == 1) {
						// EX AF, AF'
						reg16 temp = af_;
						af_ = af_prime_;
						af_prime_ = temp;

						// Instruction finished, set m_cycle to 1.
						machine_cycle_ = 1;
					} else if (y == 2) {
						// DJNZ
						NotImplemented();
					} else if (y == 3) {
						// JR, disp8
						NotImplemented();
					} else {
						// (y >= 4 && y <=7)
						// JR cond, disp8
						NotImplemented();
					}
				} else if (z == 1) {
					// Z = 1: 16-bit load immediate/add.
					if (!q) {
						// LD reg16, imm16
						NotImplemented();
					} else {
						// ADD HL, reg16
						NotImplemented();
					}
				} else if (z == 2) {
					// Z = 2: Indirect loading.
					if (!q) {
						if (p == 0) {
							// LD (BC), A
							NotImplemented();
						} else if (p == 1) {
							// LD (DE), A
							NotImplemented();
						} else if (p == 2) {
							// LD (imm16), HL
							NotImplemented();
						} else {
							// (p == 3)
							// LD (imm16), A
							NotImplemented();
						}
					} else {
						if (p == 0) {
							// LD A, (BC)
							NotImplemented();
						} else if (p == 1) {
							// LD A, (DE)
							NotImplemented();
						} else if (p == 2) {
							// LD HL, (imm16)
							NotImplemented();
						} else {
							// (p == 3)
							// LD A, (imm16)
							NotImplemented();
						}
					}
				} else if (z == 3) {
					if (!q) {
						// INC reg16
						NotImplemented();
					} else {
						// DEC reg16
						NotImplemented();
					}
				} else if (z == 4) {
					// INC reg8
					NotImplemented();
				} else if (z == 5) {
					// DEC reg8
					NotImplemented();
				} else if (z == 6) {
					// LD reg8, imm8
					NotImplemented();
				} else {
					// z = 7: Assorted operations on accumulator/flags.
					NotImplemented();
				}
			} else {
				NotImplemented();
			}

			if (instruction_cache_ == HALT) {
				// HALT
				pc_ -= 1;
				machine_cycle_ = 1;
			}
			break;
		case 5:
			// Extra execute state.
			break;
		}
	}
}

void Z80::BindToBus(Bus* bus) {
	bus_ = bus;
}

void Z80::DebugDisassemble() {
	std::cout << "[INFO] [z80.cc] Recieved instruction: "
		<< instruction_labels_[instruction_cache_] << std::endl;
}

void Z80::NotImplemented() {
	std::cout << "[FATL] [z80.cc] Instruction not implemented!" << std::endl;
	exit(-1);
}

void Z80::UnexpectedState() {
	std::cout << "[FATL] [z80.cc] Unexpected/Impossible state, or "
		<< "Instruction not implemented!" << std::endl;
	exit(-1);
}