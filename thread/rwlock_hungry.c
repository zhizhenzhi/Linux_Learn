#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
//静态初始化
//static pthread_rwlock_t rwlock=__PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t rwlock;
int shared_data=0;

void *lock_write(void *arg){
    //给多个线程写入添加写锁
    //同一时间只有只能由一个线程获取写锁 会造成两个线程顺序执行
    printf("我是%s 我要获取写锁\n",(char*)arg);
    pthread_rwlock_wrlock(&rwlock);
    int temp=shared_data+1;
    shared_data=temp;
    printf("%s unlock\t%d\n",(char*)arg,shared_data);
    //写入完成之后释放写锁
    pthread_rwlock_unlock(&rwlock);
    printf("我是%s 我释放了写锁\n",(char*)arg);
}
void *lock_read(void *arg){
    //读写锁中读是可以多个线程统一读取的
    printf("我是%s 我要获取读锁\n",(char*)arg);
    pthread_rwlock_rdlock(&rwlock);
    sleep(1);
    printf("%s\t%d\n",(char*)arg,shared_data);
    pthread_rwlock_unlock(&rwlock);
    printf("我是%s 我释放了读锁\n",(char*)arg);
}
int main(int argc, char const *argv[])
{
    //显示初始化读写锁
    pthread_rwlock_init(&rwlock,NULL);
    pthread_t write1,write2,reader1,reader2,reader3;
    pthread_create(&write1,NULL,lock_write,"write1");
    
    
    pthread_create(&reader1,NULL,lock_read,"reader1");
    pthread_create(&reader2,NULL,lock_read,"reader2");
    //在线程读取数据的时候，中间添加一个获取写锁的写操作
    pthread_create(&write2,NULL,lock_write,"write2");
    pthread_create(&reader3,NULL,lock_read,"reader3");
    //主线程等待创建的子线程运行完成
    pthread_join(write1,NULL);
    pthread_join(write2,NULL);
    pthread_join(reader1,NULL);
    pthread_join(reader2,NULL);
    pthread_join(reader3,NULL);
    //销毁读写锁
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
