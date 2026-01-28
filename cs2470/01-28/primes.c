
#include <stdio.h>
#include <stdlib.h>

int is_prime(long xx, long* primes, long nn);

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        puts("Which prime do you want?");
        return 1;
    }

    long nn = atol(argv[1]);
    long primes[nn + 1];

    long xx = 1;
    long count = 0;
    do {
        xx++;
        if (is_prime(xx, primes, count)) {
            primes[count] = xx;
            count += 1;
        }
    } while (count <= nn);

    /*
    printf("%ld\n", (long)primes);
    printf("%ld\n", (long)(primes + 2));
    printf("%ld\n", (long)(&(primes[2])));
    */

    printf("The %ldth prime is %ld\n", nn, primes[nn]);

    return 0;
}
