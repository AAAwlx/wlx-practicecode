#ifndef _CLIENT_CLASS_H_
#define _CLIENT_CLASS_H_
//登陆页面
#define EXIT"0"//退出
#define SIGN_UP "1"//注册
#define  LOGIN"2"//登陆
#define Reset_Password "1"//找回密码
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
public:
    Clenit(int port, string ip)
    :server_port(port),server_ip(ip){};
    ~Clenit();
    void clirun();
    //登陆函数组
    void sign_menu(int cfd);
    int sign_up(int cfd);
    int login(int cfd);
    
    void main_mnue(int cfd,string ID);//主界面函数
    void privateChat(int cfd,string ID);
    void group_menu(int cfd,string ID);
    //好友管理函数组
    void friends_menu(int cfd,string ID);//
    void friendadd(int cfd,string ID);
    void ignorefriend(int cfd,string ID);
    void delfriend(int cfd,string ID);
    void viewfriend(int cfd,string ID);
    void file_menu(int cfd,string ID);
};
#endif
