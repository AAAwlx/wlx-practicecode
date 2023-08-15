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
    std::variant<Json::Value, std::string> result = m.takeMassage("option");
    std::string o = std::get<std::string>(result);
    if(o==EXIT){
        cout<<"退出"<<endl;
        return;
    }
    string groupid = m.Deserialization("groupid");
    string g= groupid+ "gr";
    Value info;
    redisReply *reply = (redisReply *)redisCommand(Library, "LRANGE %s 0 -1", g.c_str());
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
    cout << s1 << endl;
    Err::sendMsg(cfd, s1.c_str(), s1.length()); // 将待处理的请求发送到客户端
    if(info.empty()){
        cout<<"好友申请为空"<<endl;
        return;
    }
    
    string r;
    while (1)
    {
        r = Err::recvMsg(cfd);
        if (r.length() > 0)
        {
            break;
        }
    }
    Massage m2(r);
    cout<<r<<endl;
    std::variant<Json::Value, std::string> result2 = m.takeMassage("option");
    std::string o1 = std::get<std::string>(result2);
    if(o1==EXIT){
        cout<<"退出"<<endl;
        return;
    }
    std::variant<Json::Value, std::string> result1 = m2.takeMassage("content");
    Value rlist = std::get<Json::Value>(result1);
    Json::Value::Members members = rlist.getMemberNames();
    for (const auto &key : members)
    {
        Value j;
        string mid=rlist[key].asString();
        User k(mid, Library);
        Group g(groupid, Library);
        cout<<mid<<endl;
        k.add_group(groupid); 
        g.add_member(mid);  
        try
        {
            int cfd2 = user_cfd.at(key);
            j["groupid"] = groupid;
            Massage m3("g_accapt", j, "0", "0");
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout << m3.Serialization() << endl;
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
    std::variant<Json::Value, std::string> result = m.takeMassage("option");
    std::string o = std::get<std::string>(result);
    if(o==EXIT){
        cout<<"退出"<<endl;
        return;
    }
    string groupid = m.Deserialization("groupid");
    Group g(groupid, Library);
    Massage m1(MAN_VIEW, g.member_List, "0", "0");
    string s1 = m1.Serialization();
    Err::sendMsg(cfd, s1.c_str(), s1.length());
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
    Group g(groupid, Library);
    string r;
    if (!g.member_List.isMember(add_id))
    {
        r = "NULL";
    }
    else if (g.member_List[add_id].asInt() == 1)
    {
        r = "bemanage";
    }
    else
    {
        g.Modify_permissions(add_id, 1);
        r = "Succeed";
        try
        {
            Value j;
            int cfd2 = user_cfd.at(add_id);
            j["groupid"] = groupid;
            Massage m3("addmanager", j, "0", "0");
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout << m3.Serialization() << endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }
    Err::sendMsg(cfd, r.c_str(), r.length());
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
    Group g(groupid, Library);
    string r;
    if (g.member_List[del_id].asInt() == 0)
    {
        r = "NULL";
    }
    else
    {
        g.Modify_permissions(del_id, 0);
        r = "Succeed";
        try
        {
            Value j;
            int cfd2 = user_cfd.at(del_id);
            j["groupid"] = groupid;
            Massage m3("delmanager", j, "0", "0");
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout << m3.Serialization() << endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }
    Err::sendMsg(cfd, r.c_str(), r.length());
}
void Server::man_addmember(int cfd)
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
    std::variant<Json::Value, std::string> result = m.takeMassage("option");
    std::string o = std::get<std::string>(result);
    if(o==EXIT){
        cout<<"退出"<<endl;
        return;
    }
    string groupid = m.Deserialization("groupid");
    string add_id = m.Deserialization("add_id");
    Group g(groupid, Library);
    string r;
    User u(add_id, Library);
    if (u.Inquire("ID") == "-1234567")
    {
        r = "NULL";
    }
    else
    {
        if (g.member_List.isMember(add_id))
        {
            r = "bemember";
        }
        else
        {
            r = "Succeed";
            u.add_group(groupid);
            g.add_member(add_id);
            try
            {
                Value j;
                int cfd2 = user_cfd.at(add_id);
                j["groupid"] = groupid;
                Massage m3("addmember", j, "0", "0");
                Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
                std::cout << m3.Serialization() << endl;
            }
            catch (const std::out_of_range &e)
            {
                std::cout << "Key not found." << std::endl;
            }
        }
    }
    Err::sendMsg(cfd, r.c_str(), r.length());
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
    std::variant<Json::Value, std::string> result = m.takeMassage("option");
    std::string o = std::get<std::string>(result);
    if(o==EXIT){
        cout<<"退出"<<endl;
        return;
    }
    string groupid = m.Deserialization("groupid");
    string del_id = m.Deserialization("del_id");
    Group g(groupid, Library);
    string r;
    if (!g.member_List.isMember(del_id))
    {
        r = "NULL";
    }else if(g.member_List[del_id].asInt()==2){
        r="Lord";
    }
    else
    {
        g.delete_member(del_id);
        r = "Succeed";
        try
        {
            Value j;
            int cfd2 = user_cfd.at(del_id); // 通知被踢出的成员
            j["groupid"] = groupid;
            Massage m3("delmember", j, "0", "0");
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout << m3.Serialization() << endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }
    Err::sendMsg(cfd, r.c_str(), r.length());
}
void Server::ignoregroup(int cfd)
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
    std::variant<Json::Value, std::string> result = m.takeMassage("option");
    std::string o = std::get<std::string>(result);
    if(o==EXIT){
        cout<<"退出"<<endl;
        return;
    }
    string groupid = m.Deserialization("groupid");
    string ID = m.Deserialization("ID");
    User u(ID,Library);
    string r;
    if(u.group_List[ID].asInt()==0){
        r="blocked";
    }else{
        r="Succeed";
        u.shield_group(groupid);
    }
    Err::sendMsg(cfd, r.c_str(), r.length());
}
void Server::grouprecover(int cfd)
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
    std::variant<Json::Value, std::string> result = m.takeMassage("option");
    std::string o = std::get<std::string>(result);
    if(o==EXIT){
        cout<<"退出"<<endl;
        return;
    }
    string groupid = m.Deserialization("REC_group");
    string ID = m.Deserialization("ID");
    User u(ID,Library);
    string r;
 if(u.group_List[ID].asInt()==1){
        r="not_blocked";
    }else{
        r="Succeed";
        u.recover_group(groupid);
    }
    Err::sendMsg(cfd, r.c_str(), r.length());
}
void Server::transfer_group(int cfd)
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
    string ID = m.Deserialization("ID");
    string tra_id = m.Deserialization("tra_id");
    Group g(groupid, Library);
    string r;
    if(g.member_List.isMember(tra_id)){
        r=="Succeed";
        g.Modify_permissions(tra_id,2);
        g.Modify_permissions(ID,0);
        try
        {
            Value j;
            int cfd2 = user_cfd.at(tra_id);
            j["groupid"] = groupid;
            Massage m3("transfer_group", j, "0", "0");
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout << m3.Serialization() << endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }else{
        r="NULL";
    }
    Err::sendMsg(cfd,r.c_str(),r.length());
}
bool Server::man_delgroup(int cfd)
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
    string ID = m.Deserialization("ID");
    Group g(groupid, Library);
    string r;
    Json::Value::Members members = g.member_List.getMemberNames();
    for (const auto &key : g.member_List.getMemberNames())
    {
        User u(key,Library);
        u.delete_group(groupid);
        try
        {
            Value j;
            int cfd2 = user_cfd.at(key);
            j["groupid"] = groupid;
            Massage m3("man_delgroup", j, "0", "0");
            Err::sendMsg(cfd2, m3.Serialization().c_str(), m3.Serialization().length()); // 如果在线，通知申请人申请已经通过
            std::cout << m3.Serialization() << endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Key not found." << std::endl;
        }
    }
    redisReply *reply = (redisReply *)redisCommand(Library, "HDEL Group %s",groupid.c_str());
    freeReplyObject(reply);
    return true;
}
void Server::manage_menu0(int cfd)
{
    cout << cfd << "已进入群管理界面" << endl;
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