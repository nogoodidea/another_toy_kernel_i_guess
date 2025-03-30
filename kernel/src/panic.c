#include "panic.h"

#include "io/serial.h"
#include "io/kprint.h"
#include "framebuffer.h"

//infine loop of sadness
__attribute__((noreturn)) static void hcf(void) {
  for(;;){
    __asm__ inline ("wfi");
  } 
}

#define UART_ADDR 0x10000000

//NO FUNCTIONS IN HERE CAN PANIC 
// if it does bad things will happen.
__attribute__((noreturn)) void _panic(const char *text,int line,const char *file){
  // flush io buffer
  kprint_flush(); 
  // disable interupts just to be safe
  //interupt_disable();
  //
  serial_int(UART_ADDR); // reinit serial bc we don't know it's state
  kprints_s(UART_ADDR,"\n\rPANIC! "); 
  kprints_s(UART_ADDR,file);
  kprints_s(UART_ADDR,":");
  kprintu_s(UART_ADDR,line,10);
  kprints_s(UART_ADDR,"\n\rmsg: ");
  kprints_s(UART_ADDR,text);

  hcf(); //TODO replace w/ power off
}

