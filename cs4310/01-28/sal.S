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
*/


/*
char ltoa_buf[24];

char*
ltoa(long xx, int* nn)
{
    if (xx < 1) {
        ltoa_buf[0] = '0';
        ltoa_buf[1] = 0;
        *nn = 1;
        return ltoa_buf;
    }

    int ii = 0;
    while (xx > 0) {
        ltoa_buf[ii] = '0' + xx % 10;
        xx = xx / 10;
        ii = ii + 1;
    }

    ltoa_buf[ii] = 0;
    *nn = ii;

    reverse(ltoa_buf, 0, ii - 1);

    return ltoa_buf;
}

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
