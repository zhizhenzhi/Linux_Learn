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
        printf("failed");
    else printf("success");
    return 0;
}
