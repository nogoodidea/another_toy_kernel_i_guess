#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <limine.h>

#include "common/mem.h"
#include "common/types.h"

#include "panic.h"
#include "framebuffer.h"
#include "interrupt.h"

#include "tables/GDT.h"
#include "tables/IDT.h"
#include "tables/TTS.h"

// LIMINE PROROCAL
__attribute__((used, section(".requests")))
static volatile LIMINE_BASE_REVISION(3);

// need to both be volitial and used bc the compiler hates this
__attribute__((used, section(".requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};



// the start and end makers for Limine

__attribute__((used,section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used,section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;


// CODE


// main kernal funtion
// does not return bc called by bootloader and bootloader pushes a 0 reutrn addr
__attribute__((noreturn))
void kmain(void) {

  // check the fb
  if(framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1){ // if no fb or no reply
    PANIC("UNABLE TO AQUIRE FRAMEBUFFER"); // l bozo
  }
  struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

  fb_fill(framebuffer,200,200,200);

  init_gdt(tts_get_address());
  
  interupt_disable();
  idt_init_table();
  idt_set_handler(0x08,double_fault);
  idt_set_privlage(0x08,0x0);
  idt_set_present(0x08,true);
  
  // interupt up
  interupt_enable();
  
  PANIC("END OF KMAIN TRAP");
}
