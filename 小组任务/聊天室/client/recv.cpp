#include "public.hpp"
#include "clit.hpp"
//实时接收好友申请提示，私聊与群聊消息，群中权限变更提醒
void thread_recv(const std::string& ID, int cfd, const std::string& chatobject )
{
    if(stopFlag==false){
        cout<<stopFlag<<endl;
    }
    while (stopFlag){
        string r;
        r=Err::recvMsg(cfd); 
        if(r.length()> 0){
            Massage m(r);
            cout<<r<<endl;
            std::variant<Json::Value, std::string> result = m.takeMassage("option");
            string o = std::get<std::string>(result);
            Clenit::PrientfR(o);
            if (o == "f_accapt"){//好友请求通过
                string friendid = m.Deserialization("friend");
                string s = "id为" + friendid + "通过了你的好友申请，你们可以开始聊天了。";
                Clenit::PrientfT(s);
            }else if(o == "add_friend"){//好友申请
                string friendid = m.Deserialization("ID");
                string s = "id为" + friendid + "申请与您成为好友关系";
                Clenit::PrientfT(s);
            }else if(o == "del_friend"){
                string friendid = m.Deserialization("friend");
                string s = "id为" + friendid + "解除了与你的好友关系";
                f_flag=false;
                Clenit::PrientfT(s);
            }
            else if(o == "Direct_send"){//私聊消息
                string massage = m.Deserialization("massage");
                std::variant<Json::Value, std::string> result = m.takeMassage("form");
                string id = std::get<std::string>(result);
                string s = "id为" + id + "发给你："+massage;
                Clenit::PrientfT(s);
            }else if(o == "Pchat_space"){
                std::variant<Json::Value, std::string> result = m.takeMassage("form");
                string f = std::get<std::string>(result);//取出发送者
                string s = m.Deserialization("massage");
                if(f == chatobject){//如果消息来自当前的聊天的对象
                    Clenit::PrientfR(f+":");
                    Clenit::PrientfR(s);
                }else{
                    string s2 = "id为" + f + "发给你："+ s;
                    Clenit::PrientfT(s2);
                }
            }else if(o == "add_group"){//申请加群
                string id = m.Deserialization("ID");
                string groupid=m.Deserialization("groupid");
                string s = "id为" + id + "申请加入群聊" + groupid;
                Clenit::PrientfT(s);
            }else if(o == "quit_group"){//申请退群
                string id = m.Deserialization("ID");
                string groupid=m.Deserialization("groupid");
                string s = "id为" + id + "退出群聊" + groupid;
                Clenit::PrientfT(s);
            }else if(o == "g_accapt" || o == "g_reject")
            {
                string groupid=m.Deserialization("groupid");
                string result;
                if(o == "g_accapt"){
                    result="同意了你的入群申请";
                }else if(o == "g_reject"){
                    result="拒绝了你的入群申请";
                }
                string s="id为："+groupid+"的群聊"+result;
                Clenit::PrientfT(s);
            }else if(o == "addmember" || o == "delmember")
            {
                string groupid=m.Deserialization("groupid");
                string result;
                if(o == "addmember"){
                    result="群管理将你拉入";
                }else if(o == "delmember"){
                    g_flag=false;
                    result="群管理将你踢出";
                }
                string s=result+"id为："+groupid+"的群聊";
                Clenit::PrientfT(s);
            }else if(o == "addmanager" || o == "delmanager")
            {
                string groupid=m.Deserialization("groupid");
                string result;
                if(o == "addmanager"){
                    result="的群主将你设置为管理员";
                }else if(o == "delmanager"){
                    m_flag=false;
                    result="的群主取消了你的管理员";
                }
                string s="id为："+groupid+result;
                Clenit::PrientfT(s);
            }else if(o == "transfer_group"){
                string groupid=m.Deserialization("groupid");
                string s="id为："+groupid+"的群主将群主权限转让给了你";
                Clenit::PrientfT(s);
            }
            else if(o == "JOIN_GROUP"){//群聊
                std::variant<Json::Value, std::string> result = m.takeMassage("to");
                string t = std::get<std::string>(result);//取出发送者
                std::variant<Json::Value, std::string> result1 = m.takeMassage("form");
                string f = std::get<std::string>(result1);//取出发送者
                if(t==chatobject){
                    if(f==ID){
                        Clenit::PrientfL(f);
                        Clenit::PrientfL(m.Deserialization("massage"));
                    }else{
                        Clenit::PrientfR(f);
                        Clenit::PrientfR(m.Deserialization("massage"));
                    }  
                }
            }else if(o == "man_delgroup"){
                string groupid=m.Deserialization("groupid");
                string s = "id为" + groupid + "群聊已被群主解散";
                g_flag=false;
                Clenit::PrientfT(s);
            }
            else{//非实时消息
                qmutex.lock();
                masqueue.push(r);
                bool aaa=masqueue.empty();
                qmutex.unlock();
                queueCondVar.notify_one();
            }
        }
    }
}