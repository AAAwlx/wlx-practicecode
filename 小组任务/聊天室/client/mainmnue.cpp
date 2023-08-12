#include "public.hpp"
#include "clit.hpp"
void Clenit::historicalnews(string ID)//用户上线后立即发送未处理消息
{
    string r;
    while (1)
    {
        r=Err::recvMsg(cfd);
        if(r.length()>0){
            cout<<r<<endl;
            Massage m(r);
            std::variant<Json::Value, std::string> result = m.takeMassage("content");
            Value s = std::get<Json::Value>(result);
            Value s1=s["request"];
            Value s2=s["chat"];
            if(s1.empty()){
                cout<<"无好友申请"<<endl;
            }else{
                Json::Value::Members  members= s1.getMemberNames();
                for (const auto& key : members) {
                    std::cout << "id为" << s1[key].asString()<<"请求与你建立好友关系"<< std::endl;
                }
            }
            if(s1.empty()){
                cout<<"无新消息"<<endl;
            }else{
                Json::Value::Members members2 = s2.getMemberNames();
                for (const auto& key : members2) {
                    std::cout << "您有新消息" << s2[key].asString() << std::endl;
                }
            }
            break;
        }
    }
    return;
}
void Clenit::main_mnue(string ID)
{
    string in;
    //char r[BUFSIZ];
    cout<<"开启实时接收线程"<<endl;
    std::thread t([&]() { thread_recv(ID, cfd, chatobject); });
    while (true)
    {
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
        Value j;
        Massage m(in,j,"0","0");
        string s=m.Serialization();
        Err::sendMsg(cfd, s.c_str(), s.length());
        system("clear");
        if (in == PRIVATE){
            Clenit::privateChat(ID);
        }else if (in == GROUP){
            Clenit::group_menu(ID);
        }else if (in == FRIENDS_MENU){
            Clenit::friends_menu(ID);
        }/*else if(in==FILE_MANAGE){
            string s = FILE_MANAGE;
            Err::Write(cfd, s.c_str(), s.length());
            Clenit::file_menu(ID);
        }*/else if (in==EXIT){
            stopFlag=false;
            cout<<"1111111"<<endl;
            t.join();
            cout<<"线程结束"<<endl;
            break;
        }else{
            cout<<"您的输入不符合规范，请再次输入选项"<<endl;
            continue;
        }
    }
    return;    
} 