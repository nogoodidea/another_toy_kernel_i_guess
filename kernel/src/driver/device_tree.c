#include <stdbool.h>

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

  while(!brk && ptr <= bound_ptr){
    switch(*ptr){
      case FDT_BEGIN_NODE:

        char *unit_name = (char *) (ptr + 1);
        
        kprintf("{ name: %s\r\n",unit_name);

        while(*unit_name != '\0') unit_name +=1;

        usize offset = ((usize) unit_name) - ((usize) ptr);

        ptr += (offset / sizeof(u32)) + ((offset % sizeof(u32)) > 0);

        break;
      case FDT_END_NODE:
        kprintf("}\n\r");
        break;
      case FDT_PROP:
        
        struct fdt_prop_s *prop = (struct fdt_prop_s *) ++ptr;
        
        kprintf("prop: %s:\t%S \r\n",stringoff + endian32(prop->nameoff),((char*) (ptr + 4)) + 1,endian32(prop->len));

        ptr += endian32(prop->len)/sizeof(u32)+((endian32(prop->len) % sizeof(u32)) > 1);
        break;
      case FDT_NOP:
        break;
      case FDT_END:
        brk = true;
        break;
      default:
    }
    ptr++;
  }
  kprint_flush();
}
