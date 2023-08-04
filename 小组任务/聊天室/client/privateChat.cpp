#include "public.hpp"
#include "clit.hpp"
void Clenit::directsend(string ID)
{
    while (1)
    {
        string id, massage;
        Value info;
        char a[BUFFERSIZE];
        cout << "请输入发送对象的id" << endl;
        while (1)
        {
            cin >> id;
            if (id.length() > 20 || id.length() < 3)
            {
                std::cout << "您输入的id不符合规范，请重新输入一次" << endl;
            }
            else
            {
                break;
            }
        }
        cout << "请输入你要说的话" << endl;
        cin >> massage;
        info["massage"] = massage;
        Massage m("Direct_send", info, id, ID);
        string s = m.Serialization();
        Err::Write(cfd, s.c_str(), s.length());
        string r;
        while (1)
        {
            if (Err::Read(cfd, a, sizeof(a)) > 0)
            {
                Massage m1(a);
                r=m1.Deserialization("return");
                break;
            }
        }
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
        string in;
        bool flag;
        while (1)
        {
            cin >> in;
            if (in == "0")
            {
                true;
                break;
            }
            else if(in=="1")
            {
                false;
                break;
            }else{
                std::cout << "您输入的选项不符合规范，请重新输入一次" << endl;
                continue;
            }
        }
        if (flag)
        {
            break;
        }else{
            
            continue;
        }
    }
    return;
}
void Clenit::pchatspace(string ID)
{
    while (1)
    {
        string id, massage;
        Value info;
        char r[BUFFERSIZE];
        cout << "请输入发送对象的id" << endl;
        while (1)
        {
            cin >> id;
            if (id.length() > 20 || id.length() < 3)
            {
                std::cout << "您输入的id不符合规范，请重新输入一次" << endl;
            }
            else
            {
                break;
            }
        }
        info["friendID"] = id;
        info["myID"] = ID;
        Massage m1(Pchat_space, info, "0", "0");
        string s1 = m1.Serialization();
        Err::Write(cfd, s1.c_str(), s1.length());
        while (1)
        {
            if (Err::Read(cfd, r, sizeof(r)) > 0)
            {
                break;
            }
        }
        string in;
        if (r == "NOTfriend")
        {
            std::cout << "您与id为" << id << "还不是好友，请先添加他为好友（输入1继续，输入0退出）" << endl;
            cin >> in;
            if (in == "1")
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else if (r == "Hidden")
        {
            std::cout << "您被id为" << id << "屏蔽了（输入1继续，输入0退出）" << endl;
            cin >> in;
            if (in == "1")
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            Massage m2(r);
            std::variant<Json::Value, std::string> result = m2.takeMassage("content");
            Value o = std::get<Json::Value>(result);
            Value j1 = o[ID + id];
            Value j2 = o[id + ID];
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

        cout << "您已经进入与好友：" << id << "的私聊空间（输入Q退出）" << endl;
        chatobject = id;
        string in2;
        while (1)
        {
            cin >> in2;
            if (in2 == "Q")
            {
                chatobject = id;
                Clenit::Exit();
                break;
            }
            else
            {
                Value j;
                j["massage"] = in2;
                Massage m3(Pchat_space, j, id, ID);
                string s = m3.Serialization();
                Err::Write(cfd, s.c_str(), s.length());
                cout << "----------------------------------------------------" << endl;
            }
        }
    }
    return;
}
void Clenit::chathistory(string ID)
{
    while (1)
    {
        string friendid;
        cout << "请输入您要查看的好友id" << endl;
        cin >> friendid;
        Value j;
        j["friendID"] = friendid;
        j["myID"] = ID;
        Massage m(Chat_History, j, "0", "0");
        string s = m.Serialization();
        Err::Write(cfd, s.c_str(), s.length());
        char r[BUFFERSIZE];
        while (1)
        {
            if (Err::Read(cfd, r, sizeof(r)) > 0)
            {
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

                break;
            }
        }
        cout << "是否继续查看历史" << endl;
        string in;
        cin >> in;
        if (in == "Q")
        {
            break;
        }
    }
    return;
}
void Clenit::privateChat(string ID)
{
    string in;
    while (1)
    {
        cout << "+------------------+" << endl;
        cout << "|     ChatRoom     |" << endl;
        cout << "+------------------+" << endl;
        cout << "|                  |" << endl;
        cout << "|    1:私聊空间    |" << endl; // 可显示部分聊天记录
        cout << "|    2.直接发送    |" << endl;
        cout << "|    3.历史消息    |" << endl;
        cout << "|    0:退回上步    |" << endl;
        cout << "|                  |" << endl;
        cout << "+------------------+" << endl;
        cin >> in;
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
            cout << "您的输入不符合规范，请再次输入选项" << endl;
            continue;
        }
    }
}