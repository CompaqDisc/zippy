#ifndef ZIPPY_CHIP_Z80_H_
#define ZIPPY_CHIP_Z80_H_

#include <stdint.h>

class Z80 {
public:
	const bool halt();
	void reset();
	void clock();
	Z80();
private:
	union reg16 {
		uint16_t r;

		struct {
			uint8_t l;
			uint8_t h;
		};
	};

	/*
		The Z80 registers
			Main registers
				A	Flags		AF (accumulator and flags)
				B	C			BC
				D	E			DE
				H	L			HL (indirect address)
			Alternate registers
				A'	Flags'		AF' (accumulator and flags)
				B'	C'			BC'
				D' 	E'			DE'
				H' 	L'			HL' (indirect address)
			Index registers
				IX				Index X
				IY				Index Y
				SP				Stack Pointer
			Other registers
					I			Interrupt vector
					R			Refresh counter
			Program counter
				PC				Program Counter
			Status register
					SZ-H-PNC	Flags 
	*/

	/*
		Internal registers.
	*/
	reg16 af;
	reg16 bc;
	reg16 de;
	reg16 hl;
	
	reg16 af_prime;
	reg16 bc_prime;
	reg16 de_prime;
	reg16 hl_prime;

	reg16 ix;
	reg16 iy;
	reg16 sp;

	uint8_t i;
	uint8_t r;

	uint16_t pc;

	/*
		Internal states/signals
	*/
	// Interrupts enabled?
	bool ie;
	// Interrupt mode
	uint8_t im;
	// Current M-Cycle
	uint8_t m_cycle;
	// Current T_State
	uint8_t t_state;

	/*
		Exposed I/O Lines
		(Going from pin 1 to pin 40, roughly.)
	*/
	// Address bus, output.
	uint16_t _address;
	// Data bus.
	uint8_t _data;
	
	/*
		Name: /INT,
		Pin#: 16,
		Direction: Input,
		Description: Interrupt
	*/
	bool _int;
	// Non-Maskable Interrupt, input.
	bool _nmi;
	// Halt, output.
	bool _halt;
	// Memory Request, output.
	bool _mreq;
	// I/O Request, output.
	bool _iorq;
	// Read line, output.
	bool _rd;
	// Write line, output.
	bool _wr;
	// Bus Acknowledge
	bool _busack;
	// Wait, input.
	bool _wait;
	// Bus Request, input.
	bool _busrq;
	// M1, output.
	bool _m1;
	// Refresh, output.
	bool _rfsh;
};

#endif