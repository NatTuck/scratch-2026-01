#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(int argc, char* argv[])
{
    int opid = getpid();
    int opar = getppid();
    int cpid;

    printf("Hi, I'm %d, child of %d\n", opid, opar);

    if ((cpid = fork())) {
        // cpid != 0, this is the parent
        int pid1 = getpid();
        int par1 = getppid();

        printf("Hallo, I'm %d, child of %d\n", pid1, par1);
    }
    else {
        // cpid == 0, this is the child
        int pid2 = getpid();
        int par2 = getppid();

        printf("Ahoy! I'm %d, child of %d\n", pid2, par2);
    }

    printf("All done.\n");

    return 0;
}
