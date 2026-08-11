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

void *read_write(void *arg){
    // 取出堆上分配的clientfd
    int client_fd = *(int *)arg;
    // 用完释放这个int
    free(arg);

    char *read_buf=NULL;
    char* write_buf=NULL;
    ssize_t count=0,send_count=0;

    read_buf=malloc(BUF_SIZE);
    write_buf=malloc(BUF_SIZE);

    // malloc失败：释放另一个已经分配成功的缓冲区
    if(!read_buf){
        perror("read_buf malloc");
        close(client_fd);
        free(write_buf);
        return NULL;
    }
    if(!write_buf){
        perror("write_buf malloc");
        close(client_fd);
        free(read_buf);
        return NULL;
    }

    while ((count = recv(client_fd,read_buf,BUF_SIZE-1,0)) > 0)
    {
        // recv读到数据，手动补字符串结束符
        read_buf[count] = '\0';
        printf("从客户端%d收到数据: %s\n",client_fd,read_buf);

        strcpy(write_buf,"收到\n");
        // send只发送有效字节，strlen获取真实长度
        send_count = send(client_fd,write_buf,strlen(write_buf),0);
        if(send_count < 0){
            perror("send");
            break;
        }
    }

    if(count < 0){
        perror("recv");
    }else if(count == 0){
        printf("客户端%d正常断开连接\n",client_fd);
    }

    close(client_fd);
    free(read_buf);
    free(write_buf);
    return NULL;
}

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr,client_addr;
    memset(&server_addr,0,sizeof(server_addr));
    memset(&client_addr,0,sizeof(client_addr));

    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(6666);

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    handle_error("socket",sockfd);

    // 设置端口复用，快速重启服务，避免bind失败
    int opt = 1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    int temp=bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    handle_error("bind",temp);

    int temp1=listen(sockfd,100);
    handle_error("listen",temp1);

    socklen_t cliaddr_len=sizeof(client_addr);
    while (1)
    {
        int clientfd=accept(sockfd,(struct sockaddr *)&client_addr,&cliaddr_len);
        handle_error("accept",clientfd);

        printf("与客户端 %s:%d 建立连接，fd=%d\n",
               inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),clientfd);

        // 关键：堆分配int，把fd传给子线程，解决栈变量覆盖bug
        int *pfd = malloc(sizeof(int));
        *pfd = clientfd;

        pthread_t pid_read_write;
        if(pthread_create(&pid_read_write,NULL,read_write,(void *)pfd) !=0 )
        {
            perror("pthread_create");
            free(pfd);
            close(clientfd);
            continue;
        }
        pthread_detach(pid_read_write);
    }

    close(sockfd);
    return 0;
}