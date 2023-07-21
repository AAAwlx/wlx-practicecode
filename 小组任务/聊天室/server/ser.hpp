#ifndef _SERVER_CLASS_H_
#define _SERVER_CLASS_H_
#define LOGIN "0"//登陆
#define SIGN_UP "1"//注册
#define EXIT "2"//退出
#define Reset_Password "1"//找回密码
//
#include<iostream>
#include<hiredis/hiredis.h>
using namespace std;
class Server
{
private:
    redisContext* user;//用户信息
    redisContext* Group;//群信息
    redisContext* P_massage;//私聊记录
    redisContext* G_massage;//群聊记录
public:
    Server(/* args */);
    ~Server();
};

Server::Server(/* args */)
{

}

Server::Server()
{
}
#endif