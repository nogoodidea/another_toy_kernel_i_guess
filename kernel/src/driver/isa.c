#include <stdbool.h>
#include <stdint.h>
#include <limits.h>


#include "../common/types.h"
#include "../common/endian.h"

#include "../panic.h"
#include "../io/kprint.h"

#include "../paging/page.h"
#include "csr.h"

bool isa_check(u8 extension){

  if(extension > 25){
    PANIC("extention number out of range");
  }
  u64 out = _csr_misa_read();
  return out == extension;
}

bool isa_check_char(unsigned char extension){
  extension-=65;
  if(extension > 25){
    PANIC("extention char invalid");
  }
  u64 out = _csr_misa_read();
  return out == extension;
}

// make sure print works ... yeah good idea
void isa_print(){
  const char *EXTENTIONS = "ABCDEFHIJMNPQSUVX";

  u64 out = _csr_misa_read();

  usize i = 0;

  while(EXTENTIONS[i]){
    kprintf("%c: %c\r\n",EXTENTIONS[i],(1<<(EXTENTIONS[i]-65) & out)==0 ? 'T' : 'F');
    i+=1;
  }
}

#define INS16MASK   endian16(0x3) 
#define INS32MASK   endian16(0x1C)
#define INS48MASK   endian16(0x20)
#define INS64MASK   endian16(0x40)
#define INS80vMASK  endian16(0x7000)

// in bytes ,,, does a deref so give it a pointer to the instruction
// ... like from mepc ... 
usize isa_get_instruction_len(void * ins){
  if(!page_table_check_valid(ins) ){
    return 0;
  }


  u16 instruction = endian16(*((u16 *) ins));
  if((instruction & INS16MASK) == INS16MASK){ // page 17 of the unprivlaged isa btw
    kprintf("Instruction: %x\n\r%x\n\r",instruction,(instruction & INS16MASK));
    return 2; // 2 bytes (16 bits)
  }else if ((instruction & INS32MASK) == INS32MASK){
    return 4; // 32
  } // technicaly frozen

  else if ((instruction & INS48MASK) == 0){
    return 6; // 48
  }else if ((instruction & INS64MASK) == 0){
    return 8; // 64
  }else if ((instruction & INS80vMASK) != INS80vMASK){
    return 10 + 2 * ((instruction & INS80vMASK) >> 12); // 80 + 16 * nnn
  }
  PANIC("error in instruction length getter");
}

