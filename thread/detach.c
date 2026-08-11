#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *task(void *arg)
{
    printf("start");
    sleep(2);
    printf("\tend");
    return NULL;
}
int main(int argc, char const *argv[])
{
    //创建线程
    pthread_t tid;
    pthread_create(&tid,NULL,task,NULL);
    //使用detach标记会等待线程完成之后回收相关资源
    pthread_detach(tid);
    printf("1");
    sleep(5);
    
    return 0;
}
