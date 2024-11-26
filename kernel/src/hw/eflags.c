
#include <stdbool.h>

#include "common/types.h"
#include "hw/eflags.h"

eflags_t get_rflags(){
  eflags_t flags;
  asm("PUSHFQ \n"
      "POP %0" 
      : "=m" (flags)
      :
      :"memory");
  return flags;
}

void put_eflags(eflags_t input){
  asm("PUSH %0\n"
      "POPF"
      :
      : "m" (input)
      : "memory");
}

/*
bool check_cpuid(){
  asm("PUSHFQ \n"
    "PUSHFQ \n"
    "XOR [esp],0x00200000 \n"
    "POPF \n"
    "PUSHFQ"

    :
    :
    : "memory"
    );
}
*/
