# Another toy kernel i guess 

A microkernel made for fun.

## Dependencys
* QEMU riscv64
* gcc riscv64 cross tool chain

## Building
TLDR follow this guide: [osdev.wiki GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) 
* the target tuple is `riscv64-none-elf`.
* alternatively you can use a prebuilt toolchain but i havent used one for building so like ... Here Be Dragons and all that.

Then the install qemu-system-riscv64 from your distros package manager.

`make` and then `make qemu` to test it. 
`make qemu-debug` and `make gdb` may be helpfull for debuging.
## Usage 

TBD

