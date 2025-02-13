
#include "common/types.h"

/*void fb_fill(*fb,u8 r, u8 b, u8 g){
  u8 *buf = fb->address;
  for(usize y = 0;y<fb->height;y++){
    for(usize x = 0;x<fb->width;x++){
      volatile u32 *base = (u32 *) buf+x;
      *base = (r << 16)|(b <<8)|(g);
    }
    buf += fb->pitch;
  }
}


void fb_clear(struct limine_framebuffer *fb){
  fb_fill(fb,0,0,0);
}

int fb_rec(struct limine_framebuffer *fb, usize start_x, usize start_y, usize off_x, usize off_y,u8 r, u8 g, u8 b){
  u8 *buf = fb->address;

  if(fb->height < start_y || fb->width < start_x || fb->height < start_y+off_y || fb->width < start_x+off_x){
    return 0;
  }

  buf += fb->pitch*start_y;

  for(usize y = start_y;y<start_y+off_y;y++){
    for(usize x = start_x;x<start_x+off_x;x++){
      volatile u32 *base = (u32 *) buf+x;
      *base = (r << 16)|(b <<8)|(g);
    }
    buf += fb->pitch;
  }
  return 1;
}*/
