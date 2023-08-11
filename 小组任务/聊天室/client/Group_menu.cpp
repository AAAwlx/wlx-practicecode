#include "public.hpp"
#include "clit.hpp"
void Clenit::add_group(string ID)
{
    string in;
    Value j;
    cout << "请输入要加入群的id" << endl;
    cin >> in;
    j["NEW_groupid"] = in;
    j["ID"] = ID;
    Massage m(ADD_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());

    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    if (r == "NULL")
    {
        std::cout << "没有此群，请再试一次" << endl;
    }
    else if (r == "Succeed")
    {
        std::cout << "入群请求已发送" << endl;
    }
    else if (r == "bemember")
    {
        std::cout << "你已经是群成员了" << endl;
    }
}
void Clenit::quit_group(string ID)
{
    string in;
    std::cout << "请输入你要退出的群id" << endl;
    std::cin >> in;
    Value j;
    j["Del_groupid"] = in;
    j["ID"] = ID;
    Massage m(QUIT_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << r << endl;
    if (r == "NULL")
    {
        std::cout << "你还未进入" << in << "请输入正确id" << endl;
    }
    else if (r == "Succeed")
    {
        std::cout << "你已退出群" << in  << endl;
    }else if(r=="belord")
    {
        std::cout << "你是" << in  <<"的群主，请你将权限转让给其他成员后再退群"<< endl;
    }
}
void Clenit::create_group(string ID)
{
    string in;
    std::cout << "请输入群id" << endl;
    std::cin >> in;
    Value j;
    j["group_name"] = in;
    j["ID"] = ID;
    Massage m(DEL_FRIEND, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string a = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    std::cout << a << endl;
    
        cout<<"你已成功创建群聊"<<in<<"群号为："<<a<<endl;
}
void Clenit::view_group(string ID)
{
    Value j;
    j["ID"] = ID;
    Massage m(VIEW_FRIENDS, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送查看群请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    Massage m(r);
    std::variant<Json::Value, std::string> result = m.takeMassage("content");
    Value glist = std::get<Json::Value>(result);
    Json::Value::Members members = glist.getMemberNames();
        for (const auto &key : members)
        {
            if(glist[key].asInt()==1){
                s="id: " + key + " 未屏蔽";
            }else{
                s="id: " + key + " 未屏蔽";
            }
            std::cout << s << std::endl;
        }
}
void Clenit::manage_menu(string ID)
{
    Value j;
    j["ID"] = ID;
    string in;
    std::cout << "请输入群id" << endl;
    std::cin >> in;
    j["man_groupid"]=in;
    Massage m(MAN_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送管理群请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    if(r=="0"){//普通群成员
        manage_menu0(ID,in);
    }else if(r=="1"){//群管理
        manage_menu1(ID,in);
    }else if(r=="2"){//群主
        manage_menu2(ID,in);
    }else if(r=="NULL"){
        std::cout << "你还未进入" << in << "请输入正确id" << endl;
    }
}
void Clenit::publicChat(string ID)
{
    Value j;
    j["ID"] = ID;
    string in;
    std::cout << "请输入群id" << endl;
    std::cin >> in;
    j["man_groupid"]=in;
    Massage m(MAN_GROUP, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::cout << "已发送聊天请求" << endl;
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    if(r=="Succeed"){
        //跳转到群聊界面
    }else if(r=="NULL"){
        std::cout << "你还未进入" << in << "请输入正确id" << endl;
    }
}
void Clenit::group_menu(string ID)
{
    string in;
    while (true)
    {
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "| 1:进入群聊       |" << endl;
        cout << "| 2:申请入群       |" << endl;
        cout << "| 3:退出群聊       |" << endl;
        cout << "| 4:创建群聊       |" << endl;
        cout << "| 5:查看已加入的群 |" << endl;
        cout << "| 6:管理群聊       |" << endl;
        cout << "| 0:退出页面       |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;

        cin >> in;
        Err::sendMsg(cfd, in.c_str(), in.length());
        if (in == JOIN_GROUP)
        {
            Clenit::publicChat(ID);
        }
        else if (in == ADD_GROUP)
        {
            Clenit::add_group(ID);
        }
        else if (in == QUIT_GROUP)
        {
            Clenit::quit_group(ID);
        }
        else if (in == CREATE_GROUP)
        {
            Clenit::create_group(ID);
        }
        else if (in == VIEW_GROUP)
        {
            Clenit::view_group(ID);
        }
        else if (in == MAN_GROUP)
        {
            Clenit::manage_menu(ID);
        }
        else if (in == EXIT)
        {
            break;
        }
    }
    return;
}