#ifndef _SERVER_CLASS_H_
#define _SERVER_CLASS_H_
#define LOGIN "2"//登陆
#define SIGN_UP "1"//注册
#define EXIT "0"//退出
#define Reset_Password "3"//找回密码
#define Historical_news "4"
#define FRIENDS_MENU "3"//好友菜单
#define PRIVATE "1"       //私聊
#define GROUP "2"         //群菜单
#define FRIENDS_MENU "3"  //好友管理
#define FILE_MANAGE "4"   //文件管理 
#define SEND_FILE "_sf"   //发文件
#define RECV_FILE "_rf"   //收文件
#define ADD_FRIEND "1"   //加好友
#define DEL_FRIEND "2"   //删好友
#define VIEW_FRIENDS "3" //查看好友
#define MAS_FRIEND "4"   //好友请求
#define IGN_FRIEND "5"   //屏蔽好友
#define BE_FRIENDS "0"   //成为好友
#define EP0LL_SIZE 1024 
#include<iostream>
#include<hiredis/hiredis.h>
#include <vector>
#include"public.hpp"
using namespace std;
extern redisContext* Library;//启用一个redis库
extern std::unordered_map<std::string, int> user_cfd;
extern int user_ID;
class Server
{
private:
    
    int server_port;
    string server_ip;
    int lfd;//套接字 
    static vector<bool> fd_pthread; //套接字描述符的线程
    static vector<string> fd_ID;    //保存套接字对应的ID
    static vector<bool> fd_in;      //保存套接字描述符登录状态
    static vector<bool> fd_new;     //保存套接字是否为新连接上的
    static vector<bool> fd_arr;     //保存所有套接字描述符的连接状态，初始均为不连接的状态
    static vector<int> fd_bor;
    //已经登陆的用户以及分配的套接字
public:
    
     
    Server(int port, string ip)
    :server_port(port),server_ip(ip){};
    ~Server();
    void serun();
    static void thread_work(int cfd);
    //登陆界面
    static bool sign_menu(int cfd);//账号主界面
    static void sign_up(int cfd,Massage m);//注册
    static void login(int cfd,Massage m);//登陆
    static void resetpassword(int cfd,Massage m);//找回密码
    //主界面
    static void main_menu(int cfd,string ID);
    //好友管理
    static void friends_menu(int cfd);//好友管理主界面
    static void friendadd(int cfd,Massage m);//添加好友
    static void ignorefriend(int cfd,Massage m);//屏蔽好友消息
    static void delfriend(int cfd,Massage m);//删除好友
    static void viewfriend(int cfd,Massage m); //查看好友在线状态
    static void friendrequests(int cfd,Massage m);//处理好友申请
    //
    static void file_menu(int cfd);
   
    static void historicalnews(int cfd,string ID);
    
};

#endif