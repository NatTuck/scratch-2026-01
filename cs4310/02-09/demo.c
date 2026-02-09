
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct team {
    char name[20];
    int players;
    int wins;
} team;

void
print_wins(team* tt)
{
    tt->wins = 11;
    printf("%s won %d times.\n", tt->name, tt->wins);
}

int
main(int argc, char* argv[])
{
    team* panthers = malloc(sizeof(team));
    memset((*panthers).name, 0, 20);
    strncpy(panthers->name, "Panthers", 19);
    panthers->players = 20;
    panthers->wins = 10;

    print_wins(panthers);

    printf("%s won %d times.\n", panthers->name, panthers->wins);

    free(panthers);

    return 0;
}

typedef struct int4 {
    int data[4];
} int4;

int
sum(int size, int xs[size])
{
    int sum = 0;
    for (int ii = 0; ii < size; ++ii) {
        sum += xs[ii];
    }
    return sum;
}

int
main1(int argc, char* argv[])
{
    int xs[4] = { 1, 2, 3, 4 };

    for (int ii = 0; ii < (sizeof(xs) / sizeof(int)); ++ii) {
        printf("%d\n", xs[ii]);
    }

    printf("sum = %d\n", sum(4, xs));

    return 0;
}
