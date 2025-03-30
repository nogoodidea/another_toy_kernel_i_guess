
KERN_DIR := $(abspath kernel/)
KERN_ELF := $(abspath kernel/bin/yamk.elf)
LIMINE_DIR := $(abspath submodules/limine/)
OUT_DIR := $(abspath bin/)

# QEMU
QEMU := qemu-system-riscv64
QEMU_OPTIONS := -bios none -machine virt -kernel $(KERN_ELF)

GDB := riscv64-none-elf-gdb

kernal:
	$(MAKE) -C $(KERN_DIR) 

clean:
	$(MAKE) -C $(KERN_DIR) clean
	rm -rf $(OUT_DIR)

qemu: 
	$(QEMU) $(QEMU_OPTIONS)

qemu-debug:
	$(QEMU) -no-reboot -S -no-shutdown -gdb tcp::1234 $(QEMU_OPTIONS)

gdb:
	$(GDB) $(KERN_ELF) -ex 'set disassemble-next-line on' -ex 'target remote localhost:1234'

ramdisk:
	## TODO
	## RAMDISK GEN


