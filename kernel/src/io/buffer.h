#ifndef IO_BUFFER_H
#define IO_BUFFER_H

#include "../common/types.h"

#include <stdarg.h>
#include <stdbool.h>

#define IO_BUFFER_LEN 512

typedef struct io_buffer_s *io_buffer;


io_buffer __io_buffer_get_static_buff();

void io_init_buffer(io_buffer b,void *data,bool (*flush)(char buffer[IO_BUFFER_LEN],usize index, void *data));

void io_output_u64(io_buffer b,u64 value,u8 base);
void io_output_u32(io_buffer b,u32 value,u8 base);


void io_output_char(io_buffer b,char c);

bool io_flush(io_buffer b);

void io_output_string(io_buffer b,char *str);

void io_output_string_len(io_buffer b,char *str,usize len);

void io_output_format(struct io_buffer_s *b,const char *format,va_list args);

#endif //IO_BUFFER_H
