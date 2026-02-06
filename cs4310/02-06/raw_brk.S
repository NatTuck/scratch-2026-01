
  .text
  .global raw_brk
raw_brk:
  enter $0, $0

  mov $12, %rax
  syscall

  leave
  ret
  
