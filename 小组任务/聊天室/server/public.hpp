/*要用到的头文件以及要用到的系统调用函数*/
/*要用到的头文件以及要用到的系统调用函数*/
#ifndef _PUBLIC_H_
#define _PUBLIC_H_
#include <iostream>
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
#include <queue>
#include <gtest/gtest.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <mutex>
#include <functional>
#include <future>
#include <utility>
#include<list>
#include <map>
#include<hiredis/hiredis.h>
#include <condition_variable>
#define Epoll_size 500
#define SERVERPORT 8888
#define BUFFERSIZE 500//单个消息不能超过五百字
#define Blank_option "100"//当消息为普通消息而非请求
using namespace std;
using namespace Json;
//系统调用与错误处理函数
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
    static void Close(int fd);
};
//消息类
class Massage
{
private:
    string Option,To,From,Time;//消息选项
    Value Content;//消息被发送时打包好的内容
    string Package;//消息被接受时收到的字符串
    int Massage_size;
public:
    Massage(string option,Value content,string to,string from);
    Massage(string package);//服务器端包的初始化
    ~Massage();
    //序列化
    string Serialization();
    //反序列化
    string Deserialization(string s);
    
    auto takeMassage (string s);
};
//用户类
/*"User用来存储用户信息"*/
class User
{
private:
    static int User_count;
    string ID,Name,Pass,Question,Answer;
   
    std::mutex user_mtx;//对数据库进行写入或删除操作时的 
    redisContext* Library;
public:
    Value friend_List;
    Value group_List;
    User(string name,string pass,string question,string answer,redisContext* userm);
    User(string id,redisContext* userm);
    User(const User &other);
    string distribute_id();//分配用户id
    bool save_user();//保存用户信息
    string Inquire(string s);//查询用户信
    void add_friend(string friend_id);//添加好友
    void delete_friend(string friend_id);//删除好友
    void shield_friend(string friend_id);//屏蔽好友
    //void Revise();//修改用户信息
    ~User();
};
/*template <typename T>
class TaskQueue
{
private:
    queue<T> m_queue;
    mutex m_mutex;

public:
    TaskQueue();
    ~TaskQueue();
    void addTask(T &t);
    bool takeTask(T &t);
    bool empty();
    inline int taskNumber()
    {
        return m_queue.size();
    }
};
class ThreadPool
{
private:
    // 省略 ThreadWorker 类定义，因为它在 ThreadPool 类的私有内部

    bool m_shutdown;
    TaskQueue<function<void()>>  m_taskQ;
    vector<thread> m_threadsID;
    mutex m_conditional_mutex;
    condition_variable m_conditional_lock;
    pthread_t m_managerID;//管理者线程
    int m_minNum;
    int m_maxNum;
    int m_busyNum;
    int m_aliveNum;
    int m_exitNum;
    bool m_shutdown;
public:
    ThreadPool(int minNum, int maxNum)
    :m_shutdown(false),m_minNum(minNum),m_maxNum(maxNum),m_busyNum(0),m_aliveNum(minNum),m_threadsID(vector<thread>(maxNum)){};
    ~ThreadPool();
    void shutdown();
    void* worker();
    void manager();
    int getAliveNumber();
    int getBusyNumber();
    void threadExit();
    template <typename F, typename... Args>
    auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>;
};*/
#endif