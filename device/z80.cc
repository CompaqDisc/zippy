#include <iostream>
#include <stdint.h>
#include "z80.h"

Z80::Z80() {}

void Z80::BindToBus(Bus* bus) {
	bus_ = bus;
}

void Z80::Reset() {
	pc_ = 0x0000;
	i_ = 0x00;
	r_ = 0x00;

	interrupts_enabled_ = false;
	interrupt_mode_ = 0;

	machine_cycle_ = 1;
	t_state_ = 1;

	std::cout << "[INFO] [z80.cc] Reset Complete" << std::endl;
}

/*
	Single-cycle step of the processor.
*/
void Z80::Clock() {
	std::cout << "[INFO] [z80.cc] Clock" << std::endl;

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
			data_ = bus_->Data();
			bus_->PushReadRequest(false);
			bus_->PushMemoryRequest(false);
			std::cout << "[INFO] [z80.cc] T3" << std::endl;
			break;
		}
	}
}