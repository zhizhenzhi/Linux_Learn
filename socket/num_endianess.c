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
    unsigned short local_num=0x1f,network_num=0;
    //将主机字节序转化为网络字节序
    network_num=htons(0x1f);
    printf("%hx\n",network_num);
    local_num=ntohs(network_num);
    printf("%hx\n",local_num);
    return 0;
}
