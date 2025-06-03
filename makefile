SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

.PHONY: all clean build prepare bootloader stdlib shell kernel link

all: build

prepare:
	mkdir -p $(BIN_DIR)
	dd if=/dev/zero of=$(BIN_DIR)/floppy.img bs=512 count=2880

bootloader: $(SRC_DIR)/bootloader.asm
	nasm -f bin $(SRC_DIR)/bootloader.asm -o $(BIN_DIR)/bootloader.bin

stdlib: $(SRC_DIR)/std_lib.c $(INCLUDE_DIR)/std_lib.h $(INCLUDE_DIR)/std_type.h
	bcc -ansi -I$(INCLUDE_DIR) -c $(SRC_DIR)/std_lib.c -o $(BIN_DIR)/std_lib.o

shell: $(SRC_DIR)/shell.c $(INCLUDE_DIR)/shell.h $(INCLUDE_DIR)/kernel.h $(INCLUDE_DIR)/std_lib.h $(INCLUDE_DIR)/std_type.h
	bcc -ansi -I$(INCLUDE_DIR) -c $(SRC_DIR)/shell.c -o $(BIN_DIR)/shell.o

kernel: $(SRC_DIR)/kernel.asm $(SRC_DIR)/kernel.c $(INCLUDE_DIR)/kernel.h $(INCLUDE_DIR)/shell.h $(BIN_DIR)/shell.o $(BIN_DIR)/std_lib.o
	nasm -f as86 $(SRC_DIR)/kernel.asm -o $(BIN_DIR)/kernel-asm.o
	bcc -ansi -I$(INCLUDE_DIR) -c $(SRC_DIR)/kernel.c -o $(BIN_DIR)/kernel.o
	# Link kernel.o, kernel-asm.o, shell.o, and std_lib.o together
	# This was the main correction needed for linking all parts of the kernel.
	ld86 -o $(BIN_DIR)/kernel.bin -d $(BIN_DIR)/kernel.o $(BIN_DIR)/kernel-asm.o $(BIN_DIR)/shell.o $(BIN_DIR)/std_lib.o

link: $(BIN_DIR)/bootloader.bin $(BIN_DIR)/kernel.bin $(BIN_DIR)/floppy.img
	dd if=$(BIN_DIR)/bootloader.bin of=$(BIN_DIR)/floppy.img bs=512 count=1 conv=notrunc
	dd if=$(BIN_DIR)/kernel.bin of=$(BIN_DIR)/floppy.img bs=512 seek=1 conv=notrunc

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.bin $(BIN_DIR)/floppy.img

build: prepare bootloader stdlib shell kernel link