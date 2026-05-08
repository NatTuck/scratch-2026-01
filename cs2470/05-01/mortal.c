#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

volatile int done = 0;

void
handle_sigint(int _sig)
{
    const char* msg = "\nCaught sigint.\n";
    write(1, msg, strlen(msg));
    done = 1;
}

int
main(int argc, char* argv[])
{
    signal(SIGINT, handle_sigint);

    while (!done) {
        sleep(1);
        printf("beep\n");
    }

    return 0;
}
