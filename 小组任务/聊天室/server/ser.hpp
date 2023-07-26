#ifndef _SERVER_CLASS_H_
#define _SERVER_CLASS_H_
#define LOGIN "0"//登陆
#define SIGN_UP "1"//注册
#define EXIT "2"//退出
#define Reset_Password "1"//找回密码
//
#define EP0LL_SIZE 1024 
#include<iostream>

using namespace std;
class Server
{
private:
    int server_port;
    string server_ip;
    redisContext* Library;//启用一个redis库
    int lfd;//套接字 

    static vector<bool> fd_pthread; //套接字描述符的线程
    static vector<string> fd_ID;    //保存套接字对应的ID
    static vector<bool> fd_in;      //保存套接字描述符登录状态
    static vector<bool> fd_new;     //保存套接字是否为新连接上的
    static vector<bool> fd_arr;     //保存所有套接字描述符的连接状态，初始均为不连接的状态
    static vector<int> fd_bor;
public:
    Server(int port, string ip)
    :server_port(port),server_ip(ip){};
    ~Server();
    void serun();
    void thread_work(int cfd);
    bool sign_menu(int cfd);
    void sign_up(int cfd,Massage m);
    void login(int cfd,Massage m);
    void resetpassword(int cfd,Massage m);//找回密码
    void main_menu(int cfd);
};
#endif