#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
check_rv(int rv)
{
    if (rv == -1) {
        perror("fail");
        exit(1);
    }
}

int
main(int argc, char* argv[])
{
    int rv;

    // octal permissions:
    // regular files are 0644
    // directories and executables should be 0755

    int fd = open("/tmp/stderr.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    check_rv(fd);

    // stdin, stdout, sterr

    // file descriptor 0 = stdin
    // file descriptor 1 = stdout
    close(2); // 2 = stderr
    dup(fd);

    fprintf(stderr, "Hello, redirect.\n");

    return 0;
}
