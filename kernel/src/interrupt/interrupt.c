#include "../common/types.h"
#include "../panic.h"
#include "../io/kprint.h"
#include "../driver/isa.h"


#include "interrupt.h"
#include "interrupt_code_map.h"


#define INTERRUPT_MASK 0x9000000000000000 // last bit is a one
#define INTERRIPT_MAX 64

usize default_interrupt(u64 status, usize epc){
  kprintf("INTERRUPT: %s\n\r",interrupt_code_map(status));
  return epc;
}

usize default_exception(u64 status, usize epc){
  kprintf("EXCEPTION: %s\n\r",exception_code_map(status));
  epc += isa_get_instruction_len((void *) epc);
  //TODO hey so remember it is a exception and like bad to continue
  PANIC("hey look an exception");
  return epc; 
}

static interruptHandler EXCEPTION_JMP_TABLE[INTERRIPT_MAX]  = {0};
static interruptHandler INTERRUPT_JMP_TABLE[INTERRIPT_MAX]  = {0};

// asm in hook
extern void _interrupt_setup();

void exception_set_handler(interruptHandler func,u8 index){
    EXCEPTION_JMP_TABLE[index]  = func;
}

void interrupt_set_handler(interruptHandler func,u8 index){
    INTERRUPT_JMP_TABLE[index]  = func;
}

void interrupt_setup(){
  for(usize i = 0;i<INTERRIPT_MAX;i+=1){
      EXCEPTION_JMP_TABLE[i] = &default_interrupt;
      INTERRUPT_JMP_TABLE[i] = &default_exception;
  }
  _interrupt_setup();
}

usize interrupt_handler(u64 status, usize epc){
  kprintf("%lx\r\n",epc);
  //TODO what ever task switching bullshit
  if((INTERRUPT_MASK & status) != 0){ // exceptions don't like need to switch ... do we  even want the task switching here?
    // exceptiion
    interruptHandler func = EXCEPTION_JMP_TABLE[ (~INTERRUPT_MASK) & status ];
    epc = func(status,epc);
  }else{
    // interrupt
    interruptHandler func = INTERRUPT_JMP_TABLE[ (~INTERRUPT_MASK) & status ];
    epc = func(status,epc);
  }
    // if we are like here we assume we want to keep going (CHANGE ME when task switching btw
  return epc;

}
