#include "mem.h"
#include "types.h"

void *memcpy(void *dest,const void *src, size_t n){
  u64 *dest_u64 = dest;
  const u64 *src_u64 = src;

  size_t i = 0;
  for(i = 0;i*sizeof(u64)<n;i++){
    dest_u64[i] = src_u64[i];
  }
  i *= sizeof(u64);

  u8 *dest_u8 = dest; 
  const u8 *src_u8 = src;

  for(;i<n;i++){
    dest_u8[i] = src_u8[i];
  }
  return dest;
}

void *memset(void *s, int c, size_t n){
  int *buf = s;

  size_t i = 0;
  for(i = 0;i*sizeof(int)<n;i++){
    buf[i] = c;
  }
  i *= sizeof(int);
  u8 *bufu8 = s; 
  for(;i<n;i++){
    bufu8[i] = (u8) c;
  }
  return s;
}

volatile void *memsetv(volatile void *s, int c, size_t n){
  volatile int *buf = s;

  size_t i = 0;
  for(i = 0;i*sizeof(int)<n;i++){
    buf[i] = c;
  }
  i *= sizeof(int);
  volatile u8 *bufu8 = s; 
  for(;i<n;i++){
    bufu8[i] = (u8) c;
  }
  return s;
}

void *memove(void *dest, const void *src, size_t n){
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    if (src > dest) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    } else if (src < dest) {
        for (size_t i = n; i > 0; i--) {
            pdest[i-1] = psrc[i-1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n){
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;  
}

u32 __bswapsi2(u32 value){
  u8 *v = (u8 *) &value; 
  u8 swap = 0;
  
  swap = *v;
  *v = *(v+3);
  *(v+3) = swap;

  swap = *(v+1);
  *(v+1) = *(v+2);
  *(v+2) = swap;

  return value;
}

u64 __bswapdi2(u64 value){
  u8 *v = (u8 *) &value;
  u8 swap = 0;

  swap = v[0];
  v[0] = v[7];
  v[7] = swap;

  swap = v[1];
  v[1] = v[6];
  v[6] = swap;

  swap = v[2];
  v[2] = v[5];
  v[5] = swap;

  swap = v[3];
  v[3] = v[4];
  v[4] = swap;

  return value;
}
