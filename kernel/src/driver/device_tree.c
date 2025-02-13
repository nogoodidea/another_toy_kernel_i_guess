#include <stdbool.h>

#include "../common/types.h"
#include "../io/kprint.h"
#include "../panic.h"

//CONSTANTS

#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__
#define BG(x) __builtin_bswap32(x)
#define DEIVICE_TREE_MAGIC  __builtin_bswap32(0xd00feed)
#define FDT_BEGIN_NODE      __builtin_bswap32(0x00000001)
#define FDT_END_NODE        __builtin_bswap32(0x00000002)
#define FDT_PROP            __builtin_bswap32(0x00000003)
#define FDT_NOP             __builtin_bswap32(0x00000004)
#define FDT_END             __builtin_bswap32(0x00000009)
#define DEIVICE_TREE_MINIMUM_VERSION __builtin_bswap32(16)
#else
#define BG(x) x
#define DEIVICE_TREE_MAGIC  0xd00dfeed
#define FDT_BEGIN_NODE      0x00000001
#define FDT_END_NODE        0x00000002
#define FDT_PROP            0x00000003
#define FDT_NOP             0x00000004
#define FDT_END             0x00000009
#define DEIVICE_TREE_MINIMUM_VERSION 16
#endif




//DEFINES

struct fdt_header {
  u32 magic;
  u32 totalsize;
  u32 off_dt_struct;
  u32 off_dt_strings;
  u32 off_mem_rsvmap;
  u32 version;
  u32 last_comp_version;
  u32 boot_cpuid_phys;
  u32 size_dt_strings;
  u32 size_dt_struct;
};

struct fdt_prop_s {
  u32 len;
  u32 nameoff;
};


// checks the magic value
bool device_tree_check_magic(struct fdt_header *devicetree_header){
  return devicetree_header->magic == DEIVICE_TREE_MAGIC;
}

bool device_tree_check_version(struct fdt_header *devicetree_header){
  return devicetree_header->last_comp_version == DEIVICE_TREE_MINIMUM_VERSION;
}

// the lexer for like all of this :3
// this function is more to see how the tree is
// assumes that the tree is valid
// see the two checking functions
// but really this just gives device names so i can see what i'm working with on my vm
/*void device_tree_craw_tree(struct fdt_header *devicetree_header){
  
  bool brk = false; // break varable
  u32 *bound_ptr = (u32 *) (((char *) devicetree_header) + BG(devicetree_header->totalsize));
  u32 *ptr = (u32 *) (((char *) devicetree_header) + BG(devicetree_header->off_dt_struct));

  while(!brk && ptr <= bound_ptr){
    switch(*ptr){
      case FDT_BEGIN_NODE:
        kprint_s(">>>\nName:\t");
        char *name =  (char *) (ptr+1);
        kprint_s(name);
        while(name) ++name;
        ptr +=((usize)name-(usize)ptr)/sizeof(u32);
        
        kprint_s("\n");

        break;
      case FDT_END_NODE:
        kprint_s("<<<\n");
        break;
      case FDT_PROP:
        //TODO get prop
        struct fdt_prop_s *s = (struct fdt_prop_s *) (++ptr);
        kprint_s((char *) (ptr + 1));
        kprint_c('\n');
        ptr += ((s->len)/sizeof(u32))-(s->len % 32 == 0);
        break;
      case FDT_NOP:
        break;
      case FDT_END:
        brk = true;
        break;
      default:
        PANIC("UNKNOWN DEVICE TREE TOKEN");
    }
    ptr+=sizeof(u32);
  }
  kprint_flush();
}*/
