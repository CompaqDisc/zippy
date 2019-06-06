#ifndef ZIPPY_DEVICE_Z80_H_
#define ZIPPY_DEVICE_Z80_H_

#include "../bus/bus.h"
#include "device.h"

#include <stdint.h>
#include <vector>

// Z80 Flags
#define FLAG_CARRY		1
#define FLAG_SUBTRACT	2
#define FLAG_PARITY		4
#define FLAG_OVERFLOW	4
#define FLAG_F3			8
#define FLAG_HALF_CARRY	16
#define FLAG_F5			32
#define FLAG_ZERO		64
#define FLAG_SIGN		128

#define NOP		0x00
#define HALT	0x76

class Z80: public IDevice {
public:
	void Reset();
	void Clock();
	void BindToBus(Bus* bus);
	Z80();
private:
	void DebugDisassemble();
	void NotImplemented();
	void UnexpectedState();
	Bus* bus_;

	const char* instruction_labels_[256] = {
	"NOP         ", "LD BC, XX   ", "LD (BC), A  ", "INC BC      ", // 0x00-0x03
	"INC B       ", "DEC B       ", "LD B, X     ", "RLCA        ", // 0x04-0x07
	"EX AF, AF'  ", "ADD HL, BC  ", "LD A, (BC)  ", "DEC BC      ", // 0x08-0x0B
	"INC C       ", "DEC C       ", "LD C, X     ", "RRCA        ", // 0x0C-0x0F
	"DJNZ X      ", "LD DE, XX   ", "LD (DE), A  ", "INC DE      ", // 0x10-0x13
	"INC D       ", "DEC D       ", "LD D, X     ", "RLA         ", // 0x14-0x17
	"JR X        ", "ADD HL, DE  ", "LD A, (DE)  ", "DEC DE      ", // 0x18-0x1B
	"INC E       ", "DEC E       ", "LD E, X     ", "RRA         ", // 0x1C-0x1F
	"            ", "            ", "            ", "            ", // 0x20-0x23
	"            ", "            ", "            ", "            ", // 0x24-0x27
	"            ", "            ", "            ", "            ", // 0x28-0x2B
	"            ", "            ", "            ", "            ", // 0x2C-0x2F
	"            ", "            ", "            ", "            ", // 0x30-0x33
	"            ", "            ", "            ", "            ", // 0x34-0x37
	"            ", "            ", "            ", "            ", // 0x38-0x3B
	"            ", "            ", "LD A, X     ", "            ", // 0x3C-0x3F
	"            ", "            ", "            ", "            ", // 0x40-0x43
	"            ", "            ", "            ", "            ", // 0x44-0x47
	"            ", "            ", "            ", "            ", // 0x48-0x4B
	"            ", "            ", "            ", "            ", // 0x4C-0x4F
	"            ", "            ", "            ", "            ", // 0x50-0x53
	"            ", "            ", "            ", "            ", // 0x54-0x57
	"            ", "            ", "            ", "            ", // 0x58-0x5B
	"            ", "            ", "            ", "            ", // 0x5C-0x5F
	"            ", "            ", "            ", "            ", // 0x60-0x63
	"            ", "            ", "            ", "            ", // 0x64-0x67
	"            ", "            ", "            ", "            ", // 0x68-0x6B
	"            ", "            ", "            ", "            ", // 0x6C-0x6F
	"            ", "            ", "            ", "            ", // 0x70-0x73
	"            ", "            ", "            ", "            ", // 0x74-0x77
	"            ", "            ", "            ", "            ", // 0x78-0x7B
	"            ", "            ", "            ", "            ", // 0x7C-0x7F
	"            ", "            ", "            ", "            ", // 0x80-0x83
	"            ", "            ", "            ", "            ", // 0x84-0x87
	"            ", "            ", "            ", "            ", // 0x88-0x8B
	"            ", "            ", "            ", "            ", // 0x8C-0x8F
	"            ", "            ", "            ", "            ", // 0x90-0x93
	"            ", "            ", "            ", "            ", // 0x94-0x97
	"            ", "            ", "            ", "            ", // 0x98-0x9B
	"            ", "            ", "            ", "            ", // 0x9C-0x9F
	"            ", "            ", "            ", "            ", // 0xA0-0xA3
	"            ", "            ", "            ", "            ", // 0xA4-0xA7
	"            ", "            ", "            ", "            ", // 0xA8-0xAB
	"            ", "            ", "            ", "            ", // 0xAC-0xAF
	"            ", "            ", "            ", "            ", // 0xB0-0xB3
	"            ", "            ", "            ", "            ", // 0xB4-0xB7
	"            ", "            ", "            ", "            ", // 0xB8-0xBB
	"            ", "            ", "            ", "            ", // 0xBC-0xBF
	"            ", "            ", "            ", "            ", // 0xC0-0xC3
	"            ", "            ", "            ", "            ", // 0xC4-0xC7
	"            ", "            ", "            ", "CB PREFIX   ", // 0xC8-0xCB
	"            ", "            ", "            ", "RST 08H     ", // 0xCC-0xCF
	"            ", "            ", "            ", "            ", // 0xD0-0xD3
	"            ", "            ", "            ", "            ", // 0xD4-0xD7
	"            ", "            ", "            ", "            ", // 0xD8-0xDB
	"            ", "DD PREFIX   ", "SBC A, X    ", "RST 18H     ", // 0xDC-0xDF
	"            ", "            ", "            ", "            ", // 0xE0-0xE3
	"            ", "            ", "            ", "            ", // 0xE4-0xE7
	"            ", "            ", "            ", "            ", // 0xE8-0xEB
	"            ", "ED PREFIX   ", "XOR X       ", "RST 28H     ", // 0xEC-0xEF
	"            ", "            ", "            ", "            ", // 0xF0-0xF3
	"            ", "            ", "            ", "            ", // 0xF4-0xF7
	"RET M       ", "LD SP, HL   ", "JP M, XX    ", "EI          ", // 0xF8-0xFB
	"CALL M, XX  ", "FD PREFIX   ", "CP X        ", "RST 38H     "};// 0xFC-0xFF

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
	uint16_t sp_;

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
	uint8_t instruction_cache_;
	// Operand Cache
	uint8_t operand_cache_;

	/*
		Tables
	*/
};

#endif	// ZIPPY_DEVICE_Z80_H_
