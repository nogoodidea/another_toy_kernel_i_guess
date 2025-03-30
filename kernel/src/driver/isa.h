#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#include "../common/types.h"
#include "../panic.h"

#define ISA_ATOMIC_EXTENSION 1<<0
#define ISA_B_EXTENSION 1<<1
#define ISA_COMPRESSED_EXTENSION 1<<2
#define ISA_DOUBLE_PRECISION_FLOATING_POINT_EXTENSION 1<<3
#define ISA_RV32E_64E_BASE 1<<4
#define ISA_SIGNLE_PRECISION_FLOATING_POINT_EXTENSION 1<<5
#define ISA_HYPERVISOR_EXTENSION 1<<7
#define ISA_RV321_64I_128I_BASE 1<<8
#define ISA_INTEGER_MULTIPLY_DIVIDE_EXTENSION 1<<12
#define ISA_QUAD_PRECISION_FLOATING_POINT_EXTENSION 1<<16
#define ISA_SUPERVISOR_MODE 1<<18
#define ISA_USER_MODE 1<<20
#define ISA_VECTOR_EXTENSION 1<<21
#define ISA_NON_STANDARD_EXTENSIONS_MODE 1<<23

bool isa_check(u8 extension);
bool isa_check_char(char extension);
void isa_print();
