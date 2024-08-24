NC=nasm
CC=i386-elf-gcc

ARGS=-nostdlib -nostdinc++ -nostdinc -ffreestanding -Wall -Wextra -m32 -c
build:
	$(NC) stage1.asm  -f bin -o bin/stage1
	$(NC) stage2.asm  -f elf -o bin/stage2.o
	$(NC) src/idt.asm -f elf -o bin/idt.elf

	$(CC) $(ARGS) kernel.cpp 			-o bin/kernel.o
	$(CC) $(ARGS) src/video/console.cc	-o bin/console.o
	$(CC) $(ARGS) src/video/vga.cc	    -o bin/vga.o
	$(CC) $(ARGS) src/disk/ata.cc		-o bin/ata.o
	$(CC) $(ARGS) src/disk/atapi.cc		-o bin/atapi.o
	$(CC) $(ARGS) src/time/rtc.cc		-o bin/rtc.o
	$(CC) $(ARGS) src/time/pit.cc		-o bin/pit.o
	$(CC) $(ARGS) src/idt.cc			-o bin/idt.o

	$(CC) -T linker.ld -o bin/stage2	\
			 bin/stage2.o bin/kernel.o  \
			 bin/idt.o	bin/idt.elf		\
			 bin/ata.o  bin/console.o   \
			 bin/atapi.o bin/pit.o      \
			 bin/rtc.o  				\
			 -nostdlib -O0

	cat bin/stage1 bin/stage2 > bin/bootable
run: build
	qemu-system-i386 -drive file=bin/bootable,if=floppy,format=raw -m 512M

