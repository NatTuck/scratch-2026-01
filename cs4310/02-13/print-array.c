#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>

void
assert_ok(long rv, char* call)
{
    if (rv == -1) {
        fprintf(stderr, "Failed call: %s\n", call);
        perror("Error:");
        exit(1);
    }
}

int
main(int argc, char* argv[])
{
    int size = 10 * sizeof(int);

    int fd = open("./array.mem", O_RDWR);
    assert_ok(fd, "open");

    int* xs = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    assert_ok((long)xs, "mmap");

    for (int ii = 0; ii < 10; ++ii) {
        printf("%d: %d\n", ii, xs[ii]);
    }

    int rv = munmap(xs, size);
    assert_ok(rv, "munmap");

    rv = close(fd);
    assert_ok(rv, "close");
    return 0;
}
