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
#define REC_FRIEND "6"   //解除屏蔽
#define BE_FRIENDS "0"   //已经是好友
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
#define MAN_GROUP "6" 
#define GROUP_HISTORY "7"//群聊历史记录
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
#include<iostream>
#include <mutex>
#include <queue>
#include<atomic>
#include <condition_variable>
using namespace std;
extern std::atomic<bool> stopFlag;
extern std::condition_variable queueCondVar;
extern std::mutex qmutex;
extern std::queue<string> masqueue;
void thread_recv(const std::string& ID, int cfd, const std::string& chatobject);
class Clenit
{
private:
   int cfd;
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
    //好友管理函数组
    void friends_menu(string ID);
    void friendadd(string ID);//加好友
    void ignorefriend(string ID);//屏蔽好友
    void delfriend(string ID);//删除好友
    void viewfriend(string ID);//查看好友在线状态
    void friendrequests(string ID);//处理好友申请
    void file_menu(string ID);
    void friendrecover(string ID);
    //实时接收
    static void PrientfT(string s);
    static void PrientfR(string s);
    static void PrientfL(string s);
    //私聊
    void privateChat(string ID);
    void directsend(string ID);
    void pchatspace(string ID);
    void chathistory(string ID);
    //群管理
    void group_menu(string ID);
    void create_group( string ID); //创建群聊
    void add_group(string ID);               //申请入群
    void quit_group(string ID);              //退出群
    void view_group(string ID);              //查看群
    void publicChat(string ID);
    void history_group(string ID);
    void manage_menu(string ID); //管理群
    void manage_menu0(string ID,string man_groupid);
    void manage_menu1(string ID,string man_groupid);
    void manage_menu2(string ID,string man_groupid);
    void man_addgroup(string ID,string man_groupid);          //入群请求
    void man_view(string ID,string man_groupid);                //查看群成员
    void man_addmanager(string ID,string man_groupid);  //添加管理员
    void man_delmanager(string ID,string man_groupid);         //取消管理员
    void man_delmember(string ID,string man_groupid);        //踢出成员
    bool man_delgroup(string ID,string man_groupid);          //解散群
    void ignoregroup(string ID,string man_groupid);
    void grouprecover(string ID,string man_groupid);
    void transfer_group(string ID,string man_groupid);
    void man_addmember(string ID,string man_groupid);

};
#endif