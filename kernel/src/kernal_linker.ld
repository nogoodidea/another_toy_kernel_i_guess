
OUTPUT_FORMAT("elf64-littleriscv")


MEMORY {
  kernel_init (rwx) : ORIGIN = 0x80000000, LENGTH = 128
  kernel_main (rwx) : ORIGIN = 0x81000000, LENGTH = 64k
}

SECTIONS {
  /* offset for start of binary */
 
  /* the like start code */
  .start : {
    *(.init)
  } > kernel_init

  .text : ALIGN(CONSTANT(MAXPAGESIZE)) {
    _TEXT_START_ = .;
      *(.text)
    _TEXT_END_ = .;
  } > kernel_main

  .data : ALIGN(CONSTANT(MAXPAGESIZE)) {
    _DATA_START_ = .;
      *(.data)
      _PAGE_SIZE_ = CONSTANT(COMMONPAGESIZE);
    _DATA_END_ = .;
  } > kernel_main

  .bss : ALIGN(CONSTANT(MAXPAGESIZE)) {
    _BSS_START_ = .;
     *(.bss)
    
    . += ALIGN(CONSTANT(COMMONPAGESIZE));/* so like we need an interrupt stack*/
    _INT_INTERRUPT_STACK_ = .;
    . +=  4098; /*.5 kibiytes*/
    
    . += ALIGN(CONSTANT(COMMONPAGESIZE));/* so like we need a stack */
    _INT_STACK_TOP_ = .;
    
    . += 8196; /*1 kibibytes*/

    _GLOBAL_POINTER_ = .;
    _BSS_END_ = .;
  } > kernel_main
}
