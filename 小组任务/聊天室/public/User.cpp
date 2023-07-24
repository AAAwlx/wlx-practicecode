#include"public.hpp"
//id是标识用户的唯一信息
int User::User_count=0;
User::User(string name,string pass,string question,string answer)
{
    vector<string> Friend(100);
    vector<string> Group(20);
}
string User::distribute_id()
{
    User_count++;
    ID=to_string(User_count);
    return ID;
}
bool User::save_user(redisContext* Userm)//将用户信息存入数据库
{
    Value inof;//打包各项用户信息
    inof["ID"]=ID;
    inof["Name"]=Name;
    inof["Pass"]=Pass;
    inof["Question"]=Question;
    inof["Answer"]=Answer;
    Value FList;//将好友列表序列化
    for (const auto& item : Friend) {
        FList.append(item);
    }
    Value GList;//将群列表序列化
    for (const auto& item : Group) {
        GList.append(item);
    }
    FastWriter w;
    inof["FriendList"]=FList;
    inof["GroupList"]=GList;
    string s=w.write(inof);//将各项用户信息打包成字符串存入redis
    const char *key = ID.c_str();//键值为唯一标识用户id
    const char *value = s.c_str();
    redisReply *reply = (redisReply *)redisCommand(Userm, "SET %s %s", key, value);
    if (reply == NULL) {
        printf("Failed to execute Redis command: %s\n", Userm->errstr);
        redisFree(Userm);
        return 1;
    }
    freeReplyObject(reply);
}
