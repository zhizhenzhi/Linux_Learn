#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char *name="father";
    printf("%s\t%d\n",name,getpid());

    pid_t pid=fork();
    if(pid==1)
    {
      printf("son creat failed\n");
      exit(EXIT_FAILURE);
    }else if(pid==0)
    {
        //子进程跳转到另一个程序
        char *new_name="son";
        char *args[]={"/home/yang/LINUX开发/process/erlou",new_name,NULL};
        char *envs[]={NULL};
        int exR=execve(args[0],args,envs);
        if(exR==-1)
        {
            printf("son jump failed\n");
            return 1;
        }
    }
    else
    {
        sleep(1);
        //父进程
        printf("father%d\tson%d\n",getpid(),pid);
    }
  
    return 0;
}
