#include "ser.hpp"
#include "public.hpp"
void Server::add_group(int cfd)
{
    string s;
    while (1)
    {
        s = Err::recvMsg(cfd);
        if (s.length() > 0){
            cout << s << endl;
        }
    }
    Massage m(s);
    string NEW_groupid = m.Deserialization("NEW_groupid");
    string ID = m.Deserialization("ID");
    Group g(NEW_groupid, Library);
    string r;
    if (g.Inquire("ID") == "-1234567")
    { // 查询是否有此群存在
        cout << "NULL" << endl;
        r = "NULL";
        Err::sendMsg(cfd, r.c_str(), r.length());
        return;
    }
    if (g.member_List.isMember(ID))
    {
        r = "bemember"; // 如果好友列表中有被加人
    }else{
        Json::Value::Members members = g.member_List.getMemberNames();
        for (const auto &key : members)
        {
            if (g.member_List[key].asInt() == 1 || g.member_List[key].asInt() == 2)//判断是否是管理员
            {
                try
                {
                    int cfd2 = user_cfd.at(key); // 当管理员在线，立即向被添加人发送好友申请通知
                    Value j;
                    j["ID"] = ID;
                    Massage m2("add_group", j, "0", "0");
                    string s3 = m2.Serialization();
                    Err::sendMsg(cfd2, s3.c_str(), s3.length());
                    r = "Succeed"; // 该请求应该被保存到被加人的好友申请的记录中
                }
                catch (const std::out_of_range &e)
                {
                    std::cout << "Key not found." << std::endl;
                }
            }
        }
        NEW_groupid += "g"; // 将该加群请求存入redis中
        redisReply *reply = (redisReply *)redisCommand(Library, "LRANGE %s 0 -1", NEW_groupid.c_str());
        bool valueExists = false;
        if (reply->type == REDIS_REPLY_ARRAY)
        {
            for (size_t i = 0; i < reply->elements; i++)
            {
                std::string element(reply->element[i]->str, reply->element[i]->len);
                if (element == ID)
                {
                    valueExists = true;
                    break;
                }
            }
        }
        if (!valueExists)
        {
            redisReply *reply2 = (redisReply *)redisCommand(Library, "LPUSH %s %s", NEW_groupid.c_str(), ID.c_str());
            freeReplyObject(reply2);
        }
        freeReplyObject(reply);
    }
    cout << r << endl;
    Err::sendMsg(cfd, r.c_str(), r.length()); // 向客户端返回处理结果
}
void Server::quit_group(int cfd)
{
    string s;
    string r;
    while (1)
    {

        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            cout << s << endl;
        }
    }
    Massage m(s);
    string Del_groupid = m.Deserialization("Del_groupid");
    string ID = m.Deserialization("ID");
    Group g(Del_groupid, Library);
    User u(ID, Library);
    if (u.group_List.isMember(Del_groupid))
    {
        if (g.member_List[ID].asInt() == 2)
        {
            r = "belord";
        }
        else
        {
            u.delete_group(Del_groupid);
            g.delete_member(ID);
            // 通知所有管理员有人退群
            Json::Value::Members members = g.member_List.getMemberNames();
            for (const auto &key : members)
            {
                if (g.member_List[key].asInt() > 0)
                {
                    try
                    {
                        int cfd2 = user_cfd.at(key); // 当管理员在线，立即向被添加人发送好友申请通知
                        Value j;
                        j["ID"] = ID;
                        Massage m2("quit_group", j, "0", "0");
                        string s3 = m2.Serialization();
                        Err::sendMsg(cfd2, s3.c_str(), s3.length());
                        r = "Succeed";
                    }
                    catch (const std::out_of_range &e)
                    {
                        std::cout << "Key not found." << std::endl;
                    }
                }
            }
        }
    }
    else
    {
        r = "NULL";
    }
    cout << r << endl;
    Err::sendMsg(cfd, r.c_str(), r.length());
}
void Server::create_group(int cfd)
{
    string s;
    string r;
    while (1)
    {

        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            cout << s << endl;
        }
    }
    Massage m(s);
    string group_name = m.Deserialization("group_name");
    string ID = m.Deserialization("ID");
    Group g(group_name, ID, Library);
    string gid = g.distribute_id();
    Err::sendMsg(cfd, gid.c_str(), gid.size());
    g.save_group();
}
void Server::view_group(int cfd)
{
    string s;
    string r;
    while (1)
    {

        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            cout << s << endl;
        }
    }
    Massage m(s);
    string group_name = m.Deserialization("group_name");
    string ID = m.Deserialization("ID");
    User u(ID, Library);
    Massage m2(VIEW_FRIENDS, u.group_List, "0", "0");
    Err::sendMsg(cfd, m2.Serialization().c_str(), m2.Serialization().length());
}
void Server::manage_menu(int cfd)
{
    string s;
    string r;
    while (1)
    {

        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            cout << s << endl;
        }
    }
    Massage m(s);
    string man_groupid = m.Deserialization("man_groupid");
    string ID = m.Deserialization("ID");
    User u(ID, Library);
    Group g(man_groupid,Library);
    if (u.group_List.isMember(man_groupid))
    {
        if(g.member_List.asInt()==0){
            r = "0";
        }else if(g.member_List.asInt()==1){
            r = "1";
        }else if(g.member_List.asInt()==2){
            r = "2";
        }
        manage_menu(cfd);
    }
    else
    {
        r = "NULL";
    }
    Err::sendMsg(cfd,r.c_str(),r.length());
}
void Server::publicChat(int cfd)
{
    string s;
    string r;
    while (1)
    {

        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            cout << s << endl;
        }
    }
    Massage m(s);
    string groupid = m.Deserialization("chat_groupid");
    string ID = m.Deserialization("ID");
    User u(ID,Library);
    if(u.group_List.isMember(groupid))
    {
        r="Succeed";
        //跳转到群聊界面
    }else{
        r="NULL";
    }
    Err::sendMsg(cfd, r.c_str(), r.size());
}
void Server::group_menu(int cfd)
{
    cout << cfd << "已进入群界面" << endl;
    string s;
    while (1)
    {
        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            cout << s << endl;
            if (s == JOIN_GROUP)
            {
                Server::publicChat(cfd);
            }
            else if (s == ADD_GROUP)
            {
                Server::add_group(cfd);
            }
            else if (s == QUIT_GROUP)
            {
                Server::quit_group(cfd);
            }
            else if (s == VIEW_GROUP)
            {
                Server::view_group(cfd);
            }
            else if (s == CREATE_GROUP)
            {
                Server::create_group(cfd);
            }
            else if (s == MAN_GROUP)
            {
                Server::manage_menu(cfd);
            }
            else if (s == EXIT)
            {
                break;
            }
        }
    }
}