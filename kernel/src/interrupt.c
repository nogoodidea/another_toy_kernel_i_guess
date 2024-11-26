#include "common/types.h"
#include "panic.h"

#define INTERRUPT_HANDLER_ALL_STATE(f)  __attribute__((naked)) void f ## _handler (){ \
  __asm__ (               \
      /* Saves regesters to the stack */ \
      "push %rax     \n" \
      "push %rcx     \n" \
      "push %rdx     \n" \
      "push %rsi     \n" \
      "push %rdi     \n" \
      "push %r8      \n" \
      "push %r9      \n" \
      "push %r10     \n" \
      "push %r11     \n" \
      "FWAIT        \n" /* does all pending floating point instructions*/ \
      "sub %esp , 512 \n" \
      "FXSAVE %esp\n" /* saves the block */ \
      "mov %rdi %rsp \n" /*move interupt frame addr to first arg*/ \
      "sub %rsp , 8\n" /*align stack*/ \
      "call " #f "\n" /*call the function*/ \
      "FXRSTOR %esp" /* restores it */ \
      "add %esp , 512" /* back from stack */ \
      "pop %r10    \n" \
      "pop %r9     \n" \
      "pop %r8     \n" \
      "pop %rdi    \n" \
      "pop %rsi    \n" \
      "pop %rdx    \n" \
      "pop %rcx    \n" \
      "pop %rax    \n" \
      "iretq      \n" \
    ); \
}

#define INTERRUPT_HANDLER(f) \
__attribute__((naked)) void f ## _handler (){ \
  __asm__ ( \
      "push %rax     \n" \
      "push %rcx     \n" \
      "push %rdx     \n" \
      "push %rsi     \n" \
      "push %rdi     \n" \
      "push %r8      \n" \
      "push %r9      \n" \
      "push %r10     \n" \
      "push %r11     \n" \
      "mov %rsp , %rdi \n" /*move interupt frame addr to first arg*/ \
      "sub %rsp , 8   \n" /*align stack*/ \
      "call " #f " \n"/*call the function*/ \
      "pop %r11      \n" \
      "pop %r10      \n" \
      "pop %r9       \n" \
      "pop %r8       \n" \
      "pop %rdi      \n" \
      "pop %rsi      \n" \
      "pop %rdx      \n" \
      "pop %rcx      \n" \
      "pop %rax      \n" \
      "iretq        \n" \
    ); \
} 

//TODO make your own small asm blocks

void double_fault(void *frame){
  PANIC("DOUBLE FAULT");
}

INTERRUPT_HANDLER(double_fault);

