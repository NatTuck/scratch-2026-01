  .global main

  .text
// static int add2(int xx);
// - xx, first argument goes in %rdi
// - return value is left in %rax
add2:
  enter $0, $0

  mov %rdi, %rax
  // return xx + 2

  add $2, %rax

  leave
  ret

main:
  enter $0, $0

  mov $5, %rdi
  call add2
  // return value in %rax

  mov %rax, %rsi       // second arg is %rsi
  mov $out_fmt, %rdi   // first arg is %rdi
  mov $0, %al
  call printf

  leave
  ret

  .data
out_fmt: .string "5 + 2 = %d\n"
