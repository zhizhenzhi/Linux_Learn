#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *ioFILE=fopen("io.txt","r");
    if(ioFILE==NULL)
    printf("不能打开不存在的分支\n");

    /*
    FILE *__stream：打开的文件
    return：读取到的一个字节
    int fgetc (FILE *__stream) __nonnull ((1));
    */
    // char c=fgetc(ioFILE);
    // while (c!=EOF)
    // {
    //     printf("%c",c);
    //     c=fgetc(ioFILE);
    //     /* code */
    // }
    
    /*
    char *__restrict __s:接受读取到的字符串
    int __n：接受数据的长度
    return:成功返回字符串 失败返回NULL
    fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
    */
   char buffer[100];
    while (fgets(buffer,sizeof(buffer),ioFILE))
    {
        printf("%s",buffer);
    }

    int closeR = fclose(ioFILE);
    if(closeR==EOF)
    printf("关闭失败\n");
    return 0;
}
