#include "panic.h"

#include "io/serial.h"
#include "io/kprint.h"
#include "framebuffer.h"

//infine loop of sadness
__attribute__((noreturn)) static void hcf(void) {
  for(;;){
    __asm__ inline ("hlt");
  } 
}

#define COM1 0x3F8

//NO FUNCTIONS IN HERE CAN PANIC 
// if it does bad things will happen.
__attribute__((noreturn)) void _panic(const char *text,int line,const char *file){
  serial_int(COM1); // reinit serial bc we don't know it's state
  kprints_s(COM1,"PANIC! "); 
  kprints_s(COM1,file);
  kprints_s(COM1,":");
  kprintu_s(COM1,line,10);
  kprints_s(COM1,"\nmsg: ");
  kprints_s(COM1,text);

  hcf();
}

