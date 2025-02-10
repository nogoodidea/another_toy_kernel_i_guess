#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <limine.h>


// kernal headers
#include "common/mem.h"
#include "common/types.h"
#include "common/addr.h"


#include "panic.h"
#include "framebuffer.h"
#include "interrupt.h"

#include "tables/GDT.h"
#include "tables/IDT.h"
#include "tables/TTS.h"

#include "io/kprint.h"
#include "io/serial.h"

// LIMINE PROROCAL
__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(3);

// need to both be volitial and used bc the compiler hates this
__attribute__((used, section(".requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};

__attribute__((used, section(".requests")))
static volatile struct limine_kernel_address_request kernel_address_request = {
  .id = LIMINE_KERNEL_ADDRESS_REQUEST,
  .revision = 0
};

// TODO DTB BLOB
__attribute__((used, section(".requests")))
static volatile struct limine_dtb_request device_tree_blob = {
  .id = LIMINE_DTB_REQUEST ,
  .revision = 0
};

// TODO and memory map
__attribute__((used, section(".requests")))
static volatile struct limine_memmap_request kernal_memory_map = {
  .id = LIMINE_MEMMAP_REQUEST,
  .revision = 0
};


// the start and end makers for Limine

__attribute__((used,section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used,section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;

// CODE

__attribute((section(".tables"),aligned(0x10))) extern struct idt_t *IDT;

// main kernal funtion
// does not return bc called by bootloader and bootloader pushes a 0 reutrn addr
__attribute__((noreturn))
void kmain(void) {
  u64 kern_stack_base;
  asm volatile("MOV %%rsp, %0"
      : "=m" (kern_stack_base)
      ::);
    
  // ok serel output
  kprint_buffer_set(__io_buffer_get_static_buff());
  io_init_serial(kprint_buffer_get(),0x3F8);

  // check the fb
  if(framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1){ // if no fb or no reply
    PANIC("UNABLE TO AQUIRE FRAMEBUFFER"); // l bozo
  }
  struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

  fb_fill(framebuffer,200,200,200);

  if(kernel_address_request.response == NULL){
    PANIC("LININE FAILED TO RETURN BASE ADDRESS");
  };
  // get the base addresses of the kernel
  load_kern_offset(kernel_address_request.response->virtual_base,kernel_address_request.response->physical_base);

  kprintf("size_of_gdt: %u\nsize_of_idt: %u\n",sizeof(gdt_entry_t)*8,sizeof(idt_entry_t)*8);
  kprint_flush();

  // load the tables 
  tts_init();
  gdt_init(tts_get_address());
  gdt_load();
  
  // setup idt first
  interupt_disable();
  idt_init_table();
  
  // test handler
  idt_set_handler(0x8,double_fault);
  idt_set_privlage(0x8,0x0);
  idt_set_gate_type(0x8,Interrupt);
  idt_set_present(0x8,true);
  
  idt_load();
    // interupt up
  interupt_enable();
  // fault
  
  PANIC("END OF KMAIN TRAP");
}
