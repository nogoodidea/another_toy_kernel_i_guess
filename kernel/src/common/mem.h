#ifndef COMMON_MEM_H
#define COMMON_MEM_H


#include <stdint.h>
#include "types.h"
#include <stddef.h>
// all the memory functions gcc wants

void *memcpy(void *dest,const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

volatile void *memsetv(volatile void *s, int c, size_t n);

u32 __bswapsi2(u32 value);

u64 __bswapsdi2(u64 value);


#endif //COMMON_MEM_H
