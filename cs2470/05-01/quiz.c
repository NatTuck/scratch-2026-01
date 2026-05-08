#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
handle_sigalrm(int _sig)
{
    const char* msg = "\nTOO SLOW!!\n";
    write(1, msg, strlen(msg));
    exit(0);
}

int
main(int argc, char* argv[])
{
    signal(SIGALRM, handle_sigalrm);
    alarm(5);

    printf("What's 2 + 2?\n");
    int answer;
    scanf("%d", &answer);

    if (answer == 4) {
        printf("Good\n");
    }
    else {
        printf("Nope\n");
    }

    return 0;
}
