#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

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

        int num;
        while (read(pp[0], &num, sizeof(num)) > 0) {
            printf("%d\n", num);
        }

        close(pp[0]);
    }

    return 0;
}
