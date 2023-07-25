#ifndef _CLIENT_CLASS_H_
#define _CLIENT_CLASS_H_
//登陆页面
#define LOGIN "0"//登陆
#define SIGN_UP "1"//注册
#define EXIT "2"//退出
#define Reset_Password "1"//找回密码
//主界面
#define PRIVATE "1"       //私聊
#define GROUP "2"         //群菜单
#define FRIENDS_MENU "3"  //好友管理
#define FILE_MANAGE "4"   //文件管理 
#define SEND_FILE "_sf"   //发文件
#define RECV_FILE "_rf"   //收文件
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
    void sign_menu(int cfd);
    int sign_up(int cfd);
    int login(int cfd);
    void main_mnue(int cfd,string ID);
    void privateChat(int cfd,string ID);
    void group_menu(int cfd,string ID);
    void friends_menu(int cfd,string ID);
    void file_menu(int cfd,string ID);
};
#endif
