#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void sigint_handler(int signum)
{
    printf("%d",signum);
    exit(signum);
}
int main(int argc, char const *argv[])
{
    signal(SIGINT,sigint_handler);
    while(1)
    {
        sleep(1);
        printf("1\n");
    }
    return 0;
}
