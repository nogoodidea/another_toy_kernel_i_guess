/* we want a elf */
OUTPUT_FORMAT(elf64-x86-64)

/* entry point */
ENTRY(kmain)


/* program headers */
PHDRS{
  requests PT_LOAD;
  text PT_LOAD;
  rodata PT_LOAD;
  data PT_LOAD;
}

SECTIONS{
    /* higher half */
    . = 0xffffffff80000000;
    /*requests for limine*/
    .requests : ALIGN(CONSTANT(MAXPAGESIZE)){
      KEEP(*(.requests_start_marker))
      KEEP(*(.requests))
      KEEP(*(.requests_end_marker))
    } :requests

    /* space for static tables */
    .tables : ALIGN(CONSTANT(MAXPAGESIZE)){
      *(.tables .tables.*)
    }

    .text : ALIGN(CONSTANT(MAXPAGESIZE)){
      *(.text .text.*)
    } :text

    .rodata : ALIGN(CONSTANT(MAXPAGESIZE)){
        *(.rodata .rodata.*)
    } :rodata

    .data : ALIGN(CONSTANT(MAXPAGESIZE)){
        *(.data .data.*)
    } :data

    /* NOTE: .bss needs to be the last thing mapped to :data, otherwise lots of */
    /* above this. */
    .bss : ALIGN(CONSTANT(MAXPAGESIZE)){
        *(.bss .bss.*)
        *(COMMON)
    } :data

    /DISCARD/ : {
        *(.eh_frame*)
        *(.note .note.*)
    }
 }


