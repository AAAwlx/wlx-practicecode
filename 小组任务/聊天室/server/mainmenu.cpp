#include"ser.hpp"
#include"public.hpp"
void Server::historicalnews(int cfd,string ID)
{
    string s=ID+"r";//好友申请列表
    Value j;
    redisReply *reply = (redisReply *)redisCommand(Library, "LRANGE %s 0 -1", s.c_str());//获取存有好友申请的列表
    if (reply != nullptr) {
        std::string requstlist(reply->str, reply->len);
        j["request"]=requstlist;
        freeReplyObject(reply);  
    } else {
        j["request"]="NULL";
    }
    string s2=ID+"c";//私聊消息
    redisReply *reply2 = (redisReply *)redisCommand(Library, "LRANGE %s 0 -1", s2.c_str());//获取存有聊天记录的列表
    if (reply2!= nullptr) {
        std::string chatlist(reply2->str, reply2->len);
        j["chat"]=chatlist;
        freeReplyObject(reply2);  
    } else {
        j["chat"]="NULL";
    }
    Massage m1(Historical_news,j,"0","0");
    string s4=m1.Serialization();
    Err::Write(cfd,s4.c_str(),s.length());
    return;
}
void Server::main_menu(int cfd,string ID)
{
    char r[BUFFERSIZE];
    while (1)
    {
        if(Err::Read(cfd,r,sizeof(r))>0){
            cout<<r<<endl;
            std::string s(r);
            if (s==PRIVATE){
                
            }else if(s==GROUP){

            }else if(s==FRIENDS_MENU){
                friends_menu(cfd);
            }else if(s==FILE_MANAGE){

            }else if (s==EXIT){
                size_t numDeleted = user_cfd.erase(ID);//删除标记在线的键值对
                if (numDeleted > 0) {
                    std::cout << "id为 " << ID << " 的用户已退出" << std::endl;
                }
                break;
            }
        }    
    }
    return ;
}