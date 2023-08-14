#include "ser.hpp"
#include "public.hpp"
void Server::historicalnews(int cfd, string ID)
{
    string s = ID + "r"; // 好友申请列表
    Value j1, j2,j;
    redisReply *reply = (redisReply *)redisCommand(Library, "LRANGE %s 0 -1", s.c_str()); // 获取存有好友申请的列表
    if (reply != nullptr)
    {
        for (size_t i = 0; i < reply->elements; i++)
        {
            redisReply *element = reply->element[i];
            if (element->type == REDIS_REPLY_STRING)
            {
                std::string id(element->str, element->len);
                std::string str = std::to_string(i);
                j1[str] = id;
            }
        }
    }
    string s2 = ID + "c";                                                                   // 私聊消息
    redisReply *reply2 = (redisReply *)redisCommand(Library, "LRANGE %s 0 -1", s2.c_str()); // 获取存有聊天记录的列表
    if (reply2 != nullptr)
    {
        for (size_t i = 0; i < reply2->elements; i++)
        {
            redisReply *element = reply2->element[i];
            if (element->type == REDIS_REPLY_STRING)
            {
                std::string massage(element->str, element->len);
                std::string str = std::to_string(i);
                j2[str] = massage;
            }
        }
    }
    j["request"]=j1;
    j["chat"]=j2;
    Massage m1(Historical_news, j, "0", "0");
    string s4 = m1.Serialization();
    Err::sendMsg(cfd, s4.c_str(), s4.length());
    cout<<"历史消息已发送"<<s4<<endl;
    freeReplyObject(reply);
    freeReplyObject(reply2);
    return;
}
void Server::main_menu(int cfd, string ID)
{
    while (1)
    {
        string r;
        r=Err::recvMsg(cfd);
        if (r.length() > 0)
        {
            cout<<r<<endl;
            Massage m(r);
            std::variant<Json::Value, std::string> result = m.takeMassage("option");
            std::string o = std::get<std::string>(result);
            cout<<o<<endl;
            if (o == PRIVATE)
            {
                Server::privateChat(cfd);
            }else if(o==GROUP){
                Server::group_menu(cfd);
            }
            else if (o == FRIENDS_MENU)
            {
                Server::friends_menu(cfd);
            } /*else if(s==FILE_MANAGE){

             }*/
            else if (o == EXIT)
            {
                size_t numDeleted = user_cfd.erase(ID); // 删除标记在线的键值对
                if (numDeleted > 0)
                {
                    std::cout << "id为 " << ID << " 的用户已退出" << std::endl;
                }
                    Value j;
                    Massage m("Exit",j,"0","0");
                    string s=m.Serialization();
                    Err::sendMsg(cfd, s.c_str(), s.length());
                    break;
            }
        }
    }
    return;
}