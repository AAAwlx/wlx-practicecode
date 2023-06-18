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
int writen(int fd,char *msg,int size){
    const char *buf=msg;
    int count=size;
    while (count>0)
    {
        int len=send(fd,buf,count,0);
        if(len==0){
            continue;
        }else if(len==-1){
            close(fd);
            return -1;
        }
        count-=len;
        buf+=len;
    }
}
int sendMsg(int fd,char *massage,int len){
    if(massage==NULL||fd<=0||len<=0);
    char *data=(char *)malloc(len+4);
    int netlen=htonl(len);
    memcpy(data,len,sizeof(int));
    memcpy(data+4,massage,len);
    int ret=writen(fd,data,len+4);
    free(data);
    return ret;
}
int main(int argc,char **argv)
{
    struct sockaddr_in serveradd;
    int clitefd,ret;
    char massage[MAXBUFFER];
    char line[MAXBUFFER];
    clitefd=socket(PF_INET,SOCK_STREAM,0);
    FILE *fp=fopen("~/123.txt",'r');
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
    while (fgets(massage, sizeof(massage), fp) != NULL)
    {
       sendMsg(clitefd,massage,sizeof(massage));
    }
    close(clitefd);
    return(EXIT_SUCCESS);

}