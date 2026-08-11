#include <stdio.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    // fopen("null.txt","r");
    // perror("error");
    fopen("/opt","a+");
    printf("errorno:%d\n",errno);
    perror("file open encouter problem");
    return 0;
}
