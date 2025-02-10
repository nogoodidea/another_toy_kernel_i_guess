#include "types.h"

static usize kern_virt;
static usize kern_flat;

void load_kern_offset(usize virt,usize flat){
  kern_virt = virt;
  kern_flat = flat;
}

usize kern_virt_to_flat(usize addr){
  return (addr - kern_virt) + kern_flat;
}

usize kern_flat_to_virt(usize addr){
  return (addr - kern_flat) + kern_virt;
}
