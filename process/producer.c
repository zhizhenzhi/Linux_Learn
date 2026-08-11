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

    //不断接收控制台中的数据 发送到消息队列
    char write_buf[100];
    struct timespec time_info;
    while (1)
    {
        memset(write_buf,0,100);
        ssize_t read_count=read(STDIN_FILENO,write_buf,100);
        clock_gettime(0,&time_info);
        time_info.tv_sec+=5;

        if(read_count==-1)
        {
            perror("read");
            continue;
        }
        //如果接受到控制台接受到停止的消息  将EOF当作一条消息发送到消息队列
        else if(read_count== 0)
        {
            printf("EOF,exit...\n");
            char eof=EOF;
            if(mq_timedsend(mqdes,&eof,1,0,&time_info)==-1)
            {
                perror("mq_timedsend");
            }
            break;
        }
        //正常接受到控制台的可读信息
        if(mq_timedsend(mqdes,write_buf,strlen(write_buf),0,&time_info)==-1)
        {
            perror("mq_timedsend");
        }
        printf("从命令行接收到数据 已经发送给消息队列\n");
    }
    //关闭消息队列描述符
    close(mqdes);
    return 0;
}
