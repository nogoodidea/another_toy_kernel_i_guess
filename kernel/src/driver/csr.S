
.section .text

.global _csr_misa_read

_csr_misa_read:
  csrrs a0,misa,zero // misa
  jr ra
.end

.global _csr_sstatus_read:
_csr_sstatus_read:
  csrrs a0,sstatus,zero
  jr ra

.global _csr_satp_read:
_csr_satp_read:
  csrrs a0,satp,zero
  jr ra

.global _csr_satp_write:
_csr_satp_write:
  csrrw zero,satp,a0
  jr ra
