
.section .text

.global __csr_misa_read

__csr_misa_read:
  csrrs a0,misa,zero // misa
  jr ra
.end
