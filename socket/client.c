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

void *read_from_server(void *arg){
    //使用recv接收服务端发送的数据 打印到控制台
    char *read_buf=NULL;
    int client_fd=*(int *)arg;
    read_buf=malloc(sizeof(char)*1024);
    ssize_t count=0;
    if(!read_buf)
    {
        perror("malloc init:");
        return NULL;
    }
    
    //只要能接收到数据 正常使用 一直挂起
    while(count=recv(client_fd,read_buf,1024,0)){
        fputs(read_buf,stdout);
    }
    printf("server close\n");
    free(read_buf);
    return NULL;

}
void *write_to_server(void *arg){
    //接收控制台输入的信息 写出去
        char *write_buf=NULL;
    int client_fd=*(int *)arg;
    write_buf=malloc(sizeof(char)*1024);
    ssize_t count=0;
    if(!write_buf)
    {
        perror("malloc init:");
        return NULL;
    }
    while(fgets(write_buf,1024,stdin)!=NULL)
    {
        count=send(client_fd,write_buf,1024,0);
        if(count<0)
        perror("send");
    }
    printf("close\n");
    shutdown(client_fd,SHUT_WR);
    free(write_buf);
    return NULL;
}
int main(int argc, char const *argv[])
{
    int sockfd,clientfd;
    pthread_t pid_read,pid_write;
    struct sockaddr_in server_addr,client_addr;
    memset(&server_addr,0,sizeof(server_addr));
    memset(&client_addr,0,sizeof(client_addr));
        //填写客户端地址
    client_addr.sin_family=AF_INET;
    // server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    inet_pton(AF_INET,"192.168.31.113",&client_addr.sin_addr);
    client_addr.sin_port=htons(8888);

     //填写服务端地址
    server_addr.sin_family=AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
    server_addr.sin_port=htons(6666);
    
    //创建socket
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    handle_error("socket",sockfd);

    //绑定
    int temp=bind(sockfd,(struct sockaddr *)&client_addr,sizeof(client_addr));
    handle_error("bind",temp);

    //主动链接服务器
    int temp1=connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    handle_error("connect",temp1);

    printf("connect server %s %d\n",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port));


    //创建线程用于收消息
    pthread_create(&pid_read,NULL,read_from_server,(void *)&sockfd);
    //创建线程用于fa消息
    pthread_create(&pid_write,NULL,write_to_server,(void *)&sockfd);

    pthread_join(pid_read,NULL);
    pthread_join(pid_write,NULL);


    close(sockfd);
    return 0;
}
