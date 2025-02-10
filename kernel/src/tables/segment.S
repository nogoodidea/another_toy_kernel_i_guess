# does the segments operations ... now w/ hard coding
# currently copyed from os dev wiki

.section .data

.section .text
.global reload_segments
.type reload_segments, @function

reload_segments:
  PUSH 0x08
  LEA (.reload_CS) , %RAX
  PUSH %RAX
  LRETq  
.reload_CS:
  MOVw   $0x10 , %ax
  MOVw   %ax , %ds
  MOVw   %ax , %es
  MOVw   %ax , %fs
  MOVw   %ax , %gs
  MOVw   %ax , %ss
  RET
