#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char *ch = malloc(100);
    fgets(ch,10,stdin);
    //从标准输入读取数据
    printf("你好:%s",ch);

    //标准输出
    fputs(ch,stdout);
    printf("\n");

    //错误输出
    fputs(ch,stderr);
    printf("\n");
    return 0;
}
