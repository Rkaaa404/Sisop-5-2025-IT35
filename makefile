SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

prepare:
	mkdir -p $(BIN_DIR)
	dd if=/dev/zero of=$(BIN_DIR)/floppy.img bs=512 count=2880

bootloader:
	nasm -f bin $(SRC_DIR)/bootloader.asm -o $(BIN_DIR)/bootloader.bin
	
stdlib:
	bcc -ansi -I$(INCLUDE_DIR) -c $(SRC_DIR)/std_lib.c -o $(BIN_DIR)/std_lib.o

shell:
	bcc -ansi -I$(INCLUDE_DIR) -c $(SRC_DIR)/shell.c -o $(BIN_DIR)/shell.o

kernel:
	nasm -f as86 $(SRC_DIR)/kernel.asm -o $(BIN_DIR)/kernel-asm.o
	bcc -ansi -I$(INCLUDE_DIR) -c $(SRC_DIR)/kernel.c -o $(BIN_DIR)/kernel.o
	ld86 -o $(BIN_DIR)/kernel.bin -d $(BIN_DIR)/kernel.o $(BIN_DIR)/kernel-asm.o

link:
	dd if=$(BIN_DIR)/bootloader.bin of=$(BIN_DIR)/floppy.img bs=512 count=1 conv=notrunc
	dd if=$(BIN_DIR)/kernel.bin of=$(BIN_DIR)/floppy.img bs=512 seek=1 conv=notrunc

clean:
	# Clean up all object files, binaries, and floppy image
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/bootloader.bin $(BIN_DIR)/kernel.bin $(BIN_DIR)/floppy.img

build: prepare bootloader stdlib shell kernel link