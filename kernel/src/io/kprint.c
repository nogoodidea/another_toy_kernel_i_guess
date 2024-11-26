#include "common/types.h"
#include "serial.h"

void kprintf_s(u16 port,const char *format, ...){
  //TODO
   
}

void kprints_s(u16 port,const char * str){
  usize i = 0;
  while(str[i] != '\0'){
    serial_write(port,str[i]);
    i++;
  }
}

void kprintu_s(u16 port,u64 value,u8 base){
  for (;value; value /= base){
    serial_write(port,"0123456789abcdefghijklmnopqrstuvwxyz"[value % base]); 
  }
}

