#ifndef SERIAL_H
#define SERIAL_H

#include <stdbool.h>

#include "../common/types.h"

#include "buffer.h"



// int it
bool serial_int(usize addr);
 
bool serial_can_receive(usize addr);
char serial_read(usize addr);

bool serial_can_transmit(usize addr);
void serial_write(usize addr,char c);

void io_init_serial(io_buffer b,usize addr);

void io_serial_echo_input(usize addr);

// int
void io_serial_register_echo_interrupt(usize addr, u16 interrupt_number);

#endif // SERIAL_H
