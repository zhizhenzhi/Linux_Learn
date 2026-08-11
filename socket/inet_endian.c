#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char const *argv[])
{
    printf("192.168.31.113  的16进制为 %x %x %x %x\n",192,168,31,113);
    //声明结构体接收数据
    struct sockaddr_in server_addr;
    struct in_addr server_in_addr;

    in_addr_t server_in_addr_t;

    memset(&server_addr,0,sizeof(server_addr));
    memset(&server_in_addr,0,sizeof(server_in_addr));
    memset(&server_in_addr_t,0,sizeof(server_in_addr_t));

    //不推荐使用
    server_in_addr_t = inet_addr("192.168.31.113");
    printf("inet_addr:%x\n",server_in_addr_t);

    //将网络字节序转换为本地字节序
    inet_aton("192.168.31.113",&server_in_addr);
    printf("inet_aton: %x\n",server_in_addr.s_addr);

    inet_pton(AF_INET,"192.168.31.113",&server_in_addr.s_addr);
    printf("inet_pton: %x\n",server_in_addr.s_addr);

    printf("inet_ntoa %s\n",inet_ntoa(server_in_addr));

    printf("主机号%x\n",inet_lnaof(server_in_addr));
    printf("网络号%x\n",inet_netof(server_in_addr));

    server_addr.sin_addr=inet_makeaddr(inet_netof(server_in_addr),inet_lnaof(server_in_addr));
    printf("%s\n",inet_ntoa(server_addr.sin_addr));
    return 0;
}
