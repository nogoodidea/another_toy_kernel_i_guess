
#include "IDT.h"

// 
__attribute__( (section(".tables")) ) static volatile struct idt_s IDT[64];


void idt_init_missing(volatile struct idt_s *idt){
  idt->offset_low = 0;
  idt->seg = 0;
  idt->IST = 0;
  idt->gate_type = 0;
  idt->DPL = 0;
  idt->present = 0;
  idt->offset_mid = 0;
  idt->offset_high = 0;
}

void idt_init_table(){
  for(usize i=0;i<64;i+=1){
    idt_init_missing(IDT+i);
  }
}

void idt_set_handler(u8 i,void (*handler)(void*)){
  volatile struct idt_s *idt = IDT + i;

  idt->offset_low = ((u64) handler) & 0xFFFF;
  idt->offset_mid = ((u64) handler >> 16) & 0xFFFF;
  idt->offset_high = ((u64) handler >> 32) & 0xFFFFFFFF;
}

void idt_set_privlage(u8 i,u8 privlage){
  volatile struct idt_s *idt = IDT + i;
  // hard coded kernal code segmetn selector
  // segment 2 gdt and the privlage bits
  idt->seg = 0x16|(privlage & 0x3);
}

void idt_set_present(u8 i,bool set){
  volatile struct idt_s *idt = IDT + i;
  
  idt->present = set;
}

/// UNSAFE
/// void idt_load()
void  idt_load(){
  struct __attribute__((packed)) {
    usize offset;
    u16 size;
    }  idtr = { (usize) IDT, sizeof(IDT) };
  __asm__ volatile ("LIDT %0": : "m"(idtr));
}

/// UNSAFE
/// void interupt_enable()
void interupt_enable(){
  __asm__ volatile ("CLI":::"cc");
}

/// UNSAFE
/// void interupt_disable()
void interupt_disable(){
  __asm__ volatile ("STI":::"cc");
}

/// UNSAFE
/// void interupt_flag()
/// needs to be cleared before function return
/// saves regester state
void interupt_set_flag(u32 flag){
  __asm__ volatile (
      "PUSHF\n"
      "POP %0\n"
      "CLI\n"
      : "=m" (flag):);
}

/// UNSAFE
/// void interupt_get_flag() 
/// restore a saved EFLAGS register
void interupt_restore_flag(u32 flag){
  __asm__ volatile (
    "PUSH %0\n"
    "POPF"
    :: "m" (flag):"cc");
}
