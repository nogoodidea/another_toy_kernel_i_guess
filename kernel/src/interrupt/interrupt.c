#include "../common/types.h"
#include "../panic.h"
#include "../io/kprint.h"


#include "interrupt.h"

#define INTERRUPT_MASK 0x9000000000000000 // last bit is a one

void default_interrupt(u64 status){
  kprintf("INTERRUPT:%u",status);
  // wecome to my hell
  // shifts the return address past the interrupt cause
  asm volatile(
      "csrrw  t0,sepc,x0\n"
      "addi   t0,t0,4\n"
      "csrrw  x0,sepc,t0\n"
      :::"t0"); 
}

void default_exception(u64 status){
  kprintf("EXCEPTION:%u",status);
}

static interruptHandler EXCEPTION_JMP_TABLE[64]  = {0};
static interruptHandler INTERRUPT_JMP_TABLE[64]  = {0};

// asm in hook
extern void _interrupt_setup();

void exception_set_handler(interruptHandler func,u8 index){
    EXCEPTION_JMP_TABLE[index]  = func;
}

void interrupt_set_handler(interruptHandler func,u8 index){
    INTERRUPT_JMP_TABLE[index]  = func;
}

void interrupt_setup(){
  for(usize i = 0;i<64;i+=1){
      EXCEPTION_JMP_TABLE[i] = &default_interrupt;
      INTERRUPT_JMP_TABLE[i] = &default_exception;
  }
  _interrupt_setup();
}

void interrupt_handler(usize status){
  kprintf("status: %lx\r\n%lx\r\n",status,(~INTERRUPT_MASK) & status);
  kprint_flush();
  //TODO what ever task switching bullshit
  if(INTERRUPT_MASK & status){
    // interrupt
    interruptHandler func = INTERRUPT_JMP_TABLE[ (~INTERRUPT_MASK) & status ];
    func(status);
  }else{
    // exception
    interruptHandler func = EXCEPTION_JMP_TABLE[ (~INTERRUPT_MASK) & status ];
    func(status);
  }
}
