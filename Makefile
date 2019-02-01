CC=g++
SRCFILES=zippy.cc
SRCFILES+=machine/machine.cc
SRCFILES+=device/z80.cc
SRCFILES+=device/device_rom.cc
SRCFILES+=bus/bus.cc

all: test.rom
	$(CC) -o zippy -O3 -Wall $(SRCFILES) -lpthread -std=c++11

test.rom:
	cd asm && zasm test.asm
	cp asm/test.rom .
