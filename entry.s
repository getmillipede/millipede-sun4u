! main OBP entry point
	
	.globl entry
entry:

! set %g4 to the start of the rodata segent to satisfy GCC (0)
	mov %g0, %g4

! save the OBP entry point
	set prom_entry, %g1
	stx %o4, [%g1]

! call the main C entry point
	ba main
	nop
