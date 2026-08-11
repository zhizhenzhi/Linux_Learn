#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
    char *shm_name="unnamed_sem_shm";
    int fd=shm_open(shm_name,O_CREAT | O_RDWR,0666);
    ftruncate(fd,sizeof(sem_t));
    sem_t *sem=mmap(NULL,sizeof(sem_t),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    sem_init(sem,1,0);
    pid_t pid =fork();
    if(pid<0)
    {
        perror("fork");
    }
    else if(pid==0)
    {
        sleep(1);
        printf("this is son\n");
        sem_post(sem);
    }
    else
    {
        sem_wait(sem);
        printf("this is father\n");
        waitpid(pid,NULL,0);
    }

    //回收资源
    if(pid>0)
    {
        if(sem_destroy(sem)==-1)
        perror("sem_destroy");
    }
    if(munmap(sem,sizeof(sem))==-1)
    perror("munmap");
    if(close(fd)==-1)
    {
        perror("close");
    }
    if(pid>0)
    {
        if(shm_unlink(shm_name)==-1)
            perror("shm_unlink");
    }
    return 0;
}
