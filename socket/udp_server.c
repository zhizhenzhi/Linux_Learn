#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


#define handle_error(cmd,result)\
    if(result<0)                \
    {                           \
        perror(cmd);            \
        return -1;              \
    }

int main(int argc, char const *argv[])
{
    //使用udp协议完成客户端和服务端的通讯
    //EOF作为关闭的信号

    int sockfd,clientfd;
    char* buf=malloc(sizeof(char)*1024);
    struct sockaddr_in server_addr,client_addr;
    memset(&server_addr,0,sizeof(server_addr));
    memset(&client_addr,0,sizeof(client_addr));
        //填写服务端地址
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);//htonl: 主机字节序 → 网络大端字节序，网络传输必须统一字节序。
    server_addr.sin_port=htons(6666);

    //socket创建
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    handle_error("socket",sockfd);

    //服务端绑定地址
    socklen_t server_len=sizeof(server_addr);
    socklen_t client_len=sizeof(client_addr);
    int temp=bind(sockfd,(struct sockaddr*)&server_addr,server_len);
    handle_error("bind",temp);

    //收发数据
    do
    {
        memset(buf,0,1024);
        int temp=recvfrom(sockfd,buf,1024,0,(struct sockaddr *)&client_addr,&client_len);
        handle_error("recvfrom",temp);

        if (strncmp(buf,"EOF",3)!=0)
        {
            printf("接收到客户端%s %d信息%s\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),buf);
            strcpy(buf,"OK\n");
        }
        else
        printf("收到结束信息，准备关闭\n");

        int temp3=sendto(sockfd,buf,4,0,(struct sockaddr *)&client_addr,client_len);
        handle_error("sendto",temp3);
        
    } while (strncmp(buf,"EOF",3)!=0);
    free(buf);

    return 0;
}

