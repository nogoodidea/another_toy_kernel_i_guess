#include <stdbool.h>


#include "../common/types.h"
#include "buffer.h"

#include "../panic.h"

bool serial_int(usize addr){
  volatile u8 *ptr = (volatile u8 *) addr;

  ptr[1]  = 0x00;    // Disable all interrupts
  ptr[3]  = 0x80;    // Enable DLAB (set baud rate divisor)
  ptr[0]  = 0x03;    // Set divisor to 3 (lo byte) 38400 baud
  ptr[1]  = 0x00;    //                  (hi byte)
  ptr[3]  = 0x03;    // 8 bits, no parity, one stop bit
  ptr[2]  = 0xC7;    // Enable FIFO, clear them, with 14-byte threshold
  ptr[4]  = 0x0B;    // IRQs enabled, RTS/DSR set
  ptr[4]  = 0x1E;    // Set in loopback mode, test the serial chip
  ptr[0]  = 0xAE;    // Test serial chip (send byte 0xAE and check if serial returns same byte)
  // Check if serial is faulty (i.e: not same byte as sent)
  if(ptr[0] != 0xAE) {
    return false;
  }

  // If serial is not faulty set it in normal operation mode
  // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
  ptr[4] = 0x0F;
  return true;
}

//
bool serial_received(usize addr){
  // TODO
  return false;
}

char serial_read(usize addr){
  // todo check if data is ready
  return *(volatile u8 *)addr; // input from line status and check if data is ready
}

bool serial_can_transmit(usize addr){
  return false; //TODO
}

void serial_write(usize addr ,char c){

  *(volatile u8 *)addr = c; 
}

// buffered io implemntation

bool buffer_io_serial_flush(char buffer[IO_BUFFER_LEN],usize index, void *data){
  for(usize i=0;i < index;i+=1){
    serial_write((usize) data,buffer[i]);
  }
  return true;
}

void io_init_serial(io_buffer b,usize addr){
  io_init_buffer(b,(void *) addr,buffer_io_serial_flush); 
  if(!serial_int(addr)){
    PANIC("UNABLE TO INT BUFFER"); // like ... this will not display.
  }
}
