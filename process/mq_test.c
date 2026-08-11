#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    //创建消息队列
    struct mq_attr attr;
    //有用的参数 表示消息队列的容量
    attr.mq_flags=0;
    attr.mq_maxmsg=10;
    attr.mq_msgsize=100;
    attr.mq_curmsgs=0;
    char *mq_name="/mq";
    mqd_t mqdes=mq_open(mq_name,O_RDWR | O_CREAT,0664,&attr);

    if(mqdes == (mqd_t)-1)
    {
        perror("mqopen");
        exit(EXIT_FAILURE);
    }

    //创建父子进程
    pid_t pid =fork();
    if(pid<0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid ==0)
    {
        //子进程 等待接受消息队列中的消息
        char read_buf[100];
        struct timespec time_info;
        for (size_t i = 0; i < 10; i++)
        {
            //清空接受数据的缓冲区
            memset(read_buf,0,100);
            //设置等待数据的时间
            clock_gettime(0,&time_info);
            time_info.tv_sec+=5;
            //接受消息队列的消息打印到控制台
            if(mq_timedreceive(mqdes,read_buf,100,NULL,&time_info)==-1)
                perror("mq_timedreceive");
            printf("son process receive data: %s\n",read_buf);
        }
        
    }
    else
    {
        //父进程 发送消息到消息队列中
        char buf[100];
        struct timespec time_info;
        for (size_t i = 0; i < 10; i++)
        {
            //清空处理buf
            memset(buf,0,100);
            sprintf(buf,"father process %ld time send data\n",(i+1));
            //获取当前具体时间
            clock_gettime(CLOCK_REALTIME,&time_info);
            time_info.tv_sec+=5;
            //发送消息
            if(mq_timedsend(mqdes,buf,strlen(buf),0,&time_info)==-1)
                perror("mq_timedsend");
            printf("farther process sleep 1\n");
            sleep(1);
        }
        
        
    }

    //释放消息队列的引用
    close(mqdes);
    //清除消息队列只需要一次
    if(pid>0)
    mq_unlink(mq_name);
    return 0;
}
