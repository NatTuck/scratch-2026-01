#include <stdio.h>

int
main(int argc, char* argv[])
{
    char aa = 'a';
    char* text = "hello";

    printf("aa = %c\n", aa);
    printf("text = %s\n", text);
    printf("text start = %c\n", *text);

    text = text + 1;

    printf("text start = %c\n", *text);

    return 0;
}
