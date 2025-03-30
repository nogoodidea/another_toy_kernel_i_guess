// guard
#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "../common/types.h"

typedef void (*interruptHandler)(u64 status);

// c functions
void  exception_set_handler(interruptHandler func,u8 index);
void  interrupt_set_handler(interruptHandler func,u8 index);
void  interrupt_handler(usize status);


void interrupt_setup(void);

extern void interrupt_enable(usize interrupt);
extern void interrupt_disable(usize interrupt);
extern void interrupt_enable_all(void);
extern void interrupt_disable_all(void);

extern void interrupt_enable_for_real_this_time_(void);

extern usize interrupt_status(void);

#endif // INTERRUPT_H
