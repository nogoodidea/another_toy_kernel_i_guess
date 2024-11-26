
KERN_DIR := $(abspath kernel/)
LIMINE_DIR := $(abspath submodules/limine/)
OUT_DIR := $(abspath bin/)



hhd_image: kernal ramdisk
	rm -f $(OUT_DIR)/image.hdd
	mkdir -p $(OUT_DIR)
	dd if=/dev/zero bs=1M count=0 seek=64 of=$(OUT_DIR)/image.hdd
	sgdisk $(OUT_DIR)/image.hdd -n 1:2048 -t 1:ef00
	$(LIMINE_DIR)/limine bios-install $(OUT_DIR)/image.hdd
	mformat -i $(OUT_DIR)/image.hdd@@1M
	mmd -i $(OUT_DIR)/image.hdd@@1M ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine
	mcopy -i $(OUT_DIR)/image.hdd@@1M $(KERN_DIR)/bin/yamk ::/boot
	mcopy -i $(OUT_DIR)/image.hdd@@1M $(LIMINE_DIR)/limine-bios.sys limine.conf ::/boot/limine
	mcopy -i $(OUT_DIR)/image.hdd@@1M $(LIMINE_DIR)/BOOTX64.EFI ::/EFI/BOOT
	mcopy -i $(OUT_DIR)/image.hdd@@1M $(LIMINE_DIR)/BOOTIA32.EFI ::/EFI/BOOT

qemu:
	qemu-system-x86_64 $(OUT_DIR)/image.hdd -serial stdio &

qemu-gdb:
	qemu-system-x86_64 $(OUT_DIR)/image.hdd -serial stdio -chardev socket,path=/tmp/gdb-socket,server=on,wait=off,id=gdb0 -gdb chardev:gdb0 -S &
	gdb --eval-command "target remote /tmp/gdb-socket"


ramdisk:
	## TODO
	## RAMDISK GEN

kernal:
	$(MAKE) -C $(KERN_DIR) 

limine:
	git submodule update --init --recursive --remote
	$(MAKE) -C $(LIMINE_DIR)


clean:
	rm -rf $(OUT_DIR)
