#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    //fork之前
    int subprocess;
    printf("father\n");
    pid_t pid=fork();
    if (pid<0)
    {
        perror("fork:");
        return 1;
    }
    else if(pid==0)
    {
        char *args[]={"/usr/bin/ping","-c","10","www.baidu.com",NULL};
        char *envs[]={NULL};
        printf("son process %d ping 10\n",getpid());
        int exR=execve(args[0],args,envs);
        if(exR<0)
        {
            perror("execve");
            return 1;
        }
    }
    else
    {
        printf("father process %d wait son process %d\n",getpid(),pid);
        waitpid(pid,&subprocess,0);
    }

    printf("farther process wait son process suceess\n");
    return 0;
}
