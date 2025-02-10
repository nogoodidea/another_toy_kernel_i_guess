#include "GDT.h"
#include "io/kprint.h"

#include "common/mem.h"
#include "common/addr.h"
#include "common/types.h"

#include "panic.h"


  // null segmetn
  // ring 0 - read write
  // ring 0 - code read
  // ring 3 - read write
  // ring 3 - code
  // TTS
  // Reserved (null)
  // Reserved (null)
  //

// asm block
extern void reload_segments();


__attribute((section(".tables"),aligned(0x10))) static volatile gdt_entry_t GDT[8];

void segment_init(volatile gdt_entry_t *gdt,u64 base,u32 limit,u8 access,u8 flags){
    // limit
    //TODO limit the limit
    gdt->limit_low =  limit;
    gdt->limit_high = (limit >> 16); 
    // base
    gdt->base_low =   base;
    gdt->base_mid_0 = base >> 16;
    gdt->base_mid_1 = base >> 24;
    gdt->base_high =  base  >> 32;

    // access
    gdt->access = access;
    gdt->flags  = flags;
}


void segment_null(volatile gdt_entry_t *gdt){
    memsetv( &gdt,0x0,sizeof(gdt_entry_t));
}

void gdt_init(const void *tts){
  // NULL DESCRIPTOR 
  segment_null(GDT);

  // kernel mode code segment
  segment_init(GDT+1,0,0x000FFFFF,0x9A,0xC);

  // kernel mode data segment
  segment_init(GDT+2,0,0x000FFFFF,0x9A,0xC);
 

  // kernel mode code segment
  segment_init(GDT+3,0,0x000fffff,0xFA,0xC);

  // kernel mode data segment
  segment_init(GDT+4,0,0x000fffff,0xF2,0xC); 
  //TTS
  segment_init(GDT+5,(usize) tts,sizeof((tts))-1,0x89,0x0);
} 


bool gdt_load(){
  // make the gdtr
  struct __attribute__((packed)){
    u16 size;
    u64 offset;
  } gdtr = {(sizeof(gdt_entry_t)*8)-1, (u64) &GDT};

  // enable it
  asm(
      "LGDT %0\n\t"
      ::"m" (gdtr)
      :);

  reload_segments();

  PANIC("GOT HERE");

  asm(
      "MOV %%ax, 0x20\n\t" // 0x28 = 101000 or the segment selector of the TTS
      "LTR %%ax\n\t"
    :::"ax");
  

  return true;
}

