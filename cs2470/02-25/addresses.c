
#include <stdio.h>

long foo = 27;

int
main(int argc, char* argv[])
{
    long bar = 58;
    char* msg = "The teapot has landed.\n";

    printf("&foo = %p\n", &foo); // .data section
    printf("&bar = %p\n", &bar); // on the stack
    printf("main = %p\n", main);
    printf("&msg = %p\n", &msg);
    printf("msg = %p\n", msg);

    printf("&foo > &bar? %d\n", &foo > &bar);

    return 0;
}
