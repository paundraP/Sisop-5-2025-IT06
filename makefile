AS = nasm
CC = gcc
LD = ld

CFLAGS = -ffreestanding -m32 -Iinclude -Wall -Wextra
LDFLAGS = -m elf_i386

BOOTLOADER_SRC = src/bootloader.asm
KERNEL_ASM_SRC = src/kernel.asm
KERNEL_C_SRC = src/kernel.c
SHELL_C_SRC = src/shell.c
STDLIB_C_SRC = src/std_lib.c

BUILD_DIR = build
BIN_DIR = bin
KERNEL_BIN = $(BIN_DIR)/kernel.bin
OS_IMAGE = $(BIN_DIR)/Eorzea

build: prepare bootloader stdlib shell kernel link

prepare:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

bootloader: $(BOOTLOADER_SRC)
	$(AS) -f bin $(BOOTLOADER_SRC) -o $(BUILD_DIR)/bootloader.o

stdlib: $(STDLIB_C_SRC)
	$(CC) $(CFLAGS) -c $(STDLIB_C_SRC) -o $(BUILD_DIR)/std_lib.o

shell: $(SHELL_C_SRC)
	$(CC) $(CFLAGS) -c $(SHELL_C_SRC) -o $(BUILD_DIR)/shell.o

kernel: $(KERNEL_C_SRC) $(KERNEL_ASM_SRC)
	$(AS) -f elf $(KERNEL_ASM_SRC) -o $(BUILD_DIR)/kernel_asm.o
	$(CC) $(CFLAGS) -c $(KERNEL_C_SRC) -o $(BUILD_DIR)/kernel.o

link:
	$(LD) $(LDFLAGS) -Ttext 0x1000 -o $(KERNEL_BIN) \
		$(BUILD_DIR)/kernel_asm.o \
		$(BUILD_DIR)/kernel.o \
		$(BUILD_DIR)/shell.o \
		$(BUILD_DIR)/std_lib.o \
		--oformat binary
	cat $(BUILD_DIR)/bootloader.o $(KERNEL_BIN) > $(OS_IMAGE)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: prepare bootloader stdlib shell kernel link build clean
