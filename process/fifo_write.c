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
    if(mkfifo(pipe_path,0664) != 0 && errno !=17)
    {
        perror("mkfifo:");
        exit(EXIT_FAILURE);
    }
    //对有名管道的特殊文件 创建fd
    int fd=open(pipe_path,O_RDWR);
    if (fd==-1)
    {
        perror("open:");
        exit(EXIT_FAILURE);
    }
    char buf[100];
    ssize_t read_num;
    //读取控制台数据写入到管道中
    while ((read_num=read(STDIN_FILENO,&buf,100))>0)
    {
        write(fd,buf,read_num);
    }
    
    if(read_num<0)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("send data sucess\n");
    close(fd);
    //释放管道
    //清除特殊文件
    if(unlink(pipe_path) == -1)
    perror("unlink:");

    return 0;
}
