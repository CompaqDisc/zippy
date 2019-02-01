CC=g++
SRCFILES=zippy.cc
SRCFILES+=machine/machine.cc
SRCFILES+=machine/rc2014.cc
SRCFILES+=peripheral/peripheral.cc
SRCFILES+=peripheral/peripheral_memory_mapped.cc
SRCFILES+=peripheral/peripheral_rom.cc
SRCFILES+=chip/z80.cc

all: test.rom
	$(CC) -o zippy -O3 -Wall $(SRCFILES) -lpthread -std=c++11

test.rom:
	cd asm && zasm test.asm
	cp asm/test.rom .
