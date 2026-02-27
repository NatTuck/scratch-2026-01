
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int ga = 12;

int
main(int argc, char* argv[])
{
    int opid = getpid();
    int ppid = getppid();

    printf("opid = %d\n", opid);
    printf("ppid = %d\n", ppid);

    printf("Before, ga = %d\n", ga);

    int cpid;
    if ((cpid = fork())) { // case 1
        // parent process
        int pid = getpid();

        ga = 29;

        printf("(1) opid = %d\n", opid);
        printf("(1) ppid = %d\n", ppid);
        printf("(1) cpid = %d, %p\n", cpid, &cpid);
        printf("(1) pid = %d\n", pid);

        sleep(1);
    }
    else { // case 2
        // child process
        int pid = getpid();

        printf("(2) opid = %d\n", opid);
        printf("(2) ppid = %d\n", ppid);
        printf("(2) cpid = %d\n", cpid);
        printf("(2) pid = %d\n", pid);

        sleep(1);
    }

    printf("After, ga = %d\n", ga);

    return 0;
}
