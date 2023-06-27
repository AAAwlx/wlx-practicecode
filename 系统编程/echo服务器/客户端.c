#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#define SERVERIP "127.0.0.1"
#define SERVEPORT 12345
#define MAXBUFFER 256
int main(int argc,char **argv)
{
    struct sockaddr_in serveradd;
    int clitefd,ret;
    char massage[MAXBUFFER];
    clitefd=socket(PF_INET,SOCK_STREAM,0);
    if (clitefd<0)
    {
        printf("socket error:%s\n",strerror(errno));
        exit(-1);
    }
    bzero(&serveradd,sizeof(serveradd));
    serveradd.sin_family=AF_INET;
    serveradd.sin_port=htons(SERVEPORT);
    inet_pton(AF_INET,SERVERIP,&serveradd.sin_addr);
    ret=connect(clitefd,( struct sockaddr *)&serveradd,sizeof(serveradd));
    if(ret!=0){
        perror("connect");
        exit(-1);
    }
    while (1)
    {
        bzero(massage,sizeof(massage));
        scanf("%s",massage);
        send(clitefd,massage,MAXBUFFER,0);
        bzero(massage,sizeof(massage));
        recv(clitefd,massage,MAXBUFFER,0);
        printf("echo:%s\n",massage);
    }
    close(clitefd);
    return(EXIT_SUCCESS);

}