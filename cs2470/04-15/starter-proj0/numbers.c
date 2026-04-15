#include <stdio.h>

int
main(int argc, char* argv[])
{
    printf("%d\n", 644); // decimal
    printf("%d\n", 0644); // octal
    printf("%d\n", 0x644); // hexidemial
    printf("%d\n", 0b1010101); // binary
    return 0;
}
