#include "public.hpp"
#include "ser.hpp"
void Server::directsend(int cfd, Massage m, string massage)
{
    std::variant<Json::Value, std::string> result1 = m.takeMassage("to");
    std::string to_id = std::get<std::string>(result1);
    std::variant<Json::Value, std::string> result2 = m.takeMassage("form");
    std::string from_id = std::get<std::string>(result2);
    cout << from_id << "+" << to_id << endl;
    cout << "----------------------------------------------------" << endl;
    User u(from_id, Library);
    Value j = u.friend_List;
    string r;
    if (j.isMember(to_id))
    {
        if (j[to_id].asInt() == 1)
        {
            string listname = from_id + to_id;
            redisReply *reply = static_cast<redisReply *>(redisCommand(Library, "LPUSH %s %s", listname.c_str(), massage)); // 长期存储历史聊天记录
            freeReplyObject(reply);
            try
            {
                
                int cfd2 = user_cfd.at(to_id); // 当被添加人在线，立即向被添加人发送好友申请通知
                Err::sendMsg(cfd2, massage.c_str(), massage.length());
                r = "Succeed";
            }
            catch (const std::out_of_range &e)
            {
                r = "NotOnline";
                cout << "succeed" << endl;
            }
        }
        else
        {
            r = "Hidden";
        }
    }
    else
    { // 好友列表中没有此人
        r = "NOTfriend";
    }
    Value v;
    v["return"] = r;
    Massage m1("0", v, "0", "0");
    string s = m1.Serialization();
    cout << r << endl;
    Err::sendMsg(cfd, s.c_str(), s.length());
    cout << r << endl;
    return;
}
void Server::pchatspace(int cfd, Massage m)
{
    cout << "----------------------------------------------------" << endl;
    string friendID = m.Deserialization("friendID");
    string myID = m.Deserialization("myID");
    User u(myID, Library);
    Value j = u.friend_List;
    string s;
    int cfd2;
    if (j.isMember(friendID)) // 是否是好友
    {
        if (j[friendID].asInt() == 1) // 是否被屏蔽
        {

            string s1 = myID + friendID;
            string s2 = friendID + myID;
            Value j1, j2, info;
            redisReply *reply = (redisReply *)redisCommand(Library, "LRANGE %s -10 -1", s1.c_str());
            for (size_t i = 0; i < reply->elements; i++)
            {
                redisReply *element = reply->element[i];
                if (element->type == REDIS_REPLY_STRING)
                {
                    std::string massage(element->str, element->len);
                    std::string str = std::to_string(i);
                    j1[str] = massage;
                }
            }
            redisReply *reply2 = (redisReply *)redisCommand(Library, "LRANGE %s -10 -1", s2.c_str());
            for (size_t i = 0; i < reply->elements; i++)
            {
                redisReply *element = reply->element[i];
                if (element->type == REDIS_REPLY_STRING)
                {
                    std::string massage(element->str, element->len);
                    std::string str = std::to_string(i);
                    j2[str] = massage;
                }
            }
            info[s1] = j1;
            info[s2] = j2;
            Massage m1(Pchat_space, info, "0", "0");
            s = m1.Serialization();
            cout<<s<<endl;
            Err::sendMsg(cfd, s.c_str(), s.length());

        }
        else
        {
            s = "Hidden";
            Err::sendMsg(cfd, s.c_str(), s.length());
            return;
        }
    }
    else
    {
        s = "NOTfriend";
        Err::sendMsg(cfd, s.c_str(), s.length());
        return;
    }
    
    while (1)
    {
        string r;
        r=Err::recvMsg(cfd);
        if (r.length() > 0)
        {
            Massage m2(r);
            std::variant<Json::Value, std::string> result = m2.takeMassage("option");
            std::string o = std::get<std::string>(result);
            if (o == EXIT)
            {
                return;
            }
            else if (o == Pchat_space)
            {
                string listname = myID + friendID;
                redisReply *reply = static_cast<redisReply *>(redisCommand(Library, "LPUSH %s %s", listname.c_str(), r)); // 长期存储历史聊天记录
                freeReplyObject(reply);
                if (user_cfd.count(friendID))
                {
                    cfd2 = user_cfd[friendID];
                    Err::sendMsg(cfd2, r.c_str(),r.length());
                }
                else
                { // 如果不在线存入未处理消息列表
                    friendID += "c";
                    redisReply *reply2 = static_cast<redisReply *>(redisCommand(Library, "LPUSH %s %s", friendID.c_str(), r)); // 存储离线用户的消息通知
                    freeReplyObject(reply2);
                    return;
                }
            }
        }
    }
}
void Server::chathistory(int cfd, Massage m)
{
    string friendID = m.Deserialization("friendID");
    string myID = m.Deserialization("myID");
    User u(myID, Library);
    Value j = u.friend_List;
    string s;
    if (j.isMember(friendID)) // 是否是好友
    {

        string s1 = myID + friendID;
        string s2 = friendID + myID;
        Value j1, j2, info;
        redisReply *reply = (redisReply *)redisCommand(Library, "LRANGE %s 0 -1", s1.c_str());
        for (size_t i = 0; i < reply->elements; i++)
        {
            redisReply *element = reply->element[i];
            if (element->type == REDIS_REPLY_STRING)
            {
                std::string massage(element->str, element->len);
                std::string str = std::to_string(i);
                j1[str] = massage;
            }
        }
        redisReply *reply2 = (redisReply *)redisCommand(Library, "LRANGE %s -0 -1", s2.c_str());
        for (size_t i = 0; i < reply->elements; i++)
        {
            redisReply *element = reply->element[i];
            if (element->type == REDIS_REPLY_STRING)
            {
                std::string massage(element->str, element->len);
                std::string str = std::to_string(i);
                j2[str] = massage;
            }
        }
        info[s1] = j1;
        info[s2] = j2;
        Massage m1(Pchat_space, info, "0", "0");
        s = m1.Serialization();
        Err::sendMsg(cfd, s.c_str(), s.length());
    }
    else
    {
        s = "NOTfriend";
        Err::sendMsg(cfd, s.c_str(), s.length());
        return;
    }
}
void Server::privateChat(int cfd)
{
    string r;
    while (1)
    {
        r=Err::recvMsg(cfd);
        if (r.length() > 0)
        {
            cout << r << endl;
            Massage m(r);
            std::variant<Json::Value, std::string> result = m.takeMassage("option");
            std::string o = std::get<std::string>(result);
            if (o == "Direct_send")
            {
                Server::directsend(cfd, m, r);
            }
            else if (o == "Pchat_space")
            {
                Server::pchatspace(cfd, m);
            }
            else if (o == Chat_History)
            {
                Server::chathistory(cfd, m);
            }
            else if (o == EXIT)
            {
                break;
            }
        }
    }
    return;
}