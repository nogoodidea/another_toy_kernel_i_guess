
#include "types.h"

u8 inb(u16 port){
  u8 out;
  asm volatile (
      "inb %w1, %b0"
      : [out] "=a" (out)
      : [port] "dN" (port)
      : "memory");
  return out;
}
u16 inw(u16 port){
  u16 out;
  asm volatile (
      "inw %w1, %0"
      : [out] "=a" (out)
      : [port] "dN" (port)
      : "memory");
  return out;
}

u32 inl(u16 port){
  u32 out;
  asm volatile (
      "inl %w1, %0"
      : [out] "=a" (out)
      : [port] "dN" (port)
      : "memory");
  return out;
}

// input
void outb(u16 port, u8 in){
  asm volatile (
      "outb %b0,%w1"
      :/* NO OUTPUTS KYS*/
      : [in] "a" (in) 
      ,[port] "dN" (port)
      );
}

void outw(u16 port, u16 in){
  asm volatile (
      "outb %b0,%w1"
      :/* NO OUTPUTS KYS*/
      : [in] "a" (in) 
      ,[port] "dN" (port)
      );
}

void outl(u16 port, u32 in){
  asm volatile (
      "outb %b0,%w1"
      :/* NO OUTPUTS KYS*/
      : [in] "a" (in) 
      ,[port] "dN" (port)
      );
}
