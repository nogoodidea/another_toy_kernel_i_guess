#include <stdarg.h>


#include "../common/types.h"
#include "serial.h"

#include "buffer.h"

#define BUF_SIZE 26

static io_buffer output_buffer;

io_buffer kprint_buffer_get(){
  return output_buffer;
}

void kprintf(const char *format,...){
  //TODO
  va_list args;
  va_start(args,format);
  io_output_format(output_buffer,format,args);
  va_end(args);
}

void kprint_buffer_set(io_buffer buffer){
  output_buffer = buffer;
}

void kprint_s(char *str){
  io_output_string(output_buffer,str);
}

void kprint_i(u64 value, u8 base){
  io_output_u64(output_buffer,value,base);
}

// prints char
void kprint_c(char value){
  io_output_char(output_buffer,value);
}

void kprint_flush(void){
  io_flush(output_buffer);
}


void kprints_s(usize port,const char * str){
  usize i = 0;
  while(str[i] != '\0'){
    serial_write(port,str[i]);
    i++;
  }
}

void kprintu_s(usize port,u64 value,u8 base){
  int int_buf[BUF_SIZE] = {0};
  usize i = BUF_SIZE-2;
  for (;value && value;--i,value /= base){
    int_buf[i] = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base]; 
  }
  for(--i;i<BUF_SIZE;i++){
    serial_write(port,int_buf[i]);
  }
}

