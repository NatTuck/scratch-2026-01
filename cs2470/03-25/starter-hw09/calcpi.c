
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// produces a random double in the range 0 - 1
double
random_double()
{
    unsigned long aa = random();
    unsigned long bb = random();
    return ((aa << 31) ^ bb) * 0x1p-62;
}

double
time_now()
{
    struct timespec ts;
    int rv = clock_gettime(CLOCK_REALTIME, &ts);
    assert(rv == 0);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
}

int
main(int argc, char* argv[])
{
    assert(argc == 2);
    long pp = atol(argv[1]);
    assert(pp == 1);

    printf("Calculating pi using %ld procs\n", pp);

    long hits = 0;
    long trials = 0;

    srandom(getpid());

    double t0 = time_now();
    double t1;

    do {
        for (int jj = 0; jj < 1000; ++jj) {
            double x = random_double();
            double y = random_double();
            if (x * x + y * y <= 1.0) {
                hits++;
            }
        }
        trials += 1000;

        t1 = time_now();
    } while ((t1 - t0) < 20.0);

    double pi = 4.0 * hits / trials;
    printf("With %ld samples: π ≈ %.10f\n", trials, pi);
    printf("It should be: %.10f\n", M_PI);
    return 0;
}
