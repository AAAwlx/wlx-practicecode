#include "ser.hpp"
#include "public.hpp"
void Server::friendadd(int cfd, Massage m)
{
    string NEW_friendid = m.Deserialization("NEW_friendid"); // 被加人的id
    string r;
    Value v;
    User f(NEW_friendid, Library);
    if (f.Inquire("ID") == "-1234567")
    { // 查询是否有此人存在
        cout << "NULL" << endl;
        v["return"] = "NULL";
        Massage m1("0", v, "0", "0");
        string s = m1.Serialization();
        Err::sendMsg(cfd, s.c_str(), s.length());
        return;
    }
    string s2 = m.Deserialization("ID"); //
    User u(s2, Library);
    if (u.friend_List.isMember(NEW_friendid))
    {
        r = "befriends"; // 如果好友列表中有被加人
    }
    else
    {
        try
        {
            int cfd2 = user_cfd.at(NEW_friendid); // 当被添加人在线，立即向被添加人发送好友申请通知
            Value j;
            j["ID"] = s2;
            Massage m2("add_friend", j, "0", "0");
            string s3 = m2.Serialization();
            Err::sendMsg(cfd2, s3.c_str(), s3.length());
            r = "Succeed"; // 该请求应该被保存到被加人的好友申请的记录中
        }
        catch (const std::out_of_range &e)
        {
            r = "NotOnline";
        }
        NEW_friendid += "r"; // 将该好友请求存入redis中
        redisReply *reply = (redisReply *)redisCommand(Library, "LRANGE %s 0 -1", NEW_friendid.c_str());
        bool valueExists = false;
        if (reply->type == REDIS_REPLY_ARRAY)
        {
            for (size_t i = 0; i < reply->elements; i++)
            {
                std::string element(reply->element[i]->str, reply->element[i]->len);
                if (element == s2)
                {
                    valueExists = true;
                    break;
                }
            }
        }
        if(!valueExists){
            redisReply *reply2 = (redisReply *)redisCommand(Library, "LPUSH %s %s", NEW_friendid.c_str(), s2.c_str());
            freeReplyObject(reply2);
        }
        freeReplyObject(reply);
    }
    v["return"] = r;
    Massage m4("0", v, "0", "0");
    string s4 = m4.Serialization();
    cout<<s4<<endl;
    Err::sendMsg(cfd, s4.c_str(), s4.length());
}
void Server::delfriend(int cfd, Massage m)
{
    string s1 = m.Deserialization("Del_friend");
    string s2 = m.Deserialization("ID");
    User u(s2, Library);
    User u2(s1,Library);
    string r;
    Value v;
    if (u.friend_List.isMember(s1))
    {
        u.delete_friend(s1);
        u2.delete_friend(s2);
        r="Succeed";
        try
        {
            Value j;
            int cfd2 = user_cfd.at(s1);
            j["friend"] = s2;
            Massage m3("del_friend", j, "0", "0");
            
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout<< m3.Serialization()<<endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }
    else
    {
       r="NULL";
    }
    v["return"] = r;
    Massage m4("0", v, "0", "0");
    string s4 = m4.Serialization();
    cout<<s4<<endl;
    Err::sendMsg(cfd, s4.c_str(), s4.length());
}
void Server::ignorefriend(int cfd, Massage m)
{
    cout << "---------------------" << endl;
    string s1 = m.Deserialization("Ign_friend");
    string s2 = m.Deserialization("ID");
    User u(s2, Library);
    string r;
    Value v;
    if (u.friend_List.isMember(s1))
    {
        if(u.friend_List[s1].asInt()==1){
            u.shield_friend(s1);
            r="Succeed";
            cout<<u.friend_List<<endl;
        }else{
            r="blocked";
        }    
    }else{
        r="NULL";
    }
    v["return"] = r;
    Massage m4("0", v, "0", "0");
    string s4 = m4.Serialization();
    cout<<s4<<endl;
    Err::sendMsg(cfd, s4.c_str(), s4.length());
}
void Server::friendrecover(int cfd, Massage m)
{
    cout << "---------------------" << endl;
    string s1 = m.Deserialization("REC_friend");
    string s2 = m.Deserialization("ID");
    User u(s2, Library);
    Value v;
    string r;
    if (u.friend_List.isMember(s1)){ 
        if(u.friend_List[s1]==0){
            u.recover_friend(s1);
            r="Succeed";
            cout<<u.friend_List<<endl;
        }else{
            r="not_blocked";
        }
    }else{
        r="NULL";
    }
    v["return"] = r;
    Massage m4("0", v, "0", "0");
    string s4 = m4.Serialization();
    cout<<s4<<endl;
    Err::sendMsg(cfd, s4.c_str(), s4.length());
}
void Server::viewfriend(int cfd, Massage m)
{
    string s2 = m.Deserialization("ID");
    User u(s2, Library);
    Value j = u.friend_List; // 好友列表
    Value flist;             // 好友状态列表
    if (j.isObject()){
        Json::Value::Members members = j.getMemberNames();
        for (const auto &key : members)
        {
            int count = user_cfd.count(key);
            if (count > 0){
                flist[key] = "online";
            }else{
                flist[key] = "not online";
            }
        }
    }
    Massage m1("0", flist, "0", "0");
    string s = m1.Serialization();
    Err::sendMsg(cfd, s.c_str(), s.length());
}
void Server::friendrequests(int cfd, Massage m)
{
    string ID = m.Deserialization("ID");
    User u(ID, Library);
    string s = ID + "r";
    Value info;
    redisReply *reply = (redisReply *)redisCommand(Library, "LRANGE %s 0 -1", s.c_str());
    if (reply->type == REDIS_REPLY_ARRAY)
    {
        for (size_t i = 0; i < reply->elements; ++i)
        {
            redisReply *value = reply->element[i];
            std::string strValue(value->str, value->len);
            info[strValue] = "0";
        }
    }
    freeReplyObject(reply);
    Massage m1(MAS_FRIEND, info, "0", "0");
    string s1 = m1.Serialization();
    cout<<s1<<endl;
    Err::sendMsg(cfd, s1.c_str(), s1.length()); // 将待处理的请求发送到客户端
    string r;
    while (1)
    {
        r=Err::recvMsg(cfd);
        if (r.length() > 0)
        {
            break;
        }
    }
    Massage m2(r);
    std::variant<Json::Value, std::string> result = m2.takeMassage("content");
    Value rlist = std::get<Json::Value>(result);
    for (Json::ValueIterator it = rlist.begin(); it != rlist.end(); ++it)
    {
        std::string key = it.name(); // key为申请人id
        std::string value = (*it).asString();
        redisReply *reply = (redisReply *)redisCommand(Library, "LREM %s 0 %s", s.c_str(), key.c_str()); // 将已经处理过的好友请求删除
        Value j;
        string result;
        if (value == "accapt")
        {
            User k(key, Library);
            k.add_friend(ID);  // 将被加人加入申请人的列表
            u.add_friend(key); // 将申请人加入被加人的列表
            result="f_accapt";
        }else{
            result="f_reject";
        }
        try
        {
            int cfd2 = user_cfd.at(key);
            j["friend"] = key;
            Massage m3(result, j, "0", "0");
            
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout<< m3.Serialization()<<endl;
            std::cout<<value<<endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }
}
void Server::friends_menu(int cfd)
{
    cout << cfd << "已进入好友管理界面" << endl;
    while (1)
    {
        string r;
        r=Err::recvMsg(cfd);
        if (r.length() > 0)
        {
            cout << r << endl;
            
            Massage m(r);
            std::variant<Json::Value, std::string> result = m.takeMassage("option");
            std::string s = std::get<std::string>(result);
            cout << s << endl;
            if (s == ADD_FRIEND)
            {
                Server::friendadd(cfd, m);
            }
            else if (s == DEL_FRIEND)
            {
                Server::delfriend(cfd, m);
            }
            else if (s == VIEW_FRIENDS)
            {
                Server::viewfriend(cfd, m);
            }
            else if (s == MAS_FRIEND)
            {
                Server::friendrequests(cfd, m);
            }
            else if (s == IGN_FRIEND)
            {
                Server::ignorefriend(cfd, m);
            }else if(s==REC_FRIEND)
            {
                Server::friendrecover(cfd,m);
            }
            else if (s == EXIT)
            {
                break;
            }
        }
    }
}