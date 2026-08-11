#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //调用fork之前 代码都在父进程中运行
    printf("%d\n",getpid());


    //使用fork创建子进程
    /*
    不需要传参
    return：-1表示出错  返回成功两个结果，父进程中表示子进程的PID，子进程中显示为0
    */
    pid_t pid=fork();
    //从fork之后，所有的代码都是在父子进程中各自执行一次的
    // printf("%d\n",pid);
    if (pid<0)
    {
        printf("error\n");
        return 1;
    }else if(pid==0)
    {
        //执行单独子进程代码
        printf("%d\t%d\n",getpid(),getppid());
    }
    else
    //执行单独父进程代码
    printf("%d\t%d\n",getpid(),pid);
    
    return 0;
}
