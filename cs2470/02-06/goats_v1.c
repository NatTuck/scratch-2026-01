
#include <stdio.h>
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

goat
mkgoat(char* name, char* color, int age)
{
    goat gg;
    gg.name = name;
    gg.age = age;
    strncpy(color, "green", 10);
    gg.color[9] = 0;
    return gg;
}

int
main(int argc, char* argv[])
{
    goat bob = mkgoat("Bob", "navy blue", 4);

    printf("Size of goat = %ld\n", sizeof(goat));
    print_goat(&bob);

    return 0;
}
