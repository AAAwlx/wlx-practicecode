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
    memcpy(data,&len,sizeof(int));
    memcpy(data+4,massage,len);
    int ret=writen(fd,data,len+4);
    free(data);
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
        while (sendMsg(servefd,(char **)&massage,sizeof(massage))==1)
        {
            printf("收到了消息：%s",massage);
        }
        
    }
    close(servefd);
}