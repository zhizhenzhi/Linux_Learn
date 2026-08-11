#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    FILE *file=fopen("/home/yang/LINUX/socket/buf.txt","w");

    //修改刷写模式
    if(setvbuf(file,NULL,_IONBF,0)!=0)
    perror("setvbuf");
    //文件写入是全缓冲 等待缓冲区满或者手动刷写
    fprintf(file,"hello");
    //手动刷写
    fflush(file);

    char *args[]={"/usr/bin/ping","-c","10","www.baidu.com",NULL};
    char *envs[]={NULL};
    execve(args[0],args,envs);
    perror("execve");
    return 0;
}
