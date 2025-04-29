#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// kernal headers
#include "common/mem.h"
#include "common/types.h"
#include "common/addr.h"

#include "panic.h"
#include "framebuffer.h"

#include "interrupt/interrupt.h"

#include "io/kprint.h"
#include "io/serial.h"

#include "driver/device_tree.h"
#include "driver/isa.h"


// main kernal funtion
// does not return bc called by bootloader and bootloader pushes a 0 reutrn addr
__attribute__((noreturn))
void kmain(usize hart_id,struct fdt_header *fdt_ptr) {
  // ok serel output
  kprint_buffer_set(__io_buffer_get_static_buff());
  io_init_serial(kprint_buffer_get(),0x10000000); // memory maped io .... but we should grab this from device tree later :3
   
  kprintf("dtree_ptr: %p\n\r",fdt_ptr);
  kprintf("hart: %u\n\r",hart_id);
  
  kprintf("\n\r");
  kprintf("\n\r");

  isa_print();
  
  kprint_flush();

  // trust
  interrupt_enable_all();
  interrupt_setup();// interrupts are enabled we just like filled out the bitmask befor
  interrupt_enable_for_real_this_time_();

  io_serial_register_echo_interrupt(0x10000000,0); 

  if(device_tree_check_magic(fdt_ptr) && device_tree_check_version(fdt_ptr)){
    device_tree_craw_tree(fdt_ptr);
    device_tree_memory(fdt_ptr);
  }else{
    PANIC("INVALID DEVICE TREE");
  }
  kprint_flush();
  
  char * ptr = NULL;
  *ptr = 2;
  
  PANIC("END OF KMAIN TRAP");
}
