#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<error.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#define SERVERIP "127.0.0.1"
#define SERVEPORT 12345
#define MAXBUFFER 256
void sys_err(char *p)
{
    perror(p);
    exit(1);
}
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
int main()
{
    int clienfd,servefd;
    struct sockaddr_in clienaddr,serveaddr;
    char massage[MAXBUFFER]={0};
    char ip[40]={0};
    servefd=socket(PF_INET,SOCK_STREAM,0);
    if(servefd==0){
        sys_err("socket()");
    }
    bzero(&serveaddr,sizeof(serveaddr));
    serveaddr.sin_family=AF_INET;
    serveaddr.sin_port=SERVEPORT;
    inet_pton(AF_INET,SERVERIP,&serveaddr.sin_addr);
    int ret=bind(servefd,(struct sockaddr *)&serveaddr,sizeof(serveaddr));
    if(ret!=0){
        sys_err("bind()");
    }
    ret=listen(servefd,5);
    if(ret!=0){
        sys_err("listen()");
    }
    socklen_t cliensize=sizeof(clienaddr);
    while (1)
    {
        ret=accept(servefd,(struct sockaddr *)&clienaddr,&cliensize);
        printf("%s 连接到服务器 \n",inet_ntop(AF_INET,&clienaddr.sin_addr,ip,sizeof(ip)));
        if(ret<0){
            sys_err("accept()");
        }
        while (readMsg(servefd,(char **)&massage)==1)
        {
            printf("收到了消息：%s",massage);
        }
        
    }
    close(servefd);
}