#include "public.hpp"
#include "clit.hpp"
void Clenit::Prientf(string s)//将实时消息在顶部显示并在下一次新消息到来时消除
{
    std::cout << "\033[44;37m"<<s<<"\033[0m" << std::endl;
    std::cout << "\033[F\033[K";
    return ;
}
void Clenit::thread_recv(string ID)
{
    while (1){
        char r[BUFFERSIZE];
        if(Err::Read(cfd,r,sizeof(r))>0){
            Massage m(r);
            std::variant<Json::Value, std::string> result=m.takeMassage("option");
            string o=std::get<std::string>(result);
            if (o=="f_accapt"){
                string friendid=m.Deserialization("friend");
                string s="id为"+friendid+"通过了你的好友申请，你们可以开始聊天了。";
                Clenit::Prientf(s);
            }else if(o=="add_friend"){
                string friendid=m.Deserialization("ID");
                string s="id为"+friendid+"申请与您成为好友关系";
                Clenit::Prientf(s);
            }
        }
    }
}