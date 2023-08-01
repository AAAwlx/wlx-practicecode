#include "public.hpp"
#include "clit.hpp"
void Clenit::historicalnews(string ID)//用户上线后立即发送未处理消息
{
    char r[BUFFERSIZE];
    while (1)
    {
        if(Err::Read(cfd,r,sizeof(r))>0){
            Massage m1(r);
            string s1=m1.Deserialization("request");
            if(s1=="NULL"){
                cout<<"无好友申请"<<endl;
            }else{
                cout<<"有id号为"<<s1<<"的用户想与您建立好友关系"<<endl;
            }
            string s2=m1.Deserialization("chat");
            if(s2=="NULL"){

            }else{
                cout<<"无新消息"<<endl;
            }
            
            break;
        }
    }
    return;
}
void Clenit::main_mnue(string ID)
{
    string in;
    char r[BUFSIZ];
    cout<<"开启实时接收线程"<<endl;
    std::thread t(thread_recv);
    t.detach();
    while (true)
    {
        bzero(r, sizeof(r));
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "|    1:私聊        |" << endl;
        cout << "|    2:群菜单      |" << endl;
        cout << "|    3:好友管理    |" << endl;
        cout << "|    4.文件管理    |" << endl;
        cout << "|    0:退出登陆    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        cin >> in;
        Err::Write(cfd, in.c_str(), in.length());
        system("clear");
        if (in == PRIVATE){
            string s = PRIVATE;
            Err::Write(cfd, s.c_str(), s.length());
            Clenit::privateChat(ID);
        }else if (in == GROUP){
            string s = GROUP;
            Err::Write(cfd, s.c_str(), s.length());
            Clenit::group_menu(ID);
        }else if (in == FRIENDS_MENU){
            string s = FRIENDS_MENU;
            Err::Write(cfd, s.c_str(), s.length());
            Clenit::file_menu(ID);
        }else if(in==FILE_MANAGE){
            string s = FILE_MANAGE;
            Err::Write(cfd, s.c_str(), s.length());
            Clenit::file_menu(ID);
        }else if (in==EXIT){
            
        }else{
            cout<<"您的输入不符合规范，请再次输入选项"<<endl;
            continue;
        }
    }
    return;    
} 