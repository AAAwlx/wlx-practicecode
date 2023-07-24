#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#define port 12345
void sys_error(char *p)
{
    perror(p);
    exit(0);
}
int main()
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        sys_error("socket()");
    }
    struct sockaddr_in sever;
    memset(&sever, 0, sizeof(sever));
    sever.sin_family = AF_INET;
    sever.sin_port = htons(port);
    sever.sin_addr.s_addr = htonl(INADDR_ANY);
    int opt = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    int ret = bind(sfd, (const struct sockaddr *)&sever, sizeof(sever));
    if (ret == -1)
    {
        sys_error("bind()");
    }
    ret = listen(sfd, 64);
    if (ret == -1)
    {
        sys_error("listen()");
    }
    int efd = epoll_create(100);
    if (efd == -1)
    {
        sys_error("epoll_creat()");
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sfd;
    ret = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &ev);
    if (ret == -1)
    {
        sys_error("epoll_clt");
    }
    struct epoll_event evs[1024];
    int size = sizeof(evs) / sizeof(struct epoll_event);
    int count=0;
    while (1)
    {
        int count = epoll_wait(efd, evs, size, -1);
        for (int i = 0; i < count; i++)
        {
            int curfd = evs[i].data.fd;
            if (curfd == sfd)
            {
                int cfd = accept(curfd, NULL, NULL);
                ev.data.fd = cfd;
                ev.events = EPOLLIN;
                ret = epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &ev);
                if (ret == -1)
                {
                    sys_error("epoll_clt");
                }
            }
            else
            {
                char buffer[256];
                memset(buffer,0,sizeof(buffer));
                int len=recv(curfd,buffer,sizeof(buffer),0);
                if(len==0){
                    printf("客户端已经断开了连接\n");
                    epoll_ctl(efd,EPOLL_CTL_DEL,curfd,NULL);
                    close(curfd);
                }else if (len>0)
                {
                    printf("客户端说%s\n",buffer);
                    send(curfd,buffer,len,0);
                }else
                {
                    sys_error("recv()");
                }
            }
            
        }
    }
    return 0;
}