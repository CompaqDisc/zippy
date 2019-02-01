#ifndef ZIPPY_CHIP_Z80_H_
#define ZIPPY_CHIP_Z80_H_

#include <stdint.h>

class Z80 {
public:
	bool halted;

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

	bool ie;
	bool m1;
	bool rd;
	bool wr;
	bool mreq;
	bool rfsh;
	bool wait;

	uint8_t im;
	uint8_t m_cycle;
	uint8_t t_state;

	uint16_t address;
	uint8_t data;
};

#endif