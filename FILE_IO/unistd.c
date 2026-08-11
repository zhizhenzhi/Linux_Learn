#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    /*
    const char *__path:打开文件的路径
    int __oflag：打开文件的模式
        O_RDONLY：只读  O_WRONLY:只写   O_RDWR:读写模式 O_CREAT：如果不存在创建文件 O_APPEND：追加写模式    O_TRUNC:截断文件长度为0
    可变参数：用到O_CREAT时 创建文件的权限 0664
    open (const char *__path, int __oflag, ...)
    return：文件描述符  如果文件打开失败 返回-1 同时设置全局变量erro表示对应的错误
    */
   //linux操作系统有文件权限的保护
    int fd=open("io1.txt",O_RDONLY|O_CREAT,0664);
    if(fd==-1)
    printf("打开文件失败\n");
    return 0;
}
