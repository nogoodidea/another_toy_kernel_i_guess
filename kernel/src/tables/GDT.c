#include "GDT.h"
#include "io/kprint.h"

  // null segmetn
  // ring 0 - read write
  // ring 0 - code read
  // ring 3 - read write
  // ring 3 - code
  // TTS
  // Reserved (null)
  // Reserved (null)
  //


__attribute((section(".tables"),aligned(0x10))) static volatile gdt_entry_t GDT[8];

void segment_init(volatile gdt_entry_t *gdt,u64 base,u32 limit, bool rw, bool DC, bool code, u8 DPL){
    // limit
    //TODO limit the limit
    gdt->limit_low = limit;
    gdt->limit_high = limit >> 16;
    // base
    gdt->base_low = base;
    gdt->base_high = base >> 23;
    // flags
    // kinda annoying
    gdt->flags.seg.accessed = 1;
    gdt->flags.seg.rw = rw;
    gdt->flags.seg.DC = DC;
    gdt->flags.seg.code = code;
    gdt->flags.seg.descriptor = false;
    gdt->flags.seg.DPL = DPL;
    gdt->flags.seg.present = true;

    gdt->size = true;
    gdt->long_mode = true;
    gdt->granularity = true;
}

void segment_init_system(volatile gdt_entry_t *gdt,u64 base,u32 limit,u8 type, u8 DPL){
    // limit
    //TODO limit the limit
    gdt->limit_low = limit;
    gdt->limit_high = limit >> 16;
    // base
    gdt->base_low = base;
    gdt->base_high = base >> 23;
    // flags
    // kinda annoying
    gdt->flags.sys.type = type;
    gdt->flags.sys.descriptor = true;
    gdt->flags.sys.DPL = DPL;
    gdt->flags.sys.present = true;

    gdt->size = true;
    gdt->long_mode = true;
    gdt->granularity = true;
}

void segment_null(volatile gdt_entry_t *gdt){
    // limit
    gdt->limit_low = 0;
    gdt->limit_high = 0;
    // base
    gdt->base_low = 0;
    gdt->base_high = 0;
    // flags
    // kinda annoying
    gdt->flags.seg.accessed = 0;
    gdt->flags.seg.rw = 0;
    gdt->flags.seg.DC = 0;
    gdt->flags.seg.code = 0;
    gdt->flags.seg.descriptor = 0;
    gdt->flags.seg.DPL = 0;
    gdt->flags.seg.present = 0;

    gdt->size = 0;
    gdt->long_mode = 0;
    gdt->granularity = 0;
}

void init_gdt(const void *tts){
  // NULL DESCRIPTOR 
  segment_null(GDT + 0);

  // kernel mode code segment
  segment_init(GDT + 1,0,0x000fffff,true,false,true,0);

  // kernel mode data segment
  segment_init(GDT + 2,0,0x000fffff,true,false,false,0);
 

  // kernel mode code segment
  segment_init(GDT + 3,0,0x000fffff,true,false,true,3);

  // kernel mode data segment
  segment_init(GDT + 4,0,0x000fffff,true,false,false,3); 
  //TTS
  segment_init_system(GDT + 5,(usize) tts,sizeof((tts)-1),0x2,0);
  
  // make the gdtr
  struct __attribute__((packed)){
    u16 size;
    u64 offset;
  } gdtr = {sizeof(GDT)-1, (u64) GDT};

  // enable it
  asm(
      "LGDT %0\n\t"
      : "=m" (gdtr)
      :);
}
