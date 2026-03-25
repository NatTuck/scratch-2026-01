  .global getsp
  .global getbp

getsp:
  mov %rsp, %rax
  ret

getbp:
  mov %rbp, %rax
  ret
