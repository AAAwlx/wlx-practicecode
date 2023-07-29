#include "public.hpp"
/*系统调用函数以及相应的错误处理函数*/
int Err::Socket(int domain, int type, int protocol)
{
    int sfd=socket(domain,type,protocol);
    if(sfd==-1){
        perror("socket()");
        exit(0);
    }
    return sfd;
}
void Err::Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int ret=bind(sockfd,addr, addrlen);
    if(ret!=0){
        perror("bind()");
        exit(0);
    }
}
void Err::Listen(int sockfd, int backlog)
{
    int ret=listen(sockfd,backlog);
    if(ret!=0){
        perror("listen()");
        exit(0);
    }
}
int Err::Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int cfd=accept(sockfd, addr, addrlen);
    if(cfd<0){
        perror("accept()");
        exit(0);
    }
    return cfd;
}
int Err::Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int ret = connect(sockfd, addr, addrlen);
    if(ret!=0){
        perror("connect()");
        exit(0);
    }
    return ret;
}
ssize_t Err::Read(int fd, void *buf, size_t count)
{
    ssize_t ret=read(fd,buf,count);
    if (ret<0)
    {
        if (!(errno == EAGAIN || errno == EWOULDBLOCK))
        {
            perror("write()");
            exit(0);
        }
    }
    return ret;
}
ssize_t Err::Write(int fd, const void *buf, size_t count)
{
    ssize_t ret=write(fd,buf,count);
    if (ret<0)
    {
        if (!(errno == EAGAIN || errno == EWOULDBLOCK))
        {
            perror("write()");
            exit(0);
        }
    }
    return ret;
}
ssize_t Err::Sendfile(int out_fd, int in_fd, off_t* offset, size_t count)
{
    int ret=sendfile(out_fd, in_fd, offset, count);
    if(ret!=0) {
        perror("sendfile()");
        exit(0);
    }
    return ret;
}
int Err::Epoll_create(int size)
{
    int efd = epoll_create(Epoll_size);
    if (efd == -1)
    {
        perror("epoll_creat()");
        exit(0);
    }
    return efd;
}
int Err::Epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)
{
    int count = epoll_wait(epfd,events,maxevents,timeout);
    if(count==-1){
        perror("epoll_wait()");
        exit(0);
    }
    return count;
}
int Err::Epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
{
    int ret = epoll_ctl(epfd, op, fd, event);
    if(ret==-1){
        perror("epoll_ctl()");
        exit(0);
    }
    return ret;
}
void Err:: Close(int fd)
{
    if(close(fd)){
        perror("close()");
        exit(0);
    }
}