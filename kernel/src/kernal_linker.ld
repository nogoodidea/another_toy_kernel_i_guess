
OUTPUT_FORMAT("elf64-littleriscv")

_KERNEL_BASE_ = 0x80000000;

SECTIONS {
  /* offset for start of binary */
 
  /* the like start code */
  .text.start (_KERNEL_BASE_) : {
    *( .init );
  }

  .text : ALIGN(CONSTANT(MAXPAGESIZE)) {
    _TEXT_START_ = .;
      *(.text)
    _TEXT_END_ = .;
  }

  .data : ALIGN(CONSTANT(MAXPAGESIZE)) {
    _DATA_START_ = .;
      *(.data)
      _PAGE_SIZE_ = CONSTANT(COMMONPAGESIZE);
    _DATA_END_ = .;
  }

  .bss : ALIGN(CONSTANT(MAXPAGESIZE)) {
    _BSS_START_ = .;
     *(.bss)
    
    . += ALIGN(CONSTANT(COMMONPAGESIZE));/* so like we need a stack */
    _INT_STACK_TOP_ = .;
    
    . += 4096;

    _GLOBAL_POINTER_ = .;
    _BSS_END_ = .;
  }
}
