#include "public.hpp"
#include"ser.hpp"
// id是标识用户的唯一信息
User::User(string name, string pass, string question, string answer, redisContext *userm)
:Name(name),Pass(pass),Question(question),Answer(answer),Library(userm)
{
} // 新用户
User::User(string id, redisContext *userm) 
:ID(id),Library(userm)
{
    Name = this->Inquire("Name");
    Pass = this->Inquire("Name");
    Question = this->Inquire("Question");
    Answer = this->Inquire("Answer");
    string f = this->Inquire("FriendList");
    string g = this->Inquire("GroupList");
    Reader r;
    r.parse(f, friend_List);
    r.parse(g, group_List);
} // 老用户
User::~User()
{
}
string User::distribute_id()
{
    redisReply *reply = (redisReply *)redisCommand(Library, "GET %s", "user_count");
    User_count= atoi(reply->str);
    freeReplyObject(reply);
    User_count++;
    redisReply *reply1 = (redisReply *)redisCommand(Library, "SET %s %d", "user_count",User_count);
    freeReplyObject(reply1);
    string s = to_string(User_count);
    ID = "11" + s;
    return ID;
}
bool User::save_user() // 将用户信息存入数据库
{
    Value inof; // 打包各项用户信息
    inof["ID"] = ID;
    inof["Name"] = Name;
    inof["Pass"] = Pass;
    inof["Question"] = Question;
    inof["Answer"] = Answer;
    FastWriter w;
    string f = w.write(friend_List);
    string g = w.write(group_List);
    inof["FriendList"] = f; // 统一变成字符串方便管
    inof["GroupList"] = g;
    string s = w.write(inof); // 将各项用户信息打包成字符串存入redis
    const char *hash_user = "User";
    const char *field = ID.c_str(); // 键值为唯一标识用户id
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
string User::Inquire(string s)
{
    const char *hash_user = "User";
    const char *field = ID.c_str();
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
void User::add_friend(string friend_id)
{
    friend_List[friend_id] = 1;
    this->save_user();
}
void User::delete_friend(string friend_id)
{
    if (friend_List.isObject()) {
        friend_List.removeMember(friend_id);
        this->save_user();
    }
}
void User::shield_friend(string friend_id)
{
    friend_List[friend_id] = 0;
    this->save_user();
}
void User::recover_friend(string friend_id)
{
    friend_List[friend_id] = 1;
    this->save_user();
}
void User::add_group(string group_id)
{
    group_List[group_id] = 1;
    this->save_user();
}
void User::delete_group(string group_id)
{
    if (group_List.isObject()) {
        group_List.removeMember(group_id);
        this->save_user();
    }
}
void User::shield_group(string group_id)
{
    group_List[group_id] = 0;
    this->save_user();
}
void User::recover_group(string group_id)
{
    group_List[group_id] = 1;
    this->save_user();
}