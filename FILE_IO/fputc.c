#include <stdio.h>
int main(int argc, char const *argv[])
{
    /*  
    char *__restrict __filename:字符串表示要打开的文件名称
    const char *__restrict __modes：访问的模式
            1.r：只读模式
            2.w：只写模式   如果文件存在清空文件 不存在创建新文件
            3.a：只追加写模式   如果文件存在末尾追加写 如果不存在创建新文件
            4.r+：读写 文件必须存在 写入是从头一个覆盖
            5.w+：读写 
            6.a+：读追加模式
    return：FILE *结构体指针 表示一个文件 报错返回NULL
    FILE *foen (const char *__restrict __filename,
		    const char *__restrict __modes)
            */
    char *filename ="io.txt";
    FILE * ioFILE = fopen(filename,"w");
    if(ioFILE==NULL)
        printf("failed\n");
    else printf("打开文件success\n");

    /* int __c:ACSLL码对应的char
    FILE *__stream:打开的一个文件
    return：成功返回char
    int fputc (int __c, FILE *__stream)
    */
    int put_result=fputc(97,ioFILE);
    if(put_result==EOF)
        printf("写入文件失败\n");
    else
        printf("写入文件%c成功\n",put_result);

    /*const char *__restrict __s:需要写入的字符串
    FILE *__restrict __stream：打开的文件
    int fputs (const char *__restrict __s, FILE *__restrict __stream)
    */

    int puts_result=fputs(" where are you\n",ioFILE);
    if(puts_result==EOF)
    printf("puts faied\n");
    else
    printf("puts success\n");
    /*FILE *__stream:需要关闭的文件
    return：成功返回0,失败返回EOF（负数）通常关闭文件失败会直接报错
    int fclose (FILE *__stream)
    */

    int result=fclose(ioFILE);
    if(result==EOF)
        printf("failed\n");
    else if(result == 0)
        printf("关闭文件success\n");

    return 0;
}
