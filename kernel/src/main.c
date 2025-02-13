#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// kernal headers
#include "common/mem.h"
#include "common/types.h"
#include "common/addr.h"

#include "panic.h"
#include "framebuffer.h"

#include "io/kprint.h"
#include "io/serial.h"

// main kernal funtion
// does not return bc called by bootloader and bootloader pushes a 0 reutrn addr
__attribute__((noreturn))
void kmain(void) {
  // ok serel output
  kprint_buffer_set(__io_buffer_get_static_buff());
  io_init_serial(kprint_buffer_get(),0x10000000); // memory maped io .... but we should grab this from device tree later :3
  kprintf("GOT HERE\n");
  
  kprintf("GOT HERE TOO\n"); 
  
  PANIC("END OF KMAIN TRAP");
}
