// kern print functions

#ifndef KPRINT_H
#define KPRINT_H

#include "common/types.h"

void kprints_s(u16 port,const char * str);

void kprintu_s(u16 port,u64 value,u8 base);


#endif //KPRINT_H
