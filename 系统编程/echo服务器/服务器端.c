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
int main(char argc,char **argv)
{
    struct  sockaddr_in serveraddr,clientaddr;//创建服务器端和客户端协议的结构体
    int serverfd, connfd;
    socklen_t clientsize;
    char massage[MAXBUFFER]={0};//
    char ip[40]={0};
    serverfd=socket(PF_INET,SOCK_STREAM,0);
    if(serverfd<0){
        perror("socket()");
        exit(-1);
    }
    bzero(&serveraddr,sizeof(serveraddr));//初始化结构体
    serveraddr.sin_family=AF_INET;//指定协议族
    serveraddr.sin_port=htons(SERVEPORT);
    inet_pton(AF_INET,SERVERIP,&serveraddr.sin_addr);
    int ret=bind(serverfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    if(ret!=0){
        close(serverfd);
        perror("bind()");
        exit(-1);
    }
    ret=listen(serverfd,5);
    if(ret!=0){
        close(serverfd);
        perror("listen()");
        exit(-1);
    }
    clientsize=sizeof(clientaddr);
    bzero(&clientaddr,sizeof(clientaddr));
    while (1)
    {
        connfd=accept(serverfd,( struct sockaddr *)&clientaddr,&clientsize);
        printf("%s 连接到服务器 \n",inet_ntop(AF_INET,&clientaddr.sin_addr,ip,sizeof(ip)));
        if(serverfd==-1){
            printf("accept error : %s\n", strerror(errno));
            continue;
        }
        while ((ret=read(connfd,massage,MAXBUFFER)))
        {
            write(connfd,massage,MAXBUFFER);
            bzero(massage,MAXBUFFER);
        }
        if(ret==0){
            printf("客户端关闭连接\n");    
        }else{
            printf("read error:%s\n",strerror(errno));
        }
        close(connfd);
    }
    close(serverfd);
}