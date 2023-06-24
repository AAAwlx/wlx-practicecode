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
int readn(int fd,char *buf,int size)
{
    int count=size;
    char *pt=buf;
    while (count>0)
    {
        int len=recv(fd, pt, count, 0);
        if(len==-1){
            return -1;
        }else if(len==0){
            continue;
        }
        count-=len;
        pt+=len;
    }
    
}
int readMsg(int serverfd,char **massage)
{
    int len=0;
    readn(serverfd,(char*)&len,4);
    len=ntohl(len);
    char *buffer=(char *)malloc(len+1);
    int ret=readn(serverfd,buffer,len);
    if(ret!=len){
        close(serverfd);
        free(buffer);
        return -1;
    }
    buffer[len]='\0';
    *massage=buffer;
    return ret;
}
int main(int argc,char **argv)
{
    struct sockaddr_in serveradd;
    int clitefd,ret;
    char massage[MAXBUFFER];
    char line[MAXBUFFER];
    clitefd=socket(PF_INET,SOCK_STREAM,0);
    FILE *fp=fopen("~/123.txt","r");
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