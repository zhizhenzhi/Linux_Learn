#include <stdio.h>  // 用于标准输入输出  
#include <stdlib.h>  // 用于常用库函数，如内存分配  
#include <string.h>  // 用于字符串操作函数  
#include <unistd.h>  // 用于底层系统调用，如fork()  
#include <sys/mman.h>  // 用于内存映射和信号量等系统调用  
#include <sys/wait.h>  // 用于等待子进程  
#include <semaphore.h>  // 用于信号量操作  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/shm.h>  
#include <fcntl.h>  
  
int main(){  
    int shm;  // 共享内存标识符  
    key_t key;  // 用于创建共享内存的键值  
    pid_t pid;  // 进程ID  
    sem_t * sem=sem_open("/my_semaphore", O_CREAT, 0666, 1);  // 创建或打开一个信号量，初始值为1  
   
    char * buff;  // 指向共享内存的指针  
    key= ftok(".", 'R');  // 使用文件系统中的唯一键值创建键，用于创建共享内存对象  
    shm=shmget(key,1024,0666|IPC_CREAT);  // 获取共享内存标识符，如果需要则创建共享内存 ,返回共享内存标识符 shmid 
    /*
    shmid：shmget 返回的 id
    shmaddr：指定挂载到哪个虚拟地址，填NULL让操作系统自己选地址（绝大多数场景这么写）
    shmflg：0 代表可读可写；SHM_RDONLY 代表只读挂载
    return:返回共享内存虚拟地址起始指针
    */
    buff=(char*)shmat(shm,NULL,0);  
   
    pid=fork();  // 创建子进程  
    if(pid<0){  // 如果fork()失败  
        perror("创建进程失败");  // 打印错误信息  
    }  
    else if(pid==0){  // 子进程代码块  
        printf("这是子进程\n");  
        sem_wait(sem);  // 子进程等待信号量，确保父进程先执行  
        printf("子进程锁住资源\n");  
        strcpy(buff,"你好,新年快乐");  // 向共享内存写入数据  
        printf("%s\n",buff);  // 打印共享内存中的数据  
        sem_post(sem);  // 子进程释放信号量，允许其他进程继续执行  
        printf("子进程释放资源\n");  
    }  
    else{  // 父进程代码块  
            printf("这是父进程\n");  
            sleep(1);  // 父进程等待1秒，确保子进程先执行  
            sem_wait(sem);  // 父进程等待信号量，确保子进程已经执行完毕  
            printf("父进程锁住资源\n");  
            printf("%s\n",buff);  // 打印共享内存中的数据  
            sem_post(sem);  // 父进程释放信号量，允许其他进程继续执行  
            printf("父进程释放资源\n");  
    }  
    sem_close(sem);  // 关闭信号量  
    sem_unlink("/my_semaphore");  // 删除信号量对象  
    shmdt(buff);  // 断开共享内存的连接，使其可以被系统回收  
    shmctl(shm,IPC_RMID,NULL);  // 删除共享内存对象  
}