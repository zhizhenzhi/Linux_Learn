#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

sem_t *full;
sem_t *empty;

int shared_num;

int rand_num()
{
    srand(time(NULL));
    return rand();
}

void *producer(void *arg){
    for (size_t i = 0; i < 5; i++)
    {
        //获取信号量    empty为1 full为0 producer可以执行 consumer阻塞无法执行 wait使信号量-1,post使信号量+1
        sem_wait(empty);
        printf("%ld\n",i+1);
        sleep(1);
        shared_num=rand_num();
        sem_post(full);
    }
    
}
void *consumer(void *arg){
     for (size_t i = 0; i < 5; i++)
    {
        //获取信号量
        sem_wait(full);
        printf("%ld\n",i+1);
        sleep(1);
        printf("%d\n",shared_num);
        sem_post(empty);
    }
    
}
int main(int argc, char const *argv[])
{
    full =malloc(sizeof(sem_t));
    empty =malloc(sizeof(sem_t));

    //初始化信号量
    sem_init(empty,0,1);
    sem_init(full,0,0);

    pthread_t producer_id,consumer_id;
    pthread_create(&producer_id,NULL,producer,NULL);
    pthread_create(&consumer_id,NULL,consumer,NULL);

    pthread_join(producer_id,NULL);
    pthread_join(consumer_id,NULL);
    //摧毁信号量
    sem_destroy(empty);
    sem_destroy(full);
    return 0;
}
