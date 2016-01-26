NAME=bootblocks.bin
SRC=main.c entry.s prom.c util.c
OBJ2=$(SRC:.c=.o)
OBJ=$(OBJ2:.s=.o)
CFLAGS=-Wall -Werror -mcpu=ultrasparc -m64 -fno-common -ffreestanding -nostdlib -nostdinc -fno-omit-frame-pointer -O0 -fno-stack-protector -fno-builtin -fno-use-linker-plugin -mno-app-regs
LDFLAGS=-nostdlib -nodefaultlibs -nostdinc
LDSCRIPT=conf/ld.scpt

LD=/usr/local/cross/sun4u/bin/sparc64-elf-ld
CC=/usr/local/cross/sun4u/bin/sparc64-elf-gcc
AS=/usr/local/cross/sun4u/bin/sparc64-elf-as
RM=rm -fr
DD=/bin/dd
MKISOFS=/usr/local/bin/mkisofs
QEMU=/usr/local/bin/qemu-system-sparc64

$(NAME): $(OBJ)
	$(LD) $(LDFLAGS) -T $(LDSCRIPT) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(NAME) $(OBJ)

re: clean all

iso:
	$(DD) if=/dev/zero of=bootblock.bin bs=8192 count=1
	$(DD) if=bootblocks.bin of=bootblock.bin bs=512 seek=1 conv=notrunc
	$(MKISOFS) -o cd.iso -G bootblock.bin .

emu:    iso
	$(QEMU) -cdrom cd.iso
