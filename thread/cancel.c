#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *task(void *arg)
{
    printf("start\n");
    printf("working\n");
    // sleep(1);

    //禁用取消响应
    // pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);

    //异步取消，什么时候收到此消息，什么是进行取消操作 
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    int i=0;
   while (1)
    {
        printf("%d\n",i++);
    }
    
    //人为调用取消点函数
    // pthread_testcancel();
    printf("end\n");
    return NULL;
}
int main(int argc, char const *argv[])
{
    //创建线程
    pthread_t tid;
    pthread_create(&tid,NULL,task,NULL);
    //取消子线程
    if(pthread_cancel(tid)!=0)
    {
        perror("pthread_cancel");
    }
    void *res;//res不是野指针，join对他赋值之前并未进行解引用
    //pthread_cancel只是发出一个停止的命令
    //join阻塞主线程，一直等待子线程运行结束
    pthread_join(tid,&res);
    if(res==PTHREAD_CANCELED)
    {
        printf("cancel successful\n");
    }
    else
    {
        printf("failed");
    }
    return 0;
}
