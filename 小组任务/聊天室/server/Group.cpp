#include "public.hpp"
#include "ser.hpp"
Group::Group(string name, string Lordname, redisContext *userm)
    : Name(name), Library(userm)
{
    this->member_List[Lordname] = 2;//创建群聊的人为
    cout << this->member_List[Lordname].asInt()<< endl;
}
Group::Group(string ID, redisContext *userm)
    : GID(ID), Library(userm)
{
    Name = this->Inquire("Name");
    string f = this->Inquire("member_List");
    Reader r;
    r.parse(f, member_List);
}
Group::~Group()
{
}
string Group::distribute_id()
{
    redisReply *reply = (redisReply *)redisCommand(Library, "GET %s", "group_count");
    Group_count= atoi(reply->str);
    freeReplyObject(reply);
    Group_count++;
    redisReply *reply1 = (redisReply *)redisCommand(Library, "SET %s %d", "group_count",Group_count);
    freeReplyObject(reply1);
    string s = to_string(Group_count);
    GID = "22" + s;
    cout<< GID << "已被创建" <<endl;
    return GID;
}
bool Group::save_group()
{
    Value inof;
    inof["ID"] = GID;
    inof["Name"] = Name;
    FastWriter w;
    string ml = w.write(member_List);
    inof["member_List"]=ml;

    string s = w.write(inof); // 将各项用户信息打包成字符串存入redis
    const char *hash_user = "Group";
    const char *field = GID.c_str(); // 键值为唯一标识用户id
    const char *value = s.c_str();
    user_mtx.lock();
    redisReply *reply = (redisReply *)redisCommand(Library, "HSET %s %s %s", hash_user, field, value);
    user_mtx.unlock();
    if (reply == NULL)
    {
        printf("Failed to execute Redis command: %s\n", Library->errstr);
        redisFree(Library);
        return false;
    }
    freeReplyObject(reply);
    return true;
}
string Group::Inquire(string s)
{
    const char *hash_user = "Group";
    const char *field = GID.c_str();
    redisReply *reply = (redisReply *)redisCommand(Library, "HGET %s %s", hash_user, field); // 通过id作为索引找到用户信息
    if (reply->type == REDIS_REPLY_NIL)
    {
        return "-1234567";
    }
    Reader r;
    Value info;
    r.parse(reply->str, info);
    return info[s].asString();
}
void Group::add_member(string member_id)
{
    member_List[member_id] = 0;
    cout<<member_id<<endl;
    this->save_group();
}
void Group::delete_member(string member_id)
{
    if (member_List.isObject())
    {
        member_List.removeMember(member_id);
        this->save_group();
    }
}
void Group::Modify_permissions(string member_id, int flag)
{
    this->member_List[member_id] = flag; // 0为普通成员，1为管理员，2为群主
    this->save_group();
}