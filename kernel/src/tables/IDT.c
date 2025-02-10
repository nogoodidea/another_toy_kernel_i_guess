
#include "IDT.h"

#include "common/types.h"
#include "common/addr.h"

#include "panic.h"

// the table
__attribute__( (section(".tables")) ) static volatile struct idt_entry_s IDT[256];


void idt_init_missing(volatile struct idt_entry_s *idt){
  idt->offset_low = 0;
  idt->selector = 0x10; // hardcoded to kern code segment (segment 2)
  idt->ist = 0;
  idt->type_attributes = 0;
  idt->offset_mid = 0;
  idt->offset_high = 0;
}

void idt_init_table(){
  for(usize i=0;i<64;i+=1){
    idt_init_missing(IDT+i);
  }
}

void idt_set_handler(u8 i,void (*handler)(void*)){
  volatile struct idt_entry_s *idt = IDT + i;

  idt->offset_low = ((u64) handler) & 0xFFFF;
  idt->offset_mid = ((u64) handler >> 16) & 0xFFFF;
  idt->offset_high = ((u64) handler >> 32) & 0xFFFFFFFF;
}

void idt_set_privlage(u8 i,u8 privlage){
  volatile struct idt_entry_s *idt = IDT + i;
  // hard coded kernal code segmetn selector
  // segment 2 gdt and the privlage bits
  idt->selector = 0x16|(privlage & 0x3);
}

void idt_set_present(u8 i,bool set){
  volatile struct idt_entry_s *idt = IDT + i;
  
  idt->type_attributes = ((u16) set << 15)| (idt->type_attributes & (!0x80));
}

void idt_set_gate_type(u8 i,enum idt_gate_type_e gate){
  volatile struct idt_entry_s *idt = IDT + i;
  
  idt->type_attributes = gate |(idt->type_attributes & (!0x03)); 
}

/// UNSAFE
/// bool idt_load()
bool idt_load(){
  struct  {
    u16 size;
    u64 offset;
  } __attribute__((packed)) IDTR = { sizeof(IDT) -1 , (u64) IDT};
  __asm__ volatile ("LIDT %0": : "m"(IDTR));
  return true;
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
      : "=m" (flag) :: "cc");
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
