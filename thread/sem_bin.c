#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
sem_t bin_sem;
void *thread_function(void *arg) {
   sem_wait(&bin_sem);
   // 执行线程任务
   printf("hello\n");
   sem_post(&bin_sem);
}
int main() {
   int res;
   pthread_t a_thread;
   void *thread_result;
   // 初始化信号量，初始值为0
   res = sem_init(&bin_sem, 0, 0);
   if (res != 0) {
       perror("Semaphore initialization failed");
       exit(EXIT_FAILURE);
   }
   // 创建线程
   res = pthread_create(&a_thread, NULL, thread_function, NULL);
   if (res != 0) {
       perror("Thread creation failed");
       exit(EXIT_FAILURE);
   }
   // 等待线程结束
   res = pthread_join(a_thread, &thread_result);
   if (res != 0) {
       perror("Thread join failed");
       exit(EXIT_FAILURE);
   }
   // 销毁信号量
   sem_destroy(&bin_sem);
   return 0;
}