#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    int val=123;

    pid_t pid =fork();

    if(pid<0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){
        val=321;
        printf("%d\t%p\n",val,&val);
    }
    else{
        sleep(1);
        printf("%d\t%p\n",val,&val);;
    }
    return 0;
}
