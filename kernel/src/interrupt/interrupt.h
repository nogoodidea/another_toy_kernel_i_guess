// guard
#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "../common/types.h"

typedef usize (*interruptHandler)(u64 status,usize epc);

void  exception_set_handler(interruptHandler func,u8 index);
void  interrupt_set_handler(interruptHandler func,u8 index);

void interrupt_setup(void);

extern void interrupt_enable(usize interrupt);
extern void interrupt_disable(usize interrupt);
extern void interrupt_enable_all(void);
extern void interrupt_disable_all(void);

/// DON'T USE THIS ... :)
extern void _interrupt_handler(void);
usize interrupt_handler(u64 status,usize epc);


extern void interrupt_enable_for_real_this_time_(void);

extern usize interrupt_status(void);

#endif // INTERRUPT_H
