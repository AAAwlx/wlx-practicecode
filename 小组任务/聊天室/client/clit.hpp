#ifndef _CLIENT_CLASS_H_
#define _CLIENT_CLASS_H_
//登陆页面
#define EXIT "0"//退出
#define SIGN_UP "1"//注册
#define  LOGIN "2"//登陆
#define Reset_Password "3"//找回密码
//主界面
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
#include<iostream>
using namespace std;
class Clenit
{
private:
   int server_port;
   string server_ip;
   int cfd;
public:
    Clenit(int port, string ip);
    ~Clenit();
    void clirun();
    //登陆函数组
    void sign_menu();
    int sign_up();
    int login();
    void resetpassword(string ID);
    void Exit();
    void main_mnue(string ID);//主界面函数
    void privateChat(string ID);
    void group_menu(string ID);
    
    //好友管理函数组
    void friends_menu(string ID);
    void friendadd(string ID);
    void ignorefriend(string ID);
    void delfriend(string ID);
    void viewfriend(string ID);
    void file_menu(string ID);
};
#endif
