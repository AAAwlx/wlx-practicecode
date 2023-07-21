/*要用到的头文件以及要用到的系统调用函数*/
#ifndef _NET_WRAP_H_
#define _NET_WRAP_H_
#include<iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <string.h>
#include <thread>
#include <algorithm>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <vector>
#include<gtest/gtest.h>
#define Epoll_size 500
#define SERVERPORT 8888
#define BUFFERSIZE 500//单个消息不能超过五百字
#define Blank_option 100//当消息为普通消息而非请求
using namespace std;
using namespace Json;
class Err
{  
public:
    static int Socket(int domain, int type, int protocol);
    static void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    static void Listen(int sockfd, int backlog);
    static int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    static int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    static ssize_t Read(int fd, void *buf, size_t count);
    static ssize_t Write(int fd, const void *buf, size_t count);
    static ssize_t Sendfile(int out_fd, int in_fd, off_t* offset, size_t count);
    static int Epoll_create(int size);
    static int Epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
    static int Epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    static void Colse(int fd);
};
class Massage
{
private:
    string Option,To,From;//消息选项
    Value Content;//消息被发送时打包好的内容
    string Package;//消息被接受时收到的字符串
    Value info;
public:
    Massage(string option,Value content,string to,string from)//客户端包的初始化
    :Option(option),Content(content),To(to),From(from){};
    Massage(string package)
    :Package(package){};//服务器端包的初始化
    ~Massage();
    //序列化
    string Serialization();
    //反序列化
    string Deserialization(string s);
    
};
#endif