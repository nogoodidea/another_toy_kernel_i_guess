
#include <stdbool.h>

#include "common/types.h"


typedef u32 eflags_t;

// returns eflags
eflags_t get_eflags();

void put_eflags(eflags_t);

bool check_cpuid();
