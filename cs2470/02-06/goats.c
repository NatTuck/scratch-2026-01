
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct goat {
    char* name;
    char color[10];
    int age;
} goat;

void
print_goat(goat* gg)
{
    printf("goat %s: color %s, age %d\n",
        gg->name, gg->color, (*gg).age);
}

int
main(int argc, char* argv[])
{
    goat* bob = malloc(sizeof(goat));
    bob->name = "Bob";
    bob->age = 4;
    strncpy(bob->color, "navy blue or magenta-ish", 10);
    bob->color[9] = 0;

    printf("Size of goat = %ld\n", sizeof(goat));
    print_goat(bob);

    free(bob);
    return 0;
}
