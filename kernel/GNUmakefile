## modified from https://wiki.osdev.org/Limine_Bare_Bones#GNUmakefile
## So it's public domain as according to https://wiki.osdev.org/OSDev_Wiki:License

# Nuke built-in rules and variables.
MAKEFLAGS += -rR
.SUFFIXES:

# This is the name that our final executable will have.
# Change as needed.
override OUTPUT := yamk.elf

# Convenience macro to reliably declare user overridable variables.
override USER_VARIABLE = $(if $(filter $(origin $(1)),default undefined),$(eval override $(1) := $(2)))

# User controllable C compiler command.
$(call USER_VARIABLE,KCC,riscv64-none-elf-gcc)

# User controllable linker command.
$(call USER_VARIABLE,KLD,riscv64-none-elf-ld)

# User controllable C flags.
$(call USER_VARIABLE,KCFLAGS,-g -O2 -pipe)

# User controllable C preprocessor flags. We set none by default.
$(call USER_VARIABLE,KCPPFLAGS,)

# User controllable nasm flags.
$(call USER_VARIABLE,KNASMFLAGS,-F dwarf -g)

# User controllable linker flags. We set none by default.
$(call USER_VARIABLE,KLDFLAGS,)

# Internal C flags that should not be changed by the user.

# root of the git repo
$(call USER_VARIABLE,GIT_ROOT, $(shell git rev-parse --show-toplevel))

LINKER_SCRIPT=src/kernal_linker.ld

override KCFLAGS += \
    -Wall \
    -Wextra \
    -ffreestanding \
		-nostartfiles \
		-nostdlib \
		-nodefaultlibs \
    -fno-lto \
    -fno-PIC \
    -mcmodel=medany \
		
# Internal C preprocessor flags that should not be changed by the user.
override KCPPFLAGS := \
    -I src \
    $(KCPPFLAGS) \
    -MMD \
    -MP

# Internal linker flags that should not be changed by the user.
override KLDFLAGS += \
    -nostdlib \
    -static \
		-T $(LINKER_SCRIPT)

# Use "find" to glob all *.c, *.S, and *.asm files in the tree and obtain the
# object and header dependency file names.
override CFILES := $(shell cd src && find -L * -type f -name '*.c' | LC_ALL=C sort)
override ASFILES := $(shell cd src && find -L * -type f -name '*.S' | LC_ALL=C sort)
override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o))
override HEADER_DEPS := $(addprefix obj/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d))

# Default target.
.PHONY: all
all: bin/$(OUTPUT)

# Link rules for the final kernel executable.
bin/$(OUTPUT): GNUmakefile $(LINKER_SCRIPT) $(OBJ)
	mkdir -p "$$(dirname $@)"
	$(KLD) $(OBJ) $(KLDFLAGS) -o $@

# Include header dependencies.
-include $(HEADER_DEPS) 
# Compilation rules for *.c files.
obj/%.c.o: src/%.c GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(KCC) $(KCFLAGS) $(KCPPFLAGS) -c $< -o $@

# Compilation rules for *.S files.
obj/%.S.o: src/%.S GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(KCC) $(KCFLAGS) $(KCPPFLAGS) -c $< -o $@

# Compilation rules for *.asm (nasm) files.
obj/%.asm.o: src/%.asm GNUmakefile
	mkdir -p "$$(dirname $@)"
	nasm $(KNASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf bin obj
