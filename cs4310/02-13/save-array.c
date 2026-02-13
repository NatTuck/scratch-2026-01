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

    int fd = open("./array.mem", O_CREAT | O_TRUNC | O_RDWR, 0644);
    assert_ok(fd, "open");

    int rv = ftruncate(fd, size);
    assert_ok(rv, "ftruncate");

    int* xs = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    assert_ok((long)xs, "mmap");

    for (int ii = 0; ii < 10; ++ii) {
        // mov %rax, (xs, ii, 4)
        xs[ii] = ii * ii;
    }

    rv = munmap(xs, size);
    assert_ok(rv, "munmap");

    rv = close(fd);
    assert_ok(rv, "close");
    return 0;
}
