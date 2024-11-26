#include "TTS.h"

#define SET_TTS(s) \
void tts_set_##s (u64 ptr){ \
  TTS.stack_##s = ptr; \
} \
  \
u64 tts_get_##s (){ \
  return TTS.stack_##s; \
} 

__attribute((section(".tables"))) static volatile tts_t TTS;

SET_TTS(RSP0)
SET_TTS(RSP1)
SET_TTS(RSP2)

SET_TTS(IST1)
SET_TTS(IST2)
SET_TTS(IST3)
SET_TTS(IST4)
SET_TTS(IST5)
SET_TTS(IST6)
SET_TTS(IST7)

const void *tts_get_address(){
  return (const void *) &TTS;
}

