#include <stdbool.h>


#include "../common/types.h"
#include "../common/port.h"
#include "io/buffer.h"

#include "panic.h"


//
bool serial_int(u16  port){
   outb(port + 1, 0x00);    // Disable all interrupts
   outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(port + 1, 0x00);    //                  (hi byte)
   outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   outb(port + 4, 0x1E);    // Set in loopback mode, test the serial chip
   outb(port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
   // Check if serial is faulty (i.e: not same byte as sent)
   if(inb(port + 0) != 0xAE) {
      return 1;
   }

   // If serial is not faulty set it in normal operation mode
   // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
   outb(port + 4, 0x0F);
   return 0;  

}

bool serial_received(u16 port){
  return (inb(port+5) & 0x01); // input from line status and check if data is ready
}

char serial_read(u16 port){
  while (serial_received(port) == false){
      //TODO don't busy loop
  }
  return inb(port+0); // input from line status and check if data is ready
}

bool serial_can_transmit(u16 port){
  return inb(port+5) & 0x20;
}

void serial_write(u16 port,char c){
  while(serial_can_transmit(port) == false){
    //TODO here
  }
  outb(port,c);
}

// buffered io implemntation

bool buffer_io_serial_flush(char buffer[IO_BUFFER_LEN],usize index, void *data){
  for(usize i=0;i < index;i+=1){
    serial_write((usize) data,buffer[i]);
  }
  return true;
}

void io_init_serial(io_buffer b,u16 port){
  io_init_buffer(b,(void *)(usize) port,buffer_io_serial_flush); 
  if(serial_int(port)){
    PANIC("UNABLE TO INT BUFFER"); // like ... this will not display.
  }
}
