#ifndef _CLIENT_CLASS_H_
#define _CLIENT_CLASS_H_
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
#define BE_FRIENDS "0"   //已经是好友
//私聊界面
#define Direct_send "2"//直接发送
#define Pchat_space "1"//进入与xx用户的聊天空间
#define Chat_History "3"//查看与某用户的聊天历史
#include<iostream>
#include <atomic>
using namespace std;


extern std::atomic<bool> stopFlag;
void thread_recv(const std::string& ID, int cfd, const std::string& chatobject);
class Clenit
{
private:
   std::atomic<int> cfd;
   int server_port;
   string server_ip;
   string chatobject;
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
    void historicalnews(string ID);
    void main_mnue(string ID);//主界面函数
    
    //void group_menu(string ID);
    //好友管理函数组
    void friends_menu(string ID);
    void friendadd(string ID);//加好友
    void ignorefriend(string ID);//屏蔽好友
    void delfriend(string ID);//删除好友
    void viewfriend(string ID);//查看好友在线状态
    void friendrequests(string ID);//处理好友申请
    void file_menu(string ID);
    //实时接收
    static void PrientfT(string s);
    static void PrientfR(string s);
    static void PrientfL(string s);
    //私聊
    void privateChat(string ID);
    void directsend(string ID);
    void pchatspace(string ID);
    void chathistory(string ID);
};
#endif
