#include "public.hpp"
#include "clit.hpp"
//实时接收好友申请提示，私聊与群聊消息，群中权限变更提醒
void thread_recv(const std::string& ID, int cfd, const std::string& chatobject )
{
    while (!stopFlag){
        char r[BUFFERSIZE];
        if(Err::Read(cfd,r,sizeof(r)) > 0){
            Massage m(r);
            std::variant<Json::Value, std::string> result = m.takeMassage("option");
            string o = std::get<std::string>(result);
            Clenit::PrientfT(o);
            if (o == "f_accapt"){
                string friendid = m.Deserialization("friend");
                string s = "id为" + friendid + "通过了你的好友申请，你们可以开始聊天了。";
                Clenit::PrientfT(s);
            }else if(o == "add_friend"){
                string friendid = m.Deserialization("ID");
                string s = "id为" + friendid + "申请与您成为好友关系";
                Clenit::PrientfT(s);
            }else if(o == "Direct_send"){
                cout<<"----------------------------------------"<<endl;
                string massage = m.Deserialization("massage");
                std::variant<Json::Value, std::string> result = m.takeMassage("From");
                string id = std::get<std::string>(result);
                string s = "id为" + id + "发给你："+massage;

                Clenit::PrientfT(s);
            }else if(o == Pchat_space){
                std::variant<Json::Value, std::string> result = m.takeMassage("From");
                string f = std::get<std::string>(result);//取出发送者
                string s = m.Deserialization("massage");
                if(f==chatobject){//如果消息来自当前的聊天的对象
                    Clenit::PrientfR(f);
                    Clenit::PrientfR(s);
                }else{
                    string s2 = "id为" + f + "发给你："+ s;
                    Clenit::PrientfT(s);
                }
            }
        }
    }
}