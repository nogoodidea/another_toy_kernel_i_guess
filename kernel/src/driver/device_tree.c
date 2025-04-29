#include <stdbool.h>
#include <stddef.h>


#include "device_tree.h"

#include "../common/types.h"
#include "../common/endian.h"
#include "../io/kprint.h"
#include "../panic.h"

//CONSTANTS

#define DEVICE_TREE_MAGIC   endian32(0xd00dfeed)
#define FDT_BEGIN_NODE      endian32(0x00000001)
#define FDT_END_NODE        endian32(0x00000002)
#define FDT_PROP            endian32(0x00000003)
#define FDT_NOP             endian32(0x00000004)
#define FDT_END             endian32(0x00000009)
#define DEVICE_TREE_MINIMUM_VERSION 16

//DEFINES

struct fdt_prop_s {
  u32 len;
  u32 nameoff;
};

struct fdt_mem_s {
  u64 address;
  u64 size;
};


// checks the magic value
bool device_tree_check_magic(struct fdt_header *devicetree_header){
  return devicetree_header->magic == DEVICE_TREE_MAGIC;
}

bool device_tree_check_version(struct fdt_header *devicetree_header){
  return endian32(devicetree_header->last_comp_version) == DEVICE_TREE_MINIMUM_VERSION;
}

// the lexer for like all of this :3
// this function is more to see how the tree is
// assumes that the tree is valid
// see the two checking functions
// but really this just gives device names so i can see what i'm working with on my vm
void device_tree_craw_tree(struct fdt_header *devicetree_header){
  
  bool brk = false; // break varable
  const u32 *bound_ptr = (u32 *) (((char *) devicetree_header) + endian32(devicetree_header->totalsize));

    char *stringoff =(((char *) devicetree_header) + endian32(devicetree_header->off_dt_strings));

  u32 *ptr = (u32 *) (((char *) devicetree_header) + endian32(devicetree_header->off_dt_struct));

  char *unit_name = NULL;
  struct fdt_prop_s *prop = NULL;

  while(!brk && ptr <= bound_ptr){
    switch(*ptr){
      case FDT_BEGIN_NODE:

        unit_name = (char *) (ptr + 1);
         
        kprintf("{ name: %s\r\n",unit_name);

        while(*unit_name != '\0') unit_name += 1;

        usize offset = ((usize) unit_name) - ((usize) (ptr + 1));

        ptr += (offset / sizeof(u32)) + (((offset % sizeof(u32)) > 0) ? 1 : 0) + 1;
        break;
      case FDT_END_NODE:
        kprintf("}\n\r");
        ptr++;
        break;
      case FDT_PROP:
        
        prop = (struct fdt_prop_s *) ptr + 1;
        
        kprintf("prop: %s:\t%S \r\n",stringoff + endian32(prop->nameoff),((char*) (ptr + 4)) + 1,endian32(prop->len));

        ptr += endian32(prop->len)/sizeof(u32) + ( ( (endian32(prop->len) % sizeof(u32)) > 1 ) ? 1 : 0 ) + 2; // number of chars div by 32 + is it not 32 ... then shift it over + 2 bc FDT_PROC_struct
        break;
      case FDT_NOP:
        ptr++;
        break;
      case FDT_END:
        brk = true;
        break;
      default:
        kprintf("ERORR: unknown device tree token %x at %p\r\n",*ptr,ptr);
        ptr++;
        break;
    }
  }
}


// memory resurved block
void device_tree_memory(struct fdt_header *devicetree_header){
  

  const u32 *bound_ptr = (u32 *) (((char *) devicetree_header) + endian32(devicetree_header->totalsize));
  struct fdt_mem_s *mem_s =(struct fdt_mem_s *) (((char *) devicetree_header) + endian32(devicetree_header->off_mem_rsvmap));
  
  while( (usize) mem_s <= (usize) bound_ptr){// bc diffrent ptr
      // format is like ... fdt_header
      kprintf("mem_block: %x, size: %x\n\r");
      mem_s++;
  }
}
