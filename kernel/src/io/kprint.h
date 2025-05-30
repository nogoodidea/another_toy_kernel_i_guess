#ifndef IO_KPRINT_H
#define IO_KPRINT_H

#include <stdarg.h>

#include "../common/types.h"
#include "buffer.h"

io_buffer kprint_buffer_get();
void kprint_buffer_set(io_buffer buffer);

void kprintf(const char *format, ...);

void kprint_s(char *str);

void kprint_i(u64 value, u8 base);

// prints char
// needs kprint buffer to be set
void kprint_c(char c);

void kprint_flush(void);

void kprints_s(usize port,const char * str);

void kprintu_s(usize port,u64 value,u8 base);

#endif //KPRINT_H
