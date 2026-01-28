#include <math.h>

int
is_prime(long xx, long* primes, long size)
{
    int max_prime = (int)(1 + sqrt(xx));

    for (int ii = 0; ii < size; ++ii) {
        if (*(ii + primes) > max_prime) {
            break;
        }
        if (xx % ii[primes] == 0) {
            return 0;
        }
    }

    return 1;
}
