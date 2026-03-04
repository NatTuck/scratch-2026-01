
#include <stdio.h>

#include "expr.h"

int
main(int argc, char* argv[])
{
    char buffer[100];

    while (fgets(buffer, 100, stdin)) {
        expr* ee = parse(buffer);
        print_expr(ee);
        printf("\n");
    }

    return 0;
}
