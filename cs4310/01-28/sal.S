/*
void
swap(char* text, int ii, int jj)
{
    char tmp = text[ii];
    text[ii] = text[jj];
    text[jj] = tmp;
}
Vars and stuff:
 - text can stay in %rdi
 - ii is %rsi
 - jj is %rdx
 - tmp   %al    (8 bits of %rax)
 - tmp2  %cl    (8 bits of %rcx)
This is a leaf function (it doesn't call any other functions),
so we can safely keep everything in temporary registers.
*/
  .text
  .global swap
swap:

  mov (%rdi,%rsi,1), %al
  mov (%rdi,%rdx,1), %cl
  mov %cl, (%rdi,%rsi,1)
  mov %al, (%rdi,%rdx,1)

  ret

/*
void
reverse(char* text, int ii, int jj)
{
    if (ii >= jj) {
        return;
    }

    swap(text, ii, jj);
    reverse(text, ii + 1, jj - 1);
}
Vars:
 - text, ii, jj - stay in rdi, rsi, rdx
*/
  .global reverse
reverse:
  enter $0, $0
reverse_body:

  cmp %rdx, %rsi
  jge reverse_done

  push %rdi  // save temp regs
  push %rsi
  push %rdx
  sub $8, %rsp // align stack to 16 bytes
  // 3 args already in correct regs
  call swap
  add $8, %rsp // restore
  pop %rdx
  pop %rsi
  pop %rdi

  // text already correct
  add $1, %rsi
  sub $1, %rdx
  //call reverse
  //tail call optimization
  jmp reverse_body
  
reverse_done:
  leave
  ret


//char ltoa_buf[24];
  .data
  .global ltoa_buf
ltoa_buf:
  .zero 24

/*
char* ltoa(long xx, int* nn);
Vars:
  - xx, nn come in as rdi, rsi
  - ii is rcx
  - extra temps are r10, r11
{
    if (xx < 1) {
        ltoa_buf[0] = '0';
        ltoa_buf[1] = 0;
        *nn = 1;
        return ltoa_buf;
    }
*/
  .text
  .global ltoa
ltoa:
  enter $0, $0

  cmp $1, %rdi
  jnl ltoa_nonzero

  mov $ltoa_buf, %r10
  movb $'0', (%r10)
  inc %r10
  movb $0, (%r10)
  movl $1, (%rsi)
  jmp ltoa_done

/*
    int ii = 0;
    while (xx > 0) {
        // % and / use the div instruction
        // div hardcodes it's outputs
        //  - quotient goes in rax 
        //    (also rax is the thing that gets divided)
        //  - remainder goes in rdx
        ltoa_buf[ii] = '0' + xx % 10;
        xx = xx / 10;
        ii = ii + 1;
    }
*/
ltoa_nonzero:
  mov $0, %rcx
ltoa_while_cond:
  cmp $0, %rdi
  jng ltoa_while_done

  mov $0, %rdx
  mov %rdi, %rax
  mov $10, %r11
  div %r11
  // %rax = xx / 10
  // %rdx = xx % 10
  mov $ltoa_buf, %r10
  add $'0', %rdx
  mov %rdx, (%r10, %rcx, 1)
  mov %rax, %rdi
  jmp ltoa_while_cond

ltoa_while_done:

/*
    ltoa_buf[ii] = 0;
    *nn = ii;

    reverse(ltoa_buf, 0, ii - 1);

    return ltoa_buf;
}
*/
  mov $ltoa_buf, %r10
  movb $0, (%r10,%rcx,1)
  
  mov %ecx, (%rsi)

  
  mov $ltoa_buf, %rdi
  mov $0, %rsi
  mov %rcx, %rdx
  dec %rdx
  call reverse

ltoa_done:
  leave
  ret


/*
int
main(int argc, char* argv[])
{
    int sum = 0;
    for (int ii = 1; ii < argc; ++ii) {
        sum += strlen(argv[ii]);
    }

    int nn;
    char* buf = ltoa(sum, &nn);

    write(1, buf, nn);
    write(1, "\n", 1);

    return 0;
}
*/
