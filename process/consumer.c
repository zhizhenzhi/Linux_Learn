#include <stdio.h>
#include <mqueue.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

    //不断接受消息队列中的数据，发送到控制台
    char read_buf[100];
    struct timespec time_info;
    while (1)
    {
        memset(read_buf,0,100);
        clock_gettime(0,&time_info);
        time_info.tv_sec+=15;
        if(mq_timedreceive(mqdes,read_buf,100,NULL,&time_info)==-1)
        {
            perror("mq_timedreceive");
        }
        if(read_buf[0]==EOF)
        {
            printf("END\n");
            break;
        }
        //正常接受到来自生产者的消息队列的信息
        printf("receive data %s\n",read_buf);
    }
    //关闭消息队列描述符
    close(mqdes);
    mq_unlink(mq_name);
    return 0;
}
