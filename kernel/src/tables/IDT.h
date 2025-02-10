
#include <stdbool.h>

#include "common/types.h"


typedef struct __attribute__((packed,unused)) idt_entry_s {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  ist;
    uint8_t  type_attributes;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;
} idt_entry_t; // 128

enum idt_gate_type_e{
  Interrupt = 0x6, // 110
  Trap = 0x7,      // 111
};


void idt_init_table();

//function blocks
//

void idt_set_handler(u8 i,void (*handler)(void*));

void idt_set_privlage(u8 i,u8 privlage);

void idt_set_present(u8 i,bool set);

void idt_set_gate_type(u8 i,enum idt_gate_type_e gate);

// idt
bool idt_load();

void interupt_enable();

void interupt_disable();

void interupt_set_flag(u32 flag);

void interupt_restore_flag(u32 flag);
