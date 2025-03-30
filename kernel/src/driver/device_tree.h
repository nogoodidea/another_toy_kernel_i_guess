#ifndef DRIVER_DEVICE_TREE_H

#include "../common/types.h"

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


bool device_tree_check_magic(struct fdt_header *devicetree_header);
bool device_tree_check_version(struct fdt_header *devicetree_header);

void device_tree_craw_tree(struct fdt_header *devicetree_header);

#endif //DRIVER_DEVICE_TREE_H
