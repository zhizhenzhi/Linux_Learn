#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    int pipefd[2];
    // 将程序传递进来的第一个命令行参数 通过管道传输给子进程
    if (argc!=2)
    {
        fprintf(stderr,"%s:请填写需要传递的信息\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    //创建管道
    if(pipe(pipefd)==-1)
    {
        perror("create pipe failed");
        exit(EXIT_FAILURE);
    }

    pid=fork();
    if(pid<0)
    {
        perror("son process create failed\n");
        exit(EXIT_FAILURE);
    }
    else if(pid==0)
    {
        //子进程 读取管道的数据 打印到控制台
        close(pipefd[1]);
        char *str ="son proocess receive information\n";
        write(STDOUT_FILENO,str,strlen(str));
        char buf;
        while(read(pipefd[0],&buf,1)>0)
        {
            write(STDOUT_FILENO,&buf,1);
        }
        write(STDOUT_FILENO,"\n",1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    }
    else
    {
        //父进程 写入管道数据 提供给子进程
        close(pipefd[0]);
        printf("father process %d give\n",getpid());
        write(pipefd[1],argv[1],strlen(argv[1]));
        close(pipefd[1]);
        waitpid(pid,NULL,0);
        exit(EXIT_SUCCESS);
    }
    return 0;
}
