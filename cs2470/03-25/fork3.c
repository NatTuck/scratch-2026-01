#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(int argc, char* argv[])
{
    int cpid;

    if ((cpid = fork())) {
        waitpid(cpid, 0, 0);
    }
    else {
        // child
        close(1);

        int fd = open("/tmp/stdout.txt", O_CREAT | O_APPEND | O_WRONLY, 0644);

        if ((cpid = fork())) {
            waitpid(cpid, 0, 0);
        }
        else {
            execlp("echo", "echo", "exec'd", "echo", NULL);
        }

        close(fd);
        return 0;
    }

    printf("Parent all done.\n");

    return 0;
}
