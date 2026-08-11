#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    char *pipe_path="/tmp/myfifo";
    // if(mkfifo(pipe_path,0664) != 0)
    // {
    //     perror("mkfifo:");
    //     exit(EXIT_FAILURE);
    // }
    //对有名管道的特殊文件 创建fd
    int fd=open(pipe_path,O_RDONLY);
    if (fd==-1)
    {
        perror("open:");
        exit(EXIT_FAILURE);
    }
    char buf[100];
    ssize_t read_num;
    //读取管道数据打印到控制台
    while ((read_num=read(fd,&buf,100))>0)
    {
        write(STDOUT_FILENO,buf,read_num);
    }
    
    if(read_num<0)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    printf("receive data sucess\n");
    close(fd);

    return 0;
}
