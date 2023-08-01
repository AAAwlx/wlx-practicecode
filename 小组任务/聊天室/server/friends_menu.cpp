#include "ser.hpp"
#include "public.hpp"
void Server::friendadd(int cfd, Massage m)
{
    string NEW_friendid = m.Deserialization("NEW_friendid"); // 被加人的id
    User f(NEW_friendid, Library);
    if (f.Inquire("ID") == "0")
    { // 查询是否有此人存在
        Err::Write(cfd, "NULL", sizeof("NULL"));
        return;
    }
    string s2 = m.Deserialization("ID"); //
    User u(s2, Library);
    Value j = u.friend_List;
    if (j.isMember(NEW_friendid))
    {
        Err::Write(cfd, "befriends", sizeof("befriends")); // 如果好友列表中有被加人
        return;
    }
    else
    {
        int cfd2 = user_cfd.at(NEW_friendid);
        Value j;
        j["ID"] = s2;
        Massage m2(MAS_FRIEND, j, "0", "0");
        string s3 = m2.Serialization();
        Err::Write(cfd2, s3.c_str(), s3.length());     // 该请求应该被保存到被加人的好友申请的记录中
        Err::Write(cfd, "succeed", sizeof("succeed")); // 向请求人发送请求成功转发
        NEW_friendid += "r";
        std::string command1 = "RPUSH " + NEW_friendid + " " + s2;
        redisReply *reply = (redisReply *)redisCommand(Library, command1.c_str());
        freeReplyObject(reply);
    }
}
void Server::delfriend(int cfd, Massage m)
{
    string s1 = m.Deserialization("Del_friend");
    string s2 = m.Deserialization("ID");
    User u(s2, Library);
    Value j = u.friend_List;
    if (j.isMember(s1))
    {
        Err::Write(cfd, "NULL", sizeof("NULL"));
    }
    else
    {
        u.delete_friend(s1);
        Err::Write(cfd, "Succeed", sizeof("succeed"));
    }
}
void Server::ignorefriend(int cfd, Massage m)
{
    string s1 = m.Deserialization("Ign_friend");
    string s2 = m.Deserialization("ID");
    User u(s2, Library);
    Value j = u.friend_List;
    if (j.isMember(s1))
    {
        Err::Write(cfd, "NULL", sizeof("NULL"));
    }
    else
    {
        u.shield_friend(s1);
        Err::Write(cfd, "Succeed", sizeof("succeed"));
    }
}
void Server::viewfriend(int cfd, Massage m)
{
    string s2 = m.Deserialization("ID");
    User u(s2, Library);
    Value j = u.friend_List;
    Value flist;
    if (j.isObject())
    {
        Json::Value::Members members = j.getMemberNames();
        for (const auto &key : members)
        {
            int count = user_cfd.count(key);
            if (count > 0)
            {
                flist[key] = "online";
            }
            else
            {
                flist[key] = "not online";
            }
        }
    }

    Massage m1("0", flist, "0", "0");
    string s = m1.Serialization();
    Err::Write(cfd, s.c_str(), s.length());
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
        // HGETALL命令的返回值是一个数组，其中奇数索引为字段名，偶数索引为对应的值
        for (size_t i = 0; i < reply->elements; ++i)
        {
            redisReply *value = reply->element[i + 1];
            std::string strValue(value->str, value->len);
            info[""]=strValue;
        }
    }
    freeReplyObject(reply);
    Massage m1(MAS_FRIEND, info, "0", "0");
    string s1 = m1.Serialization();
    Err::Write(cfd, s1.c_str(), s.length());//将待处理的请求发送到客户端
    char r[BUFFERSIZE];
    while (1)
    {
        if (Err::Read(cfd, r, sizeof(r)) > 0)
        {
            break;
        }
    }
    Massage m2(r);
    std::variant<Json::Value, std::string> result = m.takeMassage("content");
    Value rlist = std::get<Json::Value>(result);
    for (Json::ValueIterator it = rlist.begin(); it != rlist.end(); ++it)
    {
        std::string key = it.name(); // key为申请人id
        std::string value = (*it).asString();
        redisReply *reply = (redisReply *)redisCommand(Library, "LREM %s 0 %s", s.c_str(), key.c_str());
        if (value == "accapt")
        {
            u.add_friend(key);
        }
        int cfd2 = user_cfd.at(key);//获取申请人的cfd
        Err::Write(cfd2, value.c_str(), value.length());//将好友申请的结果返回给他
    }
}
void Server::friends_menu(int cfd)
{
    cout << cfd << "已进入好友管理界面" << endl;
    char r[BUFFERSIZE];
    while (1)
    {
        if (Err::Read(cfd, r, sizeof(r)) > 0)
        {
            cout << r << endl;
            Massage m(r);
            std::variant<Json::Value, std::string> result = m.takeMassage("option");
            std::string s = std::get<std::string>(result);

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
            }
        }
    }
}