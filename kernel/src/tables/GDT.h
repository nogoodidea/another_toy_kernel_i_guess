#ifndef TABLE_GDT_H
#define TABLE_GDT_H

#include "common/types.h"
#include <stdbool.h>


typedef struct __attribute__((packed)) {
  u16 limit_low;
  u16 base_low;
  u8 base_mid_0;
  u8 access;
  u8 limit_high :3;
  u8 flags :4;
  u8 base_mid_1;
  u32 base_high;
  u32 :32; // reserved
} gdt_entry_t;

void gdt_init(const void *tts);

bool gdt_load();

#endif // TABLE_GDT_H
