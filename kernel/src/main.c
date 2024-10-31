#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <limine.h>

#include "common/mem.h"
#include "common/types.h"


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

//infine loop of sadness
static void hcf(void) {
  for(;;){
    __asm__ inline ("hlt");
  } 
}

// main kernal funtion
// does not return bc called by bootloader and bootloader pushes a 0 reutrn addr
void kmain(void) __attribute__((noreturn)){

  // check the fb
  if(framebuffer_request.responce == NULL || framebuffer_request.responce->framebuffer_count < 1){ // if no fb or no reply
    hcf(); // l bozo
  }
  struct limine_framebuffer *framebuffer = framebuffer_request.responce->framebuffers[0];

  fb_fill(fb);

  hcf();
}
