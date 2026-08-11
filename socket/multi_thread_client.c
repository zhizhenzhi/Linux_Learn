#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define handle_error(cmd,result)\
    if(result<0)                \
    {                           \
        perror(cmd);            \
        return -1;              \
    }

#define BUF_SIZE 1024

//子线程：专门接收服务器返回的数据
void *recv_server(void *arg)
{
    int fd = *(int *)arg;
    free(arg);
    char buf[BUF_SIZE];
    ssize_t ret;

    while( (ret = recv(fd, buf, BUF_SIZE-1, 0)) > 0 )
    {
        buf[ret] = '\0';
        printf("【服务端回复】%s", buf);
    }

    if(ret == 0)
    {
        printf("\n服务端断开连接\n");
    }
    else if(ret <0)
    {
        perror("recv");
    }
    close(fd);
    return NULL;
}


int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));

    //填写服务端信息，和服务端端口保持一致 6666
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6666);
    // 127.0.0.1本机回环地址
    if(inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        return -1;
    }

    //创建socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    handle_error("socket", sockfd);

    //连接服务器
    int ret = connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    handle_error("connect", ret);
    printf("连接服务端成功，可以输入消息发送:\n");

    //线程传参：堆分配sockfd
    int *pfd = malloc(sizeof(int));
    *pfd = sockfd;

    pthread_t tid;
    if(pthread_create(&tid,NULL,recv_server,pfd) !=0)
    {
        perror("pthread_create");
        free(pfd);
        close(sockfd);
        return -1;
    }
    pthread_detach(tid);

    //主线程：读取键盘输入，发送给服务端
    char input_buf[BUF_SIZE];
    while(fgets(input_buf,BUF_SIZE,stdin) != NULL)
    {
        send(sockfd, input_buf, strlen(input_buf),0);
    }

    close(sockfd);
    return 0;
}