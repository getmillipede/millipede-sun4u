OUTPUT_FORMAT(binary)
ENTRY(entry)

SECTIONS
{
	. = 0x3fe0;
        .main :
	{
		LONG(0x01030107);
		LONG(_end - _start);
		LONG(0);
		LONG(0);
		LONG(0);
		LONG(entry);
		LONG(0);
		LONG(0xffffffff);
		_start = .;
		entry.o(.text)
		*(.text)
		*(.rodata)
		*(.data)
		*(.bss)
		_end = .;
	}
}
