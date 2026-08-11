#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *ioFILE=fopen("io.txt","r");
    if(ioFILE==NULL)
    printf("不能打开不存在的分支\n");

    /*
    const char *__restrict __format:带有格式化的字符串（固定格式接受）
    可变参数：填写格式化的字符串（接受数据提前声明的变量）
    extern int fscanf (FILE *__restrict __stream,
		   const char *__restrict __format, ...) __wur __nonnull ((1));
    */
   char name[50];
   int age;
   char wife[50];
    int scanfR=fscanf(ioFILE,"%s %d %s",name,&age,wife);
    if(scanfR!=EOF)
    printf("%s%d爱上%s\n",name,age,wife);



    int closeR = fclose(ioFILE);
    if(closeR==EOF)
    printf("关闭失败\n");
    return 0;
}
