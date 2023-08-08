#include "ser.hpp"
#include "public.hpp"
void Server::man_addgroup(int cfd)
{
    string s;
    while (1)
    {
        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            break;
        }
    }
    Massage m(s);
    string groupid = m.Deserialization("groupid");
    groupid+="g";
    Value info;
    redisReply *reply = (redisReply *)redisCommand(Library, "LRANGE %s 0 -1", groupid.c_str());
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
    Massage m1(MAN_ADDGROUP, info, "0", "0");
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
        std::string value = (*it).asString();//值为处理结果
        redisReply *reply = (redisReply *)redisCommand(Library, "LREM %s 0 %s", groupid.c_str(), key.c_str()); // 将已经处理过的好友请求删除
        Value j;
        string result;
        if (value == "accapt")
        {
            User k(key, Library);
            Group g(groupid,Library);

            k.add_group(groupid);  // 将被加人加入申请人的列表
            g.add_member(key); // 将申请人加入被加人的列表
            result="g_accapt";
        }else{
            result="g_reject";
        }
        try
        {
            int cfd2 = user_cfd.at(key);
            j["groupid"] = key;
            Massage m3("g_accapt", j, "0", "0");
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout<< m3.Serialization()<<endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }
}
void Server::man_view(int cfd)
{
    string s;
    while (1)
    {
        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            break;
        }
    }
    Massage m(s);
    string groupid = m.Deserialization("groupid");
    Group g(groupid,Library);
    Massage m1(MAN_VIEW,g.member_List,"0","0");
    string s1=m1.Serialization();
    Err::sendMsg(cfd,s1.c_str(),s1.length());

}
void Server::man_addmanager(int cfd)
{
    string s;
    while (1)
    {
        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            break;
        }
    }
    Massage m(s);
    string groupid = m.Deserialization("groupid");
    string add_id = m.Deserialization("add_id");
    Group g(groupid,Library);
    string r;
    if(!g.member_List.isMember(add_id)){
        r="NULL";
    }else if(g.member_List[add_id].asInt()==1){
        r="bemanage";
    }else {
        g.Modify_permissions(add_id,1);
        r="Succeed";
        try
        {
            Value j;
            int cfd2 = user_cfd.at(add_id);
            j["groupid"] = groupid;
            Massage m3("addmanager", j, "0", "0");
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout<< m3.Serialization()<<endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }
    Err::sendMsg(cfd,r.c_str(),r.length());
}
void Server::man_delmanager(int cfd)
{
    string s;
    while (1)
    {
        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            break;
        }
    }
    Massage m(s);
    string groupid = m.Deserialization("groupid");
    string del_id = m.Deserialization("del_id");
    Group g(groupid,Library);
    string r;
    if(g.member_List[del_id].asInt()==0){
        r="NULL";
    }else {
        g.Modify_permissions(del_id,0);
        r="Succeed";
        try
        {
            Value j;
            int cfd2 = user_cfd.at(del_id);
            j["groupid"] = groupid;
            Massage m3("delmanager", j, "0", "0");
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout<< m3.Serialization()<<endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }
    Err::sendMsg(cfd,r.c_str(),r.length());
}
void Server::man_addmember(int cfd)
{

}
void Server::man_delmember(int cfd)
{
    string s;
    while (1)
    {
        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            break;
        }
    }
    Massage m(s);
    string groupid = m.Deserialization("groupid");
    string del_id = m.Deserialization("del_id");
    Group g(groupid,Library);
    string r;
    if(!g.member_List.isMember(del_id)){
        r="NULL";
    }else {
        g.delete_member(del_id);
        r="Succeed";
        try
        {
            Value j;
            int cfd2 = user_cfd.at(del_id);
            j["groupid"] = groupid;
            Massage m3("delmember", j, "0", "0");
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout<< m3.Serialization()<<endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }
    Err::sendMsg(cfd,r.c_str(),r.length());
}
void Server::manage_menu(int cfd)
{
    cout << cfd << "已进入群界面" << endl;
    string s;
    while (1)
    {
        s = Err::recvMsg(cfd);
        if (s.length() > 0)
        {
            if (s == MAN_ADDGROUP)
            {
                Server::man_addgroup(cfd);
            }
            else if (s == MAN_VIEW)
            {
                Server::man_view(cfd);
            }
            else if (s == MAN_ADDMANAGER)
            {
                Server::man_addmanager(cfd);
            }
            else if (s == MAN_QUITMANAGER)
            {
                Server::man_delmanager(cfd);
            }
            else if (s == MAN_QUITMEMBER)
            {
                Server::man_delmember(cfd);
            }
            else if (s == IGN_GROUP)
            {
                Server::ignoregroup(cfd);
            }
            else if (s == REC_GROUP)
            {
                Server::grouprecover(cfd);
            }
            else if (s == TRA_GROUP)
            {
                Server::transfer_group(cfd);
            }
            else if (s == MAN_ADDMEMBER)
            {
                Server::man_addmember(cfd);
            }
            else if (s == MAN_DELGROUP)
            {
                bool del = man_delgroup(cfd);
                if (del)
                {
                    break;
                }
            }
            else if (s == EXIT)
            {

                break;
            }
        }
    }
}