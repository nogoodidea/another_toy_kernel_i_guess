#ifndef COMMON_ADDR_H
#define COMMON_ADDR_H

#include "types.h"

void load_kern_offset(usize virt,usize flat);

usize kern_virt_to_flat(usize addr);

usize kern_flat_to_virt(usize addr);

#endif //COMMON_ADDR_H

