
KERN_DIR := $(abspath kernel/)
LIMINE_DIR := $(abspath submodules/limine/)
OUT_DIR := $(abspath bin/)

# QEMU
QEMU := qemu-system-riscv64
QEMU_OPTIONS := -machine virt -kernel $(KERN_DIR)/bin/yamk.elf  -bios none

.PHONY: hdd_image out/image.hdd

qemu: kernal ramdisk
	$(QEMU) $(QEMU_OPTIONS)

qemu-debug:
	$(QEMU) -d int -no-reboot -bios none -no-shutdown -monitor stdio $(QEMU_OPTIONS)

qemu-gdb:
	$(QEMU) -chardev socket,path=/tmp/gdb-socket,server=on,wait=off,id=gdb0 -gdb chardev:gdb0 -S $(QEMU_OPTIONS)&
	gdb $(KERN_DIR)/out/yamk.elf -ex "target remote /tmp/gdb-socket


ramdisk:
	## TODO
	## RAMDISK GEN

kernal:
	$(MAKE) -C $(KERN_DIR) 

clean:
	$(MAKE) -C $(KERN_DIR) clean
	rm -rf $(OUT_DIR)
