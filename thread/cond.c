#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define buffer_size 5
int buffer[buffer_size];
int count=0;

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

void *write(void *arg){
    int item=1;
    while (1)
    { 
        pthread_mutex_lock(&mutex); //每轮加锁
        
        //缓冲区满就等待
        while (count==buffer_size)
        {
            //释放互斥锁，此线程阻塞，等待别的线程发送信号
            pthread_cond_wait(&cond,&mutex);
        }
        buffer[count]=item;
        count++;
        printf("produce: %d\n",item);
        item++;
        pthread_cond_signal(&cond); //唤醒消费者
        
        pthread_mutex_unlock(&mutex); //每轮释放锁
        usleep(200000); //模拟生产耗时
    }
}

void *read(void *arg){ 
    while (1)
    {
        pthread_mutex_lock(&mutex);
        
        while (count==0)
        {
            pthread_cond_wait(&cond,&mutex);
        }
        count--;
        int val = buffer[count];
        printf("consume: %d\n",val);
        //唤醒生产者    推荐先唤醒再释放锁是因为惊群效应 如果有三个线程都在cond等待队列 三个线程进行竞争 只有一个能拿到锁 一次唤醒一大堆线程又休眠 浪费CPU
        pthread_cond_signal(&cond);
        
        pthread_mutex_unlock(&mutex);
        usleep(300000); //模拟消费耗时
    }
}

int main(int argc, char const *argv[])
{
    pthread_t write_thread,read_thread;
    pthread_create(&write_thread,NULL,write,NULL);
    pthread_create(&read_thread,NULL,read,NULL);

    pthread_join(write_thread,NULL);
    pthread_join(read_thread,NULL);
    return 0;
}