
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int ga = 12;
int* gb = 0;
int* gc = 0;

int
main(int argc, char* argv[])
{
    int opid = getpid();
    int ppid = getppid();

    gb = mmap(0, 4096, PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *gb = 100;

    gc = malloc(sizeof(int));
    *gc = 107;

    printf("opid = %d\n", opid);
    printf("ppid = %d\n", ppid);

    printf("Before, ga = %d, gb = %d, gc = %d\n", ga, *gb, *gc);

    int cpid;
    if ((cpid = fork())) { // case 1
        // parent process
        int pid = getpid();

        ga = 29;
        *gb = 207;
        *gc = 309;

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

    printf("After, ga = %d, gb = %d, gc = %d\n", ga, *gb, *gc);

    return 0;
}
