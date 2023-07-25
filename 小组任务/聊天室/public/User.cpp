#include"public.hpp"
//id是标识用户的唯一信息
int User::User_count=0;
User::User(string name,string pass,string question,string answer,redisContext* userm)
{
    
}//新用户
User::User(string id,redisContext* userm)
{
    Name=this->Inquire("Name");
    Pass=this->Inquire("Name");
    Question=this->Inquire("Question");
    Answer=this->Inquire("Answer");
    string f=this->Inquire("FriendList");
    string g=this->Inquire("GroupList");
    Reader r;
    r.parse(f,friend_List);
    r.parse(g,group_List);
}//老用户
string User::distribute_id()
{
    User_count++;
    ID=to_string(User_count);
    return ID;
}
bool User::save_user()//将用户信息存入数据库
{
    Value inof;//打包各项用户信息
    inof["ID"]=ID;
    inof["Name"]=Name;
    inof["Pass"]=Pass;
    inof["Question"]=Question;
    inof["Answer"]=Answer;
    Value GList;//将群列表序列化
    FastWriter w;
    string f=w.write(friend_List);
    string g=w.write(group_List);
    inof["FriendList"]=f;//统一变成字符串方便管理
    inof["GroupList"]=g;
    string s=w.write(inof);//将各项用户信息打包成字符串存入redis
    const char *key = ID.c_str();//键值为唯一标识用户id
    const char *value = s.c_str();
    user_mtx.lock();
    redisReply *reply = (redisReply *)redisCommand(Userm, "SET %s %s", key, value);
    user_mtx.unlock();
    if (reply == NULL) {
        printf("Failed to execute Redis command: %s\n", Userm->errstr);
        redisFree(Userm);
        return 1;
    }
    freeReplyObject(reply);
}
string User::Inquire(string s)
{
    redisReply *reply = (redisReply *)redisCommand(Userm, "GET %s", ID);//通过id作为索引找到用户信息
    if(reply->type == REDIS_REPLY_NIL){
        return "0";
    }
    Reader r;
    Value info;
    r.parse(reply->str,info);
    return info[s].asString(); 
}
void User::add_friend(string friend_id)
{
    friend_List[friend_id]=1;
    this->save_user();
}
void User::delete_friend(string friend_id)
{
    friend_List.removeMember(friend_id);
    this->save_user();
}
void User::shield_friend(string friend_id)
{
    friend_List[friend_id]=0;
    this->save_user();
}
void User::Revise()
{

}