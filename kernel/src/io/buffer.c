#include <stdbool.h>

#include "common/types.h"
#include "common/mem.h"
#include "panic.h"

#include "io/buffer.h"

#define IO_BUFFER_LEN 512

// STRUCTS
struct io_buffer_s{
  char buffer[IO_BUFFER_LEN];
  usize index;
  void *data;
  /// function to fluch the output buffer
  bool (*flush)(char buffer[IO_BUFFER_LEN],usize index, void *data);
}io_buffer_t;


//STATICS
static struct io_buffer_s BUFFER;

//CODE

// so this is temp
io_buffer __io_buffer_get_static_buff(){
  return &BUFFER;
}

// sets up the proper values for the buffer
void io_init_buffer(struct io_buffer_s *b,void *data,bool (*flush)(char buffer[IO_BUFFER_LEN],usize index, void *data)){
  b->index = 0;
  b->data = data;
  b->flush = flush;
}

// wrapper around the buffers fluch rutine
bool io_flush(struct io_buffer_s* b){
  bool out;
  if((out = (b->flush(b->buffer,b->index,b->data))) ){
    b->index = 0;
  }
  return out;
}

// just for chars
void io_output_char(struct io_buffer_s* b,char c){
  if(b->index < IO_BUFFER_LEN || c == '\n'){
    io_flush(b);
  }
  b->buffer[b->index++] = c;
}

// strongs
void io_output_string(struct io_buffer_s *b,char *str){
  while(*str != '\0'){
    if(b->index >= IO_BUFFER_LEN -1){
      io_flush(b);
    }
    b->buffer[b->index++] = *(str++);
  }
}

void io_output_u32(struct io_buffer_s *b,u32 value,u8 base){

  if(value == 0){
    io_output_char(b,'0');
    return ;
  }

  int int_buf[26] = {0};
  usize i = 24;
  for (;value && value;--i,value /= base){
    int_buf[i] = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base]; 
  }
  for(--i;i<26;i++){
    if(b->index >= IO_BUFFER_LEN -1){
      io_flush(b);
    }
    b->buffer[b->index++] = int_buf[i];
  }
}

// just copyed from io_output_u32
void io_output_u64(struct io_buffer_s *b,u64 value,u8 base){

  if(value == 0){
    io_output_char(b,'0');
    return ;
  }


  int int_buf[26] = {0};
  usize i = 24;
  for (;value && value;--i,value /= base){
    int_buf[i] = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base]; 
  }
  for(--i;i<26;i++){
    if(b->index > IO_BUFFER_LEN -1){
      io_flush(b);
    }
    b->buffer[b->index++] = int_buf[i];
  }
}

void io_output_int(struct io_buffer_s *b,i64 value,u8 base){
  int int_buf[26] = {0};
  usize i = 24;
  
  if(value == 0){
    io_output_char(b,'0');
    return ;
  }

  bool sign = 0 > value; // drop the sign 
  if(sign) value *= -1; // don't you
  
  for (;value && value;--i,value /= base){
    int_buf[i] = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base]; 
  }

  if(b->index + 27 >= IO_BUFFER_LEN -1){
    io_flush(b);
  }
  
  if(sign) b->buffer[b->index++] = '-'; // minus

  for(--i;i<26;i++){
    b->buffer[b->index++] = int_buf[i];
  }
}

void io_output_string_len(struct io_buffer_s *b,char *str,usize len){
  while(len){
    usize block = IO_BUFFER_LEN - b->index;
    if(len < block){
      memcpy(b->buffer + b->index,str,len);
      b->index += len;
      len = 0;
    }else{
      memcpy(b->buffer + b->index,str,block);  
      len -= block;
      io_flush(b);
    }
  }
}
//printf formatter helpers

usize __io_output_printf_precision(const char *fmt,usize *i){
  usize count = 0;
  while(fmt[*i] >= 48 && fmt[*i] <= 57){
    count *=10;
    count += fmt[*i] - 48;
   (*i)++;
  }

  return count;
}

//printf but like shitty and we don't need half of the stuff here
// assumes va_list is setup
void io_output_format(struct io_buffer_s *b,const char *format, va_list args){
  usize i = 0;
  usize precision = 0;

  
  // so you craw format untill you get a %
  // probaly with a flush check too :)
  while(format[i] != '\0'){
    if(format[i] == '%'){
      i++;

      precision = __io_output_printf_precision(format,&i);

      // we saw one now show the other hand.
      switch(format[i]){
        case's': // string
          if(precision == 0){
            io_output_string(b,va_arg(args,char *));
          }else{
            io_output_string_len(b,va_arg(args,char *),precision);
          }
          break;
        case'S':
          io_output_string_len(b,va_arg(args,char *),va_arg(args,usize));
          break;
        case 'l':
          i++;
          switch(format[i]){
            case'u': // insigned int
              io_output_u64(b,va_arg(args,u64),10);
              break;
            case'x': // hex
              io_output_string_len(b,"0x",2); 
              io_output_u64(b,va_arg(args,u64),16);
              break;
            default:
              PANIC("UNKNOWN FORMATTER");
          }
          break;
        case'u': // insigned int
          io_output_u32(b,va_arg(args,u32),10);
          break;
        case'x': // hex
          io_output_string_len(b,"0x",2); 
          io_output_u32(b,va_arg(args,u32),16);
          break;
        case'p':
          io_output_string_len(b,"0x",2); // smiles,  so i get to use this after all how fun
          io_output_u64(b,(usize) va_arg(args,void *),16);
          break;
        case'%':
          io_output_char(b,'%');
          break; // a
        case'c':
            io_output_char(b,va_arg(args,int));
            break;
        default:
          PANIC("UNKNOWN FORMATTER");
          break; // unreachable  
      }
    }else{ // not aaaaaa formater
      if(b->index >= IO_BUFFER_LEN -1){
        io_flush(b);
      }
      b->buffer[b->index++] = format[i];   
    }
    i++;
  }
}

