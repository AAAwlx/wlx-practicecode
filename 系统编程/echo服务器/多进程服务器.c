#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#define SERVERIP "127.0.0.1"
#define MAXBUFFER 256
#define SERVEPORT 12345
int main()
{
    struct sockaddr_in severaddr, clientaddr;
    int severfd,clientfd;
    char massage[MAXBUFFER]={0};
    char ip[40]={0};
    pid_t pid;
    severfd=socket(PF_INET,SOCK_STREAM,0);
    if (severfd<0)
    {
        perror("scoket()");
        exit(-1);
    }
    bzero(&severaddr,sizeof(severaddr));
    severaddr.sin_family=PF_INET;
    severaddr.sin_port=htons(SERVEPORT);
    inet_pton(AF_INET,SERVERIP,&severaddr.sin_addr);
    int ret=bind(severfd,(struct sockaddr*)&severaddr,sizeof(severaddr));
    if (ret!=0)
    {
        perror("bind()");
        exit(-1);
    }
    listen(severfd,5);
    while (1)
    {
        clientfd=accept(severfd,(struct sockaddr *)&clientaddr,clientfd);
        printf("%s 连接到服务器 \n",inet_ntop(AF_INET,&clientaddr.sin_addr,ip,sizeof(ip)));
        if((pid=fork())<0){
            perror("fork()");
            exit(-1);
        }else if(pid>0){
            close(clientfd);
            continue;
        }else{
            close(severfd);
            recv(clientfd,massage,256,0);
            printf("1");
            printf("%s",massage);
            send(clientfd,massage,MAXBUFFER,0);
            bzero(massage,MAXBUFFER);
            close(severfd);
            exit(0);
            
            if(ret==0){
                printf("客户端关闭连接\n");
            }else{
                printf("read error:%s\n",strerror(errno));
            }
        }   
    }
    close(severfd);  
    return 0;
}