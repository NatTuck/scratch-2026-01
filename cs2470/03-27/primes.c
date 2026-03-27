#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void
filter(int in_fd)
{
    int prime;
    int num;
    int out_fd = -1;
    int pp[2];

    read(in_fd, &prime, sizeof(prime));
    // printf("%d (%d) got its prime\n", getpid(), prime);
    printf("%d\n", prime);

    while (read(in_fd, &num, sizeof(num)) > 0) {
        // printf("%d (%d) got %d\n", getpid(), prime, num);

        if (num % prime == 0) {
            // printf("%d (%d) dropped %d\n", getpid(), prime, num);
            continue;
        }

        if (out_fd == -1) {
            pipe(pp);

            if (fork()) {
                // printf("%d (%d) spawned child\n", getpid(), prime);
                out_fd = pp[1];
                close(pp[0]);
            }
            else {
                close(pp[1]);
                filter(pp[0]);
                return;
            }
        }

        write(out_fd, &num, sizeof(num));
    }

    close(in_fd);
    if (out_fd != -1) {
        close(out_fd);
    }
    wait(0);
}

int
main(int argc, char* argv[])
{
    assert(argc == 2);
    int nn = atoi(argv[1]);

    int pp[2];
    pipe(pp);

    if (fork()) {
        // parent
        // pp[1] is the write end
        close(pp[0]);

        for (int ii = 2; ii < nn; ++ii) {
            write(pp[1], &ii, sizeof(ii));
        }

        close(pp[1]);
        wait(0);
    }
    else {
        // child
        // pp[0] is the read end
        close(pp[1]);

        filter(pp[0]);

        close(pp[0]);
    }

    return 0;
}
