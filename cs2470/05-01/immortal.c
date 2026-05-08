#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void
handle_sigint(int _sig)
{
    const char* msg = "\nCaught sigint.\n";
    write(1, msg, strlen(msg));
}

int
main(int argc, char* argv[])
{
    signal(SIGINT, handle_sigint);

    while (1)
        ;

    return 0;
}
