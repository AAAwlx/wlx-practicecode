#include "public.hpp"
#include "clit.hpp"
void Clenit::directsend(string ID)
{

    string id, massage;
    Value info;
    std::cout << "请输入发送对象的id" << endl;
    while (1)
    {
        std::cin >> id;
        if (id.length() > 20 || id.length() < 3)
        {
            std::cout << "您输入的id不符合规范，请重新输入一次" << endl;
        }
        else
        {
            break;
        }
    }
    std::cout << "请输入你要说的话" << endl;
    std::cin >> massage;
    info["massage"] = massage;
    Massage m("Direct_send", info, id, ID);
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string a = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    Massage m1(a);
    string r = m1.Deserialization("return");
    if (r == "NOTfriend")
    {
        std::cout << "您与id为" << id << "还不是好友，请先添加他为好友，请选择继续还是退出（输入1继续，输入0退出）" << endl;
    }
    else if (r == "Hidden")
    {
        std::cout << "您被id为" << id << "屏蔽了，消息发送失败，请选择继续还是退出（输入1继续，输入0退出）" << endl;
    }
    else if (r == "NotOnline")
    {
        std::cout << "id为" << id << "暂时不在，上线后将为您发送消息，请选择继续还是退出（输入1继续，输入0退出）" << endl;
    }
    else if (r == "Succeed")
    {
        std::cout << "消息发送成功，请选择继续还是退出（输入1继续，输入0退出）" << endl;
    }
    return;
}
void Clenit::pchatspace(string ID)
{
    Value info;
    string friendid;
    std::cout << "请输入您要聊天的好友id" << endl;
    std::cin >> friendid;
    info["friendid"] = friendid;
    info["myID"] = ID;
    Massage m(Pchat_space, info, friendid, ID);
    Err::sendMsg(cfd,m.Serialization().c_str(),m.Serialization().length());
    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    string in;
    if (r == "NOTfriend")
    {
        std::cout << "您与id为" << friendid << "还不是好友，请先添加他为好友" << endl;
        std::cin >> in;
    }
    else if (r == "Hidden")
    {
        std::cout << "您被id为" << friendid << "屏蔽了" << endl;
        std::cin >> in;
    }
    else if (r == "Succeed")
    {
        string in2;
        chatobject = friendid;
        std::cout << "您已经进入与好友：" << friendid << "的私聊空间（输入Q退出）" << endl;
        f_flag=true;
        while (1)
        {
            if(!f_flag){
                std::cout << "您的好友：" << friendid << "已将你删除" << endl;
                break;
            }
            std::cin >> in2;
            if (in2 == "Q")
            {
                chatobject = friendid;
                Clenit::Exit();
                break;
            }
            else
            {
                Value j;
                j["massage"] = in2;
                Massage m3("Pchat_space", j, friendid, ID);
                string s = m3.Serialization();
                Err::sendMsg(cfd, s.c_str(), s.length());
                std::cout << "----------------------------------------------------" << endl;
            }
        }
    }
}
void Clenit::chathistory(string ID)
{
    string friendid;
    std::cout << "请输入您要查看的好友id" << endl;
    std::cin >> friendid;
    Value j;
    j["friendID"] = friendid;
    j["myID"] = ID;
    Massage m(Chat_History, j, "0", "0");
    string s = m.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());

    std::unique_lock<std::mutex> lock(qmutex);
    queueCondVar.wait(lock, []
                      { return !masqueue.empty(); });
    string r = masqueue.front();
    masqueue.pop();
    qmutex.unlock();
    if (r == "NOTfriend")
    {
        std::cout << "您与id为" << friendid << "还不是好友，请先添加他为好友" << endl;
    }
    else
    {
        Massage m2(r);
        std::variant<Json::Value, std::string> result = m2.takeMassage("content");
        Value o = std::get<Json::Value>(result);
        Value j1 = o[ID + friendid];
        Value j2 = o[friendid + ID];
        Json::Value::Members members1 = j1.getMemberNames();
        for (const auto &key : members1)
        {
            PrientfL(j1[key].asString());
        }
        Json::Value::Members members2 = j2.getMemberNames();
        for (const auto &key : members2)
        {
            PrientfR(j2[key].asString());
        }
    }

    return;
}
void Clenit::privateChat(string ID)
{
    string in;
    while (1)
    {
        std::cout << "+------------------+" << endl;
        std::cout << "|     ChatRoom     |" << endl;
        std::cout << "+------------------+" << endl;
        std::cout << "|                  |" << endl;
        std::cout << "|    1:私聊空间    |" << endl; // 可显示部分聊天记录
        std::cout << "|    2.直接发送    |" << endl;
        std::cout << "|    3.历史消息    |" << endl;
        std::cout << "|    0:退回上步    |" << endl;
        std::cout << "|                  |" << endl;
        std::cout << "+------------------+" << endl;
        std::cin >> in;
        system("clear");
        if (in == Pchat_space)
        {
            Clenit::pchatspace(ID);
        }
        else if (in == Direct_send)
        {
            Clenit::directsend(ID);
        }
        else if (in == EXIT)
        {
            Clenit::Exit();
            break;
        }
        else if (in == Chat_History)
        {
            Clenit::chathistory(ID);
        }
        else
        {
            std::cout << "您的输入不符合规范，请再次输入选项" << endl;
            continue;
        }
    }
}