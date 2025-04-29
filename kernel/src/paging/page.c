#include<stdbool.h>

#include "../common/types.h"
#include "../common/endian.h"

#include "../driver/csr.h"
/// ok so we need a page table ... and like it can be stored in the csr 
/// makes it better
/// will need to switch for applications and that

bool page_table_check_valid(void *ptr){
  //todo so like .... is is mapped??
  //:3
  return true;
}

//


struct __attribute__((packed)) pagetable_satp {
  u64 PPN  :44;
  u32 ASID :16;
  u32 MODE :4;
};


extern usize _pagetable_get_satp(void);
struct pagetable_satp *pagetable_get_satp(struct pagetable_satp *out){
  usize table = _csr_satp_read(); 

  out->PPN = table;
  out->ASID= table >> 44;
  out->MODE= table >> 60;
  return out;
}


