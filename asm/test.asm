	org 0000h
main:
	; Inversion patterns, ensure byte order when exploring memory.
	ld a,0xAA
	ld bc,0x55AA
	; Loop 256 times.
	ld de,0x0100
loop:
	dec de
	jp nz,loop
end:
	; Make sure emulator captures halt.
	; TODO: Implement interrupts instead of stopping emulation.
	halt