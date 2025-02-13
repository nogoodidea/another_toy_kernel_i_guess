#include "common/types.h"
#include "panic.h"

#define INTERRUPT_HANDLER(f) //TODO

//TODO make your own small asm blocks

void double_fault(void *frame){
  PANIC("DOUBLE FAULT");
}

//INTERRUPT_HANDLER(double_fault);

