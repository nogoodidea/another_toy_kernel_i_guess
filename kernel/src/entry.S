
.section .init

.option norvc

.type _start @function
.global _start

// start of kern
_start:
  .cfi_startproc

.option push
.option norelax
  la gp, _GLOBAL_POINTER_
.option pop
  
  // reset satp
  csrw satp, zero
  
  // stack
  la sp, _INT_INTERRUPT_STACK_

  // sets args up
  la t5, _BSS_START_
  la t6, _BSS_END_

bss_clear: // zeros the BSS
  sd zero, (t5)
  addi t5, t5, 8
  blt t5, t6, bss_clear

  
  la t0, kmain
  csrw mepc, t0

  tail kmain
  
  .cfi_endproc

.end 
