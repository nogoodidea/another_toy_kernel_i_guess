
#include "../common/types.h"


const char *exception_code_map(usize i){
  switch(i){
    case 0:
      return "Instruction address misaligned";
    case 1:
      return "Instruction access fault";
    case 2:
      return "Illegal instruction";
    case 3:
      return "Breakpoint";
    case 4:
      return "Load address misaligned";
    case 5:
      return "Load access fault";
    case 6:
      return "Store/AMO address misaligned";
    case 7:
      return "Store/AMO access fault";
    case 8:
      return "Environment call from U-mode";
    case 9:
      return "Environment call from U-mode";
    case 11:
      return "Environment call from M-mode";
    case 12:
      return "Instruction page fault";
    case 13:
      return "Load page fault";
    case 15:
      return "Store/AMO page fault";
    case 18:
      return "Software check";
    case 19:
      return "Hardware error";
    default:
      return "Reserved";
  }
}

const char *interrupt_code_map(usize i){
  switch(i){
    case 1:
      return "Supervisor software interrupt";
    case 3:
      return "Machine software interrupt";
    case 5:
      return "Supervisor timer interrupt";
    case 7:
      return "Machine timer interrupt";
    case 9:
      return "Supervisor external interrupt";
    case 11:
      return "Machine external interrupt";
    case 13:
      return "Counter-overflow interrupt";
     default:
      return "Reserved";
  }
}
