.data



.global interrupt_handler
// jump table 
.type _interrupt_handler @function
.global _interrupt_handler 
/// the handler for our interrupt system ... needs a rewrite
_interrupt_handler:
      csrrw sp, mscratch, sp
      addi sp, sp, -144
      sd    a0, 0(sp)
      sd    a1, 8(sp)
      sd    a2, 16(sp)
      sd    a3, 24(sp)
      sd    a4, 32(sp)
      sd    a5, 40(sp)
      sd    a6, 48(sp)
      sd    a7, 56(sp)
      sd    t0, 64(sp)
      sd    t1, 72(sp)
      sd    t2, 80(sp)
      sd    t3, 88(sp)
      sd    t4, 96(sp)
      sd    t5, 104(sp)
      sd    t6, 112(sp)
      sd    gp, 120(sp)
      sd    tp, 128(sp)
      sd    ra, 136(sp)
      la    gp, _GLOBAL_POINTER_
      
      // so everythings good right?
      // ok now get the interrupt number for the handler
      csrrw a0,mcause,zero
      jal   interrupt_handler 

      addi  sp, sp, 144
      ld    a0, 0(sp)
      ld    a1, 8(sp)
      ld    a2, 16(sp)
      ld    a3, 24(sp)
      ld    a4, 32(sp)
      ld    a5, 40(sp)
      ld    a6, 48(sp)
      ld    a7, 56(sp)
      ld    t0, 64(sp)
      ld    t1, 72(sp)
      ld    t2, 80(sp)
      ld    t3, 88(sp)
      ld    t4, 96(sp)
      ld    t5, 104(sp)
      ld    t6, 112(sp)
      ld    gp, 120(sp)
      ld    tp, 128(sp)
      ld    ra, 136(sp)

      // swap back
      csrrw sp, mscratch, sp
      mret


.type _interrupt_setup @function
.global _interrupt_setup
/// takes no args but sets up and enables interrupts (dosn't turn on anything tho)
_interrupt_setup:
      la    t0,_interrupt_handler
      li    t1,3 // bit mask
      not   t1,t1
      and   t0,t1,t0
      csrrw x0,mtvec,t0
      // now change to the interrupt stack
      la    t0, _INT_INTERRUPT_STACK_ 
      csrrw x0, mscratch, t0
      jr    ra

.type interrupt_enable_for_real_this_time_ @function
.global interrupt_enable_for_real_this_time_
interrupt_enable_for_real_this_time_:
      // turn them on for real this time
      li    t2,4 // 8 = 1<<2
      csrrs x0,mstatus,t2
      jr    ra // ret :3

.type interrupt_enable @function
.global interrupt_enable
/// takes a0 as the mask of interrupts to enable
interrupt_enable:
      li    t0,0x1
      sll   t0,a0,t0 // user input for any other interrupts to enable
      csrrs x0,mie,t0 
      jr    ra

.type interrupt_enable_all @function
.global interrupt_enable_all
// enables all inerupts
interrupt_enable_all:
      not   t0,x0 // fill the table to MXLEN of ones
      csrrs x0,mie,t0 
      jr    ra

.type interrupt_status @function
.global interrupt_status
// return the interrupt mask
interrupt_status:
      csrrw a0,mie,x0
      jr    ra

interrupt_disable:
      li    t0,0x1
      sll   t0,a0,t0
      csrrc x0,mie,t0
      jr    ra

interrupt_disable_all:
      not   t0,x0 // fill the table to MXLEN of ones
      csrrc x0,mie,t0 
      jr    ra
