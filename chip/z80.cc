#include <iostream>
#include "z80.h"

Z80::Z80() {
	this->reset();
}

void Z80::reset() {
	pc = 0x0000;
	im = 0;
	ie = true;
	i = 0x00;
	r = 0x00;
	halted = false;
	wait = false;
	m_cycle = 1;
	t_state = 1;
	std::cout << "[INFO] [z80.cc] Reset" << std::endl;
}

/*
	Single-cycle step of the processor.
*/
void Z80::clock() {
	std::cout << "[INFO] [z80.cc] Clock" << std::endl;
	static uint8_t instruction;
	static uint8_t prefix;
	static uint8_t data1;
	static uint8_t data2;

	switch (m_cycle) {
	case 1:
		// M1 - Opcode Fetch
		std::cout << "[INFO] [z80.cc] M1" << std::endl;
		switch (t_state) {
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
			
			// /M1 goes active.
			m1 = true;
			// The program counter is placed on the address bus.
			address = pc;
			// /MREQ goes active.
			mreq = true;
			// /RD also goes active.
			rd = true;

			// Advance to next t-state.
			t_state = 2;
			break;
		case 2:
			/*
				T2 of opcode fetch.

				Per documentation and Figure 5 of Architectural Overview:
				|*	/WAIT is sampled. Repeat T2 while active.
			*/

			if (!wait) {
				// If not waiting, advance to next t-state.
				t_state = 3;
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

			break;
		}
	}
}