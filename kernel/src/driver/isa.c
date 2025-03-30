#include <stdbool.h>
#include <stdint.h>
#include <limits.h>


#include "../common/types.h"
#include "../panic.h"
#include "../io/kprint.h"

extern u64 __csr_misa_read();

bool isa_check(u8 extension){

  if(extension > 25){
    PANIC("extention number out of range");
  }
  u64 out = __csr_misa_read();
  return out == extension;
}

bool isa_check_char(unsigned char extension){
  extension-=65;
  if(extension > 25){
    PANIC("extention char invalid");
  }
  u64 out = __csr_misa_read();
  return out == extension;
}

// make sure print works ... yeah good idea
void isa_print(){
  const char *EXTENTIONS = "ABCDEFHIJMNPQSUVX";

  u64 out = __csr_misa_read();

  usize i = 0;

  while(EXTENTIONS[i]){
    kprintf("%c: %c\r\n",EXTENTIONS[i],(1<<(EXTENTIONS[i]-65) & out)==0 ? 'T' : 'F');
    i+=1;
  }
}

