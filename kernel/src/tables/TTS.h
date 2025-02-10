#ifndef TABLES_TTS_H
#define TABLES_TTS_H

#include <stdbool.h>

#include "common/types.h"

void tts_set_RSP0 (u64 ptr);
u64 tts_get_RSP0 (void);
void tts_set_RSP1 (u64 ptr);
u64 tts_get_RSP1 (void);
void tts_set_RSP2 (u64 ptr);
u64 tts_get_RSP2 (void);

void tts_set_IST0 (u64 ptr);
u64 tts_get_IST0 ();

void tts_set_IST1 (u64 ptr);
u64 tts_get_IST1 ();

void tts_set_IST2 (u64 ptr);
u64 tts_get_IST2 ();

void tts_set_IST3 (u64 ptr);
u64 tts_get_IST3 ();

void tts_set_IST4 (u64 ptr);
u64 tts_get_IST4 ();

void tts_set_IST5 (u64 ptr);
u64 tts_get_IST5 ();

void tts_set_IST6 (u64 ptr);
u64 tts_get_IST6 ();

bool tts_init();

struct __attribute__((packed)) tts_s{
  u16 reserved0;
  u64 stack_RSP0;
  u64 stack_RSP1;
  u64 stack_RSP2;
  u32 reserved1;
  u64 stack_IST1;
  u64 stack_IST2;
  u64 stack_IST3;
  u64 stack_IST4;
  u64 stack_IST5;
  u64 stack_IST6;
  u64 stack_IST7;
  u64 reserved2;
  u16 reserved3;
  u16 IOPB;
};

typedef struct tts_s tts_t;

const void * tts_get_address();

#endif //TABLES_TTS_H
