
#include <limine.h>


#include "common/types.h"


void fb_clear(struct limine_framebuffer *fb){
  volatile u8 *buf = fb->address;

  for(usize y = 0;y<fb->height;y++){
    for(usize x = 0;x<fb->width;x++){
      buf[x*fb->bpp] = 0; // R
      buf[x*fb->bpp] = 0; // B
      buf[x*fb->bpp] = 0; // G
    }
    buf += fb->pitch;
  }
}

void fb_fill(struct limine_framebuffer *fb,u8 r, u8 b, u8 g){
  volatile u8 *buf = fb->address;

  for(usize y = 0;y<fb->height;y++){
    for(usize x = 0;x<fb->width;x++){
      buf[x*fb->bpp] = r; // R
      buf[x*fb->bpp] = b; // B
      buf[x*fb->bpp] = g; // G
    }
    buf += fb->pitch;
  }
}
