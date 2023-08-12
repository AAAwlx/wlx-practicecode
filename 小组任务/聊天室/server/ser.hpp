#ifndef _SERVER_CLASS_H_
#define _SERVER_CLASS_H_
//登陆页面
#define EXIT "0"//退出
#define SIGN_UP "1"//注册
#define  LOGIN "2"//登陆
#define Reset_Password "3"//找回密码
#define Historical_news "4"//用户上线后历史未处理消息
//主界面
#define PRIVATE "1"       //私聊
#define GROUP "2"         //群菜单
#define FRIENDS_MENU "3"  //好友管理
#define FILE_MANAGE "4"   //文件管理 
//文件管理
#define SEND_FILE "_sf"   //发文件
#define RECV_FILE "_rf"   //收文件
//好友界面
#define ADD_FRIEND "1"   //加好友
#define DEL_FRIEND "2"   //删好友
#define VIEW_FRIENDS "3" //查看好友
#define MAS_FRIEND "4"   //好友请求
#define IGN_FRIEND "5"   //屏蔽好友
#define REC_FRIEND "6"  
#define BE_FRIENDS "0"   //成为好友
//私聊界面
#define Direct_send "2"//直接发送
#define Pchat_space "1"//进入与xx用户的聊天空间
#define Chat_History "3"//查看与某用户的聊天历史
//群管理界面
#define JOIN_GROUP "1"   //群聊
#define ADD_GROUP "2"    //加入群聊
#define QUIT_GROUP "3"   //退出群聊
#define CREATE_GROUP "4" //创建群聊
#define VIEW_GROUP "5"   //查看群
#define MAN_GROUP "6"//管理菜单
#define GROUP_HISTORY "7"//查看历史记录    
//管理群
#define MAN_ADDGROUP "1"    //加群申请
#define MAN_VIEW "2"        //查看群信息
#define MAN_ADDMANAGER "3"  //添加管理
#define MAN_QUITMANAGER "4" //取消管理
#define MAN_QUITMEMBER "5"  //踢出成员
#define MAN_DELGROUP "6"    //解散该群
#define IGN_GROUP "7"
#define REC_GROUP "8"
#define TRA_GROUP "9"
#define MAN_ADDMEMBER "10"
#define EP0LL_SIZE 1024 
#include<iostream>
#include<hiredis/hiredis.h>
#include <vector>
#include"public.hpp"
using namespace std;
extern redisContext* Library;//启用一个redis库
extern std::unordered_map<std::string, int> user_cfd;
extern int user_ID;
extern std::atomic<int> cfd;
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
    
     
    Server(int port, string ip);
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
    static void friendrecover(int cfd,Massage m);
    //static void file_menu(int cfd);
   //
    static void privateChat(int cfd);
    static void directsend(int cfd,Massage m,string massage);
    static void pchatspace(int cfd,Massage m);
    static void chathistory(int cfd,Massage m);
    static void historicalnews(int cfd,string ID);
    //群
    static void group_menu(int cfd);
    static void create_group( int cfd); //创建群聊
    static void add_group(int cfd);     //申请入群
    static void quit_group(int cfd);    //退出群
    static void view_group(int cfd);    //查看群
    static void publicChat(int cfd);
    static void chat_forwarding(int cfd);
    static void manage_menu(int cfd);
    static void manage_menu0(int cfd);
    static void history_group(int cfd);
    //管理群
    static void man_addgroup(int cfd);          //入群请求
    static void man_view(int cfd);                //查看群成员
    static void man_addmanager(int cfd);  //添加管理员
    static void man_delmanager(int cfd);         //取消管理员
    static void man_delmember(int cfd);        //踢出成员
    static bool man_delgroup(int cfd);          //解散群
    static void ignoregroup(int cfd);//屏蔽群
    static void grouprecover(int cfd);//解除屏蔽
    static void transfer_group(int cfd);//转让群主
    static void man_addmember(int cfd);//添加成员
};

#endif