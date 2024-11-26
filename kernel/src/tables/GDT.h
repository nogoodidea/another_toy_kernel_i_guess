#ifndef TABLE_GDT_H
#define TABLE_GDT_H

#include "common/types.h"
#include <stdbool.h>

struct __attribute__((packed)) gdt_segment_access_s{
  bool accessed:1;
  bool rw:1;
  bool DC:1;
  bool code:1;
  bool descriptor:1; // union flag go brrr
  u8 DPL:2;
  bool present:1;
};

struct __attribute__((packed)) gdt_segment_access_sys_s{
  u8 type :4;
  bool descriptor :1; // same on both, use to check what union to use
  u8 DPL :2;
  bool present;
};


union __attribute__((packed)) gdt_flags_t{
  struct gdt_segment_access_s seg;
  struct gdt_segment_access_sys_s sys;
};

typedef struct __attribute__((packed)) {
  u16 limit_low:16;
  u32 base_low:24;
  union gdt_flags_t flags;
  u8 limit_high:3;
  char :1;
  bool long_mode :1;
  bool size :1;
  bool granularity :1;
  u64 base_high:40;
  u32 :32;
} gdt_entry_t;

void init_gdt(const void *tts);

#endif // TABLE_GDT_H
