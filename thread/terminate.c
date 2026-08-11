#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

//定义结构体接收线程结果
typedef struct result
{
    char *p;
    int len;
}Result;

void *red_thread(void *arg)
{
    //初始化result结构体
    Result *result= malloc (sizeof(Result));
    //解析传递的结果
    char code=*((char*) arg);
    char *ans=malloc(101);
    while (1)
    {
        fgets(ans,100,stdin);
        if(ans[0]==code)
        {
            free(ans);
            printf("red exit\n");
            char *redans=strdup("red goto newyear\n");
            result->p=redans;
            result->len=strlen(redans);
            pthread_exit((void*)result);
        }
        else
        {
            printf("red wait\n");
        }
    }
    
    
}
void * white_thread(void *arg){

    //初始化result结构体
    Result *result= malloc (sizeof(Result));
    //解析传递的结果
    char code=*((char*) arg);
    char *ans=malloc(101);
    while (1)
    {
        fgets(ans,100,stdin);
        if(ans[0]==code)
        {
            free(ans);
            printf("white exit\n");
            char *redans=strdup("white goto pair\n");
            result->p=redans;
            result->len=strlen(redans);
            pthread_exit((void*)result);
        }
        else
        {
            printf("white wait\n");
        }
    }
}
int main(int argc, char const *argv[])
{
    pthread_t pid_r;
    pthread_t pid_w;
    char red='r';
    char white='w';
    Result *red_result=NULL;
    Result *white_result=NULL;
    //创建线程
    pthread_create(&pid_r,NULL,red_thread,&red);
    pthread_create(&pid_w,NULL,white_thread,&white);

    //获取线程结果
    pthread_join(pid_r,(void **)&red_result);
    printf("red end %s\n",red_result->p);
    free(red_result->p);
    free(red_result);
    pthread_join(pid_w,(void **)&white_result);
    printf("white end %s\n",white_result->p);
    free(white_result->p);
    free(white_result);

    return 0;
}
