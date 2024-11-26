
#include <stdbool.h>

#include "common/types.h"


struct __attribute__((packed)) idt_s {
    u16 offset_low;
    u16 seg;
    u8 IST :2; // 0 to 2
    u8 :6;
    u8 gate_type :2;
    u8 :1;
    u8 DPL :2;
    bool present;
    u16 offset_mid;
    u32 offset_high;
    u32 :32;
};


void idt_init_table();

//function blocks
//

void idt_set_handler(u8 i,void (*handler)(void*));

void idt_set_privlage(u8 i,u8 privlage);

void idt_set_present(u8 i,bool set);

// idt
void idt_load();

void interupt_enable();

void interupt_disable();

void interupt_set_flag(u32 flag);

void interupt_restore_flag(u32 flag);
