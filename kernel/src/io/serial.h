#ifndef SERIAL_H
#define SERIAL_H

#include <stdbool.h>

#include "../common/types.h"
#include "../common/port.h"

#include "buffer.h"



// int it
bool serial_int(u16  port);
 
bool serial_can_receive(u16 port);
char serial_read(u16 port);

bool serial_can_transmit(u16 port);
void serial_write(u16 port,char c);

void io_init_serial(struct io_buffer_s *b,u16 port);

#endif // SERIAL_H
